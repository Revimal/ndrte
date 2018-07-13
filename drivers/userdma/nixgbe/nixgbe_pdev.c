/******************************************************************************
 Copyright (C) 2018 NDR Opensource Group

 Licensed under the several legal conditions.
 See 'License' in the project root for legal information.
******************************************************************************/

#include "nixgbe_pdev.h"

void ixgbe_remove_adapter(struct ixgbe_hw *hw)
{
	if (!hw->pci_addr)
		return;
	NDRTE_ACCESS_ONCE(hw->pci_addr) = NULL;
	dev_err(pci_dev_to_dev(hw->back->pdev),
		"Adapter removed\n");
}

static void ixgbe_check_status_read(struct ixgbe_hw *hw, uint32_t reg)
{
	uint32_t value;

	if (reg == IXGBE_STATUS) {
		ixgbe_remove_adapter(hw);
		return;
	}
	value = IXGBE_READ_REG(hw, IXGBE_STATUS);
	if (value == IXGBE_FAILED_READ_REG)
		ixgbe_remove_adapter(hw);
}

static uint32_t
ixgbe_validate_register_read(struct ixgbe_hw *hw, uint32_t reg)
{
	int i;
	uint32_t value;
	uint8_t __iomem *pci_addr;

	pci_addr = NDRTE_ACCESS_ONCE(hw->pci_addr);
	if (IXGBE_REMOVED(pci_addr))
		return IXGBE_FAILED_READ_REG;
	for (i = 0; i < IXGBE_DEAD_READ_RETRIES; ++i) {
		value = readl(pci_addr + reg);
		if (value != IXGBE_DEAD_READ_REG)
			break;
	}

	if (value == IXGBE_DEAD_READ_REG)
		dev_err(pci_dev_to_dev(hw->back->pdev),
			"register %x read unchanged\n", reg);
	else
		dev_warn(pci_dev_to_dev(hw->back->pdev),
			"register %x read recovered after %d retries\n", reg, i + 1);
	return value;
}

uint32_t ixgbe_read_reg(struct ixgbe_hw *hw, uint32_t reg)
{
	uint32_t value;
	uint8_t __iomem *pci_addr;

	pci_addr = NDRTE_ACCESS_ONCE(hw->pci_addr);
	if (IXGBE_REMOVED(pci_addr))
		return IXGBE_FAILED_READ_REG;

	value = readl(pci_addr + reg);
	if (unlikely(value == IXGBE_FAILED_READ_REG))
		ixgbe_check_status_read(hw, reg);
	if (unlikely(value == IXGBE_DEAD_READ_REG))
		value = ixgbe_validate_register_read(hw, reg);

	return value;
}

enum ixgbe_mac_type ixgbe_set_mac_type(int dev_id)
{
	enum ixgbe_mac_type ret = ixgbe_mac_unknown;

	switch (dev_id) {
	case IXGBE_DEV_ID_82598:
	case IXGBE_DEV_ID_82598_BX:
	case IXGBE_DEV_ID_82598AF_SINGLE_PORT:
	case IXGBE_DEV_ID_82598AF_DUAL_PORT:
	case IXGBE_DEV_ID_82598AT:
	case IXGBE_DEV_ID_82598AT2:
	case IXGBE_DEV_ID_82598EB_CX4:
	case IXGBE_DEV_ID_82598_CX4_DUAL_PORT:
	case IXGBE_DEV_ID_82598_DA_DUAL_PORT:
	case IXGBE_DEV_ID_82598_SR_DUAL_PORT_EM:
	case IXGBE_DEV_ID_82598EB_XF_LR:
	case IXGBE_DEV_ID_82598EB_SFP_LOM:
		ret = ixgbe_mac_82598EB;
		break;
	case IXGBE_DEV_ID_82599_KX4:
	case IXGBE_DEV_ID_82599_KX4_MEZZ:
	case IXGBE_DEV_ID_82599_XAUI_LOM:
	case IXGBE_DEV_ID_82599_COMBO_BACKPLANE:
	case IXGBE_DEV_ID_82599_KR:
	case IXGBE_DEV_ID_82599_SFP:
	case IXGBE_DEV_ID_82599_BACKPLANE_FCOE:
	case IXGBE_DEV_ID_82599_SFP_FCOE:
	case IXGBE_DEV_ID_82599_SFP_EM:
	case IXGBE_DEV_ID_82599_SFP_SF2:
	case IXGBE_DEV_ID_82599_SFP_SF_QP:
	case IXGBE_DEV_ID_82599_QSFP_SF_QP:
	case IXGBE_DEV_ID_82599EN_SFP:
	case IXGBE_DEV_ID_82599_CX4:
	case IXGBE_DEV_ID_82599_LS:
	case IXGBE_DEV_ID_82599_T3_LOM:
		ret = ixgbe_mac_82599EB;
		break;
	case IXGBE_DEV_ID_X540T:
	case IXGBE_DEV_ID_X540T1:
		ret = ixgbe_mac_X540;
		break;
	case IXGBE_DEV_ID_X550T:
	case IXGBE_DEV_ID_X550T1:
		ret = ixgbe_mac_X550;
		break;
	case IXGBE_DEV_ID_X550EM_X_KX4:
	case IXGBE_DEV_ID_X550EM_X_KR:
	case IXGBE_DEV_ID_X550EM_X_10G_T:
	case IXGBE_DEV_ID_X550EM_X_1G_T:
	case IXGBE_DEV_ID_X550EM_X_SFP:
	case IXGBE_DEV_ID_X550EM_X_XFI:
		ret = ixgbe_mac_X550EM_x;
		break;
	case IXGBE_DEV_ID_X550EM_A_KR:
	case IXGBE_DEV_ID_X550EM_A_KR_L:
	case IXGBE_DEV_ID_X550EM_A_SFP_N:
	case IXGBE_DEV_ID_X550EM_A_SGMII:
	case IXGBE_DEV_ID_X550EM_A_SGMII_L:
	case IXGBE_DEV_ID_X550EM_A_1G_T:
	case IXGBE_DEV_ID_X550EM_A_1G_T_L:
	case IXGBE_DEV_ID_X550EM_A_10G_T:
	case IXGBE_DEV_ID_X550EM_A_QSFP:
	case IXGBE_DEV_ID_X550EM_A_QSFP_N:
	case IXGBE_DEV_ID_X550EM_A_SFP:
		ret = ixgbe_mac_X550EM_a;
		break;
	default:
		ret = ixgbe_mac_unknown;
		break;
	}

