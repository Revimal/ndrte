PROJECT_NAME = ndrte

RDIRS += compdeps
RDIRS += archdeps
RDIRS += datastruct
RDIRS += drivers

RDIRS += test

include $(CURDIR)/ndr-build-env/ndr.mkroot.mk
