/*
 * linux/drivers/video/fbdev/exynos/panel/rm69091/rm69091.h
 *
 * Header file for RM69091 Dimming Driver
 *
 * Copyright (c) 2016 Samsung Electronics
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __RM69091_H__
#define __RM69091_H__

#include <linux/types.h>
#include <linux/kernel.h>


#define AID_INTERPOLATION
#define RM69091_GAMMA_CMD_CNT 	(35)

#define RM69091_ADDR_OFS		(0)
#define RM69091_ADDR_LEN		(1)
#define RM69091_DATA_OFS		(RM69091_ADDR_OFS + RM69091_ADDR_LEN)

#define RM69091_MTP_REG		0xC8
#define RM69091_MTP_OFS		0
#define RM69091_MTP_LEN		34

#define RM69091_DATE_REG		0xA1
#define RM69091_DATE_OFS		4
#define RM69091_DATE_LEN		(PANEL_DATE_LEN)

#define RM69091_COORDINATE_REG	0xA1
#define RM69091_COORDINATE_OFS	0
#define RM69091_COORDINATE_LEN	(PANEL_COORD_LEN)

#define RM69091_ID_REG		0x04
#define RM69091_ID_OFS		0
#define RM69091_ID_LEN		(PANEL_ID_LEN)

#define RM69091_CODE_REG		0xD6
#define RM69091_CODE_OFS		0
#define RM69091_CODE_LEN		(PANEL_CODE_LEN)

#define RM69091_ELVSS_REG		0xB5
#define RM69091_ELVSS_OFS		0
#define RM69091_ELVSS_LEN		23

#define RM69091_OCTA_ID_REG		0xA1
#define RM69091_OCTA_ID_OFS		11
#define RM69091_OCTA_ID_LEN		(PANEL_OCTA_ID_LEN)

#define RM69091_CHIP_ID_REG		0xD6
#define RM69091_CHIP_ID_OFS		0
#define RM69091_CHIP_ID_LEN		5

#define RM69091_PRODUCT_INFO1_REG		0x00
#define RM69091_PRODUCT_INFO2_REG		0x01
#define RM69091_PRODUCT_INFO3_REG		0x02
#define RM69091_PRODUCT_INFO4_REG		0x03
#define RM69091_PRODUCT_INFO5_REG		0x04
#define RM69091_PRODUCT_INFO6_REG		0x05
#define RM69091_PRODUCT_INFO7_REG		0x06
#define RM69091_PRODUCT_INFO8_REG		0x07
#define RM69091_PRODUCT_INFO9_REG		0x08
#define RM69091_PRODUCT_INFO10_REG		0x09
#define RM69091_PRODUCT_INFO11_REG		0x0A

#define RM69091_PRODUCT_INFO_LEN		1
#define RM69091_PRODUCT_INFO_OFS		0

/* for panel dump */
#define RM69091_RDDPM_REG		0x0A
#define RM69091_RDDPM_OFS		0
#define RM69091_RDDPM_LEN		1

#define RM69091_RDDSM_REG		0x0E
#define RM69091_RDDSM_OFS		0
#define RM69091_RDDSM_LEN		1

#define RM69091_DSI_ERR_REG		0x05
#define RM69091_DSI_ERR_OFS		0
#define RM69091_DSI_ERR_LEN		1

#define RM69091_SELF_DIAG_REG	0x0F
#define RM69091_SELF_DIAG_OFS	0
#define RM69091_SELF_DIAG_LEN	1

enum {
	GAMMA_MAPTBL,
	GAMMA_MODE2_MAPTBL,
	TSET_MAPTBL,
	ACL_CONTROL_MAPTBL,
	HBM_ACL_CONTROL_MAPTBL,
	NORMAL_ACL_ONOFF_MAPTBL,
	HBM_ACL_ONOFF_MAPTBL,
	HBM_TRANSITION_MAPTBL,
	LPM_WRDISBV_MAPTBL,
	HBM_ONOFF_MAPTBL,
	ELVSS_TEMP_MAPTBL,
	VINIT_TEMP_MAPTBL,
	VCL_TEMP_MAPTBL,
#ifdef CONFIG_SUPPORT_HMD
	/* HMD MAPTBL */
	HMD_GAMMA_MAPTBL,
	HMD_AOR_MAPTBL,
	HMD_ELVSS_MAPTBL,
#endif /* CONFIG_SUPPORT_HMD */
	MAX_MAPTBL,
};

