all:
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  map
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  reduce
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  mphost
clean:
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  map clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  reduce clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  mphost clean