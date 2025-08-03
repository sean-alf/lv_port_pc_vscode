#include "auto-door-ui-app/src/app_ui.h"

#include "lvgl.h"

#ifdef _MSC_VER
  #include <Windows.h>
#else
  #include <unistd.h>
//   #include <pthread.h>
#endif

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

int main(int argc, char** argv) {
    lv_init();

    app_ui_init(true, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);

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
