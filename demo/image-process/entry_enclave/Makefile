APP = entry_enclave
APP_C_SRCS = entry.c ./sod.c
EXTRA_CLEAN = $(APP).dump
LDFLAGS = -lm
CFLAGS = -I ../sod-lib/
include $(PENGLAI_SDK)/app.mk
