#include "app_ui_prefs.h"

#include <algorithm>
#include <vector>

#include "app_ui_err.h"
#include "auto_sleep_setting.h"
#include "date_picker.h"
#include "time_picker.h"

static void process_listeners(app_ui_prefs_key_t key, void* new_value);

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
static timezone_id_t tz_id;
static wifi_icon_manager_state_t wifi_state = WIFI_ICON_MANAGER_STATE_DISCONNECTED;
static bool has_wifi_error = false;
static uint8_t _id;

struct app_ui_prefs_listener {
        app_ui_prefs_listener_id_t id;
        /**
         * The keys that should trigger this listener.
         */
        app_ui_prefs_key_t ored_keys;
        /**
         * Callback to be called when this listener is triggered.
         */
        void (*cb)(app_ui_prefs_key_t key, void* new_value);
};

static std::vector<struct app_ui_prefs_listener> listeners;

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

timezone_id_t app_ui_prefs_get_timezone(timezone_id_t def) {
    (void)def;
    return tz_id;
}

wifi_icon_manager_state_t app_ui_prefs_get_wifi_state(wifi_icon_manager_state_t def) {
    (void)def;
    return wifi_state;
}

bool app_ui_prefs_get_has_wifi_error(bool def) {
    (void)def;
    return has_wifi_error;
}

/**** Setters ****/

app_ui_err_t app_ui_prefs_set_system_datetime(alf_date_t date, alf_time_t time, bool post_event) {
    (void)post_event;

    if (date != current_date) {
        current_date = date;
        process_listeners(APP_UI_PREFS_KEY_SYSTEM_DATE, (void*)&date);
    }

    if (time != current_time) {
        current_time = time;
        process_listeners(APP_UI_PREFS_KEY_SYSTEM_TIME, (void*)&time);
    }

    return APP_UI_OK;
}

app_ui_err_t app_ui_prefs_set_open_time(alf_time_t time) {
    if (time == open_time) return APP_UI_OK;
    open_time = time;
    process_listeners(APP_UI_PREFS_KEY_OPEN_TIME, (void*)&time);
    return APP_UI_OK;
}

app_ui_err_t app_ui_prefs_set_close_time(alf_time_t time) {
    if (time == close_time) return APP_UI_OK;
    close_time = time;
    process_listeners(APP_UI_PREFS_KEY_CLOSE_TIME, (void*)&time);
    return APP_UI_OK;
}

app_ui_prefs_err_t app_ui_prefs_set_enable_wifi(bool val) {
    if (val == enable_wifi) return APP_UI_OK;
    enable_wifi = val;
    process_listeners(APP_UI_PREFS_KEY_ENABLE_WIFI, (void*)&val);
    return APP_UI_OK;
}

app_ui_err_t app_ui_prefs_set_wifi_sync_enabled(bool val) {
    if (val == wifi_sync_enabled) return APP_UI_OK;
    wifi_sync_enabled = val;
    process_listeners(APP_UI_PREFS_KEY_WIFI_SYNC_ENABLED, (void*)&val);
    return APP_UI_OK;
}

app_ui_err_t app_ui_prefs_set_enable_app(bool val) {
    if (val == enable_app) return APP_UI_OK;
    enable_app = val;
    process_listeners(APP_UI_PREFS_KEY_ENABLE_APP, (void*)&val);
    return APP_UI_OK;
}

app_ui_err_t app_ui_prefs_set_darkmode_enabled(bool val) {
    if (val == darkmode_enabled) return APP_UI_OK;
    darkmode_enabled = val;
    process_listeners(APP_UI_PREFS_KEY_DARKMODE_ENABLED, (void*)&val);
    return APP_UI_OK;
}

app_ui_err_t app_ui_prefs_set_auto_sleep_setting(auto_sleep_setting_t val) {
    if (val == setting) return APP_UI_OK;
    setting = val;
    process_listeners(APP_UI_PREFS_KEY_AUTO_SLEEP_SETTING, (void*)&val);
    return APP_UI_OK;
}

app_ui_prefs_err_t app_ui_prefs_set_dev_mode_enabled(bool val) {
    if (val == dev_mode) return APP_UI_OK;
    dev_mode = val;
    process_listeners(APP_UI_PREFS_KEY_DEV_MODE_ENABLED, (void*)&val);
    return APP_UI_OK;
}

app_ui_prefs_err_t app_ui_prefs_set_timezone(timezone_id_t id) {
    if (tz_id == id) return APP_UI_OK;
    tz_id = id;
    process_listeners(APP_UI_PREFS_KEY_TIMEZONE, (void*)&tz_id);
    return APP_UI_OK;
}

app_ui_prefs_err_t app_ui_prefs_set_wifi_state(wifi_icon_manager_state_t val) {
    if (wifi_state == val) return APP_UI_OK;
    wifi_state = val;
    process_listeners(APP_UI_PREFS_KEY_WIFI_STATE, &val);
    return APP_UI_OK;
}

app_ui_prefs_err_t app_ui_prefs_set_has_wifi_error(bool val) {
    if (has_wifi_error == val) return APP_UI_OK;
    has_wifi_error = val;
    process_listeners(APP_UI_PREFS_KEY_HAS_WIFI_ERROR, &val);
    return APP_UI_OK;
}

/**** Listeners ****/

app_ui_prefs_listener_id_t app_ui_prefs_add_on_change_listener(app_ui_prefs_key_t ored_keys,
                                                               void (*l)(app_ui_prefs_key_t key, void* new_value)) {
    app_ui_prefs_listener listener = {};
    listener.id = _id++;
    listener.cb = l;
    listener.ored_keys = ored_keys;
    listeners.push_back(listener);
    return listener.id;
}

void app_ui_prefs_remove_on_change_listener(uint8_t id) {
    listeners.erase(std::remove_if(listeners.begin(), listeners.end(),
                                   [id](const app_ui_prefs_listener_t& l) {
                                       return l.id == id;
                                   }),
                    listeners.end());
}

static void process_listeners(app_ui_prefs_key_t key, void* new_value) {
    for (uint8_t i = 0; i < listeners.size(); i++) {
        if (listeners.data()[i].ored_keys & key) {
            listeners.data()[i].cb(key, new_value);
        }
    }
}
