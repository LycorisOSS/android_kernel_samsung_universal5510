/*
 * Customer HW 4 dependant file
 *
 * Portions of this code are copyright (c) 2021 Cypress Semiconductor Corporation
 *
 * Copyright (C) 1999-2017, Broadcom Corporation
 *
 *      Unless you and Broadcom execute a separate written software license
 * agreement governing use of this software, this software is licensed to you
 * under the terms of the GNU General Public License version 2 (the "GPL"),
 * available at http://www.broadcom.com/licenses/GPLv2.php, with the
 * following added to such license:
 *
 *      As a special exception, the copyright holders of this software give you
 * permission to link this software with independent modules, and to copy and
 * distribute the resulting executable under terms of your choice, provided that
 * you also meet, for each linked independent module, the terms and conditions of
 * the license of that module.  An independent module is a module which is not
 * derived from this software.  The special exception does not apply to any
 * modifications of the software.
 *
 *      Notwithstanding the above, under no circumstances may you combine this
 * software in any way with any other Broadcom software provided under a license
 * other than the GPL, without Broadcom's express prior written consent.
 *
 *
 * <<Broadcom-WL-IPTag/Open:>>
 *
 * $Id: dhd_sec_feature.h$
 */

/*
 * ** Desciption ***
 * 1. Module vs COB
 *    If your model's WIFI HW chip is COB type, you must add below feature
 *    - #undef USE_CID_CHECK
 *    - #define READ_MACADDR
 *    Because COB type chip have not CID and Mac address.
 *    So, you must add below feature to defconfig file.
 *    - CONFIG_WIFI_BROADCOM_COB
 *
 * 2. PROJECTS
 *    If you want add some feature only own Project, you can add it in 'PROJECTS' part.
 *
 * 3. Region code
 *    If you want add some feature only own region model, you can use below code.
 *    - 100 : EUR OPEN
 *    - 101 : EUR ORG
 *    - 200 : KOR OPEN
 *    - 201 : KOR SKT
 *    - 202 : KOR KTT
 *    - 203 : KOR LGT
 *    - 300 : CHN OPEN
 *    - 400 : USA OPEN
 *    - 401 : USA ATT
 *    - 402 : USA TMO
 *    - 403 : USA VZW
 *    - 404 : USA SPR
 *    - 405 : USA USC
 *    You can refer how to using it below this file.
 *    And, you can add more region code, too.
 */

#ifndef _dhd_sec_feature_h_
#define _dhd_sec_feature_h_

#include <linuxver.h>

/* For COB type feature */
#ifdef CONFIG_WIFI_BROADCOM_COB
#undef USE_CID_CHECK
#define READ_MACADDR
#endif  /* CONFIG_WIFI_BROADCOM_COB */

#if defined(CONFIG_SEC_TRLTE_PROJECT)
#define SUPPORT_MULTIPLE_BOARD_REV
#endif /* CONFIG_SEC_TRLTE_PROJECT */

#if defined(CONFIG_MACH_UNIVERSAL7420) || defined(CONFIG_ARCH_MSM8994) || \
	defined(CONFIG_ARCH_MSM8996) || defined(CONFIG_SOC_EXYNOS8890)
#define SUPPORT_MULTIPLE_MODULE_CIS
#endif /* CONFIG_MACH_UNIVERSAL7420 || CONFIG_ARCH_MSM8994 ||
	* CONFIG_ARCH_MSM8996 || CONFIG_SOC_EXYNOS8890
	*/

#if defined(CONFIG_ARCH_MSM8996) || defined(CONFIG_SOC_EXYNOS8890)
#define SUPPORT_BCM4359_MIXED_MODULES
#endif /* CONFIG_ARCH_MSM8996 || CONFIG_SOC_EXYNOS8890 */

#ifdef BCMPCIE
/* For EXYNOS PCIe RC Control */
#if defined(CONFIG_MACH_UNIVERSAL5433) || defined(CONFIG_MACH_UNIVERSAL7420) || \
	defined(CONFIG_SOC_EXYNOS8890) || defined(CONFIG_SOC_EXYNOS8895) || \
	defined(CONFIG_SOC_EXYNOS9810) || defined(CONFIG_SOC_EXYNOS9820)
#define EXYNOS_PCIE_LINKDOWN_RECOVERY
#define USE_EXYNOS_PCIE_RC_PMPATCH
#endif /* CONFIG_MACH_UNIVERSAL5433 || CONFIGA_MACH_UNIVERSAL7420 ||
	* CONFIG_SOC_EXYNOS8890 || CONFIG_SOC_EXYNOS8895 || CONFIG_SOC_EXYNOS9810 || \
	* CONFIG_SOC_EXYNOS9820
	*/
