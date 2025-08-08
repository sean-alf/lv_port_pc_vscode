#include "public/user_prefs.h"

#include "auto-door-ui-app/src/app_ui_err.h"
#include "auto-door-ui-app/src/picker/time_picker/time_picker.h"
#include "auto-door-ui-app/src/picker/date_picker/date_picker.h"

static alf_time_t current_time = DEFAULT_TIME;
static alf_date_t current_date = DEFAULT_DATE;
static alf_time_t open_time = DEFAULT_TIME;
static alf_time_t close_time = DEFAULT_TIME;
static bool wifi_sync_enabled = false;

alf_time_t user_prefs_get_system_time(alf_time_t def) {
    return current_time;
}

alf_date_t user_prefs_get_system_date(alf_time_t def) {
    return current_date;
}

alf_time_t user_prefs_get_open_time(alf_time_t def) {
    return open_time;
}

alf_time_t user_prefs_get_close_time(alf_time_t def) {
    return close_time;
}

bool user_prefs_get_wifi_sync_enabled(bool def) {
    return wifi_sync_enabled;
}

app_ui_err_t user_prefs_set_system_time(alf_time_t time) {
    current_time = time;
    return APP_UI_OK;
}

app_ui_err_t user_prefs_set_system_date(alf_date_t date) {
    current_date = date;
    return APP_UI_OK;
}

app_ui_err_t user_prefs_set_open_time(alf_time_t time) {
    open_time = time;
    return APP_UI_OK;
}

app_ui_err_t user_prefs_set_close_time(alf_time_t time) {
    close_time = time;
    return APP_UI_OK;
}

void user_prefs_set_wifi_sync_enabled(bool val) {
    wifi_sync_enabled = val;
}
