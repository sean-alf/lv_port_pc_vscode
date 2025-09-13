#include "app_ui_prefs.h"

#include "app_ui_err.h"
#include "auto_sleep_setting.h"
#include "date_picker.h"
#include "time_picker.h"

static alf_time_t current_time = DEFAULT_TIME;
static alf_date_t current_date = DEFAULT_DATE;
static alf_time_t open_time = DEFAULT_TIME;
static alf_time_t close_time = DEFAULT_TIME;
static bool enable_wifi = false;
static bool wifi_sync_enabled = false;
static bool enable_app = false;
static bool darkmode_enabled = true;
static auto_sleep_setting_t setting = AUTO_SLEEP_SETTING_DEFAULT;
static bool dev_mode = false;

/**** Getters ****/

alf_time_t app_ui_prefs_get_system_time(alf_time_t def) {
    (void)def;
    return current_time;
}

alf_date_t app_ui_prefs_get_system_date(alf_time_t def) {
    (void)def;
    return current_date;
}

alf_time_t app_ui_prefs_get_open_time(alf_time_t def) {
    (void)def;
    return open_time;
}

alf_time_t app_ui_prefs_get_close_time(alf_time_t def) {
    (void)def;
    return close_time;
}

bool app_ui_prefs_get_enable_wifi(bool def) {
    (void)def;
    return enable_wifi;
}

bool app_ui_prefs_get_wifi_sync_enabled(bool def) {
    (void)def;
    return wifi_sync_enabled;
}

bool app_ui_prefs_get_enable_app(bool def) {
    (void)def;
    return enable_app;
}

bool app_ui_prefs_get_darkmode_enabled(bool def) {
    (void)def;
    return darkmode_enabled;
}

auto_sleep_setting_t app_ui_prefs_get_auto_sleep_setting(auto_sleep_setting_t def) {
    (void)def;
    return setting;
}

bool app_ui_prefs_get_dev_mode_enabled(bool def) {
    (void)def;
    return dev_mode;
}

/**** Setters ****/

app_ui_err_t app_ui_prefs_set_system_datetime(alf_date_t date, alf_time_t time, bool post_event) {
    (void)post_event;
    current_date = date;
    current_time = time;
    return APP_UI_OK;
}

app_ui_err_t app_ui_prefs_set_open_time(alf_time_t time) {
    open_time = time;
    return APP_UI_OK;
}

app_ui_err_t app_ui_prefs_set_close_time(alf_time_t time) {
    close_time = time;
    return APP_UI_OK;
}

app_ui_prefs_err_t app_ui_prefs_set_enable_wifi(bool val) {
    enable_wifi = val;
    return APP_UI_OK;
}

app_ui_err_t app_ui_prefs_set_wifi_sync_enabled(bool val) {
    wifi_sync_enabled = val;
    return APP_UI_OK;
}

app_ui_err_t app_ui_prefs_set_enable_app(bool val) {
    enable_app = val;
    return APP_UI_OK;
}

app_ui_err_t app_ui_prefs_set_darkmode_enabled(bool val) {
    darkmode_enabled = val;
    return APP_UI_OK;
}

app_ui_err_t app_ui_prefs_set_auto_sleep_setting(auto_sleep_setting_t val) {
    setting = val;
    return APP_UI_OK;
}

app_ui_prefs_err_t app_ui_prefs_set_dev_mode_enabled(bool val) {
    dev_mode = val;
    return APP_UI_OK;
}
