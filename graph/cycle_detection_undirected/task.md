## @{keyword.statement}

@{lang.en}
You are given an undirected graph, consisting of $N$ vertices and $M$ edges.
The $i$-th edge connects vertex $u_i$ and $v_i$.
This graph may not be simple. 

A **cycle** is a pair of sequence of vertices $(v_0, \ldots, v_{L-1})$ and sequence of edges $(e_0, \ldots, e_{L-1})$ satisfying following conditions. 

- $L\geq 1$
- $i\neq j \implies v_i\neq v_j, e_i\neq e_j$
- For $0\leq i < L- 1$, the edge $e_i$ connects $v_i$ and $v_{i+1}$
- The edge $e_{L-1}$ connects $v_{L-1}$ and $v_{0}$

Determine if a cycle exists in $G$, and output it if exists. 
If there are multiple cycles, print any of them.

@{lang.ja}
$N$ 頂点 $M$ 辺の無向グラフ $G$ が与えられます。$i$ 番目の辺は頂点 $u_i$ と頂点 $v_i$ を結んでいます。
このグラフは単純とは限りません。

$G$ における **サイクル** とは、頂点の列 $(v_0, \ldots, v_{L-1})$ と辺の列 $(e_0, \ldots, e_{L-1})$ であって以下の条件を満たすもののことをいいます。

- $L\geq 1$
- $i\neq j \implies v_i\neq v_j, e_i\neq e_j$
- $0\leq i < L - 1$ に対して辺 $e_i$ は $v_i$ と $v_{i+1}$ を結ぶ
- 辺 $e_{L-1}$ は $v_{L-1}$ と $v_0$ を結ぶ

$G$ がサイクルを含むか否かを判定し、含む場合にはそのひとつを求めてください。サイクルが複数含まれるならばどれを出力しても構いません。

@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.M_MIN} \leq M \leq @{param.M_MAX}$
- $0 \leq u_i \lt N$
- $0 \leq v_i \lt N$


## @{keyword.input}

```
$N$ $M$
$u_0$ $v_0$
$u_1$ $v_1$
$u_2$ $v_2$
$\vdots$
$u_{M-1}$ $v_{M-1}$
```

## @{keyword.output}

@{lang.en}
If there are no cycles, output ```-1```. Otherwise, output one of the cycles in the following format. 

@{lang.ja}
サイクルが存在しない場合、```-1``` を出力してください。サイクルが存在する場合、それを以下の形式で出力してください。

@{lang.end}
```
$L$
$v_0$ $v_1$ $\ldots$ $v_{L-1}$
$e_0$ $e_1$ $\ldots$ $e_{L-1}$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}

@{example.example_03}

@{example.example_04}
