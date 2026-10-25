## @{keyword.statement}

@{lang.en}
This problem has $T$ cases.

You are given a simple undirected graph with $N$ vertices and $M$ edges. The $i$-th edge connects vertices $a_i$ and $b_i$. The graph is not necessarily connected.

Determine whether the graph is planar, i.e. whether it can be drawn in the plane with no two edges crossing. If it is, output a planar embedding as a rotation system: for each vertex, the cyclic order of its neighbors around it in such a drawing.
@{lang.ja}
この問題は $T$ ケースあります．

$N$ 頂点 $M$ 辺の単純無向グラフが与えられます．$i$ 番目の辺は頂点 $a_i$ と頂点 $b_i$ を結んでいます．このグラフは連結とは限りません．

このグラフが平面グラフであるか（辺が交差しないように平面に描けるか）判定し，平面グラフならばその平面埋め込みを回転系（rotation system）として出力してください．すなわち，各頂点について，その描画において隣接頂点がその頂点の周りに現れる巡回順序を出力してください．
@{lang.end}

## @{keyword.constraints}

@{lang.en}

- $@{param.T_MIN} \leq T \leq @{param.T_MAX}$
- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.M_MIN} \leq M \leq @{param.M_MAX}$
- $0 \leq a_i, b_i \lt N$
- $a_i \neq b_i$
- $\lbrace a_i, b_i \rbrace \neq \lbrace a_j, b_j \rbrace$ for $i \neq j$
- The sum of $N$ over all test cases does not exceed $@{param.N_MAX}$.
- The sum of $M$ over all test cases does not exceed $@{param.M_MAX}$.

@{lang.ja}

- $@{param.T_MIN} \leq T \leq @{param.T_MAX}$
- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.M_MIN} \leq M \leq @{param.M_MAX}$
- $0 \leq a_i, b_i \lt N$
- $a_i \neq b_i$
- $i \neq j$ ならば $\lbrace a_i, b_i \rbrace \neq \lbrace a_j, b_j \rbrace$
- 全てのテストケースに対する $N$ の総和は $@{param.N_MAX}$ を超えない．
- 全てのテストケースに対する $M$ の総和は $@{param.M_MAX}$ を超えない．

@{lang.end}

## @{keyword.input}

```
$T$
$N$ $M$
$a_0$ $b_0$
$a_1$ $b_1$
$\vdots$
$a_{M - 1}$ $b_{M - 1}$
$N$ $M$
$a_0$ $b_0$
$a_1$ $b_1$
$\vdots$
$a_{M - 1}$ $b_{M - 1}$
$\vdots$
```

## @{keyword.output}

@{lang.en}

For each case, if the graph is not planar, print `No`. Otherwise, print a planar embedding in the following format.

@{lang.ja}

各ケースについて，グラフが平面グラフでなければ `No` を出力してください．平面グラフならば，平面埋め込みを次の形式で出力してください．

@{lang.end}

~~~
Yes
$c_{0, 0}$ $c_{0, 1}$ $\ldots$ $c_{0, \deg(0) - 1}$
$c_{1, 0}$ $c_{1, 1}$ $\ldots$ $c_{1, \deg(1) - 1}$
$\vdots$
$c_{N - 1, 0}$ $c_{N - 1, 1}$ $\ldots$ $c_{N - 1, \deg(N - 1) - 1}$
~~~

@{lang.en}

- $c_{v, 0}, c_{v, 1}, \ldots, c_{v, \deg(v) - 1}$ are the neighbors of vertex $v$ in clockwise order around $v$, in some fixed planar drawing of the graph.
- If $\deg(v) = 0$, print an empty line.
- If there are multiple solutions, print any of them.

@{lang.ja}

- $c_{v, 0}, c_{v, 1}, \ldots, c_{v, \deg(v) - 1}$ は，グラフのある平面描画を固定したときに，頂点 $v$ の隣接頂点を $v$ の周りに時計回りに並べたものです．
- $\deg(v) = 0$ の場合は空行を出力してください．
- 正しい出力が複数存在する場合は，どれを出力しても構いません．

@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
