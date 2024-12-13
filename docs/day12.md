<!-- day12.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- Garden Groups -->

# Day 12: Garden Groups

Let $G=(V,E)$ be a directed graph.

## Part A

**Algorithm:**

* let $\mathcal{C}\leftarrow$ connected components of $G$:
* return $\sum_{X\in\mathcal{C}}\left(\lvert U\rvert\cdot\lvert\lbrace (u,v)\in E\mid v\notin X\rbrace\rvert\right)$.

**Time complexity:** $O(\lvert V\rvert+\lvert E\rvert)$.

**Space complexity:** $O(\lvert V\rvert)$.
