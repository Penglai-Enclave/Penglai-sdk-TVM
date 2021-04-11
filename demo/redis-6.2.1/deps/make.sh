#!/bin/bash
ARCH=""
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

make hiredis linenoise lua jemalloc CC=$CC \
            CXX=$CXX \
            STRIP=$STRIP \
            RANLIB=$RANLIB \
            OBJDUMP=$OBJDUMP \
            NM=$NM \
            LD=$LD \
            AR=$AR \
            AS=$AS
            CFLAGS="-static" EXEEXT="-static" LDFLAGS="-static" \