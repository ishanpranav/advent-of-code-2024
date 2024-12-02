<!-- day02.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- Red-Nosed Reports -->

# Day 2: Red-Nosed Reports

Let $L$ be a set of lists where for all $\ell\in L$, for all $e\in\ell$, we have
$e\in\mathbb{R}$.

**Algorithm 1.**

* let $n\leftarrow 0$;
* for $\ell\in L$:
  * let $a\leftarrow$invoke Algorithm 2 with argument $\ell$;
  * if $a$, then assign $n\leftarrow n+1$;
* return $n$.

## Part A

**Algorithm 2** with list $\ell$ as an argument.

* let $s\leftarrow 0$;
* for $i\in(1,\dots,\mathrm{len}(\ell)-1)$:
  * if $\lvert\ell_i-\ell_{i-1}\rvert\lt 1$ or $\lvert\ell_i-\ell_{i-1}\rvert\gt 3$, then return $\text{false}$;
  * if $s\neq 0$, then:
    * if $\mathrm{sgn}(\ell_i-\ell_{i-1})\neq s$, then return $\text{false}$;
  * otherwise:
    * assign $s\leftarrow\mathrm{sgn}(\ell_i-\ell_{i-1})$;
* return $\text{true}$.

## Part B
