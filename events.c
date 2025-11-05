#include "events.h"

#include "app_ui_err.h"
#include "popup/popup.h"

void events_send_reset_pos_request(void) {
    popup_show_message("Reset Position!!", 0);
}

void events_dev_mode_enable(bool enable) {
    popup_show_message(enable ? "Dev mode enabled" : "Dev mode disabled", 0);
}

void events_send_reboot_request(void) {
    popup_show_message("reboot!!", 0);
}

void events_send_show_wifi_error_request(void) {
    popup_show_message("Here's a fake WiFi error!!!", 0);
}

void events_send_enable_pairing(bool enable) {
    if (enable) {
        popup_show_message("enable pairing", 0);
    } else {
        popup_show_message("disable pairing", 0);
    }
}

void events_send_clear_paired(void) {
    popup_show_message("clear paired devices", 0);
}
