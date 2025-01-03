<!-- day23.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- LAN Party -->

# Day 23: LAN Party

Let $G=(V,E)$ be an undirected graph. Let $U\subseteq V$.

## Part A

**Algorithm:**

* let $n\leftarrow 0$;
* let $D\leftarrow\emptyset$;
* for $u\in U$:
  * assign $D\leftarrow D\cup\lbrace u\rbrace$;
  * for $(\lbrace u,v\rbrace,\lbrace u,w\rbrace)\in E\times E$:
    * if $v\neq w$ and $\lbrace v,w\rbrace\cap D=\emptyset$ and $(v,w)\in E$, then:
      * assign $n\leftarrow n+1$;
* return $n$.

**Time complexity:** $O(\lvert E\rvert^2)$.

**Space complexity:** $O(1)$.
