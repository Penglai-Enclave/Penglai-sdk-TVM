all:
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C host
	CC=$(CC) link=$(LINK) AR=$(AR) make -C ycsb-baseline
	rm sqlite_baseline -rf
	mkdir sqlite_baseline
	cp host/host sqlite_baseline
	cp ycsb-baseline/ycsb-baseline sqlite_baseline
clean:
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C host clean
	CC=$(CC) link=$(LINK) AR=$(AR) make -C ycsb-baseline clean
	rm sqlite_baseline -rf