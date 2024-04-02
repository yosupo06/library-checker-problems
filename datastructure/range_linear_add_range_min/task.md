## @{keyword.statement}

@{lang.en}
Given a size $N$ interger sequence $a_0, a_1, \dots, a_{N - 1}$. Process $Q$ queries as follows:

- `0 $l$ $r$ $b$ $c$`: For each $i = l, l+1, \dots, {r - 1}$, $a_i \gets a_i+b+c$.
- `1 $l$ $r$`: Print $\min_{i \in [l,r)} a_i$.
@{lang.ja}
長さ $N$ の整数列 $a_0, a_1, \dots, a_{N - 1}$ が与えられます。$Q$ 個のクエリが飛んできます。処理してください。

- `0 $l$ $r$ $b$ $c$`: 各 $i = l, l+1, \dots, {r - 1}$ について、$a_i \gets a_i+bi+c$
- `1 $l$ $r$`: $\min_{i \in [l,r)} a_i$ を出力する。
@{lang.end}

## @{keyword.constraints}

- $1 \leq N, Q \leq @{param.N_AND_Q_MAX}$
- $|a_i| < @{param.A_MAX}$
- $0 \leq l < r\leq N$
- $|b| < @{param.B_MAX}$
- $|c| < @{param.C_MAX}$

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
