#include <net/ip.h>

#include <linux/list.h>
#include <linux/rculist.h>
#include <linux/spinlock.h>
#include <linux/skbuff.h>

#include "drv_common.h"
#include "ngpm1_skbhook.h"

struct ngpm1_shdesc_struct
{
	uint16_t type;

	struct packet_type pt;
	struct list_head ptlist;

	struct list_head list;
};

typedef struct ngpm1_shdesc_struct * ngpm1_shdesc_t;

static LIST_HEAD( shdesc_list );
static DEFINE_SPINLOCK( shdesc_list_lock );

static int ngpm1_skbhook_dummyrcv( NGPM1_SKBHOOK_ARGS )
{
	return NET_RX_DROP;
}

static inline ngpm1_shdesc_t ngpm1_shdesc_lookup( uint16_t type )
{
	ngpm1_shdesc_t shdesc = NULL;

	list_for_each_entry( shdesc, &shdesc_list, list )
	{
		if ( shdesc->type == type )
		{
			return shdesc;
		}
	}
	return NULL;
}

static inline struct packet_type * ngmp1_ptype_entry( uint16_t type, struct list_head *head )
{
	struct packet_type *ptype_entry = NULL;

	rcu_read_lock();
	list_for_each_entry_rcu( ptype_entry, head, list )
	{
		if ( ptype_entry->type != type )
		{
			continue;
		}
		rcu_read_unlock();
		return ptype_entry;
	}
	rcu_read_unlock();
	return NULL;
}

int ngpm1_skbhook_attach( uint16_t type, int (*ptr_hook_func)( NGPM1_SKBHOOK_ARGS ) )
{
	ngpm1_shdesc_t shdesc = NULL;
	struct packet_type *pt_iter = NULL;

	spin_lock( &shdesc_list_lock );

	if ( !!ngpm1_shdesc_lookup( type ) )
	{
		DRV_WARN( "Requested skbhook already exist\n" );
		goto hook_out;
	}

	shdesc = kzalloc( sizeof( struct ngpm1_shdesc_struct ), GFP_ATOMIC );
	if ( !shdesc )
	{
		DRV_ERR( "Failed to allocate skbhook descriptor \n" );
		goto hook_out;
	}

	INIT_LIST_HEAD( &(shdesc->ptlist) );
	shdesc->type = type;
	shdesc->pt.type = type;
	shdesc->pt.func = ngpm1_skbhook_dummyrcv;
	INIT_LIST_HEAD( &(shdesc->pt.list) );

	dev_add_pack( &(shdesc->pt) );
	synchronize_rcu();

	while ( !!(pt_iter = ngmp1_ptype_entry( shdesc->type, &(shdesc->pt.list) )) )
	{
		dev_remove_pack( pt_iter );
		list_add( &(pt_iter->list), &(shdesc->ptlist) );
	}

	dev_remove_pack( &(shdesc->pt) );
	shdesc->pt.func = ptr_hook_func;
	dev_add_pack( &(shdesc->pt) );

	list_add_tail( &(shdesc->list), &shdesc_list );

hook_out:
	spin_unlock( &shdesc_list_lock );
	return !shdesc;
}

int ngpm1_skbhook_detach( uint16_t type )
{
	ngpm1_shdesc_t shdesc = NULL;
	struct packet_type *pt_iter = NULL;

	spin_lock( &shdesc_list_lock );

	shdesc = ngpm1_shdesc_lookup( type );
	if ( !shdesc )
	{
		DRV_WARN( "Requested skbhook not exist\n" );
		goto unhook_out;
	}

	while ( !!(pt_iter = ngmp1_ptype_entry( shdesc->type, &(shdesc->ptlist) )) )
	{
		list_del( &(pt_iter->list) );
		dev_add_pack( pt_iter );
		synchronize_rcu();
	}

	dev_remove_pack( &(shdesc->pt) );
	list_del( &(shdesc->list) );
	kfree( shdesc );

unhook_out:
	spin_unlock( &shdesc_list_lock );
	return !shdesc;
}