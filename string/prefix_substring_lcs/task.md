## @{keyword.statement}

@{lang.en}
You are given a string $S$ of length $M$ and a string $T$ of length $N$.
Process the following $Q$ queries in order:

- `$a$ $b$ $c$`: Print the length of the longest common subsequence of $(S_0, S_1, \dots, S_{a-1})$ and $(T_b, T_{b+1}, \dots, T_{c-1})$.
@{lang.ja}
長さ $M$ の文字列 $S$ と長さ $N$ の文字列 $T$ が与えられます。
以下で説明されるクエリを順に $Q$ 回処理してください:

- `$a$ $b$ $c$`: $(S_0, S_1, \dots, S_{a-1})$ と $(T_b, T_{b+1}, \dots, T_{c-1})$ の最長共通部分列の長さを出力する。
@{lang.end}

## @{keyword.constraints}

@{lang.en}

- $@{param.M_MIN} \leq M \leq @{param.M_MAX}$
- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $0 \leq a_i \leq M$
- $0 \leq b_i \leq c_i \leq N$
- Each character of $S$ and $T$ is lowercase English letters.

@{lang.ja}

- $@{param.M_MIN} \leq M \leq @{param.M_MAX}$
- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $0 \leq a_i \leq M$
- $0 \leq b_i \leq c_i \leq N$
- $S, T$ は英小文字からなる。

@{lang.end}

## @{keyword.input}


```
$Q$
$S$
$T$
$a_0$ $b_0$ $c_0$
$a_1$ $b_1$ $c_1$
$\vdots$
$a_{Q-1}$ $b_{Q-1}$ $c_{Q-1}$
```

## @{keyword.sample}

@{example.example_00}
