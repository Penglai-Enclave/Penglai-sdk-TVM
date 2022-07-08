HOST=rootkit

all:
	$(CC) -static -mabi=lp64  -march=rv64imac  -o $(HOST) -I $(PENGLAI_SDK)/lib/host/include/ rootkit.c  $(PENGLAI_SDK)/lib/libpenglai-enclave-host.a  -lpthread

clean:
	rm -f *.o $(HOST)
