/*
 * Copyright 2008-2009 Freescale Semiconductor, Inc.
 *
 *  linux/include/linux/mmc/card.h
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *  Card driver specific definitions.
 */
#ifndef LINUX_MMC_CARD_H
#define LINUX_MMC_CARD_H

#include "core.h"

struct mmc_cid {
	unsigned int		manfid;
	char			    prod_name[8];
	unsigned int		serial;
	union {
	unsigned short		mmc_id;
	char				sd_id[2];
	} oemid;
	unsigned short		year;
	unsigned char		hwrev;
	unsigned char		fwrev;
	unsigned char		month;
};

#define MANFID_SAMSUNG		0x15

struct mmc_csd {
	unsigned char		mmca_vsn;
	unsigned short		cmdclass;
	unsigned short		tacc_clks;
	unsigned int		tacc_ns;
	unsigned int		r2w_factor;
	unsigned int		max_dtr;
	unsigned int		read_blkbits;
	unsigned int		write_blkbits;
	unsigned int		capacity;
	unsigned int		read_partial:1,
				read_misalign:1,
				write_partial:1,
				write_misalign:1;
};

struct mmc_ext_csd {
	unsigned int		hs_max_dtr;
	unsigned int		sectors;
};

struct sd_scr {
	unsigned char		sda_vsn;
	unsigned char		bus_widths;
#define SD_SCR_BUS_WIDTH_1	(1<<0)
#define SD_SCR_BUS_WIDTH_4	(1<<2)
};

struct sd_switch_caps {
	unsigned int		hs_max_dtr;
};

struct sdio_cccr {
	unsigned int		sdio_vsn;
	unsigned int		sd_vsn;
	unsigned int		multi_block:1,
				low_speed:1,
				wide_bus:1,
				high_power:1,
				high_speed:1;
};

struct sdio_cis {
	unsigned short		vendor;
	unsigned short		device;
	unsigned short		blksize;
	unsigned int		max_dtr;
};

struct mmc_host;
struct sdio_func;
struct sdio_func_tuple;

#define SDIO_MAX_FUNCS		7

/*
 * MMC device
 */
struct mmc_card {
	unsigned int rca; /* relative card address of device */
	unsigned int type;	/* card type */
#define MMC_TYPE_MMC 0  /* MMC card */
#define MMC_TYPE_SD  1  /* SD card */
#define MMC_TYPE_SDIO 2 /* SDIO card */
	unsigned int state; /* (our) card state */
#define MMC_STATE_PRESENT   (1<<0) /* present in sysfs */
#define MMC_STATE_READONLY  (1<<1) /* card is read-only */
#define MMC_STATE_HIGHSPEED (1<<2) /* card is in high speed mode */
#define MMC_STATE_BLOCKADDR (1<<3) /* card uses block-addressing */

	u32 raw_cid[4]; /* raw card CID */
	u32 raw_csd[4]; /* raw card CSD */
	u32 raw_scr[2]; /* raw card SCR */
	struct mmc_cid cid; /* card identification */
	struct mmc_csd csd; /* card specific */
	struct mmc_ext_csd ext_csd; /* mmc v4 extended card specific */
	struct sd_scr  scr; /* extra SD information */
	struct sd_switch_caps sw_caps; /* switch (CMD6) caps */

	unsigned int sdio_funcs; /* number of SDIO functions */
	struct sdio_cccr cccr;   /* common card info */
	struct sdio_cis  cis;    /* common tuple info */
	/* SDIO functions (devices) */
	struct sdio_func *sdio_func[SDIO_MAX_FUNCS];
	unsigned num_info; /* number of info strings */
	const char **info; /* info strings */
	struct sdio_func_tuple *tuples; /* unknown common tuples */
};

#define mmc_card_mmc(c)  ((c)->type == MMC_TYPE_MMC)
#define mmc_card_sd(c)   ((c)->type == MMC_TYPE_SD)
#define mmc_card_sdio(c) ((c)->type == MMC_TYPE_SDIO)

#define mmc_card_present(c)   ((c)->state & MMC_STATE_PRESENT)
#define mmc_card_readonly(c)  ((c)->state & MMC_STATE_READONLY)
#define mmc_card_highspeed(c) ((c)->state & MMC_STATE_HIGHSPEED)
#define mmc_card_blockaddr(c) ((c)->state & MMC_STATE_BLOCKADDR)

#define mmc_card_set_present(c) ((c)->state |= MMC_STATE_PRESENT)
#define mmc_card_set_readonly(c) ((c)->state |= MMC_STATE_READONLY)
#define mmc_card_set_highspeed(c) ((c)->state |= MMC_STATE_HIGHSPEED)
#define mmc_card_set_blockaddr(c) ((c)->state |= MMC_STATE_BLOCKADDR)

#define mmc_card_name(c) ((c)->cid.prod_name)
#define mmc_card_id(c)   ((c)->dev.bus_id)

#define mmc_list_to_card(l) container_of(l, struct mmc_card, node)
#define mmc_get_drvdata(c)  dev_get_drvdata(&(c)->dev)
#define mmc_set_drvdata(c, d) dev_set_drvdata(&(c)->dev, d)

#endif