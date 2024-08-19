## @{keyword.statement}

@{lang.en}
You are given an integer sequence $a_0, a_1, \ldots, a_{N-1}$ with the length $N$. Process the following $Q$ queries in order:

- $l$ $r$ : Print the number of distinct integers that occur in $a_{l}, a_{l+1}, \ldots, a_{r-1}$.
@{lang.ja}
長さ $N$ の整数列 $a_0, a_1, \ldots, a_{N-1}$ が与えられます。以下のクエリを順に $Q$ 個処理してください:

- $l$ $r$ : $a_{l}, a_{l+1}, \ldots, a_{r-1}$ に現れる相異なる整数の個数を出力する。
@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $@{param.A_MIN} \leq a_i \leq @{param.A_MAX}$
- $0 \leq l \leq r \leq N$

## @{keyword.input}

```
$N$ $Q$
$a_0$ $a_1$ $\cdots$ $a_{N-1}$
$l_0$ $r_0$
$l_1$ $r_1$
$\vdots$
$l_{Q-1}$ $r_{Q-1}$
```

## @{keyword.sample}

@{example.example_00}
