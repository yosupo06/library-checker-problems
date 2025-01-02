## @{keyword.statement}

@{lang.en}
Given a size $N$ interger sequence $a_0, a_1, \dots, a_{N - 1}$. Initially, $a_i = 0$ for all $i$. 
Process $Q$ queries as follows:

- `0 $l$ $r$ $b$ $c$`: For each $i = l, l+1, \dots, {r - 1}$, $a_i \gets b \times a_i + c$.
- `1 $l$ $r$`: Print $\sum_{i = l}^{r - 1} a_i \bmod @{param.MOD}$.
@{lang.ja}
長さ $N$ の整数列 $a_0, a_1, \dots, a_{N - 1}$ がある．はじめすべての $i$ について $a_i=0$ である．
$Q$ 個のクエリを処理してください．

- `0 $l$ $r$ $b$ $c$`: 各 $i = l, l+1, \dots, {r - 1}$ について，$a_i \gets b \times a_i + c$
- `1 $l$ $r$`: $\sum_{i = l}^{r - 1} a_i \bmod @{param.MOD}$ を出力する．
@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $1 \leq Q \leq @{param.Q_MAX}$
- $0 \leq l < r \leq N$
- $1 \leq b < @{param.MOD}$
- $0 \leq c < @{param.MOD}$

## @{keyword.input}

~~~
$N$ $Q$
$\textrm{Query}_0$
$\textrm{Query}_1$
:
$\textrm{Query}_{Q - 1}$
~~~

@{example.example_00}

