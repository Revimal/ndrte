#include "selftest_lfqueue.h"
#include "ndrte_lfqueue.h"

#define LFQ_TEST_SIZE 10000000
#define LFQ_TEST_MPNUM 10

static void * lfq_sp_enq( void *arg )
{
	struct ndrte_lfq *lfq = (struct ndrte_lfq *)arg;
	uint64_t i;
	void *tmp;

	for ( i = 0; i < LFQ_TEST_SIZE; i++ )
	{
		tmp = (void *)(i + 1);
		while ( !ndrte_lfq_enq( lfq, &tmp, 1 ) )
		{
			ndrte_pause();
		}
	}

	return NULL;
}

static void * lfq_sp_sc_deq( void *arg )
{
	struct ndrte_lfq *lfq = (struct ndrte_lfq *)arg;
	uint64_t i;
	void *tmp;

	for ( i = 0; i < LFQ_TEST_SIZE; i++ )
	{
		while ( !ndrte_lfq_deq( lfq, &tmp, 1 ) )
		{
			ndrte_pause();
		}
		NTS_CHECK_LVL( lfqueue_sp_sc, i + 1 == (uint64_t)tmp, NTS_LVLSILENT );
	}

	return NULL;
}

NTS_DECLARE_TC( lfqueue_single )
{
	struct ndrte_lfq lfq;
	uint64_t i;
	void *tmp;

	ndrte_lfq_init( &lfq, NULL, LFQ_TEST_SIZE + 1 );

	( void ) lfq_sp_enq( (void *)&lfq );

	for ( i = 0; i < LFQ_TEST_SIZE; i++ )
	{
		while ( !ndrte_lfq_deq( &lfq, &tmp, 1 ) )
		{
			ndrte_pause();
		}
		NTS_CHECK_LVL( lfqueue_single, i + 1 == (uint64_t)tmp, NTS_LVLSILENT );
	}
}

NTS_DECLARE_TC( lfqueue_sp_sc )
{

	struct ndrte_lfq lfq;
	pthread_t enq_th, deq_th;
	void *tmp;

	ndrte_lfq_init( &lfq, NULL, LFQ_TEST_SIZE + 1 );

	pthread_create( &enq_th, NULL, &lfq_sp_enq, (void *)&lfq );
	pthread_create( &deq_th, NULL, &lfq_sp_sc_deq, (void *)&lfq );

	pthread_join( enq_th, &tmp );
	pthread_join( deq_th, &tmp );
}