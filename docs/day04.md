<!-- day04.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- Ceres Search -->

# Day 4: Ceres Search

Let $\mathbf{A}=(a_{i,j})$ be an $m\times n$ matrix and
$\mathbf{v}$ be a $k$-element vector.

## Part A

**Algorithm 1:**

* let $x\leftarrow 0$;
* let $D\leftarrow\lbrace(1,0),(-1,0),(0,-1),(0,1),(1,1),(1,-1),(-1,1),(-1,-1)\rbrace$;
* for $i\in(0,\dots,m-1)$:
  * for $j\in(0,\dots,n-1)$:
    * for $(\mathrm{d}i,\mathrm{d}j)\in D$:
      * let $c\leftarrow$ invoke Algorithm 2 with arguments $i,j,\mathrm{d}i,\mathrm{d}j$;
      * assign $x\leftarrow x+c$;
* return $x$.

**Algorithm 2** with coordinate $i,j$ and coordinate $\mathrm{d}i,\mathrm{d}j$ as arguments:

* for $v\in\mathbf{v}$:
  * if $i\lt 0$ or $j\lt 0$ or $i\geq m$ or $j\geq n$, then return $0$;
  * if $a_{i,j}\neq v$, then return $0$;
  * assign $i\leftarrow i+\mathrm{d}i$;
  * assign $j\leftarrow j+\mathrm{d}j$;
* return $1$.

**Time complexity:** $O(kmn)=O(mn)$ for small $k$.

**Space complexity:** $O(1)$.

## Part B

**Algorithm 3:**

* let $x\leftarrow 0$;
* for $i\in(1,\dots,m-2)$:
  * for $j\in(1,\dots,n-2)$:
    * let $c_0\leftarrow$ invoke Algorithm 2 with arguments $i-1,j-1,\mathrm{d}i=1,\mathrm{d}j=1$;
    * let $c_1\leftarrow$ invoke Algorithm 2 with arguments $i-1,j+1,\mathrm{d}i=1,\mathrm{d}j=-1$;
    * let $c_2\leftarrow$ invoke Algorithm 2 with arguments $i+1,j-1,\mathrm{d}i=-1,\mathrm{d}j=1$;
    * let $c_3\leftarrow$ invoke Algorithm 2 with arguments $i+1,j+1,\mathrm{d}i=-1,\mathrm{d}j=-1$;
    * if $c_0+c_1+c_2+c_3=2$, then assign $x\leftarrow x+1$;
* return $x$.

**Time complexity:** $O(kmn)=O(mn)$ for small $k$.

**Space complexity:** $O(1)$.
