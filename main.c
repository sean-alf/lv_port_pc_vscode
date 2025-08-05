#include "auto-door-ui-app/src/app_ui.h"

#include "auto-door-ui-app/src/events.h"
#include "lvgl.h"

#ifdef _MSC_VER
#include <Windows.h>
#else
#include <unistd.h>
//   #include <pthread.h>
#endif

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

uint32_t INFO_EVENT = 0;

int main(int argc, char** argv) {
    lv_init();

    INFO_EVENT = lv_event_register_id();

    app_ui_init(false, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);

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
