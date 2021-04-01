HOST=dhrystone-baseline
CC=$(MULTILIB_TOOLCHAIN)/riscv64-unknown-linux-gnu-gcc

all:
	$(CC) -static -mabi=lp64  -march=rv64imac  -o $(HOST) -I $(PENGLAI_SDK)/lib/host/include/  dhrystone.c  $(PENGLAI_SDK)/lib/libpenglai-enclave-host.a  -lpthread

clean:
	rm -f *.o $(HOST)
