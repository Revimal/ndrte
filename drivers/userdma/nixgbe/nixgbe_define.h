/*******************************************************************************
 Copyright (C) 1999 - 2018 Intel Corporation.
 Copyright (C) 2006 - 2007 Myricom, Inc. for some LRO specific code
 Copyright (C) 2018 NDR Opensource Group

 Licensed under the several legal conditions.
 See 'License' in the project root for legal information.
******************************************************************************/

#ifndef NDR_IXGBE_DEFINE_H
#define NDR_IXGBE_DEFINE_H

#include "ndrte_compiler_common.h"
#include "ndrte_arch_common.h"
#include "ndrte_arch_atomic.h"
#include "nixgbe_kcompat.h"
#include "drv_common.h"
#include "udma_common.h"

#define IXGBE_INTEL_VENDOR_ID			0x8086

/* Device IDs */
#define IXGBE_DEV_ID_82598			0x10B6
#define IXGBE_DEV_ID_82598_BX			0x1508
#define IXGBE_DEV_ID_82598AF_DUAL_PORT		0x10C6
#define IXGBE_DEV_ID_82598AF_SINGLE_PORT	0x10C7
#define IXGBE_DEV_ID_82598AT			0x10C8
#define IXGBE_DEV_ID_82598AT2			0x150B
#define IXGBE_DEV_ID_82598EB_SFP_LOM		0x10DB
#define IXGBE_DEV_ID_82598EB_CX4		0x10DD
#define IXGBE_DEV_ID_82598_CX4_DUAL_PORT	0x10EC
#define IXGBE_DEV_ID_82598_DA_DUAL_PORT		0x10F1
#define IXGBE_DEV_ID_82598_SR_DUAL_PORT_EM	0x10E1
#define IXGBE_DEV_ID_82598EB_XF_LR		0x10F4
#define IXGBE_DEV_ID_82599_KX4			0x10F7
#define IXGBE_DEV_ID_82599_KX4_MEZZ		0x1514
#define IXGBE_DEV_ID_82599_KR			0x1517
#define IXGBE_DEV_ID_82599_COMBO_BACKPLANE	0x10F8
#define IXGBE_SUBDEV_ID_82599_KX4_KR_MEZZ	0x000C
#define IXGBE_DEV_ID_82599_CX4			0x10F9
#define IXGBE_DEV_ID_82599_SFP			0x10FB
#define IXGBE_SUBDEV_ID_82599_SFP		0x11A9
#define IXGBE_SUBDEV_ID_82599_SFP_WOL0		0x1071
#define IXGBE_SUBDEV_ID_82599_RNDC		0x1F72
#define IXGBE_SUBDEV_ID_82599_560FLR		0x17D0
#define IXGBE_SUBDEV_ID_82599_ECNA_DP		0x0470
#define IXGBE_SUBDEV_ID_82599_SP_560FLR		0x211B
#define IXGBE_SUBDEV_ID_82599_LOM_SNAP6		0x2159
#define IXGBE_SUBDEV_ID_82599_SFP_1OCP		0x000D
#define IXGBE_SUBDEV_ID_82599_SFP_2OCP		0x0008
#define IXGBE_SUBDEV_ID_82599_SFP_LOM_OEM1	0x8976
#define IXGBE_SUBDEV_ID_82599_SFP_LOM_OEM2	0x06EE
#define IXGBE_DEV_ID_82599_BACKPLANE_FCOE	0x152A
#define IXGBE_DEV_ID_82599_SFP_FCOE		0x1529
#define IXGBE_DEV_ID_82599_SFP_EM		0x1507
#define IXGBE_DEV_ID_82599_SFP_SF2		0x154D
#define IXGBE_DEV_ID_82599_SFP_SF_QP		0x154A
#define IXGBE_DEV_ID_82599_QSFP_SF_QP		0x1558
#define IXGBE_DEV_ID_82599EN_SFP		0x1557
#define IXGBE_SUBDEV_ID_82599EN_SFP_OCP1	0x0001
#define IXGBE_DEV_ID_82599_XAUI_LOM		0x10FC
#define IXGBE_DEV_ID_82599_T3_LOM		0x151C
#define IXGBE_DEV_ID_82599_LS			0x154F
#define IXGBE_DEV_ID_X540T			0x1528
#define IXGBE_DEV_ID_X540T1			0x1560
#define IXGBE_DEV_ID_X550T			0x1563
#define IXGBE_DEV_ID_X550T1			0x15D1
/* Placeholder value, pending official value. */
#define IXGBE_DEV_ID_X550EM_A_KR		0x15C2
#define IXGBE_DEV_ID_X550EM_A_KR_L		0x15C3
#define IXGBE_DEV_ID_X550EM_A_SFP_N		0x15C4
#define IXGBE_DEV_ID_X550EM_A_SGMII		0x15C6
#define IXGBE_DEV_ID_X550EM_A_SGMII_L		0x15C7
#define IXGBE_DEV_ID_X550EM_A_10G_T		0x15C8
#define IXGBE_DEV_ID_X550EM_A_QSFP		0x15CA
#define IXGBE_DEV_ID_X550EM_A_QSFP_N		0x15CC
#define IXGBE_DEV_ID_X550EM_A_SFP		0x15CE
#define IXGBE_DEV_ID_X550EM_A_1G_T		0x15E4
#define IXGBE_DEV_ID_X550EM_A_1G_T_L		0x15E5
#define IXGBE_DEV_ID_X550EM_X_KX4		0x15AA
#define IXGBE_DEV_ID_X550EM_X_KR		0x15AB
#define IXGBE_DEV_ID_X550EM_X_SFP		0x15AC
#define IXGBE_DEV_ID_X550EM_X_10G_T		0x15AD
#define IXGBE_DEV_ID_X550EM_X_1G_T		0x15AE
#define IXGBE_DEV_ID_X550EM_X_XFI		0x15B0

