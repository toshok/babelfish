/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "tusb.h"

#include "reset_interface.h"
#include "hardware/watchdog.h"
#include "device/usbd_pvt.h"

#ifndef PICO_STDIO_USB_RESET_MAGIC_BAUD_RATE
#define PICO_STDIO_USB_RESET_MAGIC_BAUD_RATE 1200
#endif

#ifndef PICO_STDIO_USB_RESET_BOOTSEL_INTERFACE_DISABLE_MASK 
#define PICO_STDIO_USB_RESET_BOOTSEL_INTERFACE_DISABLE_MASK 0u
#endif

// Support for default BOOTSEL reset by changing baud rate
void tud_cdc_line_coding_cb(__unused uint8_t itf, cdc_line_coding_t const* p_line_coding) {
    if (p_line_coding->bit_rate == PICO_STDIO_USB_RESET_MAGIC_BAUD_RATE) {
#ifdef PICO_STDIO_USB_RESET_BOOTSEL_ACTIVITY_LED
        const uint gpio_mask = 1u << PICO_STDIO_USB_RESET_BOOTSEL_ACTIVITY_LED;
#else
        const uint gpio_mask = 0u;
#endif
        reset_usb_boot(gpio_mask, PICO_STDIO_USB_RESET_BOOTSEL_INTERFACE_DISABLE_MASK);
    }
}