enum {
	READ_ID,
	READ_COORDINATE,
	READ_CODE,
	READ_ELVSS,
	READ_MTP,
	READ_DATE,
	READ_OCTA_ID,
	READ_CHIP_ID,
	READ_RDDPM,
	READ_RDDSM,
	READ_DSI_ERR,
	READ_SELF_DIAG,
	READ_PRODUCT_INFO1,
	READ_PRODUCT_INFO2,
	READ_PRODUCT_INFO3,
	READ_PRODUCT_INFO4,
	READ_PRODUCT_INFO5,
	READ_PRODUCT_INFO6,
	READ_PRODUCT_INFO7,
	READ_PRODUCT_INFO8,
	READ_PRODUCT_INFO9,
	READ_PRODUCT_INFO10,
	READ_PRODUCT_INFO11,
};

enum {
	RES_ID,
	RES_COORDINATE,
	RES_CODE,
	RES_ELVSS,
	RES_MTP,
	RES_DATE,
	RES_OCTA_ID,
	RES_CHIP_ID,
	RES_RDDPM,
	RES_RDDSM,
	RES_DSI_ERR,
	RES_SELF_DIAG,
	RES_PRODUCT_INFO1,
	RES_PRODUCT_INFO2,
	RES_PRODUCT_INFO3,
	RES_PRODUCT_INFO4,
	RES_PRODUCT_INFO5,
	RES_PRODUCT_INFO6,
	RES_PRODUCT_INFO7,
	RES_PRODUCT_INFO8,
	RES_PRODUCT_INFO9,
	RES_PRODUCT_INFO10,
	RES_PRODUCT_INFO11,
};

static u8 RM69091_ID[RM69091_ID_LEN];
static u8 RM69091_COORDINATE[RM69091_COORDINATE_LEN];
static u8 RM69091_CODE[RM69091_CODE_LEN];
static u8 RM69091_ELVSS[RM69091_ELVSS_LEN];
static u8 RM69091_MTP[RM69091_MTP_LEN];
static u8 RM69091_DATE[RM69091_DATE_LEN];
static u8 RM69091_OCTA_ID[RM69091_OCTA_ID_LEN];
static u8 RM69091_CHIP_ID[RM69091_CHIP_ID_LEN];
static u8 RM69091_RDDPM[RM69091_RDDPM_LEN];
static u8 RM69091_RDDSM[RM69091_RDDSM_LEN];
static u8 RM69091_DSI_ERR[RM69091_DSI_ERR_LEN];
static u8 RM69091_SELF_DIAG[RM69091_SELF_DIAG_LEN];

static u8 RM69091_PRODUCT_INFO1[RM69091_PRODUCT_INFO_LEN];
static u8 RM69091_PRODUCT_INFO2[RM69091_PRODUCT_INFO_LEN];
static u8 RM69091_PRODUCT_INFO3[RM69091_PRODUCT_INFO_LEN];
static u8 RM69091_PRODUCT_INFO4[RM69091_PRODUCT_INFO_LEN];
static u8 RM69091_PRODUCT_INFO5[RM69091_PRODUCT_INFO_LEN];
static u8 RM69091_PRODUCT_INFO6[RM69091_PRODUCT_INFO_LEN];
static u8 RM69091_PRODUCT_INFO7[RM69091_PRODUCT_INFO_LEN];
static u8 RM69091_PRODUCT_INFO8[RM69091_PRODUCT_INFO_LEN];
static u8 RM69091_PRODUCT_INFO9[RM69091_PRODUCT_INFO_LEN];
static u8 RM69091_PRODUCT_INFO10[RM69091_PRODUCT_INFO_LEN];
static u8 RM69091_PRODUCT_INFO11[RM69091_PRODUCT_INFO_LEN];

