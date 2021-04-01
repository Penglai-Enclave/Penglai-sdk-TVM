CC=riscv64-unknown-elf-gcc
ld=riscv64-unknown-elf-ld
objdump=riscv64-unknown-elf-objdump

CFLAGS=-Wall -O2 -I. -mabi=lp64 -march=rv64imac
#LDFLAGS=-static -L. -lpenglai-enclave-eapp -lc -lgcc
SDK_LIB_DIR = $(PENGLAI_SDK)/lib
MUSL_LIB_DIR = $(PENGLAI_SDK)/musl/lib
GCC_LIB = $(MULTILIB_TOOLCHAIN)/../lib/gcc/riscv64-unknown-linux-gnu/9.2.0/lib64/lp64/libgcc.a
LDFLAGS=-static -L$(SDK_LIB_DIR) -L$(MUSL_LIB_DIR) -lc -lpenglai-enclave-eapp

OBJ=core_list_join.o core_main.o core_matrix.o core_portme.o core_state.o core_util.o
LDS=app.lds
BIN=coremark
COPY=../../../copy-files

all: 
	$(CC) $(CFLAGS) -c core_list_join.c
	$(CC) $(CFLAGS) -c core_main.c
	$(CC) $(CFLAGS) -c core_matrix.c
	$(CC) $(CFLAGS) -c core_portme.c
	$(CC) $(CFLAGS) -c core_state.c
	$(CC) $(CFLAGS) -c core_util.c
	$(ld) -o $(BIN) $(OBJ) -T $(LDS) $(LDFLAGS) $(GCC_LIB)

clean:
	rm -f *.o coremark
