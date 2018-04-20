#include "ndrte_queue.h"
#include "ndrte_lfqueue.h"

#include "perftest_queue.h"

#define QUEUE_TEST_SIZE 10000000

NTS_DEFINE_TC( queue_single )
{
	struct ndrte_queue queue;
	struct ndrte_lfq lfq;
	uint64_t i;
	uint64_t queue_enq_start, queue_enq_end, queue_enq_diff, queue_deq_start, queue_deq_end, queue_deq_diff;
	uint64_t lfq_enq_start, lfq_enq_end, lfq_enq_diff, lfq_deq_start, lfq_deq_end, lfq_deq_diff;
	void *tmp;

	ndrte_queue_init( &queue, NULL, QUEUE_TEST_SIZE + 1 );
	ndrte_lfq_init( &lfq, NULL, QUEUE_TEST_SIZE + 1 );

	queue_enq_start = ndrte_hwcnt_tsc();
	for ( i = 0; i < QUEUE_TEST_SIZE; i++ )
	{
		tmp = (void *)(i + 1);
		while ( !ndrte_queue_enq( &queue, &tmp, 1 ) )
		{
			ndrte_pause();
		}
	}
	queue_enq_end = ndrte_hwcnt_tsc();
	queue_enq_diff = queue_enq_end - queue_enq_start;

	queue_deq_start = ndrte_hwcnt_tsc();
	for ( i = 0; i < QUEUE_TEST_SIZE; i++ )
	{
		while ( !ndrte_queue_deq( &queue, &tmp, 1 ) )
		{
			ndrte_pause();
		}
	}
	queue_deq_end = ndrte_hwcnt_tsc();
	queue_deq_diff = queue_deq_end - queue_deq_start;

	lfq_enq_start = ndrte_hwcnt_tsc();
	for ( i = 0; i < QUEUE_TEST_SIZE; i++ )
	{
		tmp = (void *)(i + 1);
		while ( !ndrte_lfq_enq( &lfq, &tmp, 1 ) )
		{
			ndrte_pause();
		}
	}
	lfq_enq_end = ndrte_hwcnt_tsc();
	lfq_enq_diff = lfq_enq_end - lfq_enq_start;

	lfq_deq_start = ndrte_hwcnt_tsc();
	for ( i = 0; i < QUEUE_TEST_SIZE; i++ )
	{
		while ( !ndrte_lfq_deq( &lfq, &tmp, 1 ) )
		{
			ndrte_pause();
		}
	}
	lfq_deq_end = ndrte_hwcnt_tsc();
	lfq_deq_diff = lfq_deq_end - lfq_deq_start;

	printf( "[Queue] enq = %20lu / deq = %20lu\n", queue_enq_diff, queue_deq_diff );
	printf( "[ LFQ ] enq = %20lu / deq = %20lu\n", lfq_enq_diff, lfq_deq_diff );
	printf( "[PDIFF] enq = %20lu / deq = %20lu\n", lfq_enq_diff - queue_enq_diff, lfq_deq_diff - queue_deq_diff );
}