static struct rdinfo rm69091_rditbl[] = {
	[READ_ID] = RDINFO_INIT(id, DSI_PKT_TYPE_RD, RM69091_ID_REG, RM69091_ID_OFS, RM69091_ID_LEN),
	[READ_COORDINATE] = RDINFO_INIT(coordinate, DSI_PKT_TYPE_RD, RM69091_COORDINATE_REG, RM69091_COORDINATE_OFS, RM69091_COORDINATE_LEN),
	[READ_CODE] = RDINFO_INIT(code, DSI_PKT_TYPE_RD, RM69091_CODE_REG, RM69091_CODE_OFS, RM69091_CODE_LEN),
	[READ_ELVSS] = RDINFO_INIT(elvss, DSI_PKT_TYPE_RD, RM69091_ELVSS_REG, RM69091_ELVSS_OFS, RM69091_ELVSS_LEN),
	[READ_MTP] = RDINFO_INIT(mtp, DSI_PKT_TYPE_RD, RM69091_MTP_REG, RM69091_MTP_OFS, RM69091_MTP_LEN),
	[READ_DATE] = RDINFO_INIT(date, DSI_PKT_TYPE_RD, RM69091_DATE_REG, RM69091_DATE_OFS, RM69091_DATE_LEN),
	[READ_OCTA_ID] = RDINFO_INIT(octa_id, DSI_PKT_TYPE_RD, RM69091_OCTA_ID_REG, RM69091_OCTA_ID_OFS, RM69091_OCTA_ID_LEN),
	[READ_CHIP_ID] = RDINFO_INIT(chip_id, DSI_PKT_TYPE_RD, RM69091_CHIP_ID_REG, RM69091_CHIP_ID_OFS, RM69091_CHIP_ID_LEN),
	[READ_RDDPM] = RDINFO_INIT(rddpm, DSI_PKT_TYPE_RD, RM69091_RDDPM_REG, RM69091_RDDPM_OFS, RM69091_RDDPM_LEN),
	[READ_RDDSM] = RDINFO_INIT(rddsm, DSI_PKT_TYPE_RD, RM69091_RDDSM_REG, RM69091_RDDSM_OFS, RM69091_RDDSM_LEN),
	[READ_DSI_ERR] = RDINFO_INIT(dsi_err, DSI_PKT_TYPE_RD, RM69091_DSI_ERR_REG, RM69091_DSI_ERR_OFS, RM69091_DSI_ERR_LEN),
	[READ_SELF_DIAG] = RDINFO_INIT(self_diag, DSI_PKT_TYPE_RD, RM69091_SELF_DIAG_REG, RM69091_SELF_DIAG_OFS, RM69091_SELF_DIAG_LEN),
	[READ_PRODUCT_INFO1] = RDINFO_INIT(product_info1, DSI_PKT_TYPE_RD, RM69091_PRODUCT_INFO1_REG, RM69091_PRODUCT_INFO_OFS, RM69091_PRODUCT_INFO_LEN),
	[READ_PRODUCT_INFO2] = RDINFO_INIT(product_info2, DSI_PKT_TYPE_RD, RM69091_PRODUCT_INFO2_REG, RM69091_PRODUCT_INFO_OFS, RM69091_PRODUCT_INFO_LEN),
	[READ_PRODUCT_INFO3] = RDINFO_INIT(product_info3, DSI_PKT_TYPE_RD, RM69091_PRODUCT_INFO3_REG, RM69091_PRODUCT_INFO_OFS, RM69091_PRODUCT_INFO_LEN),
	[READ_PRODUCT_INFO4] = RDINFO_INIT(product_info4, DSI_PKT_TYPE_RD, RM69091_PRODUCT_INFO4_REG, RM69091_PRODUCT_INFO_OFS, RM69091_PRODUCT_INFO_LEN),
	[READ_PRODUCT_INFO5] = RDINFO_INIT(product_info5, DSI_PKT_TYPE_RD, RM69091_PRODUCT_INFO5_REG, RM69091_PRODUCT_INFO_OFS, RM69091_PRODUCT_INFO_LEN),
	[READ_PRODUCT_INFO6] = RDINFO_INIT(product_info6, DSI_PKT_TYPE_RD, RM69091_PRODUCT_INFO6_REG, RM69091_PRODUCT_INFO_OFS, RM69091_PRODUCT_INFO_LEN),
	[READ_PRODUCT_INFO7] = RDINFO_INIT(product_info7, DSI_PKT_TYPE_RD, RM69091_PRODUCT_INFO7_REG, RM69091_PRODUCT_INFO_OFS, RM69091_PRODUCT_INFO_LEN),
	[READ_PRODUCT_INFO8] = RDINFO_INIT(product_info8, DSI_PKT_TYPE_RD, RM69091_PRODUCT_INFO8_REG, RM69091_PRODUCT_INFO_OFS, RM69091_PRODUCT_INFO_LEN),
	[READ_PRODUCT_INFO9] = RDINFO_INIT(product_info9, DSI_PKT_TYPE_RD, RM69091_PRODUCT_INFO9_REG, RM69091_PRODUCT_INFO_OFS, RM69091_PRODUCT_INFO_LEN),
	[READ_PRODUCT_INFO10] = RDINFO_INIT(product_info10, DSI_PKT_TYPE_RD, RM69091_PRODUCT_INFO10_REG, RM69091_PRODUCT_INFO_OFS, RM69091_PRODUCT_INFO_LEN),
	[READ_PRODUCT_INFO11] = RDINFO_INIT(product_info11, DSI_PKT_TYPE_RD, RM69091_PRODUCT_INFO11_REG, RM69091_PRODUCT_INFO_OFS, RM69091_PRODUCT_INFO_LEN),
};

