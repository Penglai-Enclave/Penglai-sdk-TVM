all:
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C host
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C client
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C server
	rm async_img_process -rf
	mkdir async_img_process
	cp host/host async_img_process
	cp client/client async_img_process
	cp server/img-process async_img_process

clean:
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C host clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C client clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C server clean