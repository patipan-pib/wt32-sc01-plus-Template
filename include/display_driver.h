#pragma once

#include <Arduino.h>
#include <lvgl.h>

void display_init();
void display_set_brightness(uint8_t value);
void lvgl_display_register();
void lvgl_tick_task(void *arg);
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);

bool display_get_touch(uint16_t &x, uint16_t &y);