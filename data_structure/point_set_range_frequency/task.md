## @{keyword.statement}

@{lang.en}
You are given an integer sequence $a_0, a_1, \ldots, a_{N-1}$ with the length $N$. Process the following $Q$ queries in order:

- `0 $k$ $v$`: $a[k] \gets v$
- `1 $l$ $r$ $x$` : Print the number of times $x$ occurs in $a_{l}, a_{l+1}, \ldots, a_{r-1}$.

@{lang.ja}
長さ $N$ の整数列 $a_0, a_1, \ldots, a_{N-1}$ が与えられます。以下のクエリを順に $Q$ 個処理してください:

- `0 $k$ $v$`: $a[k] \gets v$
- `1 $l$ $r$ $x$` : $a_{l}, a_{l+1}, \ldots, a_{r-1}$ に $x$ が出現する回数を出力する。
@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $@{param.A_MIN} \leq a_i \leq @{param.A_MAX}$
- $0 \leq k < N$
- $@{param.A_MIN} \leq v \leq @{param.A_MAX}$
- $0 \leq l \leq r \leq N$
- $@{param.A_MIN} \leq x \leq @{param.A_MAX}$

## @{keyword.input}

```
$N$ $Q$
$a_0$ $a_1$ $\cdots$ $a_{N-1}$
$\mathrm{query}_0$
$\vdots$
$\mathrm{query}_{Q-1}$
```

## @{keyword.sample}

@{example.example_00}
