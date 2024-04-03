TAILLE=1000
REPETITION=100
WARMUP=30




CC=gcc
CX=/opt/intel/oneapi/compiler/2024.0/bin/icx
MAQAO=/home/noonman/mesprojets/archi_semestre2/maqao.x86_64.2.19.0/bin/maqao

#MAQAO=/home/tm/Documents/Maqao/bin/maqao




CFLAGS=-O2 -g -Wall



OPT_O2=-O2 -g -Wall
OPT_O3=-O3 -g -Wall
OPT_fast=-Ofast -g -Wall
OPT_native=-O3 -g -Wall -march=native
OPT_unroll=-O3 -g -Wall -funroll-loops


OPT_native_ICX=-O3 -g -Wall -xHost



OBJS_COMMON=kernel.o rdtsc.o



all:	check calibrate measure

check:	$(OBJS_COMMON) driver_check.o
	$(CC) -o $@ $^
calibrate: $(OBJS_COMMON) driver_calib.o
	$(CC) -o $@ $^
measure: $(OBJS_COMMON) driver.o
	$(CC) -o $@ $^



driver_check.o: driver_check.c
	$(CC) $(CFLAGS) -D CHECK -c $< -o $@
driver_calib.o: driver_calib.c
	$(CC) $(CFLAGS) -D CALIB -c $< -o $@
driver.o: driver.c
	$(CC) $(CFLAGS) -c $<



kernel_O2.o: kernel.c
	$(CC) $(OPT_O2) -D $(OPT) -c $< -o $@

kernel_O3.o: kernel.c
	$(CC) $(OPT_O3) -D $(OPT) -c $< -o $@

kernel_fast.o: kernel.c
	$(CC) $(OPT_fast) -D $(OPT) -c $< -o $@

kernel_native.o: kernel.c
	$(CC) $(OPT_native) -D $(OPT) -c $< -o $@

kernel_native_ICX.o: kernel.c
	$(CX) $(OPT_native_ICX) -D $(OPT) -c $< -o $@

kernel_unroll.o: kernel.c
	$(CC) $(OPT_unroll) -D $(OPT) -c $< -o $@



measure_O2: kernel_O2.o rdtsc.o driver.o
	$(CC) -o $@ $^

measure_O3: kernel_O3.o rdtsc.o driver.o
	$(CC) -o $@ $^

measure_fast: kernel_fast.o rdtsc.o driver.o
	$(CC) -o $@ $^

measure_native: kernel_native.o rdtsc.o driver.o
	$(CC) -o $@ $^

measure_native_ICX: kernel_native_ICX.o rdtsc.o driver.o
	$(CX) -o $@ $^



compile_kernel: kernel_O2.o kernel_O3.o kernel_fast.o kernel_native.o kernel_native_ICX.o kernel_unroll.o
compile_general: measure_O2 measure_O3 measure_fast measure_native measure_native_ICX



test:
	taskset -c 2 ./measure_O2 $(TAILLE) $(REPETITION) $(WARMUP) >> result_O2.txt
	taskset -c 2 ./measure_O3 $(TAILLE) $(REPETITION) $(WARMUP) >> result_O3.txt
	taskset -c 2 ./measure_fast $(TAILLE) $(REPETITION) $(WARMUP) >> result_fast.txt
	taskset -c 2 ./measure_native $(TAILLE) $(REPETITION) $(WARMUP) >> result_native.txt
	taskset -c 2 ./measure_native_ICX $(TAILLE) $(REPETITION) $(WARMUP) >> result_native_ICX.txt


test_maqao:
	taskset -c 2 $(MAQAO) oneview -xp=MAQAO_O2 -R1 -- ./measure_O2 $(TAILLE) $(REPETITION) $(WARMUP)
	taskset -c 2 $(MAQAO) oneview -xp=MAQAO_O3 -R1 -- ./measure_O3 $(TAILLE) $(REPETITION) $(WARMUP)
	taskset -c 2 $(MAQAO) oneview -xp=MAQAO_Ofast -R1 -- ./measure_fast $(TAILLE) $(REPETITION) $(WARMUP)
	taskset -c 2 $(MAQAO) oneview -xp=MAQAO_native -R1 -- ./measure_native $(TAILLE) $(REPETITION) $(WARMUP)
	taskset -c 2 $(MAQAO) oneview -xp=MAQAO_native_ICX -R1 -- ./measure_native_ICX $(TAILLE) $(REPETITION) $(WARMUP)



go:
	make compile_kernel
	make compile_general
	make test


go_maqao:
	make compile_kernel
	make compile_general
	make test_maqao

clean:
	rm -rf $(OBJS_COMMON) driver_check.o driver_calib.o driver.o check calibrate measure measure_O2 measure_O3 measure_fast measure_native measure_native_ICX kernel_O2.o kernel_O3.o kernel_fast.o kernel_native.o kernel_native_ICX.o kernel_unroll.o

clean_result:
	rm -rf result_O2.txt result_O3.txt result_fast.txt result_native.txt result_native_ICX.txt

clean_maqao:
	rm -rf MAQAO_*

clean_all:
	make clean
	make clean_result
	make clean_maqao