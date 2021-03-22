APP = image_enclave
APP_C_SRCS = image_enclave.c ./sod.c
EXTRA_CLEAN = $(APP).dump
LDFLAGS = -lm
CFLAGS = -I ../../sod-lib/
include $(PENGLAI_SDK)/app.mk
