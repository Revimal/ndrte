/******************************************************************************
 Copyright (C) 2018 NDR Opensource Group

 Licensed under the several legal conditions.
 See 'License' in the project root for legal information.
******************************************************************************/

#ifndef NDR_IXGBE_PDEV_H
#define NDR_IXGBE_PDEV_H

#include "nixgbe_define.h"

#ifdef HAVE_NON_CONST_PCI_DRIVER_NAME
int ixgbe_pci_init(struct pci_dev *pdev, char *ixgbe_driver_name);
#else
int ixgbe_pci_init(struct pci_dev *pdev, const char *ixgbe_driver_name);
#endif
void ixgbe_pci_uninit(struct pci_dev *pdev);

void ixgbe_remove_adapter(struct ixgbe_hw *hw);
static inline int IXGBE_REMOVED(void __iomem *addr)
{
	return unlikely(!addr);
}

uint32_t ixgbe_read_reg(struct ixgbe_hw *hw, uint32_t reg);
#define IXGBE_READ_REG ixgbe_read_reg
static inline void IXGBE_WRITE_REG(struct ixgbe_hw *hw, uint32_t reg, uint32_t val)
{
	uint8_t __iomem *pci_addr = NDRTE_ACCESS_ONCE(hw->pci_addr);

	if (IXGBE_REMOVED(pci_addr))
		return;

	writel(val, pci_addr + reg);
}

static inline void ixgbe_disable_pci(struct pci_dev *pdev, struct ixgbe_adapter *adapter)
{
	if (!adapter || !!IXGBE_STATE_TESTSET(&adapter->state, DISABLED)) {
		pci_disable_device(pdev);
	}
}

#endif