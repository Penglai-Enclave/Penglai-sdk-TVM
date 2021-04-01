CC	= $(MULTILIB_TOOLCHAIN)riscv64-unknown-linux-gnu-gcc
LINK	= $(MULTILIB_TOOLCHAIN)riscv64-unknown-linux-gnu-ld
AR	= $(MULTILIB_TOOLCHAIN)riscv64-unknown-elf-ar

all:
	make -C host
	make -C sleep-demo
	make -C host-no-attest
	make -C rv8
	make -C rv8-baseline
	make -C coremark
	make -C coremark-baseline
	# make -C stress-ng
	# make -C lmbench
	make -C map-reduce
	make -C ipc
	make -C ipc-baseline
	make -C fastboot
	make -C small-demo
	make -C hello-world
	make -C image-process

clean:
	make -C host clean
	make -C sleep-demo clean
	make -C host-no-attest clean
	make -C rv8 clean
	make -C rv8-baseline clean
	make -C coremark clean
	make -C coremark-baseline clean
	# make -C stress-ng clean
	# make -C lmbench clean
	make -C map-reduce clean
	make -C ipc clean
	make -C ipc-baseline clean
	make -C fastboot clean
	make -C small-demo clean
	make -C hello-world clean
	make -C image-process clean
