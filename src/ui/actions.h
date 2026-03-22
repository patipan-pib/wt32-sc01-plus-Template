#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_action_stop(lv_event_t * e);
extern void action_action_start(lv_event_t * e);
extern void action_action_slider(lv_event_t * e);
extern void action_action_checkbox(lv_event_t * e);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/