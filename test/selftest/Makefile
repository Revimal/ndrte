APP = selftest

SUBCOMP += test

DEPLIBS += pthread

EXTOBJS += dst_single
EXTOBJS += dst_lockfree

SRCS += selftest_queue.c
SRCS += selftest_lfqueue.c
SRCS += selftest.c

include $(NBE_DIR)/ndr.subcomp.mk
include $(NBE_DIR)/ndr.debug.mk
include $(NBE_DIR)/ndr.app.mk