## @{keyword.statement}
長さ $N$ の文字列 $S$ が与えられます。$S$ のrun、つまり以下の条件を満たすタプル $(t, l, r)$ を列挙してください。

- $S$ の $l$ 文字目から $r - 1$ 文字目の __最小__ 周期は $t$ であり、$r - l \geq 2t$ を満たす ($l$, $r$ は0-indexed)
- 上の条件を満たすもののうち、$l, r$ は極大である。つまり $(t, l - 1, r), (t, l, r + 1)$ は上の条件を満たさない

## @{keyword.constraints}

- $1 \leq N \leq 200,000$
- $S$ は英小文字からなる


## @{keyword.input}

```
$S$
```

## @{keyword.output}

```
$M$
$t_1$ $l_1$ $r_1$
$t_2$ $l_2$ $r_2$
:
$t_M$ $l_M$ $r_M$
```

ただし、$M$ はrunの個数とし、またrunは $(t, l, r)$ の順で辞書順にsortして出力すること

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}

@{example.example_03}
