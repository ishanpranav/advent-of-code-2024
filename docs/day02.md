<!-- day02.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- Red-Nosed Reports -->

# Day 2: Red-Nosed Reports

Let $L$ be a set of lists where for all $\ell\in L$, for all $e\in\ell$, we have
$e\in\mathbb{R}$.

## Part A

**Algorithm 1:**

* let $n\leftarrow 0$;
* for $\ell\in L$:
  * let $i\leftarrow$ invoke Algorithm 2 with argument $\ell$;
  * if $i=\mathrm{len}(\ell)$, then assign $n\leftarrow n+1$;
* return $n$.

**Algorithm 2** with list $\ell$ as an argument; returns the index of the first
"unsafe" index, or $\mathrm{len}(\ell)$ if all indices are "safe":

* let $s\leftarrow 0$;
* for $i\in(1,\dots,\mathrm{len}(\ell)-1)$:
  * if $\lvert\ell_i-\ell_{i-1}\rvert\lt 1$ or $\lvert\ell_i-\ell_{i-1}\rvert\gt 3$, then return $i$;
  * if $s\neq 0$, then:
    * if $\mathrm{sgn}(\ell_i-\ell_{i-1})\neq s$, then return $i$;
  * otherwise:
    * assign $s\leftarrow\mathrm{sgn}(\ell_i-\ell_{i-1})$;
* return $\mathrm{len}(\ell)$.

**Time complexity:** $O(\lvert L\rvert\cdot\max_{\ell\in L}(\text{len}(\ell)))$.

**Space complexity:** $O(1)$.

## Part B

**Algorithm 3:**

* let $n\leftarrow 0$;
* for $\ell\in L$:
  * let $i\leftarrow$ invoke Algorithm 2 with argument $\ell$;
  * if $i=\mathrm{len}(\ell)$, then:
    * assign $n\leftarrow n+1$;
    * continue to next $\ell$;
  * if $i\geq 2$, then:
    * let $\ell'\leftarrow\ell$ with $(i-2)$-th element removed;
    * assign $i\leftarrow$ invoke Algorithm 2 with argument $\ell'$;
    * if $i=\mathrm{len}(\ell)$, then:
      * assign $n\leftarrow n+1$;
      * continue to next $\ell$;
  * if $i\geq 1$, then:
    * let $\ell'\leftarrow\ell$ with $(i-1)$-th element removed;
    * assign $i\leftarrow$ invoke Algorithm 2 with argument $\ell'$;
    * if $i=\mathrm{len}(\ell)$, then:
      * assign $n\leftarrow n+1$;
      * continue to next $\ell$;
* return $n$.

**Time complexity:** $O(\lvert L\rvert\cdot\max_{\ell\in L}(\text{len}(\ell)))$.

**Space complexity:** $O(1)$.
