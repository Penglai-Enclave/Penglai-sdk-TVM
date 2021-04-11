all:
	riscv64-unknown-linux-gnu-gcc -static random-access.c -o random-access

# build/RISCV/gem5.opt --debug-flags=MYTRACE --redirect-stdout -r --stdout-file=simout configs/example/se.py -n 1 --caches --cpu-type=TimingSimpleCPU --mem-size=2GB --mem-channels=1 -c