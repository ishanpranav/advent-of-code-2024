<!-- day16.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- Reindeer Maze -->

# Day 16: Reindeer Maze

Let $G=(V,E)$ be a directed graph.

Let $D$ be the set of directions where for all $d\in D$, we have $d:V\to V$.

Let $r_0:D\to D$ and $r_1:D\to D$ be rotation functions.

Let $s\in V$ be the source vertex, $t\in V$ be the target vertex, and
$d^\ast\in D$ be the current direction.

## Part A

**Algorithm:**

* let $Q\leftarrow$ empty priority queue;
* let $w_{u,d}\leftarrow+\infty$ for $u\in V$ and $d\in D$;
* enqueue item $(s,d^\ast)$ into $Q$ with priority $0$;
* while $Q$ is not empty:
  * let item $(u,d)$, priority $w\leftarrow$ dequeue from $Q$;
  * if $u=t$, then return $w$;
  * if $w_{u,d}\leq w$, then continue to next iteration;
  * assign $w_{u,d}\leftarrow w$;
  * let $v\leftarrow u+d$;
  * if $v\in V$, then enqueue item $(v,d)$ into $Q$ with priority $w+1$;
  * enqueue item $(u,r_0(d))$ into $Q$ with priority $w+1000$;
  * enqueue item $(u,r_1(d))$ into $Q$ with priority $w+1000$;
* return $+\infty$.

**Time complexity:** $O((\lvert V\rvert+\lvert E\rvert)\log{\lvert V\rvert})=O(\lvert V\rvert\log{\lvert V\rvert})$ for $\lvert E\rvert=O(\lvert V\rvert)$.
