## @{keyword.statement}

@{lang.en}

Given a multiset $S=\lbrace S_1, \ldots, S_N \rbrace$. Process the following $Q$ queries in order:

- `0 x`: Add $x$ to $S$.
- `1`: Output one of the minimum elements in $S$ and remove it from $S$.
- `2`: Output one of the maximum elements in $S$ and remove it from $S$.

It is guaranteed that $S$ is not empty when processing queries of types `1` and `2`.

@{lang.ja}

多重集合 $S=\lbrace S_1, \ldots, S_N \rbrace$ が与えられます。以下の形式のクエリ $Q$ 個を順に処理してください。

- `0 x`: $S$ に $x$ を追加する。
- `1`: $S$ に含まれる最小の要素を出力して $S$ から除く。最小の要素が複数ある場合は $1$ つだけ除く。
- `2`: $S$ に含まれる最大の要素を出力して $S$ から除く。最大の要素が複数ある場合は $1$ つだけ除く。

ただし、タイプ `1`, `2` のクエリを処理する直前に $S$ が空ではないことが保証される。

@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $@{param.V_MIN} \leq S _ i, x \leq @{param.V_MAX}$

## @{keyword.input}

```
$N\; Q$
$S_1 \cdots S_N$
$\mathrm{Query}_0$
$\vdots$
$\mathrm{Query}_{Q-1}$
```

## @{keyword.sample}

@{example.example_00}
