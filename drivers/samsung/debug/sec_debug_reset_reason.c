/*
 *secdbg_reset_reason.c
 *
 * Copyright (c) 2016 Samsung Electronics Co., Ltd
 *              http://www.samsung.com
 *
 *  This program is free software; you can redistribute  it and/or modify it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/sec_debug.h>
#include <linux/soc/samsung/exynos-soc.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/stacktrace.h>
#include <linux/uaccess.h>
#include <linux/memblock.h>
#include <linux/of.h>
#include <linux/of_reserved_mem.h>
#include "sec_debug_internal.h"
#include <linux/ctype.h>

unsigned int reset_reason = RR_N;
#define PWRSRC_RS_SIZE	20
static char pwrsrc_rs[PWRSRC_RS_SIZE + 1];

static const char *regs_bit[][8] = { 
	{ "RSVD0", "TSD", "TIMEOUT", "LDO2OK", "PWRHOLD", "WTSR", "SMPL", "UVLOB" }, /* PWROFFSRC */
	{ "PWRON", "JIGONB", "ACOK", "MRST", "ALARM0", "ALARM1", "SMPL", "WTSR" }, /* PWRONSRC */
}; /* S2MPW02 */

static const char *dword_regs_bit[][32] = { 
	{ "CLUSTER0_DBGRSTREQ0", "CLUSTER0_DBGRSTREQ1", "CLUSTER0_DBGRSTREQ2", "CLUSTER0_DBGRSTREQ3",	/* 0, 1, 2, 3 */
	  "CLUSTER1_DBGRSTREQ0", "CLUSTER1_DBGRSTREQ1", "CLUSTER1_DBGRSTREQ2", "CLUSTER2_DBGRSTREQ0",	/* 4, 5, 6, 7 */
	  "RSVD8", "RSVD9", "RSVD10", "RSVD11",				/* 8, 9, 10, 11 */
	  "RSVD12", "RSVD13", "PINRESET", "SSPCORE_CPU_WDTRESET",	/* 12, 13, 14, 15 */
	  "OIS_CPU_WDTRESET", "RSVD17", "RSVD18", "APM_CPU_WDTRESET",	/* 16, 17, 18, 19 */
	  "APM_CPU_SYSRESET", "ARM_CPU_WDTRESET", "CHUB_WDTRESET", "CLUSTER0_WDTRESET",	/* 20, 21, 22, 23 */
	  "RSVD24", "CLUSTER2_WDTRESET", "AUD_CPU0_WDTRESET", "SSS_WDTRESET",		/* 24, 25, 26, 27 */
	  "DBGCORE_CPU_WDTRESET", "WRESET", "SWRESET", ""				/* 28, 29,  30, 31 */
	}, /* RST_STAT */
}; /* EXYNOS 5515 */

static struct outbuf extra_buf;
static struct outbuf pwrsrc_buf;

static int __init secdbg_set_reset_reason(char *arg)
{
	get_option(&arg, &reset_reason);
	pr_info("%s: reset_reason: %d\n", __func__, reset_reason);
	return 0;
}

early_param("sec_debug.reset_reason", secdbg_set_reset_reason);

static int __init secdbg_set_pwrsrc_rs(char *arg)
{
	if (strlen(arg) > PWRSRC_RS_SIZE)
		return 0;

	memcpy(pwrsrc_rs, arg, (int)strlen(arg));
	return 0;
}

early_param("sec_debug.pwrsrc_rs", secdbg_set_pwrsrc_rs);

static int secdbg_reset_reason_proc_show(struct seq_file *m, void *v)
{
	if (reset_reason == RR_S)
		seq_puts(m, "SPON\n");
	else if (reset_reason == RR_W)
		seq_puts(m, "WPON\n");
	else if (reset_reason == RR_D)
		seq_puts(m, "DPON\n");
	else if (reset_reason == RR_K)
		seq_puts(m, "KPON\n");
	else if (reset_reason == RR_M)
		seq_puts(m, "MPON\n");
	else if (reset_reason == RR_P)
		seq_puts(m, "PPON\n");
	else if (reset_reason == RR_R)
		seq_puts(m, "RPON\n");
	else if (reset_reason == RR_B)
		seq_puts(m, "BPON\n");
	else if (reset_reason == RR_T)
		seq_puts(m, "TPON\n");
	else if (reset_reason == RR_C)
		seq_puts(m, "CPON\n");
	else
		seq_puts(m, "NPON\n");

	return 0;
}

