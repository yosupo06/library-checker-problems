## @{keyword.statement}

@{lang.en}
Given a size $N$ interger sequence $a_0, a_1, \dots, a_{N - 1}$. Process $Q$ queries as follows:

- `0 $l$ $r$ $k$`: For each $i = l, l+1, \dots, r$, $a_i \gets a_i + (i - l + 1) \times k$.
- `1 $l$ $r$`: Print $\sum_{i = l}^{r} a_i \bmod @{param.MOD}$.
@{lang.end}

## @{keyword.constraints}

- $1 \leq N, Q \leq @{param.N_AND_Q_MAX}$
- $-@{param.A_K_MIN_MAX} \leq a_i, k \leq @{param.A_K_MIN_MAX}$
- $0 \leq l \le r \le N$

## @{keyword.input}

~~~
$N$ $Q$
$a_0$ $a_1$ ... $a_{N - 1}$
$\textrm{Query}_0$
$\textrm{Query}_1$
:
$\textrm{Query}_{Q - 1}$
~~~

@{example.example_00}
