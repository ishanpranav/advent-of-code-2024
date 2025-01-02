<!-- day18.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- RAM Run -->

# RAM Run

## Part A

Let $G=(V,E)$ be a graph. Let $s,t\in V$.

**Algorithm:**

* let $w_u~\forall u\in V\leftarrow$ breadth-first search of $G$ from $s$;
* return $w_t$.

**Time complexity:** $O(\lvert V\rvert+\lvert E\rvert)=O(\lvert V\rvert)$ for $\lvert E\rvert=O(\lvert V\rvert)$.

**Space complexity:** $O(\lvert V\rvert)=O(\lvert V\rvert)$ for $\lvert E\rvert=O(\lvert V\rvert)$.

## Part B

Let $G=(V,E)$ be a graph. Let $s,t\in V$.

Let $U\subseteq V\setminus\lbrace s,t\rbrace$.

Let $S$ be a stack where for all $u\in S$, we have $u\in U$.

**Algorithm:**

* let $\mathcal{P}\leftarrow$ disjoint set over $V$;
* for $u\in V\setminus U$:
  * for $(u,v)\in E$ where $v\notin U$:
    * union $u,v$ in $\mathcal{P}$;
* let $u\leftarrow$ nil;
* while $s,t$ disjoint in $\mathcal{P}$:
  * assign $u\leftarrow$ pop off of $S$;
  * assign $U\leftarrow U\setminus\lbrace u\rbrace$;
  * for $(u,v)\in E$ where $v\notin U$:
    * union $u,v$ in $\mathcal{P}$;
* return $u$.

**Time complexity:** $O(\lvert V\rvert+\lvert E\rvert)=O(\lvert V\rvert)$ for $\lvert E\rvert=O(\lvert V\rvert)$.

**Space complexity:** $O(\lvert V\rvert)=O(\lvert V\rvert)$ for $\lvert E\rvert=O(\lvert V\rvert)$.
