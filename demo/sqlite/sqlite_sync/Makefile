all:
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C host
	CC=$(CC) link=$(LINK) AR=$(AR) make -C server
	CC=$(CC) link=$(LINK) AR=$(AR) make -C client
	rm sqlite_sync -rf
	mkdir sqlite_sync
	cp host/host sqlite_sync
	cp server/sqlite-sync-server sqlite_sync
	cp client/client sqlite_sync
clean:
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C host clean
	CC=$(CC) link=$(LINK) AR=$(AR) make -C server clean
	CC=$(CC) link=$(LINK) AR=$(AR) make -C client clean
	rm sqlite_sync -rf