<!-- day05.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- Print Queue -->

# Day 5: Print Queue

Let $G=(V,E)$ be a directed graph. Let $X$ be a set of directed acyclic induced
subgraphs of $G$ with ordered vertices.

## Part A

**Algorithm:**

* let $n\leftarrow 0$;
* for $G'=(V',E')\in X$:
  * $(t_0,\dots,t_{\lvert V'\rvert})\leftarrow$ topological sort of $G'$;
  * for $i\in\lbrace 0,\dots,\lvert V'\rvert\rbrace$:
    * if $V'_i\neq t_i$, then continue to next $G'$;
  * assign $n\leftarrow n+t_{\left\lfloor\frac{\lvert V'\rvert}{2}\right\rfloor}$;
* return $n$.

**Time complexity:** $O(\lvert X\rvert\cdot(\lvert V\rvert+\lvert E\rvert))$.

**Space complexity:** $O(\lvert V\rvert)$.

## Part B

**Algorithm:**

* let $n\leftarrow 0$;
* for $G'=(V',E')\in X$:
  * $(t_0,\dots,t_{\lvert V'\rvert})\leftarrow$ topological sort of $G'$;
  * for $i\in\lbrace 0,\dots,\lvert V'\rvert\rbrace$:
    * if $V'_i\neq t_i$, then:
      * assign $n\leftarrow n+t_{\left\lfloor\frac{\lvert V'\rvert}{2}\right\rfloor}$;
      * continue to next $G'$;
* return $n$.

**Time complexity:** $O(\lvert X\rvert\cdot(\lvert V\rvert+\lvert E\rvert))$.

**Space complexity:** $O(\lvert V\rvert)$.
