<!-- day10.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- Hoof It -->

# Day 10: Hoof It

Let $G=(V,E)$ be a directed graph and $S,T\subseteq V$ be subsets of its
vertices.

## Part A

**Algorithm:**

* let $x\leftarrow 0$;
* for $s\in S$:
  * $F=(V',E')\leftarrow$ depth-first search forest of $G$;
  * $x\leftarrow x+\lvert V'\cap T\rvert$;
* return $x$.

**Time complexity:** $O(\lvert S\rvert\cdot(\lvert V\rvert+\lvert E\rvert))$.

**Space complexity:** $O(\lvert V\rvert)$.
