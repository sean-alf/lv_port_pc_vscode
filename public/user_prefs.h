#ifndef USER_PREFS
#define USER_PREFS

#include "auto-door-ui-app/src/app_ui_err.h"
#include "alf_datetime.h"

#include <stdbool.h>

alf_time_t user_prefs_get_system_time(alf_time_t);

alf_date_t user_prefs_get_system_date(alf_time_t);

alf_time_t user_prefs_get_open_time(alf_time_t);

alf_time_t user_prefs_get_close_time(alf_time_t);

bool user_prefs_get_wifi_sync_enabled(bool);

app_ui_err_t user_prefs_set_system_time(alf_time_t time);

app_ui_err_t user_prefs_set_system_date(alf_date_t date);

app_ui_err_t user_prefs_set_open_time(alf_time_t time);

app_ui_err_t user_prefs_set_close_time(alf_time_t time);

void user_prefs_set_wifi_sync_enabled(bool val);

#endif// USER_PREFS