static DEFINE_RESUI(id, &rm69091_rditbl[READ_ID], 0);
static DEFINE_RESUI(coordinate, &rm69091_rditbl[READ_COORDINATE], 0);
static DEFINE_RESUI(code, &rm69091_rditbl[READ_CODE], 0);
static DEFINE_RESUI(elvss, &rm69091_rditbl[READ_ELVSS], 0);
static DEFINE_RESUI(mtp, &rm69091_rditbl[READ_MTP], 0);
static DEFINE_RESUI(date, &rm69091_rditbl[READ_DATE], 0);
static DEFINE_RESUI(octa_id, &rm69091_rditbl[READ_OCTA_ID], 0);
static DEFINE_RESUI(chip_id, &rm69091_rditbl[READ_CHIP_ID], 0);
static DEFINE_RESUI(rddpm, &rm69091_rditbl[READ_RDDPM], 0);
static DEFINE_RESUI(rddsm, &rm69091_rditbl[READ_RDDSM], 0);
static DEFINE_RESUI(dsi_err, &rm69091_rditbl[READ_DSI_ERR], 0);
static DEFINE_RESUI(self_diag, &rm69091_rditbl[READ_SELF_DIAG], 0);
static DEFINE_RESUI(product_info1, &rm69091_rditbl[READ_PRODUCT_INFO1], 0);
static DEFINE_RESUI(product_info2, &rm69091_rditbl[READ_PRODUCT_INFO2], 0);
static DEFINE_RESUI(product_info3, &rm69091_rditbl[READ_PRODUCT_INFO3], 0);
static DEFINE_RESUI(product_info4, &rm69091_rditbl[READ_PRODUCT_INFO4], 0);
static DEFINE_RESUI(product_info5, &rm69091_rditbl[READ_PRODUCT_INFO5], 0);
static DEFINE_RESUI(product_info6, &rm69091_rditbl[READ_PRODUCT_INFO6], 0);
static DEFINE_RESUI(product_info7, &rm69091_rditbl[READ_PRODUCT_INFO7], 0);
static DEFINE_RESUI(product_info8, &rm69091_rditbl[READ_PRODUCT_INFO8], 0);
static DEFINE_RESUI(product_info9, &rm69091_rditbl[READ_PRODUCT_INFO9], 0);
static DEFINE_RESUI(product_info10, &rm69091_rditbl[READ_PRODUCT_INFO10], 0);
static DEFINE_RESUI(product_info11, &rm69091_rditbl[READ_PRODUCT_INFO11], 0);

