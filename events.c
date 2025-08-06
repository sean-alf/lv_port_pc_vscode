#include "auto-door-ui-app/src/events.h"

static bool fake_val = false;

bool events_send_reset_pos_request() {
    fake_val = !fake_val;
    return fake_val;
}
