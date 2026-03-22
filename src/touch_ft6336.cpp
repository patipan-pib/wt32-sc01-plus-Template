#include "touch_ft6336.h"
#include "display_driver.h"

void touch_init() {
    // ไม่ต้องทำอะไรเพิ่ม เพราะ touch ถูก init ใน LovyanGFX แล้ว
}

bool touch_read_raw(uint16_t &x, uint16_t &y) {
    return display_get_touch(x, y);
}

void lvgl_touch_read_cb(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
    (void)indev_driver;

    uint16_t x, y;
    if (touch_read_raw(x, y)) {
        data->state = LV_INDEV_STATE_PR;
        data->point.x = x;
        data->point.y = y;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
}