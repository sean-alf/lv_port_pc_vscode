#include "auto-door-ui-app/src/alf_hal.h"

#include "lvgl.h"

static lv_indev_t* kb;

void alf_hal_init(int32_t w, int32_t h, void* arg) {
    (void)arg;

    lv_group_set_default(lv_group_create());

    lv_display_t* disp = lv_sdl_window_create(w, h);

    lv_indev_t* mouse = lv_sdl_mouse_create();
    lv_indev_set_display(mouse, disp);
    lv_indev_set_group(mouse, lv_group_get_default());
    lv_display_set_default(disp);

    kb = lv_sdl_keyboard_create();
    lv_indev_set_display(kb, disp);
    lv_indev_set_group(kb, lv_group_get_default());
}

void alf_hal_set_group(lv_group_t* new_group) {
    lv_indev_set_group(kb, new_group);
}

void alf_hal_reset_group(void) {
    lv_indev_set_group(kb, lv_group_get_default());
}
