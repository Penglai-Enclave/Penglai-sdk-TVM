HOST=coremark-baseline
CC=$(MULTILIB_TOOLCHAIN)/riscv64-unknown-linux-gnu-gcc

all:
	$(CC) -Wall -O2 -static -mabi=lp64  -march=rv64imac  -o $(HOST) -I $(PENGLAI_SDK)/lib/host/include/  core_list_join.c core_main.c core_matrix.c core_portme.c core_state.c core_util.c $(PENGLAI_SDK)/lib/libpenglai-enclave-host.a  -lpthread

clean:
	rm -f *.o $(HOST)
