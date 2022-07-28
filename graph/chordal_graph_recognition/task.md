## @{keyword.statement}

@{lang.en}
You are given a simple undirected unweighted graph, consisting of $N$ vertices and $M$ edges.  
The $i$-th edge is between vertex $a_i$ and vertex $b_i$.

A graph is chordal if it does not have an induced cycle of length four or more.
A perfect elimination ordering is an ordering of the vertices such that for every vertex $v$, $v$ and the neighbors of $v$ that appear after it in the ordering form a clique.
It can be shown that a graph is chordal if and only if it has a perfect elimination ordering.

If the graph is chordal, find a perfect elimination ordering. If there are multiple perfect elimination orderings, print any of them.

If the graph is not chordal, find an induced cycle of length four or more. If there are multiple such cycles, print any of them.
@{lang.ja}
$N$ 頂点 $M$ 辺の単純無向グラフが与えられます。$i$ 番目の辺は頂点 $a_i$, $b_i$ をつないでいます。

グラフは、長さ $4$ 以上の induced cycle を持たない時、またその時のみ chordal graph と呼びます。
perfect elimination orderingとは、次の条件を満たす頂点の順序付けです: 各頂点 $v$ について、$v$ と $v$ に隣接した、$v$ より後ろの順序の頂点はクリークをなす。

グラフはPerfect elimination orderingを持つときのみ chordal graph であることが知られています。

入力のグラフが chordal graph ならば、perfect elimination ordering を出力してください。
chordal graph ではない場合、長さ $4$ 以上の induced cycle を出力してください。

どちらも複数存在する場合、どれか一つを出力してください。
@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.M_MIN} \leq M \leq @{param.M_MAX}$
- $0 \leq a_i \lt N$
- $0 \leq b_i \lt N$
- $a_i \neq b_i$
- $\lbrace a_i, b_i \rbrace \neq \lbrace a_j, b_j \rbrace (i \neq j)$


## @{keyword.input}

```
$N$ $M$
$a_0$ $b_0$
$a_1$ $b_1$
$a_2$ $b_2$
$\vdots$
$a_{M - 1}$ $b_{M - 1}$
```

## @{keyword.output}

@{lang.en}
If the graph is not chordal, output an induced cycle of length four or more in the following format.
@{lang.ja}
もしグラフが chordal graph ではない場合、次の形式に従い(長さ $4$ 以上の) induced cycle を出力してください。
@{lang.end}
```
NO
$K$
$c_0$ $c_1$ $\ldots$ $c_K$
```
@{lang.en}
$K$ represents length of the induced cycle.
$c_i$ is the $i$-th vertex in the cycle.
@{lang.ja}
$K$ はサイクルの長さ。
$c_i$ はサイクルの $i$ 番目の頂点です。
@{lang.end}

@{lang.en}
If the graph is chordal, output a perfect elimination ordering in the following format.
@{lang.ja}
もしグラフが chordal graph の場合、次の形式に従い perfect elimination ordering を出力してください。
@{lang.end}
```
YES
$v_0$ $v_1$ $\ldots$ $v_N$
```

@{lang.en}
$v_i$ is the $i$-th vertex in the perfect elimination ordering.
@{lang.ja}
$v_i$ は perfect elimination ordering の $i$ 番目の頂点です。
@{lang.end}

## @{keyword.sample}

@{example.example_00}
@{example.example_01}
@{example.example_02}
