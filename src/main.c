/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   2000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec led3 = GPIO_DT_SPEC_GET(LED3_NODE, gpios);

struct gpio_dt_spec v[4];

int main(void)
{
	const struct device *dev;
	dev = DEVICE_DT_GET(DT_NODELABEL(uart0));

	if (!device_is_ready(dev))
		return 0;

	int ret;

	v[0] = led;
	v[1] = led1;
	v[2] = led2;
	v[3] = led3;

	for (unsigned int i = 0; i < 4; ++i)
	{
		if (!gpio_is_ready_dt(&v[i]))
			return 0;

		ret = gpio_pin_configure_dt(&v[i], GPIO_OUTPUT_ACTIVE);

		if (ret < 0) 
			return 0;
	}

	while (1) 
	{
		for (unsigned int i = 0; i < 4; ++i)
		{
			ret = gpio_pin_toggle_dt(&v[i]);

			if (ret < 0)
				return 0;
		}
	
		k_msleep(SLEEP_TIME_MS);
	}

	return 0;
}
