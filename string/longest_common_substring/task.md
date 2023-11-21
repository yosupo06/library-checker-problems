## @{keyword.statement}

@{lang.en}

Strings $S$ and $T$ is given. Find a longest common substring of $S$ and $T$. 

@{lang.ja}

文字列 $S, T$ が与えられます．$S$ と $T$ の最長共通部分文字列をひとつ答えてください．

@{lang.end}



## @{keyword.constraints}

@{lang.en}

- $1 \leq |S|, |T| \leq @{param.N_MAX}$
- Each character of $S$, $T$ is lowercase English letters.

@{lang.ja}

- $1 \leq |S|, |T| \leq @{param.N_MAX}$
- $S$, $T$ は英小文字からなる。

@{lang.end}

## @{keyword.input}

```
$S$
$T$
```

## @{keyword.output}

@{lang.en}

Output $a,b,c,d$ when a longest common substring can be taken as $(S_a, \ldots, S_{b-1})$ and $(T_c, \ldots, T_{d-1})$.

```
$a$ $b$ $c$ $d$
```

Here, $S_i$ represents the $(1+i)$-th character of $S$, and $T_j$ represents the $(j+1)$-th character of $T$.

If the longest common substring is empty, print: 

```
$0$ $0$ $0$ $0$
```

@{lang.ja}

最長共通部分文字列として $(S_a, \ldots, S_{b-1})$ と $(T_c, \ldots, T_{d-1})$ がとれるとき，$a,b,c,d$ を出力してください．

```
$a$ $b$ $c$ $d$
```

ただし $S_i$ は $S$ の $(1+i)$ 文字目，$T_j$ は $T$ の $(1+j)$ 文字目を表します．

最長共通部分文字列が空である場合には 

```
$0$ $0$ $0$ $0$
```

と出力してください．

@{lang.end}

## @{keyword.sample}

@{example.example_00}


@{lang.en}
`3 6 4 7` is also accepted. 
@{lang.ja}
`3 6 4 7` も正答です．
@{lang.end}

@{example.example_01}

@{example.example_02}

@{example.example_03}
