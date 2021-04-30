all:
	riscv64-unknown-linux-gnu-gcc -static random-access.c -o random-access

# build/RISCV/gem5.opt --debug-flags=MYTRACE --redirect-stdout -r --stdout-file=simout configs/example/se.py -n 1 --caches --cpu-type=TimingSimpleCPU --mem-size=2GB --mem-channels=1 -c random-access
# build/RISCV/gem5.mmt --debug-flags=MYTRACE --redirect-stdout -r --stdout-file=simout.mmt configs/example/se.py -n 1 --caches --cpu-type=TimingSimpleCPU --mem-size=2GB --mem-channels=1 -c random-access
# build/RISCV/gem5.vault --debug-flags=MYTRACE --redirect-stdout -r --stdout-file=simout.vault configs/example/se.py -n 1 --caches --cpu-type=TimingSimpleCPU --mem-size=2GB --mem-channels=1 -c random-access
# build/RISCV/gem5.sit --debug-flags=MYTRACE --redirect-stdout -r --stdout-file=simout.sit configs/example/se.py -n 1 --caches --cpu-type=TimingSimpleCPU --mem-size=2GB --mem-channels=1 -c random-access