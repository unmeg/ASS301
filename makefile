all: times comps algo_test

median_time: median-time.c
	gcc -o times times.c -lm

median_comps: comps.c
	gcc -o comps basic_operations.c -lm

algo_test: algorithm-testing.c
	gcc -o algo-test algorithm-testing.c -lm