all: brute_time brute_comps median_time median_comps

brute_time: median-brute-time.c
	gcc -o brute-time median-brute-time.c -lm

brute_comps: median-brute-comps.c
	gcc -o brute-comps median-brute-comps.c -lm

median_time: median-time.c
	gcc -o median-time median-time.c -lm

median_comps: median-comps.c
	gcc -o median-comps median-comps.c -lm
