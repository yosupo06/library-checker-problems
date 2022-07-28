## @{keyword.statement}

@{lang.en}

Given a length $N$ string $S$. Please enumerate the runs of $S$. In other words, please enumerate tuples $(t, l, r)$ that satisfy the following conditions.

- The minimum period of the $S[l..r-1]$ is $t$, and $r - l \geq 2t$ is satisfied.
- $l$ and $r$ are maximal. In other words, $(t, l - 1, r)$ and $(t, l, r + 1)$ do not satisfy the above condition.

@{lang.ja}

長さ $N$ の文字列 $S$ が与えられます。$S$ のrun、つまり以下の条件を満たすタプル $(t, l, r)$ を列挙してください。

- $S$ の $l$ 文字目から $r - 1$ 文字目の __最小__ 周期は $t$ であり、$r - l \geq 2t$ を満たす ($l$, $r$ は0-indexed)
- 上の条件を満たすもののうち、$l, r$ は極大である。つまり $(t, l - 1, r), (t, l, r + 1)$ は上の条件を満たさない

@{lang.end}

## @{keyword.constraints}

@{lang.en}

- $1 \leq N \leq 200,000$
- Each character of $S$ is lowercase English letters.

@{lang.ja}

- $1 \leq N \leq 200,000$
- $S$ は英小文字からなる。

@{lang.end}

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

@{lang.en}

Here, $M$ is the number of runs, and runs are printed as $(t, l, r)$ tuples in lexicographical order.

@{lang.ja}

ただし、$M$ はrunの個数とし、またrunは $(t, l, r)$ の順で辞書順にsortして出力すること

@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}

@{example.example_03}
