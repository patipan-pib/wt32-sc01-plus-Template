#include <Arduino.h>
#include <lvgl.h>
#include "display_driver.h"
#include "touch_ft6336.h"

extern "C" {
#include "ui/ui.h"
}

void setup() {
    Serial.begin(115200);
    delay(3000);

    Serial.println("1");
    display_init();
    Serial.println("2");

    touch_init();
    Serial.println("3");

    lv_init();
    Serial.println("4");

    lvgl_display_register();
    Serial.println("5");

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = lvgl_touch_read_cb;
    lv_indev_drv_register(&indev_drv);
    Serial.println("6");

    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lvgl_tick_task,
        .arg = nullptr,
        .dispatch_method = ESP_TIMER_TASK,
        .name = "lvgl_tick"
    };

    esp_timer_handle_t periodic_timer;
    esp_timer_create(&periodic_timer_args, &periodic_timer);
    esp_timer_start_periodic(periodic_timer, 1000);
    Serial.println("7");

    ui_init();
    Serial.println("8");
}

void loop() {
    lv_timer_handler();
    delay(5);
}