static struct resinfo rm69091_restbl[] = {
	[RES_ID] = RESINFO_INIT(id, RM69091_ID, RESUI(id)),
	[RES_COORDINATE] = RESINFO_INIT(coordinate, RM69091_COORDINATE, RESUI(coordinate)),
	[RES_CODE] = RESINFO_INIT(code, RM69091_CODE, RESUI(code)),
	[RES_ELVSS] = RESINFO_INIT(elvss, RM69091_ELVSS, RESUI(elvss)),
	[RES_MTP] = RESINFO_INIT(mtp, RM69091_MTP, RESUI(mtp)),
	[RES_DATE] = RESINFO_INIT(date, RM69091_DATE, RESUI(date)),
	[RES_OCTA_ID] = RESINFO_INIT(octa_id, RM69091_OCTA_ID, RESUI(octa_id)),
	[RES_CHIP_ID] = RESINFO_INIT(chip_id, RM69091_CHIP_ID, RESUI(chip_id)),
	[RES_RDDPM] = RESINFO_INIT(rddpm, RM69091_RDDPM, RESUI(rddpm)),
	[RES_RDDSM] = RESINFO_INIT(rddsm, RM69091_RDDSM, RESUI(rddsm)),
	[RES_DSI_ERR] = RESINFO_INIT(dsi_err, RM69091_DSI_ERR, RESUI(dsi_err)),
	[RES_SELF_DIAG] = RESINFO_INIT(self_diag, RM69091_SELF_DIAG, RESUI(self_diag)),
	[RES_PRODUCT_INFO1] = RESINFO_INIT(product_info1, RM69091_PRODUCT_INFO1, RESUI(product_info1)),
	[RES_PRODUCT_INFO2] = RESINFO_INIT(product_info2, RM69091_PRODUCT_INFO2, RESUI(product_info2)),
	[RES_PRODUCT_INFO3] = RESINFO_INIT(product_info3, RM69091_PRODUCT_INFO3, RESUI(product_info3)),
	[RES_PRODUCT_INFO4] = RESINFO_INIT(product_info4, RM69091_PRODUCT_INFO4, RESUI(product_info4)),
	[RES_PRODUCT_INFO5] = RESINFO_INIT(product_info5, RM69091_PRODUCT_INFO5, RESUI(product_info5)),
	[RES_PRODUCT_INFO6] = RESINFO_INIT(product_info6, RM69091_PRODUCT_INFO6, RESUI(product_info6)),
	[RES_PRODUCT_INFO7] = RESINFO_INIT(product_info7, RM69091_PRODUCT_INFO7, RESUI(product_info7)),
	[RES_PRODUCT_INFO8] = RESINFO_INIT(product_info8, RM69091_PRODUCT_INFO8, RESUI(product_info8)),
	[RES_PRODUCT_INFO9] = RESINFO_INIT(product_info9, RM69091_PRODUCT_INFO9, RESUI(product_info9)),
	[RES_PRODUCT_INFO10] = RESINFO_INIT(product_info10, RM69091_PRODUCT_INFO10, RESUI(product_info10)),
	[RES_PRODUCT_INFO11] = RESINFO_INIT(product_info11, RM69091_PRODUCT_INFO11, RESUI(product_info11)),
};

enum {
	DUMP_RDDPM = 0,
	DUMP_RDDPM_SLEEP_IN,
	DUMP_RDDSM,
	DUMP_DSI_ERR,
	DUMP_SELF_DIAG,
};

static void show_rddpm(struct dumpinfo *info);
static void show_rddpm_before_sleep_in(struct dumpinfo *info);
static void show_rddsm(struct dumpinfo *info);
static void show_dsi_err(struct dumpinfo *info);
static void show_self_diag(struct dumpinfo *info);

static struct dumpinfo rm69091_dmptbl[] = {
	[DUMP_RDDPM] = DUMPINFO_INIT(rddpm, &rm69091_restbl[RES_RDDPM], show_rddpm),
	[DUMP_RDDPM_SLEEP_IN] = DUMPINFO_INIT(rddpm_sleep_in, &rm69091_restbl[RES_RDDPM], show_rddpm_before_sleep_in),
	[DUMP_RDDSM] = DUMPINFO_INIT(rddsm, &rm69091_restbl[RES_RDDSM], show_rddsm),
	[DUMP_DSI_ERR] = DUMPINFO_INIT(dsi_err, &rm69091_restbl[RES_DSI_ERR], show_dsi_err),
	[DUMP_SELF_DIAG] = DUMPINFO_INIT(self_diag, &rm69091_restbl[RES_SELF_DIAG], show_self_diag),
};

enum {
	RM69091_ACL_RATIO_0,
	RM69091_ACL_RATIO_8,
	RM69091_ACL_RATIO_15,
	MAX_RM69091_ACL_RATIO,
};

enum {
	OVER_TEMP_0,
	UNDER_TEMP_0,
	UNDER_TEMP_MINUS_15,
	MAX_TEMP,
};

static int init_common_table(struct maptbl *);
static int init_gamma_mode2_brt_table(struct maptbl *tbl);
static int getidx_gamma_mode2_brt_table(struct maptbl *);
static void copy_common_maptbl(struct maptbl *, u8 *);

static int getidx_acl_control_table(struct maptbl *tbl);
static int getidx_hbm_transition_table(struct maptbl *tbl);
static int getidx_hbm_onoff_table(struct maptbl *tbl);
static int getidx_elvss_temp_table(struct maptbl *tbl);
static int getidx_acl_onoff_table(struct maptbl *tbl);

static inline bool is_id_lt_01(struct panel_device *panel);
static bool is_smooth_dimming_available(struct panel_device *panel);
static bool is_hbm_on(struct panel_device *panel);
static bool is_prev_normal_brt(struct panel_device *panel);


#endif /* __RM69091_H__ */
