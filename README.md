<!-- README.md -->
<!-- Licensed under the MIT license. -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->

# Advent of Code 2024

This is a collection of solutions to the
[Advent of Code 2024](https://adventofcode.com/2024) programming implemented in
the C programming language.

For this project, we focus on efficient algorithms and include formal pseudocode
for each solution.

## Acknowledgements

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
