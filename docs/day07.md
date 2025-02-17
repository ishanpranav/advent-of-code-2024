<!-- day07.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- Bridge Repair -->

# Day 7: Bridge Repair

Let $X\subseteq\mathbb{Z}$. Let $L$ be a set of tuples where for all
$(x,\ell)\in L$, we have $x\in X$, and $\ell$ is a list where for all $e\in\ell$
we have $e\in X$. Let $n^\ast=\max_{(x,\ell)\in L}(\mathrm{len}(\ell))$.

## Part A

**Algorithm 1:**

* let $\Sigma\leftarrow 0$;
* for $(x,\ell)\in L$:
  * let $p\leftarrow$ invoke Algorithm 2 with arguments $x$ and $y=0$ and $\ell$;
  * if $p$, then assign $\Sigma\leftarrow\Sigma+x$;
* return $\Sigma$.
  
**Algorithm 2** with $x,y\in\mathbb{Z}$ and list $\ell=(s_0,\dots,s_{n-1})$ as arguments:

* if $\mathrm{len}(\ell)=0$, then return $x=y$;
* if $y>x$, then return $\mathrm{false}$;
* let $p\leftarrow$ invoke Algorithm 2 with arguments $x,y+s_0,(s_1,\dots,s_{n-1})$;
* if $p$, then return $\mathrm{true}$;
* assign $p\leftarrow$ invoke Algorithm 2 with arguments $x,y\cdot s_0,(s_1,\dots,s_{n-1})$;
* return $p$.

**Time complexity:** $O(\lvert L\rvert\cdot 2^{n^\ast})$.

**Space complexity:** $O(n^\ast)$.

## Part B

**Algorithm 3:**

* let $\Sigma\leftarrow 0$;
* for $(x,\ell)\in L$:
  * let $p\leftarrow$ invoke Algorithm 4 with arguments $x$ and $y=0$ and $\ell$;
  * if $p$, then assign $\Sigma\leftarrow\Sigma+x$;
* return $\Sigma$.
  
**Algorithm 4** with $x,y\in\mathbb{Z}$ and list $\ell=(s_0,\dots,s_{n-1})$ as arguments:

* if $\mathrm{len}(\ell)=0$, then return $x=y$;
* if $y>x$, then return $\mathrm{false}$;
* let $p\leftarrow$ invoke Algorithm 4 with arguments $x,y+s_0,(s_1,\dots,s_{n-1})$;
* if $p$, then return $\mathrm{true}$;
* assign $p\leftarrow$ invoke Algorithm 4 with arguments $x,y\cdot s_0,(s_1,\dots,s_{n-1})$;
* if $p$, then return $\mathrm{true}$;
* let $y'\leftarrow y\cdot 10^{\lfloor\log_{10}{s_0}\rfloor+1}+s_0$;
* assign $p\leftarrow$ invoke Algorithm 4 with arguments $x,y',(s_1,\dots,s_{n-1})$;
* return $p$.

**Time complexity:** $O(\lvert L\rvert\cdot 3^{n^\ast})$.

**Space complexity:** $O(n^\ast)$.
