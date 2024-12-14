<!-- day14.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- Restroom Redoubt -->

# Day 14: Restroom Redoubt

Let $L$ be a set of pairs $(\vec{s},\vec{v})$ where $\vec{s},\vec{v}$ are
integer vectors $(x,y)$ for $x,y\in\mathbb{Z}$. Let $x^\ast,y^\ast\in\mathbb{N}$
be the boundaries and $t$ be the duration. Let $S_0,\dots,S_3$ be sets of vectors.

## Part A

**Algorithm:**

* let $c_i\leftarrow 0$ for $0\leq i\leq 3$;
* for $(\vec{s}_0,\vec{v})\in L$:
  * assign $\vec{s}_t\leftarrow ((\vec{s_0}_x+\vec{v}_xt)\mod{x^\ast},(\vec{s_0}_y+\vec{v}_yt)\mod{y^\ast})$;
  * for $i\in\lbrace 0,\dots, 3\rbrace$:
    * if $\vec{s}_t\in S_i$, then assign $c_i\leftarrow c_i+1$;
    * break iteration;
* return $\prod_{i=0}^{3}{c_i}$.

**Time complexity:** $O(\lvert L\rvert)$.

**Space complexity:** $O(1)$.
