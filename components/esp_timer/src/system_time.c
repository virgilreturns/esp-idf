/*
 * SPDX-FileCopyrightText: 2017-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

// Provides strong definition for system time functions relied upon
// by core components.
#include "sdkconfig.h"

#if CONFIG_ESP_TIME_FUNCS_USE_ESP_TIMER
#include "esp_timer.h"
#include "esp_timer_impl.h"
#include "esp_system.h"
#include "esp_newlib.h"
#include "esp_log.h"

#include "esp_private/startup_internal.h"
#include "esp_rtc_time.h"

__attribute__((unused)) static const char* TAG = "system_time";

// Correction for underlying timer to keep definition
// of system time consistent.
static int64_t s_correction_us = 0;

void esp_timer_impl_init_system_time(void)
{
    s_correction_us = esp_rtc_get_time_us() - g_startup_time - esp_timer_impl_get_time();
#if defined(CONFIG_ESP_TIME_FUNCS_USE_ESP_TIMER) && defined(CONFIG_ESP_TIME_FUNCS_USE_RTC_TIMER)
    esp_err_t err = esp_register_shutdown_handler(esp_sync_timekeeping_timers);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "Register shutdown handler failed, err = 0x%x", err);
    }
#endif
}

int64_t ESP_TIMER_IRAM_ATTR esp_system_get_time(void)
{
    return esp_timer_get_time() + s_correction_us;
}

uint32_t ESP_TIMER_IRAM_ATTR esp_system_get_time_resolution(void)
{
    return 1000;
}
#endif
