HOST=qsort-baseline
CC=$(MULTILIB_TOOLCHAIN)/riscv64-unknown-linux-gnu-gcc

all:
	$(CC) -static -mabi=lp64  -march=rv64imac  -o $(HOST) -I $(PENGLAI_SDK)/lib/host/include/  qsort.c  $(PENGLAI_SDK)/lib/libpenglai-enclave-host.a  -lpthread

clean:
	rm -f *.o $(HOST)
