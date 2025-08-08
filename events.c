#include "auto-door-ui-app/src/events.h"

#include "auto-door-ui-app/src/app_ui_err.h"

static uint8_t fake;

const char* events_send_reset_pos_request() {
    fake++;
    fake = fake % 3;

    switch (fake) {
    case 1: return "Some fake err 1";
    case 2: return "Some fake err 2";
    default: return "APP_UI_OK";
    }
}
