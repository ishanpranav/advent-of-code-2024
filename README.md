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

**Day 18:** The union–find-based technique for Day 18(b)
is inspired by [this Reddit conversation](https://www.reddit.com/r/adventofcode/comments/1hguacy/comment/m2m8wlg/?utm_source=share&utm_medium=web3x&utm_name=web3xcss&utm_term=1&utm_content=share_button).

## Omissions

**Day 14(b), Day 17(b), Day 24(b):** By design, there is no generalized
heuristic-free algorithm for Day 14(b), Day 17(b), and Day 23(b). These
reverse-engineering problems that require assumptions about the input.

**Day 20:** The generalized solution for Day 20(a) and Day 20(b) is inefficient.

**Day 21:** My favorite solution for Day 21(a) and Day 21(b) comes from the
insights at [expectancyViolation/aoc_2024](https://github.com/expectancyViolation/aoc_2024).
I have no improvements to offer.

**Day 22(b):** The generalized solution for Day 22(b) is inefficient.

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
* The return values of all C standard library functions must be checked, except for those returned from the following:
  * `fprintf`
  * `memcpy`
  * `memmove`
  * `memset`
  * `printf`
