<!-- day23.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- LAN Party -->

# Day 23: LAN Party

Let $G=(V,E)$ be an undirected graph. Let $U\subseteq V$.

## Part A

**Algorithm:**

* let $n\leftarrow 0$;
* for $\lbrace u,v\rbrace\in E$:
  * for $w\in U\cap\lbrace w\mid\lbrace u,w\rbrace\in E\rbrace\cap\lbrace w\mid\lbrace v,w\rbrace\in E\rbrace$:
    * assign $n\leftarrow n+1$;
* return $n$.

**Time complexity:** $O(\lvert E\rvert^2)$.

**Space complexity:** $O(1)$.
