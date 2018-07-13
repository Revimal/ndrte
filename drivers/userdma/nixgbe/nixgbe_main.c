/******************************************************************************
 Copyright (C) 2018 NDR Opensource Group

 Licensed under the several legal conditions.
 See 'License' in the project root for legal information.
******************************************************************************/

#include <linux/dca.h>

#include "nixgbe_define.h"
#include "nixgbe_pdev.h"

#define NIXGBE_MODULE_VER "1.0.0"
#define NIXGBE_MODULE_IVER "5.3.7" /* Intel Driver Base Version */
#define NIXGBE_MODULE_NAME "nixgbe"
#define NIXGBE_MODULE_DESC "NDR User-DMA driver for Intel(R) 10GbE PCIe NICs"
#define NIXGBE_MODULE_ORGDATE "1999 - 2018"
#define NIXGBE_MODULE_ORGAUTH "Intel Corporation"
#define NIXGBE_MODULE_ORGMAIL "<linux.nics@intel.com>"
#define NIXGBE_MODULE_ORGINFO "Based on Intel(R) 10GbE PCI Express Linux Network Driver"
#define NIXGBE_MODULE_LICENSE "GPL"

NDR_MODULE_COPYRIGHT(NIXGBE_MODULE_NAME);
MODULE_DESCRIPTION(NIXGBE_MODULE_DESC);
MODULE_VERSION(NIXGBE_MODULE_VER);

const char ixgbe_driver_orgver[] = NIXGBE_MODULE_IVER;
const char ixgbe_driver_version[] = NIXGBE_MODULE_VER "-ixgbe+" NIXGBE_MODULE_IVER;
#ifdef HAVE_NON_CONST_PCI_DRIVER_NAME
char ixgbe_driver_name[] = NIXGBE_MODULE_NAME;
#else
const char ixgbe_driver_name[] = NIXGBE_MODULE_NAME;
#endif
static const char ixgbe_driver_orginfo[] = NIXGBE_MODULE_ORGINFO;
static const char ixgbe_driver_string[] = NIXGBE_MODULE_DESC;
static const char ixgbe_orgright[] = "Copyright (c) " NIXGBE_MODULE_ORGDATE " " NIXGBE_MODULE_ORGAUTH;
static const char ixgbe_copyright[] = "Copyright (c) " NDR_MODULE_DATE " " NDR_MODULE_AUTHOR;
static const char ixgbe_overheat_msg[] =
		"Network adapter has been stopped because it has over heated. "
		"Restart the computer. If the problem persists, "
		"power off the system and replace the adapter";

static int __devinit ixgbe_probe(struct pci_dev *pdev,
				 const struct pci_device_id __always_unused *ent)
{
	struct udma_dev *udev = NULL;
	struct ixgbe_adapter *adapter = NULL;
	struct ixgbe_hw *hw = NULL;
	int err = 0, pci_using_dac = 0;
#ifdef HAVE_TX_MQ
	unsigned int indices = MAX_TX_QUEUES;
#endif /* HAVE_TX_MQ */
	bool disable_dev = false;

	dev_info(pci_dev_to_dev(pdev),
		"probing PCI device %s...", pci_name(pdev));

	err = ixgbe_pci_init(pdev, ixgbe_driver_name);
	if (err) {
		dev_err(pci_dev_to_dev(pdev),
			"ixgbe_pci_init failed 0x%x\n", err);
		goto err_out;
	}

	udev = udma_dev_alloc(pdev, sizeof(struct ixgbe_adapter), indices, indices);
	if (!udev) {
		dev_err(pci_dev_to_dev(pdev),
			"udma_dev_alloc failed 0x%x\n", err);
		err = -ENOMEM;
		goto err_after_pci_init;
	}

	adapter = udma_dev_priv(udev);
	adapter->udev = udev;
	adapter->pdev = pdev;
	adapter->indices = indices;
	hw = &adapter->hw;
	hw->back = adapter;
	hw->pci_start = pci_resource_start(pdev, 0);
	hw->pci_len = pci_resource_len(pdev, 0);
	hw->pci_addr = ioremap(hw->pci_start, hw->pci_len);
	if (!hw->pci_addr) {
		err = -EIO;
		goto err_after_udma_dev_alloc;
	}

	// err = ixgbe_hw_init(adapter);
	// if (err) {
	// 	dev_err(pci_dev_to_dev(pdev),
	// 		"ixgbe_hw_init failed 0x%x\n", err);
	// 	goto err_after_ioremap;
	// }

	// err = ixgbe_hw_check(adapter);
	// if (err) {
	// 	dev_err(pci_dev_to_dev(pdev),
	// 		"ixgbe_hw_check failed 0x%x\n", err);
	// 	goto err_after_hw_init;
	// }

	// err = ixgbe_sw_init(adapter);
	// if (err) {
	// 	dev_err(pci_dev_to_dev(pdev),
	// 		"ixgbe_sw_init failed 0x%x\n", err);
	// 	goto err_after_hw_init;
	// }

	// err = ixgbe_hw_sw_sync(adapter);
	// if (err) {
	// 	dev_err(pci_dev_to_dev(pdev),
	// 		"ixgbe_hw_sw_sync failed 0x%x\n", err);
	// 	goto err_after_sw_init;
	// }

	// err = udma_dev_register(udev, pdev, ixgbe_driver_name);
	// if (err) {
	// 	dev_err(pci_dev_to_dev(pdev),
	// 		"udma_dev_register failed 0x%x\n", err);
	// 	goto err_after_sw_init;
	// }

	pci_set_drvdata(pdev, adapter);

	return 0;

err_after_ioremap:
	iounmap(hw->pci_addr);
err_after_udma_dev_alloc:
	udma_dev_free(udev);
err_after_pci_init:
	ixgbe_pci_uninit(pdev);
err_out:
	return err;
}

