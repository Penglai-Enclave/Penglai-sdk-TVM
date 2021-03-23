CC = $(MULTILIB_TOOLCHAIN)/riscv64-unknown-linux-gnu-gcc

all:
	#CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  host-no-shm
	#CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  host-shm
	#CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  shadow-host-shm
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  shadow-host-no-shm

clean:
	#CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  host-no-shm clean
	#CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  host-shm clean
	#CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  shadow-host-shm clean
	CC=$(CC) LINK=$(LINK) AR=$(AR) make -C  shadow-host-no-shm clean
