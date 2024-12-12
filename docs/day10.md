<!-- day10.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- Hoof It -->

# Day 10: Hoof It

## Part A

Let $G=(V,E)$ be a directed graph and $S,T\subseteq V$ be subsets of its
vertices.

**Algorithm:**

* let $x\leftarrow 0$;
* for $s\in S$:
  * $F=(V',E')\leftarrow$ depth-first search forest of $G$ from $s$;
  * $x\leftarrow x+\lvert V'\cap T\rvert$;
* return $x$.

**Time complexity:** $O(\lvert S\rvert\cdot(\lvert V\rvert+\lvert E\rvert))$.

**Space complexity:** $O(\lvert V\rvert)$.

## Part B

Let $G=(V,E)$ be a tree and $S,T\subseteq V$ be subsets of its vertices.

**Algorithm:**

* let $x\leftarrow 0$;
* for $s\in S$:
  * let $S\leftarrow$ empty stack;
  * push $s$ onto $S$;
  * while $S$ is not empty:
    * let $u\leftarrow$ pop $S$;
    * if $u\in T$, then:
      * assign $x\leftarrow x+1$;
      * continue to next iteration;
    * for $(u,v)\in E$:
      * push $v$ onto $S$;
* return $x$.

**Time complexity:** $O(\lvert S\rvert\cdot\lvert V\rvert\cdot p)$, where $p$ is
the average number of paths between source and target vertices.

**Space complexity:** $O(\lvert V\rvert)$.
