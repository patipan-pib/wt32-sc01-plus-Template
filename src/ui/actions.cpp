#include <Arduino.h>
#include "actions.h"
#include "ui.h"


// ==========================
// Slider
// ==========================
void action_action_slider(lv_event_t * e) {
    int value = lv_slider_get_value(objects.sl_val);

    Serial.print("Slider = ");
    Serial.println(value);
}

// ==========================
// Checkbox
// ==========================
void action_action_checkbox(lv_event_t * e) {
    bool checked = lv_obj_has_state(objects.cb_ok, LV_STATE_CHECKED);

    Serial.print("Checkbox = ");
    Serial.println(checked ? "ON" : "OFF");
}

// ==========================
// ปุ่ม start (ตัวอย่างใช้ค่ารวม)
// ==========================
void action_action_start(lv_event_t * e) {
    int value = lv_slider_get_value(objects.sl_val);
    bool checked = lv_obj_has_state(objects.cb_ok, LV_STATE_CHECKED);

    Serial.println("---- START ----");
    Serial.print("Slider: ");
    Serial.println(value);

    Serial.print("Checkbox: ");
    Serial.println(checked ? "ON" : "OFF");
}


void action_action_stop(lv_event_t * e) {
    Serial.println("---- STOP ----");
}