/* Error Codes */
#define IXGBE_SUCCESS				0
#define IXGBE_ERR_EEPROM			-1
#define IXGBE_ERR_EEPROM_CHECKSUM		-2
#define IXGBE_ERR_PHY				-3
#define IXGBE_ERR_CONFIG			-4
#define IXGBE_ERR_PARAM				-5
#define IXGBE_ERR_MAC_TYPE			-6
#define IXGBE_ERR_UNKNOWN_PHY			-7
#define IXGBE_ERR_LINK_SETUP			-8
#define IXGBE_ERR_ADAPTER_STOPPED		-9
#define IXGBE_ERR_INVALID_MAC_ADDR		-10
#define IXGBE_ERR_DEVICE_NOT_SUPPORTED		-11
#define IXGBE_ERR_MASTER_REQUESTS_PENDING	-12
#define IXGBE_ERR_INVALID_LINK_SETTINGS		-13
#define IXGBE_ERR_AUTONEG_NOT_COMPLETE		-14
#define IXGBE_ERR_RESET_FAILED			-15
#define IXGBE_ERR_SWFW_SYNC			-16
#define IXGBE_ERR_PHY_ADDR_INVALID		-17
#define IXGBE_ERR_I2C				-18
#define IXGBE_ERR_SFP_NOT_SUPPORTED		-19
#define IXGBE_ERR_SFP_NOT_PRESENT		-20
#define IXGBE_ERR_SFP_NO_INIT_SEQ_PRESENT	-21
#define IXGBE_ERR_NO_SAN_ADDR_PTR		-22
#define IXGBE_ERR_FDIR_REINIT_FAILED		-23
#define IXGBE_ERR_EEPROM_VERSION		-24
#define IXGBE_ERR_NO_SPACE			-25
#define IXGBE_ERR_OVERTEMP			-26
#define IXGBE_ERR_FC_NOT_NEGOTIATED		-27
#define IXGBE_ERR_FC_NOT_SUPPORTED		-28
#define IXGBE_ERR_SFP_SETUP_NOT_COMPLETE	-30
#define IXGBE_ERR_PBA_SECTION			-31
#define IXGBE_ERR_INVALID_ARGUMENT		-32
#define IXGBE_ERR_HOST_INTERFACE_COMMAND	-33
#define IXGBE_ERR_OUT_OF_MEM			-34
#define IXGBE_ERR_FEATURE_NOT_SUPPORTED		-36
#define IXGBE_ERR_EEPROM_PROTECTED_REGION	-37
#define IXGBE_ERR_FDIR_CMD_INCOMPLETE		-38
#define IXGBE_ERR_FW_RESP_INVALID		-39
#define IXGBE_ERR_TOKEN_RETRY			-40

