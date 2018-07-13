/******************************************************************************
 Copyright (C) 2018 NDR Opensource Group

 Licensed under the several legal conditions.
 See 'License' in the project root for legal information.
******************************************************************************/

#include "nhpgman.h"
#include "linux/hugetlb.h"

#define NHPGMAN_MODULE_NAME "nhgpman"
#define NHPGMAN_MODULE_VERSION "1.0.0"
#define NHPGMAN_MODULE_DESC "NDR hugepage manager for NDR drivers"

NDR_MODULE_COPYRIGHT(NHPGMAN_MODULE_NAME)
MODULE_VERSION(NHPGMAN_MODULE_VERSION);
MODULE_DESCRIPTION(NHPGMAN_MODULE_DESC);

#define NHPGMAN_DEFSET_ORDER 10
#define NHPGMAN_DEFSET_EDENSZ 256
#define NHPGMAN_HASH_ORDER 3

struct nhpg_desc {
	unsigned int hugepg_order;
	unsigned long hugepg_size;
	struct page *hugepg_ptr;

	struct list_head list;
}

struct nhpg_info {
	ndrte_uint64_t hugepg_total_free[MAX_ORDER - 1];
	ndrte_uint64_t hugepg_total_inuse[MAX_ORDER - 1];
	ndrte_uint64_t hugepg_total_mapped[MAX_ORDER - 1];

	ndrte_uint64_t hugepg_local_free[MAX_NUMNODES][MAX_ORDER - 1];
	ndrte_uint64_t hugepg_local_inuse[MAX_NUMNODES][MAX_ORDER - 1];
	ndrte_uint64_t hugepg_local_mapped[MAX_NUMNODES][MAX_ORDER - 1];

	struct ndrte_lfq hugepg_eden_pool[MAX_NUMNODES][MAX_ORDER - 1];

	struct list_head hugepg_surv_list[MAX_NUMNODES][NHPGMAN_HASH_ORDER];
	spinlock_t hugepg_hashlock[MAX_NUMNODES][NHPGMAN_HASH_ORDER];
}
static nhpg_info nhpg_global_info;

struct page *nhpg_hugepg_resolv(const char *name)
{

}

static void nhpg_hugepg_free(struct page *page)
{
	set_page_private(page, 0);
	page->mapping = NULL;
	VM_BUG_ON_PAGE(page_count(page), page);
	VM_BUG_ON_PAGE(page_mapcount(page), page);

}

struct page *nhpg_hugepg_alloc(const char *name, int numa_node, unsigned long size, nhpg_gfp_t nhpg_gfp)
{
	struct page *hugepg = NULL;
	int order = get_order(size);
	gfp_t gfp_flag;

	switch (nhpg_gfp) {
	case NHPG_DEV:
		gfp_flag = NHPGMAN_GFP_FLAG_DEVICE;
		break;
	case NHPG_IRQ:
		gfp_flag = NHPGMAN_GFP_FLAG_ATOMIC;
		break;
	case NHPG_NORM:
	default:
		gfp_flag = NHPGMAN_GFP_FLAG_NORMAL;
		break;
	}

	if (numa_node == NUMA_NO_NODE)
		hugepg = alloc_pages(gfp_flag, order);
	else
		hugepg = alloc_pages_exact_node(numa_node,
			gfp_flag | __GFP_THISNODE, order );

	if (hugepg) {
		INIT_LIST_HEAD(&hugepg->lru);
		set_compound_page_dtor(hugepg, nhpg_hugepg_free);
	}

	return hugepg;
}

static int __init nhpg_load(void)
{
	int i, j, ret = 0;

	for ( i = 0; i < MAX_NUMNODES; i++ ) {
		if (ndrte_lfq_init(&nhpg_global_info->hugepg_eden_pool[i],
				NULL, NHPGMAN_DEFSET_EDENSZ)) {
			pr_err("failed to init hugepg eden pool (%d)\n", i);
			goto err_out_reclaim_eden_pool;
		}

	}

err_out:
	return ret;

err_out_reclaim_eden_pool:
	for ( i; i > 0; ) {
		struct ndrte_lfq *reclaim_lfq = &nhpg_global_info->hugepg_eden_pool[--i];
		uint64_t pg_cnt = ndrte_lfq_fill_count(reclaim_lfq);

		for ( pg_cnt; pg_cnt > 0; pg_cnt = ndrte_lfq_fill_count(reclaim_lfq) ) {
			void *reclaim_pages[pg_cnt];
			uint64_t reclaim_pg_cnt = ndrte_lfq_deq(reclaim_lfq, reclaim_pages, pg_cnt);

			for ( reclaim_pg_cnt; reclaim_pg_cnt > 0; ) {
				__free_pages((struct page *)reclaim_pages[--reclaim_idx],
					nhpg_global_info->hugepg_order);
			}
		}
		ndrte_lfq_cleanup(reclaim_lfq);
	}
}

static void __exit nhpg_unload(void)
{
	return;
}

module_init(nhpg_load);
module_exit(nhpg_unload);