static void __devexit ixgbe_remove(struct pci_dev *pdev)
{
	struct udma_dev *udev = NULL;
	struct ixgbe_adapter *adapter = NULL;
	struct ixgbe_hw *hw = NULL;

	if (!pdev)
		goto err_out;

	udev = pci_get_drvdata(pdev);
	if (!udev)
		goto err_after_pdev_resolv;

	adapter = udev->priv;
	if (!adapter)
		goto err_after_udev_resolv;

	hw = &adapter->hw;

	if (hw->pci_addr)
		iounmap(hw->pci_addr);

err_after_udev_resolv:
	udma_dev_free(udev);
err_after_pdev_resolv:
	ixgbe_pci_uninit(pdev);
err_out:
	return;
}

// #ifdef CONFIG_PM
// #ifndef USE_LEGACY_PM_SUPPORT
// static const struct dev_pm_ops ixgbe_pm_ops = {
// 	.suspend        = ixgbe_suspend,
// 	.resume         = ixgbe_resume,
// 	.freeze         = ixgbe_freeze,
// 	.thaw           = ixgbe_thaw,
// 	.poweroff       = ixgbe_suspend,
// 	.restore        = ixgbe_resume,
// };
// #endif /* USE_LEGACY_PM_SUPPORT */
// #endif

static struct pci_driver ixgbe_driver = {
	.name     = ixgbe_driver_name,
	.probe    = ixgbe_probe,
	.remove   = __devexit_p(ixgbe_remove),
// #ifdef CONFIG_PM
// #ifndef USE_LEGACY_PM_SUPPORT
// 	.driver = {
// 		.pm = &ixgbe_pm_ops,
// 	},
// #else
// 	.suspend  = ixgbe_suspend,
// 	.resume   = ixgbe_resume,
// #endif /* USE_LEGACY_PM_SUPPORT */
// #endif
// #ifndef USE_REBOOT_NOTIFIER
// 	.shutdown = ixgbe_shutdown,
// #endif
// #ifdef HAVE_PCI_ERS
// 	.err_handler = &ixgbe_err_handler
// #endif
};

#if IS_ENABLED(CONFIG_DCA)
static int __ixgbe_notify_dca(struct device *dev, void *data)
{
	struct ixgbe_adapter *adapter = dev_get_drvdata(dev);
	ndrte_atomic64_t *flags = &adapter->flags;
	unsigned long event = *(unsigned long *)data;

	if (!IXGBE_FLAGS_ENABLED(flags, DCA_CAPABLE))
		return 0;

	switch (event) {
	case DCA_PROVIDER_ADD:
		/* if we're already enabled, don't do it again */
		if (IXGBE_FLAGS_ENABLED(flags, DCA_ENABLED))
			break;
		if (dca_add_requester(dev) == IXGBE_SUCCESS) {
			IXGBE_FLAGS_SET(flags, DCA_ENABLED);
			IXGBE_WRITE_REG(&adapter->hw, IXGBE_DCA_CTRL, 2);
			break;
		}
		/* fall through - DCA is disabled */
	case DCA_PROVIDER_REMOVE:
		if (IXGBE_FLAGS_ENABLED(flags, DCA_ENABLED)) {
			dca_remove_requester(dev);
			IXGBE_FLAGS_UNSET(flags, DCA_ENABLED);
			IXGBE_WRITE_REG(&adapter->hw, IXGBE_DCA_CTRL, 1);
		}
		break;
	}

	return IXGBE_SUCCESS;
}

static int ixgbe_notify_dca(struct notifier_block __always_unused *nb, unsigned long event,
	void __always_unused *p)
{
	int ret_val;

	ret_val = driver_for_each_device(&ixgbe_driver.driver, NULL, &event,
		__ixgbe_notify_dca);

	return ret_val ? NOTIFY_BAD : NOTIFY_DONE;
}

static struct notifier_block dca_notifier = {
	.notifier_call	= ixgbe_notify_dca,
	.next		= NULL,
	.priority	= 0
};
#endif /* CONFIG_DCA */

static int __init ixgbe_init_module(void)
{
	int ret;
	pr_info("%s - version %s\n", ixgbe_driver_string, ixgbe_driver_version);
	pr_info("%s\n", ixgbe_orgright);
	pr_info("%s\n", ixgbe_copyright);
	pr_info("%s\n", ixgbe_driver_orginfo);

	ret = pci_register_driver( &ixgbe_driver );
	if (ret) {
		return ret;
	}

#if IS_ENABLED(CONFIG_DCA)
	dca_register_notify(&dca_notifier);
#endif

	return ret;
}

static void __exit ixgbe_exit_module(void)
{
#if IS_ENABLED(CONFIG_DCA)
	dca_unregister_notify(&dca_notifier);
#endif
	pci_unregister_driver(&ixgbe_driver);
}

module_init(ixgbe_init_module);
module_exit(ixgbe_exit_module);
