all:
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C host
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C client
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C server
	rm sync_img_process -rf
	mkdir sync_img_process
	cp host/host sync_img_process
	cp client/client sync_img_process
	cp server/img-process sync_img_process

clean:
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C host clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C client clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C server clean