/*
 * Copyright (c) 2024 Tenstorrent AI ULC
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef INCLUDE_TENSTORRENT_LIB_WAKE_MAIN_LOOP_H_
#define INCLUDE_TENSTORRENT_LIB_WAKE_MAIN_LOOP_H_

#include <stdint.h>
#include <zephyr/kernel.h>

int wake_main_loop(void);
int sleep_main_loop(k_timeout_t timeout);

#endif
