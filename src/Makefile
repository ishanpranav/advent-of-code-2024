# Makefile
# Copyright (c) 2024-2025 Ishan Pranav
# Licensed under the MIT license.

CC = clang
CFLAGS = -O3 -gdwarf-4 -pedantic -std=c99 -Wall -Wextra

all: day01a day01b day02a day02b day03a day03b day04a day04b day05a day05b \
	day06a day06b day07a day07b day08a day08b day09a day09b day10a day10b \
	day11a day11b day12a day12b day13a day13b \
	day14a day14s \
	day15a day15b day16a day16b \
	day17a day17s \
	day18a day18b day18s day18t \
	day19a day19b \
	day22a \
	day23a day23b \
	day24a day24b \
	day25z

day05a: day05x.c
	$(CC) $(CFLAGS) -DDAY05 -DBUFFER_SIZE=128 -DEQUAL=false -DMAX_VERTICES=128  $< -o $@

day05b: day05x.c
	$(CC) $(CFLAGS) -DDAY05 -DBUFFER_SIZE=128 -DEQUAL=true -DMAX_VERTICES=128 $< -o $@

day07b: day07b.c
	$(CC) $(CFLAGS) -lm $< -o $@

day11a: day11x.c
	$(CC) $(CFLAGS) -DDAY11 -DK=25 -DK_PRIME=101 -DMAX_LOAD_FACTOR=1.0 -DMIN_BUCKET_COUNT=6151 -DMIN_CAPACITY=4096 -lm $< -o $@
	
day11b: day11x.c
	$(CC) $(CFLAGS) -DDAY11 -DK=75 -DK_PRIME=101 -DMAX_LOAD_FACTOR=0.3 -DMIN_BUCKET_COUNT=393241 -DMIN_CAPACITY=131072 -lm $< -o $@

day13a: day13x.c
	$(CC) $(CFLAGS) -DDAY13 -DBUFFER_SIZE=64 -DOFFSET=0 -lm $< -o $@

day13b: day13x.c
	$(CC) $(CFLAGS) -DDAY13 -DBUFFER_SIZE=64 -DOFFSET=10000000000000ll -lm $< -o $@

day14a: day14a.c
	$(CC) $(CFLAGS) -DDAY14 -DMAX_X=101 -DMAX_Y=103 $< -o $@
	
day14s: day14a.c
	$(CC) $(CFLAGS) -DDAY14 -DMAX_X=11 -DMAX_Y=7 $< -o $@

day17a: day17a.c
	$(CC) $(CFLAGS) -DDAY17 -DBUFFER_SIZE=16 -DPROGRAM_SIZE=16 -DSAMPLE=false  $< -o $@
	
day17s: day17a.c
	$(CC) $(CFLAGS) -DDAY17 -DBUFFER_SIZE=16 -DPROGRAM_SIZE=16 -DSAMPLE=true  $< -o $@

day18a: day18a.c
	$(CC) $(CFLAGS) -DDAY18 -DN=71 -DMAX_POINTS=1024 $< -o $@
	
day18s: day18a.c
	$(CC) $(CFLAGS) -DDAY18 -DN=7 -DMAX_POINTS=12 $< -o $@

day18b: day18b.c
	$(CC) $(CFLAGS) -DDAY18 -DN=71 $< -o $@
	
day18t: day18b.c
	$(CC) $(CFLAGS) -DDAY18 -DN=7 $< -o $@

%: %.c
	$(CC) $(CFLAGS) $< -o $@
