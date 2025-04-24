/*
 * Copyright (c) 2024 Tenstorrent AI ULC
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

K_MSGQ_DEFINE(main_queue, sizeof(uint8_t), 1, _Alignof(uint8_t));
LOG_MODULE_REGISTER(main_queue, CONFIG_TT_WAKE_MAIN_LOOP_LOG_LEVEL);

int wake_main_loop(void)
{
        uint8_t msg = 0;

        int ret = k_msgq_put(&main_queue, &msg, K_NO_WAIT);

        if (ret != 0) {
                LOG_WRN("Failed to send message with error code: %d", ret);
        }

        return ret;
}

int sleep_main_loop(k_timeout_t timeout)
{
        uint8_t msg;

        int ret = k_msgq_get(&main_queue, &msg, timeout);

        if (ret == 0) {
		LOG_WRN("Message received: %u, waking up main loop.", msg);
	}

        return ret;
}
