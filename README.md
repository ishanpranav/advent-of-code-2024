<!-- README.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

# Advent of Code 2024

This is a collection of solutions to the
[Advent of Code 2024](https://adventofcode.com/2024) programming implemented in
the C programming language.

For this project, we focus on efficient algorithms and include formal pseudocode
for each solution.

## Acknowledgements

**Day 9:** My original algorithm for Day 9(a) and Day 9(b) had space complexity
exceeding $O(1)$. The algorithm with $O(1)$ space complexity comes from the
impressive work at [maneatingape/advent-of-code-rust](https://github.com/maneatingape/advent-of-code-rust).

## Usage

These programs are cross-platform, having been tested on Windows and Linux
operating systems.

**Important:** There is no error-checking. An invalid input usually results in a
segmentation violation.

**Important:** I have tested each program on the example test cases and two
puzzle input files - not a large sample size! I have avoided assumptions about
the input, sometimes even at the cost of performance. However, to avoid memory
allocation, all buffers have fixed sizes. Ensure that all buffers (see `#define`
statements) have sufficient capacity before running. Not doing so could result
in a stack smashing, segmentation violation, or worse.

## Constraints

I am working within the following constraints to ensure high code quality.

* Final solutions must be implemented in the C programming language following the C99 standard, with the following non-standard assumptions:
  * asssume that all characters are ASCII-encoded.
* Bounds checking is not required for data structures whose capacity is defined by a macro.
* Dynamic memory allocation is not permitted unless the following requirements are met:
  * the total amount of memory consumed exceeds 1 MB; and,
  * the size of the allocated space is known in advance.
* The return values of all C standard library functions must be checked, except for those returned from the following:
  * `printf`
  * `memcpy`
  * `memset`
