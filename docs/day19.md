<!-- day19.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- Linen Layout -->

# Linen Layout

Let $A,B$ be sets of sequences.

## Part A

**Algorithm:**

* let $k\leftarrow 0$;
* for $(b_0,\dots b_{n-1})\in B$:
  * define $d_i\leftarrow\mathrm{false}$ for $0\leq i\lt n$;
  * assign $d_0\leftarrow\mathrm{true}$;
  * for $i\in(0,\dots,n-1)$:
    * if not $d_i$, then continue to next $i$;
    * for $(a_0,\dots,a_{m-1})\in A$:
      * assign $d_{i+m}\leftarrow(b_i,\dots,b_{i+m})\equiv(a_0,\dots,a_{m-1})$;
  * if $d_{n-1}$, then assign $k\leftarrow k+1$;
* return $k$.
