# Makefile
# Copyright (c) 2024-2025 Ishan Pranav
# Licensed under the MIT license.

CC = clang
CFLAGS = -O3 -gdwarf-4 -pedantic -std=c99 -Wall -Wextra

all: day01a day01b day02a day02b day03a day03b day04a day04b day05a day05b \
	day06a day06b day07a day07b day08a day08b day09a day09b day10a day10b \
	day11a day11b day12a day12b day13a day13b day14a day14b day15a day15b \
	day16a day16b day17a day17b day18a day18b day19a day19b day20a day20b \
	day21a day21b day22a day22b day23a day23b day24a day24b day25z

day05a: day05x.c
	$(CC) $(CFLAGS) -DDAY05 -DBUFFER_SIZE=128 -DEQUAL=false -DMAX_VERTICES=128  $< -o $@

day05b: day05x.c
	$(CC) $(CFLAGS) -DDAY05 -DBUFFER_SIZE=128 -DEQUAL=true -DMAX_VERTICES=128 $< -o $@

day07b: day07b.c
	$(CC) $(CFLAGS) -lm $< -o $@

day11a: day11x.c
	$(CC) $(CFLAGS) -DDAY11 -DK=25 -DMAX_LOAD_FACTOR=1.0 -lm $< -o $@
	
day11b: day11x.c
	$(CC) $(CFLAGS) -DDAY11 -DK=75 -DMAX_LOAD_FACTOR=1.0 -lm $< -o $@

day13a: day13x.c
	$(CC) $(CFLAGS) -DDAY13 -DBUFFER_SIZE=64 -DOFFSET=0 -lm $< -o $@

day13b: day13x.c
	$(CC) $(CFLAGS) -DDAY13 -DBUFFER_SIZE=64 -DOFFSET=10000000000000ll -lm $< -o $@

%: %.c
	$(CC) $(CFLAGS) $< -o $@
