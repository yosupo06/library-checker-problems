## @{keyword.statement}

@{lang.en}
You are given an integer sequence $a_0, a_1, ..., a_{N-1}$ with the length $N$.
Process the following $Q$ queries in order:

- `0 $p$ $x$`: $a_p \gets x$
- `1 $l$ $r$`: Print the majority element in $(a_l, a_{l+1}, ..., a_{r-1})$. If there is no majority element, print $-1$.

@{lang.ja}
長さ $N$ の整数列 $a_0, a_1, \dots, a_{N - 1}$ が与えられます。
$i=0,1,\ldots ,Q-1$ についてクエリを処理してください。

- `0 $p$ $x$`: $a_{p} \gets x$
- `1 $l$ $r$`: $a_{l} \ldots a_{r-1}$ に過半数を占める要素があればそれを、なければ $-1$ を出力

@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $0 \leq p < N$
- $@{param.A_MIN} \leq x \leq @{param.A_MAX}$
- $0 \leq l < r \leq N$

## @{keyword.input}

~~~
$N$ $Q$
$a_0$ $a_1$ ... $a_{N-1}$
$\textrm{Query}_0$
$\textrm{Query}_1$
:
$\textrm{Query}_{Q-1}$
~~~

@{example.example_00}
