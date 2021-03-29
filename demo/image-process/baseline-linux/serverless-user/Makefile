#CC=riscv64-unknown-linux-gnu-gcc

HOST=serverless-user

all:
	$(CC) -static -mabi=lp64  -march=rv64imac -o $(HOST) -I ../../sod-lib/  host.c  ./sod.c -lpthread -lm

clean:
	rm -f *.o $(HOST)
