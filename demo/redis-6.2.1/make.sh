#!/bin/bash

CC=$MULTILIB_TOOLCHAIN/riscv64-unknown-linux-gnu-gcc 
CXX=$MULTILIB_TOOLCHAIN/riscv64-unknown-linux-gnu-g++ 
STRIP=$MULTILIB_TOOLCHAIN/riscv64-unknown-linux-gnu-strip 
RANLIB=$MULTILIB_TOOLCHAIN/riscv64-unknown-linux-gnu-ranlib 
OBJDUMP=$MULTILIB_TOOLCHAIN/riscv64-unknown-linux-gnu-objdump 
NM=$MULTILIB_TOOLCHAIN/riscv64-unknown-linux-gnu-nm 
LD=$MULTILIB_TOOLCHAIN/riscv64-unknown-linux-gnu-ld 
AR=$MULTILIB_TOOLCHAIN/riscv64-unknown-linux-gnu-ar 
AS=$MULTILIB_TOOLCHAIN/riscv64-unknown-linux-gnu-as
CFLAGS=-static

make MALLOC=libc CC=$MULTILIB_TOOLCHAIN/riscv64-unknown-linux-gnu-gcc CFLAGS="-static" EXEEXT="-static" LDFLAGS="-static"