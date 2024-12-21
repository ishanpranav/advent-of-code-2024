<!-- day16.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- Reindeer Maze -->

# Day 16: Reindeer Maze

Let $G=(V,E)$ be a graph.

Let $D$ be the set of directions where for all $d\in D$, we have $d:V\to V$.

Let $R_0:D\to D$ and $R_1:D\to D$ be rotation functions.

Let $s\in V$ be the source vertex, $t\in V$ be the target vertex, and
$d^\ast\in D$ be the current direction.

## Part A

**Algorithm 1:**

* let $(w^\ast,\dots)\leftarrow$ invoke Algorithm 2;
* return $w^\ast$.

**Algorithm 2 (Dijkstra's algorithm):**

* let $Q\leftarrow$ empty priority queue;
* let $w_{u,d}\leftarrow+\infty$ for all $u\in V$ and all $d\in D$;
* enqueue item $(s,d^\ast)$ into $Q$ with priority $0$;
* assign $w_{s,d^\ast}\leftarrow 0$;
* let $w^\ast\leftarrow+\infty$;
* while $Q$ is not empty:
  * let item $(u,d)$, priority $w\leftarrow$ dequeue from $Q$;
  * if $w_{u,d}\leq w$, then continue to next iteration;
  * if $u=t$, then assign $w^\ast\leftarrow w_{u,d}$;
  * if $u+d\in V$, then:
    * assign $w_{u+d,d}\leftarrow w+1$;
    * enqueue item $(u+d,d)$ into $Q$ with priority $w+1$;
  * assign $w_{u,R_0(d)}\leftarrow w+1000$;
  * enqueue item $(u,R_0(d))$ into $Q$ with priority $w+1000$;
  * assign $w_{u,R_1(d)}\leftarrow w+1000$;
  * enqueue item $(u,R_1(d))$ into $Q$ with priority $w+1000$;
* return $(w^\ast,w_{u,d}~\forall u\in V~\forall d\in D)$.

**Time complexity:** $O((\lvert V\rvert+\lvert E\rvert)\log{\lvert V\rvert})=O(\lvert V\rvert\log{\lvert V\rvert})$ for $\lvert E\rvert=O(\lvert V\rvert)$.

**Space complexity:** $O(\lvert V\rvert)$.

## Part B

**Algorithm 3:**

* let $(w^\ast,w_{u,d}~\forall u\in V~\forall d\in D)\leftarrow$ invoke Algorithm 2;
* let $r_u\leftarrow\mathrm{false}$ for all $u\in V$;
* let $x\leftarrow 0$;
* for $d\in D$:
  * if $w_{t,d}=w^\ast$, then:
    * assign $r_u~\forall u\in V\leftarrow$ invoke Algorithm 4 with arguments $t,d,w^*,r_u~\forall u\in V$;
* return $\lvert\lbrace u\mid r_u=\mathrm{true}\rbrace\rvert$.

**Algorithm 4 (Depth-first search)** with $u\in V,d\in D,w^*$, and $r_v\in\lbrace\mathrm{true},\mathrm{false}\rbrace$ for all $v\in V$ as arguments:

* assign $r_u\leftarrow\mathrm{true}$;
* if $u=s$, then return $r_v~\forall v\in V$;
* if $u-d\in V$ and $w^\ast-1=w_{u-d,d}$, then:
  * assign $r_v~\forall v\in V\leftarrow$ invoke Algorithm 4 with arguments $u+d,d,w^\ast-1,r_v~\forall v\in V$;
* if $w^\ast-1000=w_{u,R_1(d)}$, then:
  * assign $r_v~\forall v\in V\leftarrow$ invoke Algorithm 4 with arguments $u,R_1(d),w^\ast-1000,r_v~\forall v\in V$;
* if $w^\ast-1000=w_{u,R_0(d)}$, then:
  * assign $r_v~\forall v\in V\leftarrow$ invoke Algorithm 4 with arguments $u,R_0(d),w^\ast-1000,r_v~\forall v\in V$;
* return $r_v~\forall v\in V$.

**Time complexity:** $O((\lvert V\rvert+\lvert E\rvert)\log{\lvert V\rvert})=O(\lvert V\rvert\log{\lvert V\rvert})$ for $\lvert E\rvert=O(\lvert V\rvert)$.

**Space complexity:** $O(\lvert V\rvert)$.
