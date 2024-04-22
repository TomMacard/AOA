TAILLE=1000
REPETITION=500
WARMUP=10




CC=gcc
CX=/opt/intel/oneapi/compiler/2024.0/bin/icx

# Myriam
#CX=/opt/intel/oneapi/compiler/2024.1/bin/icx

# Chris
#MAQAO=/home/noonman/mesprojets/archi_semestre2/maqao.x86_64.2.19.0/bin/maqao

# Tom
MAQAO=/home/tm/Documents/Maqao/bin/maqao




CFLAGS=-O2 -g -Wall



OPT_O2=-O2 -g -Wall
OPT_O3=-O3 -g -Wall
OPT_fast=-Ofast -g -Wall
OPT_native=-O3 -g -Wall -march=native
OPT_unroll=-O3 -g -Wall -funroll-loops

OPT_native_ICX=-O3 -g -Wall -xHost


OBJS_COMMON=kernel.o rdtsc.o



all:	check calibrate measure measure_O2 measure_O3 measure_fast measure_native measure_native_ICX measure_ICX measure_unroll

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

kernel_unroll.o: kernel.c
	$(CC) $(OPT_unroll) -D $(OPT) -c $< -o $@

kernel_ICX.o: kernel.c
	$(CX) $(OPT_O3) -D $(OPT) -c $< -o $@

kernel_native_ICX.o: kernel.c
	$(CX) $(OPT_native_ICX) -D $(OPT) -c $< -o $@

kernel_fast_ICX.o: kernel.c
	$(CX) $(OPT_fast) -D $(OPT) -c $< -o $@



measure_O2: kernel_O2.o rdtsc.o driver.o
	$(CC) -o $@ $^

measure_O3: kernel_O3.o rdtsc.o driver.o
	$(CC) -o $@ $^

measure_fast: kernel_fast.o rdtsc.o driver.o
	$(CC) -o $@ $^

measure_native: kernel_native.o rdtsc.o driver.o
	$(CC) -o $@ $^

measure_unroll: kernel_unroll.o rdtsc.o driver.o
	$(CC) -o $@ $^

measure_ICX: kernel_ICX.o rdtsc.o driver.o
	$(CX) -o $@ $^

measure_native_ICX: kernel_native_ICX.o rdtsc.o driver.o
	$(CX) -o $@ $^

measure_fast_ICX: kernel_fast_ICX.o rdtsc.o driver.o
	$(CX) -o $@ $^


check_O2: kernel_O2.o rdtsc.o driver_check.o
	$(CC) -o $@ $^



compile_kernel: kernel_O2.o kernel_O3.o kernel_fast.o kernel_native.o kernel_native_ICX.o kernel_unroll.o kernel_ICX.o kernel_unroll.o kernel_fast_ICX.o
compile_general: measure_O2 measure_O3 measure_fast measure_native measure_native_ICX measure_ICX measure_unroll measure_fast_ICX



test:
	taskset -c 2 ./measure_O2 $(TAILLE) $(WARMUP) $(REPETITION) >> result_O2.txt
	taskset -c 2 ./measure_O3 $(TAILLE) $(WARMUP) $(REPETITION) >> result_O3.txt
	taskset -c 2 ./measure_fast $(TAILLE) $(WARMUP) $(REPETITION) >> result_fast.txt
	taskset -c 2 ./measure_native $(TAILLE) $(WARMUP) $(REPETITION) >> result_native.txt
	taskset -c 2 ./measure_unroll $(TAILLE) $(WARMUP) $(REPETITION) >> result_unroll.txt
	taskset -c 2 ./measure_ICX $(TAILLE) $(WARMUP) $(REPETITION) >> result_ICX.txt
	taskset -c 2 ./measure_native_ICX $(TAILLE) $(WARMUP) $(REPETITION) >> result_native_ICX.txt
	taskset -c 2 ./measure_fast_ICX $(TAILLE) $(WARMUP) $(REPETITION) >> result_fast_ICX.txt


test_maqao:
	taskset -c 2 $(MAQAO) oneview -xp=MAQAO_O2 -R1 -- ./measure_O2 $(TAILLE) $(WARMUP) $(REPETITION)
	taskset -c 2 $(MAQAO) oneview -xp=MAQAO_O3 -R1 -- ./measure_O3 $(TAILLE) $(WARMUP) $(REPETITION)
	taskset -c 2 $(MAQAO) oneview -xp=MAQAO_Ofast -R1 -- ./measure_fast $(TAILLE) $(WARMUP) $(REPETITION)
	taskset -c 2 $(MAQAO) oneview -xp=MAQAO_native -R1 -- ./measure_native $(TAILLE) $(WARMUP) $(REPETITION)
	taskset -c 2 $(MAQAO) oneview -xp=MAQAO_unroll -R1 -- ./measure_unroll $(TAILLE) $(WARMUP) $(REPETITION)
	taskset -c 2 $(MAQAO) oneview -xp=MAQAO_ICX -R1 -- ./measure_ICX $(TAILLE) $(WARMUP) $(REPETITION)
	taskset -c 2 $(MAQAO) oneview -xp=MAQAO_native_ICX -R1 -- ./measure_native_ICX $(TAILLE) $(WARMUP) $(REPETITION)
	taskset -c 2 $(MAQAO) oneview -xp=MAQAO_fast_ICX -R1 -- ./measure_fast_ICX $(TAILLE) $(WARMUP) $(REPETITION)



go_phase2:
	make kernel_O2.o OPT=NOOPT
	make measure_O2
	make check_O2
	taskset -c 2 ./check_O2 $(TAILLE) result_NOOPT.txt
	taskset -c 2 $(MAQAO) oneview -xp=MAQAO_NOOPT -R1 -- ./measure_O2 $(TAILLE) $(WARMUP) $(REPETITION)
	rm kernel_O2.o
	rm check_O2
	rm measure_O2

	make kernel_O2.o OPT=OPT1
	make measure_O2
	make check_O2
	taskset -c 2 ./check_O2 $(TAILLE) result_OPT1.txt
	taskset -c 2 $(MAQAO) oneview -xp=MAQAO_OPT1 -R1 -- ./measure_O2 $(TAILLE) $(WARMUP) $(REPETITION)
	rm kernel_O2.o
	rm check_O2
	rm measure_O2

	make kernel_O2.o OPT=OPT2
	make measure_O2
	make check_O2
	taskset -c 2 ./check_O2 $(TAILLE) result_OPT2.txt
	taskset -c 2 $(MAQAO) oneview -xp=MAQAO_OPT2 -R1 -- ./measure_O2 $(TAILLE) $(WARMUP) $(REPETITION)
	rm kernel_O2.o
	rm check_O2
	rm measure_O2


	firefox &
	firefox /home/tm/Documents/Taf/AOA/src/MAQAO_NOOPT/RESULTS/measure_O2_one_html/index.html &
	firefox /home/tm/Documents/Taf/AOA/src/MAQAO_OPT1/RESULTS/measure_O2_one_html/index.html &
	firefox /home/tm/Documents/Taf/AOA/src/MAQAO_OPT2/RESULTS/measure_O2_one_html/index.html &



go:
	make compile_kernel
	make compile_general
	make test


go_maqao:
	make compile_kernel
	make compile_general
	make test_maqao

clean:
	rm -rf $(OBJS_COMMON) *.o
	rm -rf measure*
	rm -rf check*
	rm -rf calibrate*

clean_result:
	rm -rf result_*.txt

clean_maqao:
	rm -rf MAQAO_*

clean_all:
	make clean
	make clean_result
	make clean_maqao
