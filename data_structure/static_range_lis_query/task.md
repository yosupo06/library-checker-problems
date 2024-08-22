## @{keyword.statement}

@{lang.en}
You are given permutation $P$ of $\lbrace 0, 1, \dots, N-1 \rbrace$.
Process the following $Q$ queries in order:

- `$l$ $r$`: Print the length of the longest increasing subsequence of $(P_l, P_{l+1}, \dots, P_{r-1})$.
@{lang.ja}
$\lbrace 0, 1, \dots, N-1 \rbrace$ の順列 $P$ が与えられます。
以下で説明されるクエリを順に $Q$ 回処理してください:

- `$l$ $r$`: $(P_l, P_{l+1}, \dots, P_{r-1})$ の最長増加部分列の長さを出力する。
@{lang.end}

## @{keyword.constraints}

@{lang.en}
- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $P$ is a permutation of $\lbrace 0, 1, \dots, N-1 \rbrace$
- $0 \leq l_i \leq r_i \leq N$
@{lang.ja}
- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $P$ は $\lbrace 0, 1, \dots, N-1 \rbrace$ の順列
- $0 \leq l_i \leq r_i \leq N$
@{lang.end}

## @{keyword.input}


```
$N$ $Q$
$P_0$ $P_1$ $\cdots$ $P_{N-1}$
$l_0$ $r_0$
$l_1$ $r_1$
$\vdots$
$l_{Q-1}$ $r_{Q-1}$
```

## @{keyword.sample}

@{example.example_00}
