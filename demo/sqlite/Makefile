all:
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C sqlite_sync
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C sqlite_async
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C sqlite_baseline

clean:
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C sqlite_sync clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C sqlite_async clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C sqlite_baseline clean