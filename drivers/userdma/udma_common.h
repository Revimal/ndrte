/******************************************************************************
 Copyright (C) 2018 NDR Opensource Group

 Licensed under the several legal conditions.
 See 'License' in the project root for legal information.
******************************************************************************/

#ifndef NDR_UDMA_COMMON_H
#define NDR_UDMA_COMMON_H

#include "ndrte_compiler_common.h"
#include "ndrte_arch_common.h"
#include "ndrte_arch_atomic.h"
#include "drv_common.h"

#include "linux/fs.h"

#define UDMA_PREDEF_STRSIZE 32
#define UDMA_PREDEF_DEVQBIT 64
#define UDMA_PREDEF_DEVQSET 4

struct udma_fops_priv {
	struct udma_dev *back;

	int mapped_cpu_id;
	uint32_t udma_rxq_id;
	uint32_t udma_txq_id;
};

struct udma_dev {
	char pcibus[UDMA_PREDEF_STRSIZE];
	char driver[UDMA_PREDEF_STRSIZE];
	int numa_node;

	void *priv;
	uint32_t priv_size;

	uint32_t max_rxq_num;
	uint32_t max_txq_num;
	ndrte_atomic64_t busy_rxq_map[UDMA_PREDEF_DEVQSET];
	ndrte_atomic64_t busy_txq_map[UDMA_PREDEF_DEVQSET];

	struct page **hugepg_list;
	int hugepg_order;
	int hugepg_count;

	phys_addr_t dma_start;
	unsigned long dma_len;
	uint8_t __iomem *dma_addr;

	struct file_operations udma_fops;
	char const *ifname;

	// struct proc_dir_entry *udma_root_dir;

	// struct proc_dir_entry *udma_dev_pci;
	// struct proc_dir_entry *udma_dev_drv;
	// struct proc_dir_entry *udma_dev_numa;

	// struct proc_dir_entry *udma_dev_rxq;
	// struct proc_dir_entry *udma_dev_txq;

	// struct proc_dir_entry *udma_mmap_pktpool;
	// struct proc_dir_entry *udma_mmap_devreg;
	// struct proc_dir_entry *udma_mmap_rxq;
	// struct proc_dir_entry *udma_mmap_txq;

	// struct proc_dir_entry *udma_ent_rxq;
	// struct proc_dir_entry *udma_ent_txq;

	// ndrte_atomic64_t rx_success;
	// ndrte_atomic64_t tx_success;
	// ndrte_atomic64_t rx_drop;
	// ndrte_atomic64_t tx_drop;
	// ndrte_atomic64_t rx_missed;
	// ndrte_atomic64_t tx_missed;

	// struct proc_dir_entry *udma_rx_success;
	// struct proc_dir_entry *udma_tx_success;
	// struct proc_dir_entry *udma_rx_drop;
	// struct proc_dir_entry *udma_tx_drop;
	// struct proc_dir_entry *udma_rx_missed;
	// struct proc_dir_entry *udma_tx_missed;
} NDRTE_ALIGN(NDRTE_ARCH_CACHELINE);

struct udma_dev * udma_dev_alloc(struct pci_dev *pdev, uint32_t priv_size, uint32_t max_rxq, uint32_t max_txq);
void udma_dev_free(struct udma_dev *udev);

static inline void * udma_dev_priv(struct udma_dev *udev)
{
	if (udev && udev->priv_size)
		return udev->priv;
	return NULL;
}

static inline uint8_t __iomem * udma_dma_virt(struct udma_dev *udev)
{
	if (udev)
		return udev->dma_addr;
}

#endif