APP = perftest

SUBCOMP += test

DEPLIBS += pthread

EXTOBJS += dst_single
EXTOBJS += dst_lockfree

SRCS += perftest_queue.c
SRCS += perftest.c

include $(NBE_DIR)/ndr.subcomp.mk
include $(NBE_DIR)/ndr.debug.mk
include $(NBE_DIR)/ndr.app.mk