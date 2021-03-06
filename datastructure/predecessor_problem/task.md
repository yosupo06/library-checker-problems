## @{keyword.statement}

@{lang.en}
Let $S$ be a set consisting of integers between $0$ to $N-1$. Process the following $Q$ queries: 

- 0 $k$ : Insert $k$ into $S$.
- 1 $k$ : Remove $k$ from $S$.
- 2 $k$ : if $S$ contains $k$, print $1$. Otherwise, print $0$.
- 3 $k$ : Print the smallest key which is greater than or equal to $k$(if there are no keys, print $-1$).
- 4 $k$ : Print the largest key which is smaller than or equal to $k$(if there are no keys, print $-1$).
@{lang.ja}
N未満の非負整数からなる集合$S$が与えられます。以下で説明されるクエリを順に$Q$回処理してください。

- 0 $k$ : $k$を$S$に挿入する
- 1 $k$ : $k$を$S$から取り除く
- 2 $k$ : $k$が$S$に属する場合は$1$,そうでない場合は$0$を出力
- 3 $k$ : $S$に属する$k$以上の要素のうち最小のものを出力(存在しない場合は$-1$を出力)
- 4 $k$ : $S$に属する$k$以下の要素のうち最大のものを出力(存在しない場合は$-1$を出力)
@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $0 \leq k_i \lt N$

## @{keyword.input}

@{lang.en}
The initial state of $S$ is given as a length $N$ string $T$  consisting of $0$ and $1$. $S$ contains $i$ if and only if $T_i = 1$.
@{lang.ja}
クエリを処理する前の集合$S$は$0,1$からなる長さ$N$の文字列$T$で与えられる。$T_i$が$1$の時、かつその時に限り$i$は$S$に属する。
@{lang.end}

```
$N\ Q$
$T$
$c_0\ k_0$
$c_1\ k_1$
$\vdots$
$c_{Q-1}\ k_{Q-1}$
```

## @{keyword.sample}

@{example.example_00}
