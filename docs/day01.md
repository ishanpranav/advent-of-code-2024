<!-- day01.md -->
<!-- Licensed under the MIT license. -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->

<!-- Historian Hysteria -->

# Day 1: Historian Hysteria

## Part A

Let $(a_0,\dots,a_{n-1}),(b_0,\dots,b_{n-1})$ be $n$-element lists with
$a_i,b_i\in\mathbb{Z}$ for all $0\leq i\lt n$.

**Algorithm:**

* sort $(a_0,\dots,a_{n-1})$;
* sort $(b_0,\dots,b_{n-1})$;
* return $\sum_{i=0}^{n-1}{\lvert a_i-b_i\rvert}$.

**Time complexity:** $O(n\log n)$.

**Space complexity:** $O(1)$.

## Part B

Let $X\subseteq\mathbb{Z}$. Let $A,B$ be lists with $a,b\in X$ for all
$a\in A,b\in B$.

**Algorithm:**

* let $c_x\leftarrow 0$ for $x\in X$;
* for $b\in B$, assign $c_b\leftarrow c_b+1$;
* return $\sum_{a\in A}(a\cdot c_a)$.

**Time complexity:** $O(n)$.

**Space complexity:** $O(1)$.