#define IXGBE_NOT_IMPLEMENTED			0x7FFFFFFF

/* Registers - Errcode */
#define IXGBE_DEAD_READ_RETRIES 10
#define IXGBE_DEAD_READ_REG 0xdeadbeefU
#define IXGBE_FAILED_READ_REG 0xffffffffU
#define IXGBE_FAILED_READ_CFG_DWORD 0xffffffffU
#define IXGBE_FAILED_READ_CFG_WORD 0xffffU
#define IXGBE_FAILED_READ_CFG_BYTE 0xffU

/* General Registers */
#define IXGBE_CTRL		0x00000
#define IXGBE_STATUS		0x00008
#define IXGBE_CTRL_EXT		0x00018
#define IXGBE_ESDP		0x00020
#define IXGBE_EODSDP		0x00028
#define IXGBE_I2CCTL_82599	0x00028
#define IXGBE_I2CCTL		IXGBE_I2CCTL_82599
#define IXGBE_I2CCTL_X540	IXGBE_I2CCTL_82599
#define IXGBE_I2CCTL_X550	0x15F5C
#define IXGBE_I2CCTL_X550EM_x	IXGBE_I2CCTL_X550
#define IXGBE_I2CCTL_X550EM_a	IXGBE_I2CCTL_X550
#define IXGBE_I2CCTL_BY_MAC(_hw) IXGBE_BY_MAC((_hw), I2CCTL)
#define IXGBE_PHY_GPIO		0x00028
#define IXGBE_MAC_GPIO		0x00030
#define IXGBE_PHYINT_STATUS0	0x00100
#define IXGBE_PHYINT_STATUS1	0x00104
#define IXGBE_PHYINT_STATUS2	0x00108
#define IXGBE_LEDCTL		0x00200
#define IXGBE_FRTIMER		0x00048
#define IXGBE_TCPTIMER		0x0004C
#define IXGBE_CORESPARE		0x00600
#define IXGBE_EXVET		0x05078

/* Registers - DCA */
#define IXGBE_DCA_ID		0x11070
#define IXGBE_DCA_CTRL		0x11074

#define IXGBE_MAX_RSS_INDICES		16
#define IXGBE_MAX_RSS_INDICES_X550	63
#define IXGBE_MAX_FDIR_INDICES		63
#define MAX_RX_QUEUES	(IXGBE_MAX_FDIR_INDICES + 1)
#define MAX_TX_QUEUES	(IXGBE_MAX_FDIR_INDICES + 1)

