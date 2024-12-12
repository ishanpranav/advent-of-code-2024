<!-- day11.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- Plutonian Pebbles -->

# Day 11: Plutonian Pebbles

Let $\ell$ be a list where for $e\in\ell$ we have $e\in\mathbb{N}$.

## Part A

**Algorithm 1:**

* let $n\leftarrow$ invoke Algorithm 2 with argument $k=25$;
* return $n$.

**Algorithm 2** with argument $k\in\mathbb{N}$:

* let $\Sigma\leftarrow 0$;
* for $e\in\ell$:
  * let $a\leftarrow$ invoke Algorithm 3 with arguments $n=e$ and $k$;
  * assign $\Sigma\leftarrow\Sigma+a$;
* return $\Sigma$.

**Algorithm 3** with arguments $n,k\in\mathbb{N}$:

* if $k=0$, then return $0$;
* if $n=0$, then:
  * let $a\leftarrow$ invoke Algorithm 3 with arguments $n=1$ and $k-1$;
  * return $a$;
* let $d\leftarrow\lfloor\log_{10}{n}+1\rfloor$;
* if $2\mid d$, then:
  * let $a\leftarrow$ invoke Algorithm 3 with arguments $n\mod 10^{\frac{d}{2}}$ and $k-1$;
  * let $b\leftarrow$ invoke Algorithm 3 with arguments $\left\lfloor\frac{n}{10^{\frac{d}{2}}}\right\rfloor$ and $k-1$;
  * return $a+b$;
* let $a\leftarrow$ invoke Algorithm 3 with arguments $2024\cdot n$ and $k-1$;
* return $a$.

**Time complexity:** $O(n)$.

**Space complexity:** $O(n)$.

## Part B

**Algorithm 3:**

* let $n\leftarrow$ invoke Algorithm 2 with argument $k=75$;
* return $n$.

**Time complexity:** $O(n)$.

**Space complexity:** $O(n)$.
