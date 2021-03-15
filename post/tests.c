/*
 * (C) Copyright 2002
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 * Be sure to mark tests to be run before relocation as such with the
 * CONFIG_SYS_POST_PREREL flag so that logging is done correctly if the
 * logbuffer support is enabled.
 */

#include <common.h>

#include <post.h>

extern int inventory_post_test (int flags);
extern int accelerometer_self_test (int flags);
extern int mmc_crc32_post_test (int flags);
extern int gpio_post_test (int flags);

extern int ocm_post_test (int flags);
extern int cache_post_test (int flags);
extern int watchdog_post_test (int flags);
extern int i2c_post_test (int flags);
extern int rtc_post_test (int flags);
extern int memory_post_test (int flags);
extern int cpu_post_test (int flags);
extern int fpu_post_test (int flags);
extern int uart_post_test (int flags);
extern int ether_post_test (int flags);
extern int spi_post_test (int flags);
extern int usb_post_test (int flags);
extern int spr_post_test (int flags);
extern int sysmon_post_test (int flags);
extern int dsp_post_test (int flags);
extern int codec_post_test (int flags);
extern int ecc_post_test (int flags);

extern int dspic_init_post_test (int flags);
extern int dspic_post_test (int flags);
extern int gdc_post_test (int flags);
extern int fpga_post_test (int flags);
extern int lwmon5_watchdog_post_test(int flags);
extern int sysmon1_post_test(int flags);

extern int sysmon_init_f (void);

extern void sysmon_reloc (void);

#if CONFIG_POST & CONFIG_SYS_POST_FAIL
int fail_post_test (int flags)
{
	post_log ("Testing failure mechanism.\n");
	return -1;
}
#endif