#define IXGBE_FLAGS_ENABLED(flags, bit) \
	(ndrte_atomic64_btest((flags), IXGBE_FLAGBIT_ ## bit))
#define IXGBE_FLAGS_SET(flags, bit) \
	(ndrte_atomic64_bset((flags), IXGBE_FLAGBIT_ ## bit))
#define IXGBE_FLAGS_UNSET(flags, bit) \
	(ndrte_atomic64_bclear((flags), IXGBE_FLAGBIT_ ## bit))
#define IXGBE_FLAGS_CONV(flags, bit) \
	(ndrte_atomic64_bxchg((flags), IXGBE_FLAGBIT_ ## bit))
#define IXGBE_FLAGS_TESTSET(flags, bit) \
	(ndrte_atomic64_btestset((flags), IXGBE_FLAGBIT_ ## bit))
#define IXGBE_FLAGS_TESTUNSET(flags, bit) \
	(ndrte_atomic64_btestclear((flags), IXGBE_FLAGBIT_ ## bit))
#define IXGBE_FLAGS_TESTCONV(flags, bit) \
	(ndrte_atomic64_btestxchg((flags), IXGBE_FLAGBIT_ ## bit))

#define IXGBE_STATE_ENABLED(state, bit) \
	(ndrte_atomic64_btest((state), IXGBE_STATEBIT_ ## bit))
#define IXGBE_STATE_SET(state, bit) \
	(ndrte_atomic64_bset((state), IXGBE_STATEBIT_ ## bit))
#define IXGBE_STATE_UNSET(state, bit) \
	(ndrte_atomic64_bclear((state), IXGBE_STATEBIT_ ## bit))
#define IXGBE_STATE_CONV(state, bit) \
	(ndrte_atomic64_bxchg((state), IXGBE_STATEBIT_ ## bit))
#define IXGBE_STATE_TESTSET(state, bit) \
	(ndrte_atomic64_btestset((state), IXGBE_STATEBIT_ ## bit))
#define IXGBE_STATE_TESTUNSET(state, bit) \
	(ndrte_atomic64_btestclear((state), IXGBE_STATEBIT_ ## bit))
#define IXGBE_STATE_TESTCONV(state, bit) \
	(ndrte_atomic64_btestxchg((state), IXGBE_STATEBIT_ ## bit))

enum ixgbe_mac_type {
	ixgbe_mac_unknown = 0,
	ixgbe_mac_82598EB,
	ixgbe_mac_82599EB,
	ixgbe_mac_X540,
	ixgbe_mac_X550,
	ixgbe_mac_X550EM_x,
	ixgbe_mac_X550EM_a,
	ixgbe_num_macs
};

enum ixgbe_phy_type {
	ixgbe_phy_unknown = 0,
	ixgbe_phy_none,
	ixgbe_phy_tn,
	ixgbe_phy_aq,
	ixgbe_phy_x550em_kr,
	ixgbe_phy_x550em_kx4,
	ixgbe_phy_x550em_xfi,
	ixgbe_phy_x550em_ext_t,
	ixgbe_phy_ext_1g_t,
	ixgbe_phy_cu_unknown,
	ixgbe_phy_qt,
	ixgbe_phy_xaui,
	ixgbe_phy_nl,
	ixgbe_phy_sfp_passive_tyco,
	ixgbe_phy_sfp_passive_unknown,
	ixgbe_phy_sfp_active_unknown,
	ixgbe_phy_sfp_avago,
	ixgbe_phy_sfp_ftl,
	ixgbe_phy_sfp_ftl_active,
	ixgbe_phy_sfp_unknown,
	ixgbe_phy_sfp_intel,
	ixgbe_phy_qsfp_passive_unknown,
	ixgbe_phy_qsfp_active_unknown,
	ixgbe_phy_qsfp_intel,
	ixgbe_phy_qsfp_unknown,
	ixgbe_phy_sfp_unsupported, /*Enforce bit set with unsupported module*/
	ixgbe_phy_sgmii,
	ixgbe_phy_fw,
	ixgbe_phy_generic
};
/*
 * SFP+ module type IDs:
 *
 * ID	Module Type
 * =============
 * 0	SFP_DA_CU
 * 1	SFP_SR
 * 2	SFP_LR
 * 3	SFP_DA_CU_CORE0 - 82599-specific
 * 4	SFP_DA_CU_CORE1 - 82599-specific
 * 5	SFP_SR/LR_CORE0 - 82599-specific
 * 6	SFP_SR/LR_CORE1 - 82599-specific
 */
enum ixgbe_sfp_type {
	ixgbe_sfp_type_da_cu = 0,
	ixgbe_sfp_type_sr = 1,
	ixgbe_sfp_type_lr = 2,
	ixgbe_sfp_type_da_cu_core0 = 3,
	ixgbe_sfp_type_da_cu_core1 = 4,
	ixgbe_sfp_type_srlr_core0 = 5,
	ixgbe_sfp_type_srlr_core1 = 6,
	ixgbe_sfp_type_da_act_lmt_core0 = 7,
	ixgbe_sfp_type_da_act_lmt_core1 = 8,
	ixgbe_sfp_type_1g_cu_core0 = 9,
	ixgbe_sfp_type_1g_cu_core1 = 10,
	ixgbe_sfp_type_1g_sx_core0 = 11,
	ixgbe_sfp_type_1g_sx_core1 = 12,
	ixgbe_sfp_type_1g_lx_core0 = 13,
	ixgbe_sfp_type_1g_lx_core1 = 14,
	ixgbe_sfp_type_not_present = 0xFFFE,
	ixgbe_sfp_type_unknown = 0xFFFF
};

enum ixgbe_media_type {
	ixgbe_media_type_unknown = 0,
	ixgbe_media_type_fiber,
	ixgbe_media_type_fiber_qsfp,
	ixgbe_media_type_fiber_lco,
	ixgbe_media_type_copper,
	ixgbe_media_type_backplane,
	ixgbe_media_type_cx4,
	ixgbe_media_type_virtual
};

/* Smart Speed Settings */
#define IXGBE_SMARTSPEED_MAX_RETRIES	3
enum ixgbe_smart_speed {
	ixgbe_smart_speed_auto = 0,
	ixgbe_smart_speed_on,
	ixgbe_smart_speed_off
};

struct ixgbe_phy_info {
	// struct ixgbe_phy_operations ops;
	enum ixgbe_phy_type type;
	uint32_t addr;
	uint32_t id;
	enum ixgbe_sfp_type sfp_type;
	int sfp_setup_needed;
	uint32_t revision;
	enum ixgbe_media_type media_type;
	uint32_t phy_semaphore_mask;
	int reset_disable;
	uint32_t autoneg_advertised;
	uint32_t speeds_supported;
	uint32_t eee_speeds_supported;
	uint32_t eee_speeds_advertised;
	enum ixgbe_smart_speed smart_speed;
	int smart_speed_active;
	int multispeed_fiber;
	int reset_if_overtemp;
	int qsfp_shared_i2c_bus;
	uint32_t nw_mng_if_sel;
};

enum ixgbe_statebit_t {
	IXGBE_STATEBIT_TESTING,
	IXGBE_STATEBIT_RESETTING,
	IXGBE_STATEBIT_DOWN,
	IXGBE_STATEBIT_DISABLED,
	IXGBE_STATEBIT_REMOVE,
	IXGBE_STATEBIT_SERVICE_SCHED,
	IXGBE_STATEBIT_SERVICE_INITED,
	IXGBE_STATEBIT_IN_SFP_INIT,
#ifdef HAVE_PTP_1588_CLOCK
	IXGBE_STATEBIT_PTP_RUNNING,
	IXGBE_STATEBIT_PTP_TX_IN_PROGRESS,
#endif
	IXGBE_STATEBIT_RESET_REQUESTED,
};

struct ixgbe_hw {
	phys_addr_t pci_start;
	unsigned long pci_len;
	uint8_t __iomem *pci_addr;

	struct ixgbe_adapter *back;

	struct ixgbe_phy_info phy;

	uint16_t device_id;
	uint16_t vendor_id;
	uint16_t subsystem_device_id;
	uint16_t subsystem_vendor_id;
	uint8_t revision_id;
	uint8_t adapter_stopped;
	int api_version;
};

enum ixgbe_flagbit_t {
	IXGBE_FLAGBIT_DCA_CAPABLE,
	IXGBE_FLAGBIT_DCA_ENABLED,
};

struct ixgbe_adapter {
	struct udma_dev *udev;
	struct pci_dev *pdev;
	unsigned int indices;
	struct ixgbe_hw hw;
	ndrte_atomic64_t state;
	ndrte_atomic64_t flags;

	phys_addr_t dma_start;
	unsigned long dma_len;
	uint8_t __iomem *pkt_addr;

} NDRTE_ALIGN(NDRTE_ARCH_CACHELINE);

#endif
