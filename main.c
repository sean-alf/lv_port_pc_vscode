#include "auto-door-ui-app/src/app_ui.h"

#include "auto-door-ui-app/src/events.h"
#include "auto-door-ui-app/src/pages/screen_brightness_page.h"
#include "lvgl.h"

#ifdef _MSC_VER
#include <Windows.h>
#else
#include <unistd.h>
//   #include <pthread.h>
#endif

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define SCREEN_BRIGHTNESS_MIN 1
#define SCREEN_BRIGHTNESS_MAX 15
#define SCREEN_BRIGHTNESS_STEP 1
#define SCREEN_BRIGHTNESS_INIT 7

static void on_brightness_change(uint8_t val) {
    LV_LOG_USER("brightness: %u", val);
}

int main(int argc, char** argv) {
    lv_init();

    app_ui_init(false, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);

    screen_brightness_page_config_t cfg = {};
    cfg.initial_value = SCREEN_BRIGHTNESS_INIT;
    cfg.min_value = SCREEN_BRIGHTNESS_MIN;
    cfg.max_value = SCREEN_BRIGHTNESS_MAX;
    cfg.step = SCREEN_BRIGHTNESS_STEP;
    cfg.on_value_change_cb = on_brightness_change;

    screen_brightness_page_init(cfg);

    while (1) {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        lv_timer_handler();
#ifdef _MSC_VER
        Sleep(5);
#else
        usleep(5 * 1000);
#endif
    }

    return 0;
}
