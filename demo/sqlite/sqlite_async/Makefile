all:
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C host
	CC=$(CC) link=$(LINK) AR=$(AR) make -C server
	CC=$(CC) link=$(LINK) AR=$(AR) make -C client
	rm sqlite_async -rf
	mkdir sqlite_async
	cp host/host sqlite_async
	cp server/sqlite-async-server sqlite_async
	cp client/client sqlite_async
clean:
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C host clean
	CC=$(CC) link=$(LINK) AR=$(AR) make -C server clean
	CC=$(CC) link=$(LINK) AR=$(AR) make -C client clean
	rm sqlite_async -rf