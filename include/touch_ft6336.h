#pragma once

#include <Arduino.h>
#include <lvgl.h>

void touch_init();
bool touch_read_raw(uint16_t &x, uint16_t &y);
void lvgl_touch_read_cb(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);