	return ret;
}

// static void ixgbe_get_hw_control(struct ixgbe_adapter *adapter)
// {
// 	u32 ctrl_ext;

// 	/* Let firmware know the driver has taken over */
// 	ctrl_ext = IXGBE_READ_REG(&adapter->hw, IXGBE_CTRL_EXT);
// 	IXGBE_WRITE_REG(&adapter->hw, IXGBE_CTRL_EXT,
// 			ctrl_ext | IXGBE_CTRL_EXT_DRV_LOAD);
// }

#ifdef HAVE_NON_CONST_PCI_DRIVER_NAME
int ixgbe_pci_init(struct pci_dev *pdev, char *ixgbe_driver_name)
#else
int ixgbe_pci_init(struct pci_dev *pdev, const char *ixgbe_driver_name)
#endif
{
	int err;
	enum ixgbe_mac_type mac_type = ixgbe_mac_unknown;

	err = pci_enable_device_mem(pdev);
	if (err)
		goto err_out;

	if (!dma_set_mask(pci_dev_to_dev(pdev), DMA_BIT_MASK(64)) &&
	    !dma_set_coherent_mask(pci_dev_to_dev(pdev), DMA_BIT_MASK(64))) {
		dev_info(pci_dev_to_dev(pdev),
			"PCI device will request HIGH DMA AREA");
	} else {
		err = dma_set_mask(pci_dev_to_dev(pdev), DMA_BIT_MASK(32));
		if (err) {
			err = dma_set_coherent_mask(pci_dev_to_dev(pdev),
						    DMA_BIT_MASK(32));
			if (err) {
				dev_err(pci_dev_to_dev(pdev), "No usable DMA "
					"configuration, aborting\n");
				goto err_after_pci_enable;
			}
		}
		dev_info(pci_dev_to_dev(pdev),
			"PCI device will request NORMAL DMA AREA");
	}

	err = pci_request_mem_regions(pdev, ixgbe_driver_name);
	if (err) {
		dev_err(pci_dev_to_dev(pdev),
			"pci_request_selected_regions failed 0x%x\n", err);
		goto err_after_pci_enable;
	}

	/*
	 * The mac_type is needed before we have the adapter is set up
	 * so rather than maintain two devID -> MAC tables we dummy up
	 * an ixgbe_hw stuct and use ixgbe_set_mac_type.
	 */
	mac_type = ixgbe_set_mac_type(pdev->device);

	/*
	 * Workaround of Silicon errata on 82598. Disable LOs in the PCI switch
	 * port to which the 82598 is connected to prevent duplicate
	 * completions caused by LOs.  We need the mac type so that we only
	 * do this on 82598 devices, ixgbe_set_mac_type does this for us if
	 * we set it's device ID.
	 */
	if (mac_type == ixgbe_mac_82598EB)
		pci_disable_link_state(pdev, PCIE_LINK_STATE_L0S);

	pci_set_master(pdev);

	return 0;

err_after_pci_enable:
	ixgbe_disable_pci(pdev, NULL);
err_out:
	return err;
}

void ixgbe_pci_uninit(struct pci_dev *pdev)
{
	pci_release_mem_regions(pdev);
	ixgbe_disable_pci(pdev, NULL);
}