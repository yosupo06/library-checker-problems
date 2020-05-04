## @{keyword.statement}

@{lang.en}
You are given an integer sequence $a_0, a_1, ..., a_{N-1}$ with the length $N$.
Process the following $Q$ queries in order:

- `0 $p$ $x$`: $a_p \gets a_p + x$
- `1 $l$ $r$`: Print $\sum_{i = l}^{r - 1}{a_i}$
@{lang.ja}
長さ $N$ の数列 $a_0, a_1, ..., a_{N-1}$ に $Q$ 個のクエリが飛んできます。処理してください。

- `0 $p$ $x$`: $a_p \gets a_p + x$
- `1 $l$ $r$`: $\sum_{i = l}^{r - 1}{a_i}$ を出力する。
@{lang.end}


## @{keyword.constraints}

- $1 \leq N, Q \leq 500,000$
- $0 \leq a_i, x \leq 10^9$
- $0 \leq p < N$
- $0 \leq l_i < r_i \leq N$

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