#endif /* BCMPCIE */

#if defined(CONFIG_ARGOS)
#if defined(CONFIG_SPLIT_ARGOS_SET)
#define ARGOS_IRQ_WIFI_TABLE_LABEL "WIFI TX"
#define ARGOS_WIFI_TABLE_LABEL "WIFI RX"
#else /* CONFIG_SPLIT_ARGOS_SET */
#define ARGOS_IRQ_WIFI_TABLE_LABEL "WIFI"
#define ARGOS_WIFI_TABLE_LABEL "WIFI"
#endif /* CONFIG_SPLIT_ARGOS_SET */
#define ARGOS_P2P_TABLE_LABEL "P2P"
#endif /* CONFIG_ARGOS */

/* PROJECTS START */

#if defined(CONFIG_MACH_SAMSUNG_ESPRESSO) || defined(CONFIG_MACH_SAMSUNG_ESPRESSO_10)
#define READ_MACADDR
#define HW_OOB
#endif /* CONFIG_MACH_SAMSUNG_ESPRESSO && CONFIG_MACH_SAMSUNG_ESPRESSO_10 */

#if defined(CONFIG_MACH_UNIVERSAL5430) && !defined(CONFIG_BCM43455)
#undef CUSTOM_SET_CPUCORE
#define PRIMARY_CPUCORE 0
#define DPC_CPUCORE 4
#define RXF_CPUCORE 7
#define ARGOS_CPU_SCHEDULER
#elif defined(CONFIG_MACH_UNIVERSAL5430) && defined(CONFIG_BCM43455)
#define CUSTOM_SET_CPUCORE
#define PRIMARY_CPUCORE 0
#define MAX_RETRY_SET_CPUCORE 5
#define DPC_CPUCORE 0
#define RXF_CPUCORE 4
#elif defined(CONFIG_MACH_UNIVERSAL7580) && defined(CONFIG_BCM43455)
#define CUSTOM_SET_CPUCORE
#define PRIMARY_CPUCORE 0
#define MAX_RETRY_SET_CPUCORE 5
#define DPC_CPUCORE 1
#define RXF_CPUCORE 2
#elif defined(CONFIG_MACH_UNIVERSAL5433) || defined(CONFIG_MACH_UNIVERSAL7420) || \
	defined(CONFIG_SOC_EXYNOS8890) || defined(CONFIG_SOC_EXYNOS8895)
#undef CUSTOM_SET_CPUCORE
#define PRIMARY_CPUCORE 0
#define DPC_CPUCORE 4
#define RXF_CPUCORE 5
#define TASKLET_CPUCORE 5
#define ARGOS_CPU_SCHEDULER
#define ARGOS_RPS_CPU_CTL

#ifdef CONFIG_SOC_EXYNOS8895
#define ARGOS_DPC_TASKLET_CTL
#endif /* CONFIG_SOC_EXYNOS8895 */

#ifdef CONFIG_MACH_UNIVERSAL7420
#define EXYNOS_PCIE_DEBUG
#endif /* CONFIG_MACH_UNIVERSAL7420 */

#elif defined(CONFIG_MACH_HL3G) || defined(CONFIG_MACH_HLLTE) || \
	defined(CONFIG_MACH_UNIVERSAL5422) || defined(CONFIG_MACH_UNIVERSAL5430)
#define CUSTOM_SET_CPUCORE
#define PRIMARY_CPUCORE 0
#define MAX_RETRY_SET_CPUCORE 5
#define DPC_CPUCORE 4
#define RXF_CPUCORE 5
#endif /* CONFIG_MACH_UNIVERSAL5433 || CONFIG_MACH_UNIVERSAL7420  || CONFIG_SOC_EXYNOS8890 */

#if defined(CONFIG_SOC_EXYNOS9810) || defined(CONFIG_SOC_EXYNOS9820)
#define PCIE_IRQ_CPU_CORE 5
#endif /* CONFIG_SOC_EXYNOS9810 || CONFIG_SOC_EXYNOS9820 */

#if defined(DHD_LB)
#if defined(CONFIG_ARCH_SM8150)
#define DHD_LB_PRIMARY_CPUS     (0x70)
#define DHD_LB_SECONDARY_CPUS   (0x0E)
#elif defined(CONFIG_SOC_EXYNOS9810) || defined(CONFIG_SOC_EXYNOS9820)
#define DHD_LB_PRIMARY_CPUS     (0x10)
#define DHD_LB_SECONDARY_CPUS   (0x0E)
#elif defined(CONFIG_SOC_EXYNOS8890)
/*
 * Removed core 6~7 from NAPI CPU mask.
 * Exynos 8890 disabled core 6~7 by default.
 */
