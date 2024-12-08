<!-- day08.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- Resonant Collinearity -->

# Day 8: Resonant Collinearity

Let $X\subseteq\mathbb{N}$. Let $m,n\in\mathbb{R}$. Let $L$ be a set where for all $(i,j,k)\in L$ we have $0\leq i\lt m$, $0\leq j\lt n$, and and $k\in X$.

## Part A

**Algorithm 1:**

* let $M_x\leftarrow\emptyset$ for $x\in X$;
* for $(i,j,k)\in L$:
  * assign $M_k\leftarrow M_k\cup\lbrace(i,j)\rbrace$;
* let $S\leftarrow\emptyset$;
* for $x\in X$:
  * for $(p_i,p_j)\in M_x$:
    * for $(q_i,q_j)\in M_x\setminus\lbrace(p_i,p_j)\rbrace$:
      * let $(i,j)\leftarrow(2p_i-q_i,2p_j-q_j)$;
      * if $0\leq i\lt m$ and $0\leq j\lt n$, then assign $S\leftarrow S\cup\lbrace(i,j)\rbrace$;
* return $\lvert S\rvert$.

**Time complexity:** $O(\lvert X\rvert\cdot m^2n^2)=O(m^2n^2)$ for small $\lvert X\rvert$.

**Space complexity:** $O(\lvert X\rvert+mn)=O(mn)$ for small $\lvert X\rvert$.

## Part B

* let $M_x\leftarrow\emptyset$ for $x\in X$;
* for $(i,j,k)\in L$:
  * assign $M_k\leftarrow M_k\cup\lbrace(i,j)\rbrace$;
* let $S\leftarrow\emptyset$;
* for $x\in X$:
  * for $(p_i,p_j)\in M_x$:
    * for $(q_i,q_j)\in M_x\setminus\lbrace(p_i,p_j)\rbrace$:
      * let $(\mathrm{d}i,\mathrm{d}j)\leftarrow(p_i-q_i,p_j-q_j)$;
      * let $(i,j)\leftarrow(p_i,p_j)$;
      * while $0\leq i\lt m$ and $0\leq j\lt n$:
        * assign $S\leftarrow S\cup\lbrace(i,j)\rbrace$;
        * assign $(i,j)\leftarrow(i+\mathrm{d}i,j+\mathrm{d}j)$.
* return $\lvert S\rvert$.
