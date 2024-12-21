<!-- day18.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- RAM Run -->

# RAM Run

Let $G=(V,E)$ be a graph. Let $s,t\in V$.

## Part A

**Algorithm:**

* let $w_u~\forall u\in V\leftarrow$ breadth-first search of $G$ from $s$;
* return $w_t$.

**Time complexity:** $O(\lvert V\rvert+\lvert E\rvert)=O(\lvert V\rvert)$ for $\lvert E\rvert=O(\lvert V\rvert)$.

**Space complexity:** $O(\lvert V\rvert)=O(\lvert V\rvert)$ for $\lvert E\rvert=O(\lvert V\rvert)$.
