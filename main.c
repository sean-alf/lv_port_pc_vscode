#include "app_ui.h"
#include "app_ui_prefs.h"
#include "events.h"
#include "global_handler.h"
#include "home_page.h"
#include "lvgl.h"
#include "screen_brightness_page.h"

#ifdef _MSC_VER
#include <Windows.h>
#else
#include <unistd.h>
//   #include <pthread.h>
#endif

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

static void on_brightness_change(uint8_t val) {
    LV_LOG_USER("brightness=%u", val);
}

static wifi_icon_manager_state_t wifi_state;
static bool focused = false;
static bool conn = false;
static bool error_shown = false;

static void on_conn_toggle_click(void) {
    conn = !conn;
    app_ui_show_connected(conn);
}

static void on_home_toggle_click(void) {
    focused = false == focused;
    app_ui_update_focus(focused);
}

static void on_info_btn_click(void) {
    lv_obj_t* o = lv_group_get_focused(lv_group_get_default());
    lv_obj_send_event(o, INFO_EVENT, NULL);
}

static void on_wifi_toggle_click(void) {
    wifi_state = (wifi_state + 1) % WIFI_ICON_MANAGER_STATE_MAX;
    app_ui_set_wifi_state(wifi_state);
    app_ui_prefs_set_has_wifi_error(WIFI_ICON_MANAGER_STATE_ERROR == wifi_state);
}

void on_global_key_press(uint32_t key) {
    LV_LOG_USER("key pressed=%u", key);
}

void on_global_key_released(uint32_t key) {
    LV_LOG_USER("key released=%u", key);
    switch (key) {
        case 'c': {
            on_conn_toggle_click();
            break;
        }
        case 'e': {
            if (error_shown) {
                error_shown = false;
                home_page_hide_message();
            } else {
                error_shown = true;
                home_page_show_message("Device Broked!");
            }
            break;
        }
        case 'h': {
            on_home_toggle_click();
            break;
        }
        case 'i': {
            on_info_btn_click();
            break;
        }
        case 'w': {
            on_wifi_toggle_click();
            break;
        }
    }
}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    lv_init();

    app_ui_init(focused, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);

    screen_brightness_page_config_t sbpc = {
        .initial_value = 50,
        .min_value = 10,
        .max_value = 100,
        .step = 10,
        .on_value_change_cb = on_brightness_change,
    };
    screen_brightness_page_init(sbpc);

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
