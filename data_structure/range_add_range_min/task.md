## @{keyword.statement}

@{lang.en}
Given a size $N$ integer sequence $a_0, a_1, \dots, a_{N - 1}$. Process the following $Q$ queries in order:

- `0 $l$ $r$ $x$`: For each $i = l, l+1, \dots, {r - 1}$, $a_i \gets a_i + x$.
- `1 $l$ $r$`: Print $\min_{l \le i \le r-1} a_i$.
@{lang.ja}
長さ $N$ の整数列 $a_0, a_1, \dots, a_{N - 1}$ が与えられます．$Q$ 個のクエリが飛んできます．処理してください．

- `0 $l$ $r$ $x$`: 各 $i = l, l+1, \dots, {r - 1}$ について，$a_i \gets a_i + x$.
- `1 $l$ $r$`: $\min_{l \le i \le r-1} a_i$ を出力する．
@{lang.end}

## @{keyword.constraints}

@{lang.en}
- $1 \leq N, Q \leq @{param.N_AND_Q_MAX}$
- $|a_i|, |x| \leq @{param.A_AND_X_ABS_MAX}$
- $0 \leq l < r \leq N$
- The values in input are all integers．

@{lang.ja}
- $1 \leq N, Q \leq @{param.N_AND_Q_MAX}$
- $|a_i|, |x| \leq @{param.A_AND_X_ABS_MAX}$
- $0 \leq l < r \leq N$
- 入力は全て整数．

@{lang.end}

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
