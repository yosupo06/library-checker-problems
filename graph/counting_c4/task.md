## @{keyword.statement}

@{lang.en}
You are given an undirected graph, consisting of $N$ vertices and $M$ edges. This graph may not be simple.
The $i$-th edge is $\lbrace u _ i, v _ i \rbrace$.

For each edge $i$, find $A _ i$ , as the number of unordered combinations of $3$ edges $x$ , $y$ , $z$
that those $4$ edges ( $i,x,y,z$ ) forms a subgraph isomorphic to $C _ 4$ ( A cycle with $4$ edges ).

@{lang.ja}
$N$ 頂点 $M$ 辺の無向グラフが与えられます。 $i$ 番目の辺は $\lbrace u _ i, v _ i \rbrace$ です。このグラフは単純とは限りません。

各辺 $i$ について、 $3$ つの辺 $x$ , $y$ , $z$ の非順序組であって、 $4$ 辺 $i,x,y,z$ が $C _ 4$ ( $4$ 辺かならなるサイクル )に同型な部分グラフをなすものの個数 $A _ i$ を求めてください。

@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \le N \le @{param.N_MAX}$
- $@{param.M_MIN} \le M \le @{param.M_MAX}$
- $0 \le u _ i \lt N$
- $0 \le v _ i \lt N$
- $u _ i \neq v _ i$

## @{keyword.input}

```
$N$ $M$
$u _ 0$ $v _ 0$
$u _ 1$ $v _ 1$
$\vdots$
$u _ {M-1}$ $v _ {M-1}$
```

## @{keyword.output}

```
$A _ 0$ $A _ 1$ $\cdots$ $A _ {N-1}$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
