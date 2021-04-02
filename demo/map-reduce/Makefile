CC=$(MULTILIB_TOOLCHAIN)/riscv64-unknown-linux-gnu-gcc

all:
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  map
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  reduce
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  mphost
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  map2
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  reduce2
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  mphost2
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  map4
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  reduce4
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  mphost4
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  mphost-normal
clean:
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  map clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  reduce clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  mphost clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  map2 clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  reduce2 clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  mphost2 clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  map4 clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  reduce4 clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  mphost4 clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  mphost-normal clean
