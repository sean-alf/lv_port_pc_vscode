#include "alf_hal.h"

#include "app_ui.h"
#include "global_handler.h"
#include "lvgl.h"

static lv_indev_t* kb;

typedef struct {
        char buf[KEYBOARD_BUFFER_SIZE];
        bool dummy_read;
} lv_sdl_keyboard_t;

static void keyboard_read(lv_indev_t* indev, lv_indev_data_t* data) {
    lv_sdl_keyboard_t* dev = (lv_sdl_keyboard_t*)lv_indev_get_driver_data(indev);

    const size_t len = lv_strlen(dev->buf);

    /*Send a release manually*/
    if (dev->dummy_read) {
        dev->dummy_read = false;
        data->state = LV_INDEV_STATE_RELEASED;

        on_global_key_released(data->key);
    }
    /*Send the pressed character*/
    else if (len > 0) {
        dev->dummy_read = true;
        data->state = LV_INDEV_STATE_PRESSED;
        data->key = dev->buf[0];
        lv_memmove(dev->buf, dev->buf + 1, len);

        on_global_key_press(data->key);
    }
}

void alf_hal_init(int32_t w, int32_t h, void* arg) {
    (void)arg;

    lv_group_set_default(lv_group_create());

    lv_display_t* disp = lv_sdl_window_create(w, h);
    lv_display_set_default(disp);

    lv_indev_t* mouse = lv_sdl_mouse_create();
    lv_indev_set_display(mouse, disp);
    lv_indev_set_group(mouse, lv_group_get_default());

    kb = lv_sdl_keyboard_create();
    lv_indev_set_display(kb, disp);
    lv_indev_set_group(kb, lv_group_get_default());
    lv_indev_set_read_cb(kb, keyboard_read);
}

void alf_hal_set_group(lv_group_t* new_group) {
    lv_indev_set_group(kb, new_group);
}

void alf_hal_reset_group(void) {
    lv_indev_set_group(kb, lv_group_get_default());
}
