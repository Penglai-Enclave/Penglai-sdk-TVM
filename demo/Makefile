all:
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C host
	make -C hello-world
	make -C relay-page
	make -C mem

	#CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  mphost_normal

clean:
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C host clean
	make -C hello-world clean
	make -C relay-page clean
	make -C mem clean

