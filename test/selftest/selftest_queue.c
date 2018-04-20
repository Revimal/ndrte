#include "ndrte_queue.h"

#include "selftest_queue.h"

#define QUEUE_TEST_SIZE 10000000

NTS_DEFINE_TC( queue_single )
{
	struct ndrte_queue queue;
	uint64_t i;
	void *tmp;

	ndrte_queue_init( &queue, NULL, QUEUE_TEST_SIZE + 1 );

	for ( i = 0; i < QUEUE_TEST_SIZE; i++ )
	{
		tmp = (void *)(i + 1);
		while ( !ndrte_queue_enq( &queue, &tmp, 1 ) )
		{
			ndrte_pause();
		}
	}

	for ( i = 0; i < QUEUE_TEST_SIZE; i++ )
	{
		while ( !ndrte_queue_deq( &queue, &tmp, 1 ) )
		{
			ndrte_pause();
		}
		NTS_CHECK_LVL( queue_single, i + 1 == (uint64_t)tmp, NTS_LVLSILENT );
	}
}