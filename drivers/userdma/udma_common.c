/******************************************************************************
 Copyright (C) 2018 NDR Opensource Group

 Licensed under the several legal conditions.
 See 'License' in the project root for legal information.
******************************************************************************/

#include "udma_common.h"

// static int udma_dev_hugepg_init(struct udma_dev *udev)
// {
// 	int i, err = 0;

// 	if (!udev || !udev->hugepg_count || udev->hugepg_list) {
// 		pr_err("hugepg init args invalid\n");
// 		err = -EINVAL;
// 		goto err_out;
// 	}

// 	udev->hugepg_list = kcalloc(udev->hugepg_count, sizeof(struct page *), GFP_KERNEL);
// 	if (!udev->hugepg_list)
// 	{
// 		pr_err("allocate hugepg list failed\n");
// 		err = -ENOMEM;
// 		goto err_out;
// 	}

// 	for (i = 0; i < udev->hugepg_count; i++) {
// 		udev->hugepg_list[i] = udma_hugepg_alloc(udev->numa_node, udev->hugepg_order);
// 		if ( !udev->hugepg_list[i] ) {
// 			pr_err("allocate hugepg idx=%d failed\n", i);
// 			err = -ENOMEM;
// 			goto err_out_reclaim_hugepg;
// 		}
// 	}

// 	return 0;

// err_out:
// 	return err;

// err_out_reclaim_hugepg:
// 	for ( i -= 1; i >= 0; i-- ) {

// 	}
// 	goto err_out;

// }

struct udma_dev * udma_dev_alloc(struct pci_dev *pdev, uint32_t priv_size, uint32_t max_rxq, uint32_t max_txq)
{
	struct udma_dev *udev = NULL;
	int i;

	if (!pdev || !max_rxq || !max_txq) {
		pr_err("allocate udma_dev arg invalid\n");
		goto err_out;
	}

	udev = kzalloc(sizeof(struct udma_dev), GFP_KERNEL);
	if (!udev) {
		pr_err("allocate udma_dev failed\n");
		goto err_out;
	}

	strlcpy(udev->pcibus, pci_name(pdev), UDMA_PREDEF_STRSIZE);
	strlcpy(udev->driver, pdev->driver->name, UDMA_PREDEF_STRSIZE);
	udev->numa_node = pdev->dev.numa_node;

	if (priv_size) {
		udev->priv = kzalloc(priv_size, GFP_KERNEL);
		if (!udev->priv) {
			pr_err("allocate udma_dev private failed\n");
			goto err_after_udma_alloc;
		}
		udev->priv_size = priv_size;
	}

	udev->max_rxq_num = max_rxq;
	udev->max_txq_num = max_txq;

	for (i = 0; i < udev->max_rxq_num; i++) {
		unsigned int qidx = i / UDMA_PREDEF_DEVQBIT;
		unsigned int qbit = i % UDMA_PREDEF_DEVQBIT;
		ndrte_atomic64_bset(&udev->busy_rxq_map[qidx], qbit);
	}

	for (i = 0; i < udev->max_txq_num; i++) {
		unsigned int qidx = i / UDMA_PREDEF_DEVQBIT;
		unsigned int qbit = i % UDMA_PREDEF_DEVQBIT;
		ndrte_atomic64_bset(&udev->busy_txq_map[qidx], qbit);
	}

	udev->hugepg_count = udev->max_rxq_num + udev->max_txq_num;
	udev->hugepg_order = HUGETLB_PAGE_ORDER;

	return udev;

err_after_udma_alloc:
	kfree(udev);
err_out:
	return NULL;
}

void udma_dev_free(struct udma_dev *udev)
{
	int i;

	if (!udev)
		goto err_out;

	for (i = 0; i < udev->max_rxq_num; i++) {
		unsigned int qidx = i / UDMA_PREDEF_DEVQBIT;
		unsigned int qbit = i % UDMA_PREDEF_DEVQBIT;
		ndrte_atomic64_bset(&udev->busy_rxq_map[qidx], qbit);
	}

	for (i = 0; i < udev->max_txq_num; i++) {
		unsigned int qidx = i / UDMA_PREDEF_DEVQBIT;
		unsigned int qbit = i % UDMA_PREDEF_DEVQBIT;
		ndrte_atomic64_bset(&udev->busy_txq_map[qidx], qbit);
	}

	if (udev->priv)
		kfree(udev->priv);

err_after_udev_resolv:
	kfree(udev);
err_out:
	return;
}