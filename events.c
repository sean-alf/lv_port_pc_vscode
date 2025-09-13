#include "auto-door-ui-app/src/events.h"

#include "auto-door-ui-app/src/app_ui_err.h"
#include "auto-door-ui-app/src/popup/popup.h"

void events_send_reset_pos_request(void) {
    popup_show_message("Reset Position!!", 0);
}

void events_dev_mode_enable(bool enable) {
    popup_show_message(enable ? "Dev mode enabled" : "Dev mode disabled", 0);
}

void events_send_reboot_request(void) {
    popup_show_message("reboot!!", 0);
}
