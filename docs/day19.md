<!-- day19.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- Linen Layout -->

# Linen Layout

Let $A,B$ be sets of sequences.

## Part A

**Algorithm:**

* let $x\leftarrow 0$;
* for $(b_0,\dots b_{n-1})\in B$:
  * define $d_0\leftarrow\mathrm{true}$;
  * define $d_k\leftarrow\mathrm{false}$ for $1\leq k\leq n$;
  * for $k\in(1,\dots,n)$:
    * for $(a_0,\dots,a_{m-1})\in A$:
      * if $(b_{k-m},\dots,b_{k-1})\equiv(a_0,\dots,a_{m-1})$, then:
        * assign $d_k\leftarrow d_k\lor d_{k-m}$;
  * if $d_n$, then assign $x\leftarrow x+1$;
* return $x$.
