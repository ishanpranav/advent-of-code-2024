# Makefile
# Licensed under the MIT license.
# Copyright (c) 2024-2025 Ishan Pranav

CC = clang
CFLAGS = -O3 -pedantic -std=c99 -Wall -Wextra

all: day01a day01b day02a day02b day03a day03b day04a day04b day05a day05b \
	day06a day06b day07a day07b day08a day08b day09a day09b day10a day10b \
	day11a day11b day12a day12b day13a day13b day14a day14b day15a day15b \
	day16a day16b day17a day17b day18a day18b day19a day19b day20a day20b \
	day21a day21b day22a day22b day23a day23b day24a day24b day25z

%: %.c
	$(CC) $(CFLAGS) $< -o $@
