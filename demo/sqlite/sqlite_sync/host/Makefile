#CC=riscv64-unknown-linux-gnu-gcc
HOST=host

all:
	$(CC) -static -mabi=lp64  -march=rv64imac -o $(HOST) -I $(PENGLAI_SDK)/lib/host/include/  host.c  $(PENGLAI_SDK)/lib/libpenglai-enclave-host.a  -lpthread -lm

clean:
	rm -f *.o $(HOST)