struct post_test post_list[] =
{
#if CONFIG_POST & CONFIG_SYS_POST_FAIL
    {
	"Non-Critical failure test",
	"fail",
	"This test checks the failure mechanism.",
	POST_RAM | POST_MANUAL,
	&fail_post_test,
	NULL,
	NULL,
	CONFIG_SYS_POST_FAIL
    },
#endif
#if CONFIG_POST & CONFIG_SYS_POST_GPIO
    {
	"GPIO test",
	"gpio",
	"This test verifies the GPIO operation.",
	POST_RAM | POST_MANUAL,
	&gpio_post_test,
	NULL,
	NULL,
	CONFIG_SYS_POST_GPIO
    },
#endif
#if CONFIG_POST & CONFIG_SYS_POST_LED
    CONFIG_SYS_POST_LED,
#endif
#if CONFIG_POST & CONFIG_SYS_POST_PMIC
    CONFIG_SYS_POST_PMIC,
#endif
#if CONFIG_POST & CONFIG_SYS_POST_MMC_CRC32
    {
	"MMC CRC32 checksum test",
	"mmc_crc32",
	"This tests the CRC32 checksum of the MMC.",
	POST_RAM | POST_MANUAL,
	&mmc_crc32_post_test,
	NULL,
	NULL,
	CONFIG_SYS_POST_MMC_CRC32
    },
#endif
#if CONFIG_POST & CONFIG_SYS_POST_INVENTORY
    {
	"Device inventory test",
	"inventory",
	"This test checks that devices exist.",
	POST_RAM | POST_MANUAL,
	&inventory_post_test,
	NULL,
	NULL,
	CONFIG_SYS_POST_INVENTORY
    },
#endif
#if CONFIG_POST & CONFIG_SYS_POST_INVENTORY
    {
        "Device run accelerometer test",
        "acc",
        "This test is do accelerometer self test",
	POST_RAM | POST_MANUAL,
	&accelerometer_self_test,
	NULL,
	NULL,
	CONFIG_SYS_POST_INVENTORY,
    },
#endif
#if CONFIG_POST & CONFIG_SYS_POST_OCM
    {
	"OCM test",
	"ocm",
	"This test checks on chip memory (OCM).",
	POST_ROM | POST_ALWAYS | POST_PREREL | POST_CRITICAL | POST_STOP,
	&ocm_post_test,
	NULL,
	NULL,
	CONFIG_SYS_POST_OCM
    },
#endif
#if CONFIG_POST & CONFIG_SYS_POST_CACHE
    {
	"Cache test",
	"cache",
	"This test verifies the CPU cache operation.",
	POST_RAM | POST_ALWAYS,
	&cache_post_test,
	NULL,
	NULL,
	CONFIG_SYS_POST_CACHE
    },
#endif
#if CONFIG_POST & CONFIG_SYS_POST_WATCHDOG
#if defined(CONFIG_POST_WATCHDOG)
	CONFIG_POST_WATCHDOG,
#else
    {
	"Watchdog timer test",
	"watchdog",
	"This test checks the watchdog timer.",
	POST_RAM | POST_POWERON | POST_SLOWTEST | POST_MANUAL | POST_REBOOT,
	&watchdog_post_test,
	NULL,
	NULL,
	CONFIG_SYS_POST_WATCHDOG
    },
#endif
#endif
#if CONFIG_POST & CONFIG_SYS_POST_I2C
    {
	"I2C test",
	"i2c",
	"This test verifies the I2C operation.",
	POST_RAM | POST_ALWAYS,
	&i2c_post_test,
	NULL,
	NULL,
	CONFIG_SYS_POST_I2C
    },
#endif
#if CONFIG_POST & CONFIG_SYS_POST_RTC
    {
	"RTC test",
	"rtc",
	"This test verifies the RTC operation.",
	POST_RAM | POST_SLOWTEST | POST_MANUAL,
	&rtc_post_test,
	NULL,
	NULL,
	CONFIG_SYS_POST_RTC
    },
#endif
#if CONFIG_POST & CONFIG_SYS_POST_MEMORY
    {
	"Memory test",
	"memory",
	"This test checks RAM.",
	POST_ROM | POST_ALWAYS | POST_SLOWTEST | POST_PREREL | POST_CRITICAL,
	&memory_post_test,
	NULL,
	NULL,
	CONFIG_SYS_POST_MEMORY
    },
#endif
#if CONFIG_POST & CONFIG_SYS_POST_CPU
    {
	"CPU test",
	"cpu",
	"This test verifies the arithmetic logic unit of"
	" CPU.",
	POST_RAM | POST_ALWAYS,
	&cpu_post_test,
	NULL,
	NULL,
	CONFIG_SYS_POST_CPU
    },
#endif
#if CONFIG_POST & CONFIG_SYS_POST_FPU
    {
	"FPU test",
	"fpu",
	"This test verifies the arithmetic logic unit of"
	" FPU.",
	POST_RAM | POST_ALWAYS,
	&fpu_post_test,
	NULL,
	NULL,
	CONFIG_SYS_POST_FPU
    },
#endif
#if CONFIG_POST & CONFIG_SYS_POST_UART
    {
	"UART test",
	"uart",
	"This test verifies the UART operation.",
	POST_RAM | POST_SLOWTEST | POST_MANUAL,
	&uart_post_test,
	NULL,
	NULL,
	CONFIG_SYS_POST_UART
    },
#endif
#if CONFIG_POST & CONFIG_SYS_POST_ETHER
    {
	"ETHERNET test",
	"ethernet",
	"This test verifies the ETHERNET operation.",
	POST_RAM | POST_ALWAYS | POST_MANUAL,
	&ether_post_test,
	NULL,
	NULL,
	CONFIG_SYS_POST_ETHER
    },
#endif
#if CONFIG_POST & CONFIG_SYS_POST_SPI
    {
	"SPI test",
	"spi",
	"This test verifies the SPI operation.",
	POST_RAM | POST_ALWAYS | POST_MANUAL,
	&spi_post_test,
	NULL,
	NULL,
	CONFIG_SYS_POST_SPI
    },
#endif
#if CONFIG_POST & CONFIG_SYS_POST_USB
    {
	"USB test",
	"usb",
	"This test verifies the USB operation.",
	POST_RAM | POST_ALWAYS | POST_MANUAL,
	&usb_post_test,
	NULL,
	NULL,
	CONFIG_SYS_POST_USB
    },
#endif
#if CONFIG_POST & CONFIG_SYS_POST_SPR
    {
	"SPR test",
	"spr",
	"This test checks SPR contents.",
	POST_RAM | POST_ALWAYS,
	&spr_post_test,
	NULL,
	NULL,
	CONFIG_SYS_POST_SPR
    },
#endif
#if CONFIG_POST & CONFIG_SYS_POST_SYSMON
    {
	"SYSMON test",
	"sysmon",
	"This test monitors system hardware.",
	POST_RAM | POST_ALWAYS,
	&sysmon_post_test,
	&sysmon_init_f,
	&sysmon_reloc,
	CONFIG_SYS_POST_SYSMON
    },
#endif
#if CONFIG_POST & CONFIG_SYS_POST_DSP
    {
	"DSP test",
	"dsp",
	"This test checks any connected DSP(s).",
	POST_RAM | POST_ALWAYS | POST_MANUAL,
	&dsp_post_test,
	NULL,
	NULL,
	CONFIG_SYS_POST_DSP
    },
#endif
#if CONFIG_POST & CONFIG_SYS_POST_CODEC
    {
	"CODEC test",
	"codec",
	"This test checks any connected codec(s).",
	POST_RAM | POST_MANUAL,
	&codec_post_test,
	NULL,
	NULL,
	CONFIG_SYS_POST_CODEC
    },
#endif
#if CONFIG_POST & CONFIG_SYS_POST_ECC
    {
	"ECC test",
	"ecc",
	"This test checks the ECC facility of memory.",
	POST_ROM | POST_ALWAYS | POST_PREREL,
	&ecc_post_test,
	NULL,
	NULL,
	CONFIG_SYS_POST_ECC
    },
#endif
#if CONFIG_POST & CONFIG_SYS_POST_BSPEC1
	CONFIG_POST_BSPEC1,
#endif
#if CONFIG_POST & CONFIG_SYS_POST_BSPEC2
	CONFIG_POST_BSPEC2,
#endif
#if CONFIG_POST & CONFIG_SYS_POST_BSPEC3
	CONFIG_POST_BSPEC3,
#endif
#if CONFIG_POST & CONFIG_SYS_POST_BSPEC4
	CONFIG_POST_BSPEC4,
#endif
#if CONFIG_POST & CONFIG_SYS_POST_BSPEC5
	CONFIG_POST_BSPEC5,
#endif
};

unsigned int post_list_size = sizeof (post_list) / sizeof (struct post_test);
