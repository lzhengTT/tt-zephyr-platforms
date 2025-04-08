/*
 * Copyright (c) 2024 Tenstorrent AI ULC
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "bh_arc_priv.h"

#include <tenstorrent/bh_chip.h>

#include <zephyr/drivers/gpio.h>

struct tt_smbus_stm32_config {
	const struct pinctrl_dev_config *pcfg;
	const struct device *i2c_dev;
};

void bh_chip_set_straps(struct bh_chip *chip)
{
	k_mutex_lock(&chip->data.reset_lock, K_FOREVER);

	volatile int ret;

	bharc_enable_i2cbus(&chip->config.arc);
	if (chip->config.strapping.gpio6.port != NULL) {
		ret = gpio_pin_configure_dt(&chip->config.strapping.gpio6, GPIO_OUTPUT_ACTIVE);
	}
	if (chip->config.strapping.gpio38.port != NULL) {
		ret = gpio_pin_configure_dt(&chip->config.strapping.gpio38, GPIO_OUTPUT_ACTIVE);
	}
	if (chip->config.strapping.gpio39.port != NULL) {
		ret = gpio_pin_configure_dt(&chip->config.strapping.gpio38, GPIO_OUTPUT_ACTIVE);
	}
	if (chip->config.strapping.gpio40.port != NULL) {
		ret = gpio_pin_configure_dt(&chip->config.strapping.gpio40, GPIO_OUTPUT_ACTIVE);
	}
	bharc_disable_i2cbus(&chip->config.arc);

	k_mutex_unlock(&chip->data.reset_lock);
}

void bh_chip_unset_straps(struct bh_chip *chip)
{
	k_mutex_lock(&chip->data.reset_lock, K_FOREVER);

	bharc_enable_i2cbus(&chip->config.arc);
	if (chip->config.strapping.gpio6.port != NULL) {
		gpio_pin_configure_dt(&chip->config.strapping.gpio6, GPIO_INPUT);
	}
	if (chip->config.strapping.gpio38.port != NULL) {
		gpio_pin_configure_dt(&chip->config.strapping.gpio38, GPIO_INPUT);
	}
	if (chip->config.strapping.gpio39.port != NULL) {
		gpio_pin_configure_dt(&chip->config.strapping.gpio38, GPIO_INPUT);
	}
	if (chip->config.strapping.gpio40.port != NULL) {
		gpio_pin_configure_dt(&chip->config.strapping.gpio40, GPIO_INPUT);
	}
	bharc_disable_i2cbus(&chip->config.arc);

	k_mutex_unlock(&chip->data.reset_lock);
}