bool is_target_reset_reason(void)
{
	if (reset_reason == RR_K ||
		reset_reason == RR_D ||
		reset_reason == RR_P ||
		reset_reason == RR_S)
		return true;

	return false;
}

static int secdbg_reset_reason_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, secdbg_reset_reason_proc_show, NULL);
}

static const struct file_operations secdbg_reset_reason_proc_fops = {
	.open = secdbg_reset_reason_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int secdbg_reset_reason_store_lastkmsg_proc_show(struct seq_file *m, void *v)
{
	if (is_target_reset_reason())
		seq_puts(m, "1\n");
	else
		seq_puts(m, "0\n");

	return 0;
}

static int secdbg_reset_reason_store_lastkmsg_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, secdbg_reset_reason_store_lastkmsg_proc_show, NULL);
}

static const struct file_operations secdbg_reset_reason_store_lastkmsg_proc_fops = {
	.open = secdbg_reset_reason_store_lastkmsg_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

int secdbg_rere_get_rstcnt_from_cmdline(void)
{
	long long_pwrsrc_rs;

	kstrtol(pwrsrc_rs, 16, &long_pwrsrc_rs);

	return long_pwrsrc_rs >> 48;
}

static void parse_pwrsrc_rs(struct outbuf *buf)
{
	int i;
	unsigned long tmp;
	long long_pwrsrc_rs;

	kstrtol(pwrsrc_rs, 16, &long_pwrsrc_rs);

	secdbg_base_write_buf(buf, 0, "OFFSRC::");
	tmp = long_pwrsrc_rs & 0xff0000000000;
	tmp >>= 40;
	if (!tmp)
		secdbg_base_write_buf(buf, 0, " -");
	else 
		for(i = 0; i < 8; i++)
			if (tmp & (1 << i))
				secdbg_base_write_buf(buf, 0, " %s", regs_bit[0][i]);

	secdbg_base_write_buf(buf, 0, " /");

	secdbg_base_write_buf(buf, 0, " ONSRC::");
	tmp = long_pwrsrc_rs & 0x00ff00000000;
	tmp >>= 32;
	if (!tmp)
		secdbg_base_write_buf(buf, 0, " -");
	else
		for(i = 0; i < 8; i++)
			if (tmp & (1 << i))
				secdbg_base_write_buf(buf, 0, " %s", regs_bit[1][i]);

	secdbg_base_write_buf(buf, 0, " /");

	secdbg_base_write_buf(buf, 0, " RSTSTAT::");
	tmp = long_pwrsrc_rs & 0x0000ffffffff;
	if (!tmp)
		secdbg_base_write_buf(buf, 0, " -");
	else
		for (i = 0; i < 32; i++)
			if (tmp & (1 << i))
				secdbg_base_write_buf(buf, 0, " %s", dword_regs_bit[0][i]);

	buf->already = 1;
}

static int secdbg_rere_pwr_to_ul(char *src, unsigned long *dst)
{
	char val[32] = {0, };
	int i, pos = 0;

	for (i = 0 ; i < strlen(src) ; i++)
		if (isdigit(*(src + i)))
			val[pos++] = *(src + i);

	return kstrtoul(val, 16, dst);
}

/*
 * proc/pwrsrc
 * OFFSRC (from PWROFF - 32) + ONSRC (from PWR - 32) + RSTSTAT (from RST - 32)
 * regs_bit (max 8) / dword_regs_bit (max 32)
 * total max : 48
 */
static int secdbg_reset_reason_pwrsrc_show(struct seq_file *m, void *v)
{
	int i;
	char val[32] = {0, };
	unsigned long tmp;
	int check_tmp = 0;

	if (pwrsrc_buf.already)
		goto out;

	memset(&pwrsrc_buf, 0, sizeof(pwrsrc_buf));

	memset(val, 0, 32);
	get_bk_item_val_as_string("PWROFF", val);
	if (secdbg_rere_pwr_to_ul(val, &tmp) < 0) {
		pr_err("%s: Bad PWROFF value\n", __func__);
		tmp = 0;
	}

	secdbg_base_write_buf(&pwrsrc_buf, 0, "OFFSRC:");
	if (!tmp) {
		secdbg_base_write_buf(&pwrsrc_buf, 0, " -");
		check_tmp++;
	} else
		for (i = 0; i < 8; i++)
			if (tmp & (1 << i))
				secdbg_base_write_buf(&pwrsrc_buf, 0, " %s", regs_bit[0][i]);

	secdbg_base_write_buf(&pwrsrc_buf, 0, " /");

	memset(val, 0, 32);
	get_bk_item_val_as_string("PWR", val);
	if (secdbg_rere_pwr_to_ul(val, &tmp) < 0) {
		pr_err("%s: Bad PWR value\n", __func__);
		tmp = 0;
	}

	secdbg_base_write_buf(&pwrsrc_buf, 0, " ONSRC:");
	if (!tmp) {
		secdbg_base_write_buf(&pwrsrc_buf, 0, " -");
		check_tmp++;
	} else
		for (i = 0; i < 8; i++)
			if (tmp & (1 << i))
				secdbg_base_write_buf(&pwrsrc_buf, 0, " %s", regs_bit[1][i]);

	secdbg_base_write_buf(&pwrsrc_buf, 0, " /");

	memset(val, 0, 32);
	get_bk_item_val_as_string("RST", val);
	if (kstrtoul(val, 0, &tmp) < 0) {
		pr_err("%s: Bad RST value\n", __func__);
		tmp = 0;
	}

	secdbg_base_write_buf(&pwrsrc_buf, 0, " RSTSTAT:");
	if (!tmp) {
		secdbg_base_write_buf(&pwrsrc_buf, 0, " -");
		check_tmp++;
	} else
		for (i = 0; i < 32; i++)
			if (tmp & (1 << i))
				secdbg_base_write_buf(&pwrsrc_buf, 0, " %s", dword_regs_bit[0][i]);

	if (check_tmp == 3) {
		memset(&pwrsrc_buf, 0, sizeof(pwrsrc_buf));
		parse_pwrsrc_rs(&pwrsrc_buf);
	}

	pwrsrc_buf.already = 1;
out:
	seq_printf(m, "%s", pwrsrc_buf.buf);

	return 0;
}

static int secdbg_reset_reason_pwrsrc_open(struct inode *inode, struct file *file)
{
	return single_open(file, secdbg_reset_reason_pwrsrc_show, NULL);
}

static const struct file_operations secdbg_reset_reason_pwrsrc_proc_fops = {
	.open = secdbg_reset_reason_pwrsrc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

#define BBP_STR_LEN (64)

static void handle_bug_string(char *buf, char *src)
{
	int idx = 0, len, i;

	len = strlen(src);
	if (len > BBP_STR_LEN)
		len = BBP_STR_LEN;

	for (i = 0; i < len; i++) {
		if (src[i] == '/')
			idx = i;
	}

	if (idx)
		strncpy(buf, &(src[idx + 1]), len - idx);
	else
		strncpy(buf, src, len);
}

static void handle_bus_string(char *buf, char *src)
{
	int idx = 0, len, max = 2, cnt = 0, i;

	len = strlen(src);
	if (len > BBP_STR_LEN)
		len = BBP_STR_LEN;

	for (i = 0; i < len; i++) {
		if (src[i] == '/') {
			idx = i;
			cnt++;

			if (cnt == max)
				goto out;
		}
	}

out:
	if (idx)
		strncpy(buf, src, idx);
	else
		strncpy(buf, src, len);
}

enum pnc_str {
	PNC_STR_IGNORE = 0,
	PNC_STR_UNRECV = 1,
	PNC_STR_REST = 2,
};

static int handle_panic_string(char *src)
{
	if (!src)
		return PNC_STR_IGNORE;

	if (!strncmp(src, "Fatal", 5))
		return PNC_STR_IGNORE;
	else if (!strncmp(src, "ITMON", 5))
		return PNC_STR_IGNORE;
	else if (!strncmp(src, "Unrecoverable", 13))
		return PNC_STR_UNRECV;

	return PNC_STR_REST;
}

/*
 * proc/extra
 * RSTCNT (32) + PC (256) + LR (256) (MAX: 544)
 * + BUG (256) + BUS (256) => get only 64 (BBP_STR_LEN) (MAX: 672)
 * + PANIC (256) => get only 64 (MAX: 736)
 * + SMU (256) => get only 64 (MAX: 800)
 * total max : 800
 */
static int secdbg_reset_reason_extra_show(struct seq_file *m, void *v)
{
	ssize_t ret = 0;
	char *rstcnt, *pc, *lr;
	char *bug, *bus, *dssbus, *pnc, *smu;
	char buf_log[BBP_STR_LEN] = {0, };

	if (extra_buf.already)
		goto out;

	memset(&extra_buf, 0, sizeof(extra_buf));

	rstcnt = get_bk_item_val("RSTCNT");
	pc = get_bk_item_val("PC");
	lr = get_bk_item_val("LR");

	bug = get_bk_item_val("BUG");
	bus = get_bk_item_val("BUS");
	dssbus = get_bk_item_val("DSSBUS");
	pnc = get_bk_item_val("PANIC");
	smu = get_bk_item_val("SMU");

	secdbg_base_write_buf(&extra_buf, 0, "RCNT:");
	if (rstcnt && strnlen(rstcnt, MAX_ITEM_VAL_LEN))
		secdbg_base_write_buf(&extra_buf, 0, " %s /", rstcnt);
	else
		secdbg_base_write_buf(&extra_buf, 0, " - /");

	secdbg_base_write_buf(&extra_buf, 0, " PC:");
	if (pc && strnlen(pc, MAX_ITEM_VAL_LEN))
		secdbg_base_write_buf(&extra_buf, 0, " %s", pc);
	else
		secdbg_base_write_buf(&extra_buf, 0, " -");

	secdbg_base_write_buf(&extra_buf, 0, " LR:");
	if (lr && strnlen(lr, MAX_ITEM_VAL_LEN))
		secdbg_base_write_buf(&extra_buf, 0, " %s", lr);
	else
		secdbg_base_write_buf(&extra_buf, 0, " -");

	/* BUG */
	if (bug && strnlen(bug, MAX_ITEM_VAL_LEN)) {
		handle_bug_string(buf_log, bug);

		secdbg_base_write_buf(&extra_buf, 0, " BUG: %s", buf_log);
		memset(buf_log, 0, BBP_STR_LEN);
	}

	/* BUS */
	if (bus && strnlen(bus, MAX_ITEM_VAL_LEN)) {
		handle_bus_string(buf_log, bus);

		secdbg_base_write_buf(&extra_buf, 0, " BUS: %s", buf_log);
		memset(buf_log, 0, BBP_STR_LEN);
	}

	/* DSSBUS */
	if (dssbus && strnlen(dssbus, MAX_ITEM_VAL_LEN)) {
		handle_bus_string(buf_log, dssbus);

		secdbg_base_write_buf(&extra_buf, 0, " DSSBUS: %s", buf_log);
		memset(buf_log, 0, BBP_STR_LEN);
	}


	/* PANIC */
	ret = handle_panic_string(pnc);
	if (ret == PNC_STR_UNRECV) {
		if (smu && strnlen(smu, MAX_ITEM_VAL_LEN))
			secdbg_base_write_buf(&extra_buf, BBP_STR_LEN, " SMU: %s", smu);
		else
			secdbg_base_write_buf(&extra_buf, BBP_STR_LEN, " PANIC: %s", pnc);
	} else if (ret == PNC_STR_REST) {
		if (strnlen(pnc, MAX_ITEM_VAL_LEN))
			secdbg_base_write_buf(&extra_buf, BBP_STR_LEN, " PANIC: %s", pnc);
	}

	extra_buf.already = 1;

out:
	seq_printf(m, "%s", extra_buf.buf);

	return 0;
}

static int secdbg_reset_reason_extra_open(struct inode *inode, struct file *file)
{
	return single_open(file, secdbg_reset_reason_extra_show, NULL);
}

static const struct file_operations secdbg_reset_reason_extra_proc_fops = {
	.open = secdbg_reset_reason_extra_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int __init secdbg_reset_reason_init(void)
{
	struct proc_dir_entry *entry;

	pr_info("%s: reset_reason: %d\n", __func__, reset_reason);

	entry = proc_create("reset_reason", 0400, NULL, &secdbg_reset_reason_proc_fops);
	if (!entry)
		return -ENOMEM;

	entry = proc_create("store_lastkmsg", 0400, NULL, &secdbg_reset_reason_store_lastkmsg_proc_fops);
	if (!entry)
		return -ENOMEM;

	entry = proc_create("extra", 0400, NULL, &secdbg_reset_reason_extra_proc_fops);
	if (!entry)
		return -ENOMEM;

	entry = proc_create("pwrsrc", 0400, NULL, &secdbg_reset_reason_pwrsrc_proc_fops);
	if (!entry)
		return -ENOMEM;

	return 0;
}
device_initcall(secdbg_reset_reason_init);
