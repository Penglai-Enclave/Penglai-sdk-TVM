APP = sqlite-sync-server
APP_C_SRCS = server.c sqlite3.c
EXTRA_CLEAN = $(APP).dump
CFLAGS += -DSQLITE_THREADSAFE=0 -DSQLITE_OMIT_LOAD_EXTENSION
include $(PENGLAI_SDK)/app.mk