#define DHD_LB_PRIMARY_CPUS     (0x30)
#define DHD_LB_SECONDARY_CPUS   (0x0E)
#elif defined(CONFIG_SOC_EXYNOS8895)
/* using whole big core with NAPI mask */
#define DHD_LB_PRIMARY_CPUS     (0xF0)
#define DHD_LB_SECONDARY_CPUS   (0x0E)
#elif defined(CONFIG_ARCH_MSM8998)
#define DHD_LB_PRIMARY_CPUS     (0x20)
#define DHD_LB_SECONDARY_CPUS   (0x0E)
#elif defined(CONFIG_ARCH_MSM8996)
#define DHD_LB_PRIMARY_CPUS     (0x0C)
#define DHD_LB_SECONDARY_CPUS   (0x03)
#else /* Default LB masks */
/* using whole big core with NAPI mask */
#define DHD_LB_PRIMARY_CPUS     (0xF0)
#define DHD_LB_SECONDARY_CPUS   (0x0E)
#endif /* CONFIG_SOC_EXYNOS8890 */
#else /* !DHD_LB */
#define ARGOS_DPC_TASKLET_CTL
#endif /* !DHD_LB */

#if defined(CONFIG_ARCH_MSM) || defined(CONFIG_SOC_EXYNOS8895) || \
	defined(CONFIG_SOC_EXYNOS9810) || defined(CONFIG_SOC_EXYNOS9820)
#if defined(CONFIG_BCMDHD_PCIE)
#define BCMPCIE_DISABLE_ASYNC_SUSPEND
#endif /* CONFIG_BCMDHD_PCIE */
#endif /* CONFIG_ARCH_MSM */

/* Q1 also uses this feature */
#if defined(CONFIG_MACH_U1) || defined(CONFIG_MACH_TRATS)
#ifdef CONFIG_MACH_Q1_BD
#define HW_OOB
#endif /* CONFIG_MACH_Q1_BD */
#define USE_CID_CHECK
#define WRITE_MACADDR
#endif /* CONFIG_MACH_U1 || CONFIG_MACH_TRATS */

#ifdef CONFIG_ARCH_MSM7X30
#define HW_OOB
#define READ_MACADDR
#endif /* CONFIG_ARCH_MSM7X30 */

#if defined(CONFIG_MACH_GC1) || defined(CONFIG_MACH_U1_NA_SPR) || \
	defined(CONFIG_MACH_VIENNAEUR) || defined(CONFIG_MACH_LT03EUR) || \
	defined(CONFIG_MACH_LT03SKT) || defined(CONFIG_MACH_LT03KTT) || \
	defined(CONFIG_MACH_LT03LGT) || defined(CONFIG_V1A) || defined(CONFIG_N1A) || \
	defined(CONFIG_N2A) || defined(CONFIG_V2A) || defined(CONFIG_MACH_VIENNAEUR)
#undef USE_CID_CHECK
#define READ_MACADDR
#endif	/* CONFIG_MACH_GC1 || CONFIG_MACH_U1_NA_SPR || CONFIG_MACH_VIENNAEUR ||
	 * CONFIG_MACH_LT03EUR || CONFIG_MACH_LT03SKT || CONFIG_MACH_LT03KTT ||
	 * CONFIG_MACH_LT03LGT || CONFIG_V1A ||
	 * CONFIG_N1A || CONFIG_N2A || CONFIG_V2A ||
	 * CONFIG_MACH_VIENNAEUR
	 */

#ifdef CONFIG_MACH_P10
#define READ_MACADDR
#endif /* CONFIG_MACH_P10 */

#ifdef CONFIG_ARCH_MSM8960
#undef WIFI_TURNOFF_DELAY
#define WIFI_TURNOFF_DELAY	200
#endif /* CONFIG_ARCH_MSM8960 */

/* PROJECTS END */

/* REGION CODE START */

#ifndef CONFIG_WLAN_REGION_CODE
#define CONFIG_WLAN_REGION_CODE 100
#endif /* CONFIG_WLAN_REGION_CODE */

#if (CONFIG_WLAN_REGION_CODE >= 100) && (CONFIG_WLAN_REGION_CODE < 200) /* EUR */
#if (CONFIG_WLAN_REGION_CODE == 101) /* EUR ORG */
/* GAN LITE NAT KEEPALIVE FILTER */
#define GAN_LITE_NAT_KEEPALIVE_FILTER
#endif /* CONFIG_WLAN_REGION_CODE == 101 */
#if (CONFIG_WLAN_REGION_CODE == 150) /* EUR FD(DualSIM) */
#define SUPPORT_MULTIPLE_BOARD_REV_FROM_HW
#endif /* CONFIG_WLAN_REGION_CODE == 150 */
#endif /* CONFIG_WLAN_REGION_CODE >= 100 && CONFIG_WLAN_REGION_CODE < 200 */

