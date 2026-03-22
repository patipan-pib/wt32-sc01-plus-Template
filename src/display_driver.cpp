#include "display_driver.h"

#define LGFX_USE_V1
#include <LovyanGFX.hpp>

#include "board_pins.h"

class LGFX : public lgfx::LGFX_Device {
    lgfx::Panel_ST7796 _panel_instance;
    lgfx::Bus_Parallel8 _bus_instance;
    lgfx::Light_PWM _light_instance;
    lgfx::Touch_FT5x06 _touch_instance;

public:
    LGFX() {
        {
            auto cfg = _bus_instance.config();
            cfg.freq_write = 40000000;
            cfg.pin_wr = LCD_WR;
            cfg.pin_rd = LCD_RD;
            cfg.pin_rs = LCD_RS;
            cfg.pin_d0 = LCD_D0;
            cfg.pin_d1 = LCD_D1;
            cfg.pin_d2 = LCD_D2;
            cfg.pin_d3 = LCD_D3;
            cfg.pin_d4 = LCD_D4;
            cfg.pin_d5 = LCD_D5;
            cfg.pin_d6 = LCD_D6;
            cfg.pin_d7 = LCD_D7;
            _bus_instance.config(cfg);
            _panel_instance.setBus(&_bus_instance);
        }

        {
            auto cfg = _panel_instance.config();
            cfg.pin_cs = LCD_CS;
            cfg.pin_rst = LCD_RST;
            cfg.pin_busy = LCD_BUSY;

            cfg.memory_width  = 320;
            cfg.memory_height = 480;
            cfg.panel_width   = 320;
            cfg.panel_height  = 480;

            cfg.offset_x = 0;
            cfg.offset_y = 0;
            cfg.offset_rotation = 0;
            cfg.dummy_read_pixel = 8;
            cfg.dummy_read_bits = 1;
            cfg.readable = true;
            cfg.invert = true;
            cfg.rgb_order = false;
            cfg.dlen_16bit = false;
            cfg.bus_shared = true;

            _panel_instance.config(cfg);
        }

        {
            auto cfg = _light_instance.config();
            cfg.pin_bl = LCD_BL;
            cfg.invert = false;
            cfg.freq = 44100;
            cfg.pwm_channel = LCD_BL_CHANNEL;
            _light_instance.config(cfg);
            _panel_instance.setLight(&_light_instance);
        }

        {
            auto cfg = _touch_instance.config();
            cfg.i2c_port = 1;
            cfg.i2c_addr = FT6336_ADDR;
            cfg.pin_sda = TP_SDA;
            cfg.pin_scl = TP_SCL;
            cfg.freq = 400000;
            cfg.x_min = 0;
            cfg.x_max = 320;
            cfg.y_min = 0;
            cfg.y_max = 480;
            _touch_instance.config(cfg);
            _panel_instance.setTouch(&_touch_instance);
        }

        setPanel(&_panel_instance);
    }
};

static LGFX tft;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[LCD_WIDTH * 100];

void display_init() {
    tft.begin();
    tft.setRotation(1);
    tft.setBrightness(255);
    tft.fillScreen(TFT_BLACK);
}

void display_set_brightness(uint8_t value) {
    tft.setBrightness(value);
}

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.writePixels((lgfx::rgb565_t *)&color_p->full, w * h);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}

void lvgl_display_register() {
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, LCD_WIDTH * 100);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = LCD_WIDTH;
    disp_drv.ver_res = LCD_HEIGHT;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);
}

void lvgl_tick_task(void *arg) {
    (void)arg;
    lv_tick_inc(1);
}

// ให้ touch module เรียกใช้ได้
bool display_get_touch(uint16_t &x, uint16_t &y) {
    return tft.getTouch(&x, &y);
}