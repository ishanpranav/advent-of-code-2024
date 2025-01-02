<!-- day19.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- Linen Layout -->

# Linen Layout

Let $A,B$ be sets of sequences.

## Part A

**Algorithm:**

* let $x\leftarrow 0$;
* let $T\leftarrow$ trie over $A$;
* for $(b_0,\dots b_{n-1})\in B$:
  * define $d_0\leftarrow\mathrm{true}$;
  * define $d_k\leftarrow\mathrm{false}$ for $1\leq k\leq n$;
  * for $i\in(0,\dots,n-1)$:
    * if $\lnot d_i$, then continue to next $i$;
    * let $T'\leftarrow T$;
    * for $k\in(0,\dots,n-i-1)$:
      * assign $T'\leftarrow$ child of $T'$ matching $b_{i+k}$;
      * if $T'$ is nil, then break iteration;
      * if $T'$ is a leaf, then assign $d_{i+k+1}\leftarrow d_{i+k+1}\lor d_i$;
  * if $d_n$, then assign $x\leftarrow x+1$;
* return $x$.
