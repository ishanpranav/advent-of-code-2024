<!-- day06.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- Guard Gallivant -->

# Day 6: Guard Gallivant

Let $\mathbf{A}=(a_{i,j})$ be an $m\times n$ matrix. Let $(i^\ast,j^\ast)$ be a coordinate for $0\leq i\lt m$ and $0\leq j\lt n$.

## Part A

**Algorithm:**

* let $(\mathrm{d}i,\mathrm{d}j)\leftarrow(-1,0)$;
* let $k\leftarrow 0$;
* let $\mathbf{B}=(b_{i,j})$ be an $m\times n$ matrix;
* assign $b_{i,j}\leftarrow 0$ for $0\leq i\lt m$ and $0\leq j\lt n$;
* loop:
  * if $b_{i^\ast,j^\ast}=0$, then:
    * assign $k\leftarrow k+1$;
    * assign $b_{i^\ast,j^\ast}\leftarrow 1$;
  * if $i^\ast+\mathrm{d}i\geq m$ or $j^\ast+\mathrm{d}j\geq n$, then break loop;
  * while $a_{i^\ast+\mathrm{d}i,j^\ast+\mathrm{d}j}=1$:
    * if $\mathrm{d}i=1$, then assign $(\mathrm{d}i,\mathrm{d}j)\leftarrow(0,-1)$;
    * if $\mathrm{d}i=-1$, then assign $(\mathrm{d}i,\mathrm{d}j)\leftarrow(0,1)$;
    * if $\mathrm{d}j=1$, then assign $(\mathrm{d}i,\mathrm{d}j)\leftarrow(1,0)$;
    * if $\mathrm{d}j=-1$, then assign $(\mathrm{d}i,\mathrm{d}j)\leftarrow(-1,-0)$;
  * assign $(i^\ast,j^\ast)\leftarrow(i^\ast+\mathrm{d}i,j^\ast+\mathrm{d}j)$;

**Space complexity:** $O(1)$.

## Part B
