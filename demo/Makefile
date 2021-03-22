CC	= $(MULTILIB_TOOLCHAIN)riscv64-unknown-linux-gnu-gcc
LINK	= $(MULTILIB_TOOLCHAIN)riscv64-unknown-linux-gnu-ld
AR	= $(MULTILIB_TOOLCHAIN)riscv64-unknown-elf-ar

all:
	make -C host
	make -C rv8
	make -C coremark
	make -C stress-ng
	make -C lmbench
	make -C map-reduce
	make -C ipc
	make -C fastboot
	make -C small-demo

clean:
	make -C host clean
	make -C rv8 clean
	make -C coremark clean
	make -C stress-ng clean
	make -C lmbench clean
	make -C map-reduce clean
	make -C ipc clean
	make -C fastboot clean
	make -C small-demo clean
