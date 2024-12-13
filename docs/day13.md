<!-- day13.md -->
<!-- Copyright (c) 2024-2025 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

<!-- Claw Contraption -->

# Day 13: Claw Contraption

Let $S$ be a set where each pair $(\mathbf{A},\mathbf{b})\in S$ represents a
system of linear equations $\mathbf{A}\mathbf{x}=\mathbf{b}$ using the
$n\times n$ coefficient matrix $\mathbf{A}$, solution vector $\mathbf{x}$, and
constant vector $\mathbf{b}$.

Let $\mathbf{v}$ be a weight vector.

## Part A

**Algorithm:**

* let $m\leftarrow 0$;
* for $(\mathbf{A},\mathbf{b})\in S$:
  * let $\mathbf{A}'\leftarrow$ augmented $n\times(n+1)$ matrix for $\mathbf{A}\mathbf{x}=\mathbf{b}$;
  * let $\mathbf{A}''\leftarrow$ forward elimination of $\mathbf{A}'$ where $\mathbf{A}''$ is in row-echelon form;
  * if $\mathbf{A}''$ is inconsistent, then continue to next $(\mathbf{A},\mathbf{b})$;
  * assign $\mathbf{x}\leftarrow$ back substitution of $\mathbf{A}''$;
  * assign $\mathbf{x}=(x_i)\leftarrow(\lfloor x_i\rfloor)$;
  * if $\mathbf{A}''\mathbf{x}\neq\mathbf{b}$, then continue to next $(\mathbf{A},\mathbf{b})$;
  * $m\leftarrow m+\mathbf{v}\cdot\mathbf{x}$;
* return $m$.

**Time complexity:** $O(n^3)$.

**Space complexity:** $O(1)$.