#if defined(CONFIG_V1A) || defined(CONFIG_V2A) || defined(CONFIG_MACH_VIENNAEUR)
#define SUPPORT_MULTIPLE_CHIPS
#endif /* CONFIG_V1A || CONFIG_V2A || CONFIG_MACH_VIENNAEUR */

#if (CONFIG_WLAN_REGION_CODE >= 200) && (CONFIG_WLAN_REGION_CODE < 300) /* KOR */
#undef USE_INITIAL_2G_SCAN
#ifndef ROAM_ENABLE
#define ROAM_ENABLE
#endif /* ROAM_ENABLE */
#ifndef ROAM_API
#define ROAM_API
#endif /* ROAM_API */
#ifndef ROAM_CHANNEL_CACHE
#define ROAM_CHANNEL_CACHE
#endif /* ROAM_CHANNEL_CACHE */
#ifndef OKC_SUPPORT
#define OKC_SUPPORT
#endif /* OKC_SUPPORT */

#ifndef ROAM_AP_ENV_DETECTION
#define ROAM_AP_ENV_DETECTION
#endif /* ROAM_AP_ENV_DETECTION */

#undef WRITE_MACADDR
#ifndef READ_MACADDR
#define READ_MACADDR
#endif /* READ_MACADDR */

#if (CONFIG_WLAN_REGION_CODE == 201) /* SKT */
#ifdef CONFIG_MACH_UNIVERSAL5410
/* Make CPU core clock 300MHz & assign dpc thread workqueue to CPU1 */
#define FIX_CPU_MIN_CLOCK
#endif /* CONFIG_MACH_UNIVERSAL5410 */
#endif /* CONFIG_WLAN_REGION_CODE == 201 */

#if (CONFIG_WLAN_REGION_CODE == 202) /* KTT */
#define VLAN_MODE_OFF
#define FULL_ROAMING_SCAN_PERIOD_60_SEC

#ifdef CONFIG_MACH_UNIVERSAL5410
/* Make CPU core clock 300MHz & assign dpc thread workqueue to CPU1 */
#define FIX_CPU_MIN_CLOCK
#endif /* CONFIG_MACH_UNIVERSAL5410 */
#endif /* CONFIG_WLAN_REGION_CODE == 202 */

#if (CONFIG_WLAN_REGION_CODE == 203) /* LGT */
#ifdef CONFIG_MACH_UNIVERSAL5410
/* Make CPU core clock 300MHz & assign dpc thread workqueue to CPU1 */
#define FIX_CPU_MIN_CLOCK
#define FIX_BUS_MIN_CLOCK
#endif /* CONFIG_MACH_UNIVERSAL5410 */
#endif /* CONFIG_WLAN_REGION_CODE == 203 */
#endif /* CONFIG_WLAN_REGION_CODE >= 200 && CONFIG_WLAN_REGION_CODE < 300 */

#if (CONFIG_WLAN_REGION_CODE >= 300) && (CONFIG_WLAN_REGION_CODE < 400) /* CHN */
#define BCMWAPI_WPI
#define BCMWAPI_WAI
#endif /* CONFIG_WLAN_REGION_CODE >= 300 && CONFIG_WLAN_REGION_CODE < 400 */

#if (CONFIG_WLAN_REGION_CODE == 402) /* TMO */
#undef CUSTOM_SUSPEND_BCN_LI_DTIM
#define CUSTOM_SUSPEND_BCN_LI_DTIM 3
#endif /* CONFIG_WLAN_REGION_CODE == 402 */

#if (CONFIG_WLAN_REGION_CODE == 500) /* JP */
#if defined(BCM4375_CHIP)
#define DISABLE_HE_ENAB
#endif /* BCM4375_CHIP */
#endif /* CONFIG_WLAN_REGION_CODE == 500 */

/* REGION CODE END */

#if !defined(READ_MACADDR) && !defined(WRITE_MACADDR)
#define GET_MAC_FROM_OTP
#define SHOW_NVRAM_TYPE
#endif /* !READ_MACADDR && !WRITE_MACADDR */

#define WRITE_WLANINFO

#if defined(CONFIG_MACH_KONA)
#define DISABLE_FLOW_CONTROL
#endif /* CONFIG_MACH_KONA */

#endif /* _dhd_sec_feature_h_ */
