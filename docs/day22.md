<!-- day22.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- Monkey Market -->

# Monkey Market

Let $S$ be a set and $m\in\mathbb{Z}$.

## Part A

**Algorithm:**

* let $\Sigma\leftarrow 0$;
* for $n\in S$:
  * let $n'\leftarrow n$;
  * for $m$ iterations:
    * assign $n'\leftarrow(n'\oplus 2^6\cdot n')\mod 2^{24}$;
    * assign $n'\leftarrow\left(n'\oplus\lfloor\frac{n'}{2^5}\rfloor\right)\mod 2^{24}$;
    * assign $n'\leftarrow(n'\oplus 2^{11}\cdot n')\mod 2^{24}$;
  * assign $\Sigma\leftarrow\Sigma+n'$;
* return $\Sigma$.

**Time complexity:** $O(\lvert S\lvert\cdot m)$.

**Space complexity:** $O(1)$.
