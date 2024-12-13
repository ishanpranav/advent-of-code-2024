<!-- day12.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- Garden Groups -->

# Day 12: Garden Groups

## Part A

Let $G=(V,E)$ be a directed graph.

**Algorithm:**

* let $x\leftarrow 0$;
* for $s\in S$:
  * $F=(V',E')\leftarrow$ depth-first search forest of $G$ from $s$;
  * $x\leftarrow x+\lvert V'\cap T\rvert$;
* return $x$.

**Time complexity:** $O(\lvert S\rvert\cdot(\lvert V\rvert+\lvert E\rvert))$.

**Space complexity:** $O(\lvert V\rvert)$.
