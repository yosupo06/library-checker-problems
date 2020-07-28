## @{keyword.statement}

@{lang.en}

You are given an integer sequence $(A_0, A_1, \ldots, A_{N-1})$ 
with the length $N$. Process the following $Q$ queries in order.

- `$l_i$ $r_i$`: Print the number of inversions in $(A_{l_i}, A_{l_i+1}, \ldots, A_{r_i-1})$

An inversion in a sequence $(B_0, B_1, \ldots, B_{M-1})$
is a pair of indices $(i, j)$ such that
$0 \leq i < j \lt M$ and $B_i \gt B_j$.

@{lang.ja}

長さ$N$の整数列$(A_0, A_1, \ldots, A_{N-1})$が与えられます。
$Q$個のクエリを処理してください。

- `$l_i$ $r_i$`: $(A_{l_i}, A_{l_i+1}, \ldots, A_{r_i-1})$の転倒数を出力

ただし、数列$(B_0, B_1, \ldots, B_{M-1})$の転倒数は
$0 \leq i < j \lt M$かつ$B_i \gt B_j$を満たす組$(i, j)$の個数です。

@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $@{param.A_MIN} \leq A_i \leq @{param.A_MAX}$
- $0 \leq l_i \lt r_i \leq N$

## @{keyword.input}

```
$N$ $Q$
$A_0$ $A_1$ $\ldots$ $A_{N-1}$
$l_0$ $r_0$
$l_1$ $r_1$
$\vdots$
$l_{Q-1}$ $r_{Q-1}$
```

## @{keyword.sample}

@{example.example_00}
