#CC=riscv64-unknown-linux-gnu-gcc
HOST=onefunc-user

all:
	$(CC) -static -mabi=lp64  -march=rv64imac -o $(HOST) -I $(PENGLAI_SDK)/lib/host/include/ -I ../../sod-lib/  host.c  ./sod.c $(PENGLAI_SDK)/lib/libpenglai-enclave-host.a  -lpthread -lm

clean:
	rm -f *.o $(HOST)
