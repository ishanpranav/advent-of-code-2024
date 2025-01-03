<!-- day19.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- Linen Layout -->

# Linen Layout

Let $A,B$ be sets of sequences.

Let $m^\ast=\max_{a\in A}(\mathrm{len}(a)),n^\ast=\max_{b\in B}(\mathrm{len}(b))$.

## Part A

**Algorithm:**

* let $x\leftarrow 0$;
* let $T\leftarrow$ trie over $A$;
* for $(b_0,\dots b_{n-1})\in B$:
  * define $d_0\leftarrow\mathrm{true}$;
  * define $d_i\leftarrow\mathrm{false}$ for $1\leq i\leq n$;
  * for $i\in(0,\dots,n-1)$:
    * if $\lnot d_i$, then continue to next $i$;
    * let $T'\leftarrow T$;
    * for $k\in(0,\dots,n-i-1)$:
      * assign $T'\leftarrow$ child of $T'$ matching $b_{i+k}$;
      * if $T'$ is nil, then break iteration;
      * if $T'$ is a leaf, then assign $d_{i+k+1}\leftarrow d_{i+k+1}\lor d_i$;
  * if $d_n$, then assign $x\leftarrow x+1$;
* return $x$.

**Time complexity:** $O(\lvert B\rvert\cdot m^\ast\cdot n^\ast)$.

**Space complexity:** $O(\lvert A\rvert\cdot m^\ast+n^\ast)$.

## Part B

**Algorithm:**

* let $x\leftarrow 0$;
* let $T\leftarrow$ trie over $A$;
* for $(b_0,\dots b_{n-1})\in B$:
  * define $d_0\leftarrow 1$;
  * define $d_i\leftarrow 0$ for $1\leq i\leq n$;
  * for $i\in(0,\dots,n-1)$:
    * if $d_i=0$, then continue to next $i$;
    * let $T'\leftarrow T$;
    * for $k\in(0,\dots,n-i-1)$:
      * assign $T'\leftarrow$ child of $T'$ matching $b_{i+k}$;
      * if $T'$ is nil, then break iteration;
      * if $T'$ is a leaf, then assign $d_{i+k+1}\leftarrow d_{i+k+1}+d_i$;
  * assign $x\leftarrow x+d_n$;
* return $x$.

**Time complexity:** $O(\lvert B\rvert\cdot m^\ast\cdot n^\ast)$.

**Space complexity:** $O(\lvert A\rvert\cdot m^\ast+n^\ast)$.
