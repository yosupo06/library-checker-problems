## @{keyword.statement}

@{lang.en}
You are given a simple directed weighted graph, consisting of $N$ vertices and $M$ edges.  
The $i$-th edge is directed from vertex $a_i$ to vertex $b_i$ and has a weight of $c_i$.  
Find the (simple) shortest path from vertex $s$ to vertex $t$, or report that no such path exists.  
If there are multiple shortest paths, print any of them.  
@{lang.ja}
$N$ 頂点 $M$ 辺の単純重み付き有向グラフが与えられます。$i$番目の辺は頂点 $a_i$ から頂点 $b_i$ に張られており、重さは $c_i$ です。

頂点 $s$ から 頂点 $t$ への(単純な)最短パスを一つ構築してください。パスが存在しない場合その旨を報告してください。
@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.M_MIN} \leq M \leq @{param.M_MAX}$
- $0 \leq s \lt N$
- $0 \leq t \lt N$
- $s \neq t$
- $0 \leq a_i \lt N$
- $0 \leq b_i \lt N$
- $a_i \neq a_j$
- $(a_i, b_i) \neq (a_j, b_j) (i \neq j)$
- $@{param.C_MIN} \leq c_i \leq @{param.C_MAX}$


## @{keyword.input}

```
$N$ $M$ $s$ $t$
$a_0$ $b_0$ $c_0$
$a_1$ $b_1$ $c_1$
$a_2$ $b_2$ $c_2$
$\vdots$
$a_{M - 1}$ $b_{M - 1}$ $c_{M - 1}$
```

## @{keyword.output}

@{lang.en}
If there are no paths from vertex $s$ to vertex $t$, output ```-1```.
Otherwise, output one of the shortest paths in the following format.
@{lang.ja}
頂点 $s$ から頂点 $t$ へのパスが存在しない場合```-1```を出力してください。
そうでない場合以下の形式で出力してください。
@{lang.end}
```
$X$ $Y$
$u_0$ $v_0$
$u_1$ $v_1$
$u_2$ $v_2$
$u_{Y - 1}$ $v_{Y - 1}$
```
@{lang.en}
$X$ represents length of the shortest path.
$Y$ represents the number of edges in the path.
$u_i$ and $v_i$ are beginning and end of the $i$-th edge in the path, respectively.
@{lang.ja}
$X$は最短距離、$Y$は出力するパスの辺数を表し、$u_i, v_i$はそれぞれ$i$番目に通る辺の始点と終点を表します。
同じ頂点を $2$ 回以上通ってはなりません。
@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
