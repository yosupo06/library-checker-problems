## @{keyword.statement}

@{lang.en}
You are given an undirected graph, consisting of $N$ vertices and $M$ edges. The $i$-th edge connects vertex $u_i$ and $v_i$. This graph may not be simple.

Find the number of spanning tree of the graph modulo $998244353$. 

@{lang.ja}
$N$ 頂点 $M$ 辺の無向グラフが与えられます．$i$ 番目の辺は頂点 $u_i$ と頂点 $v_i$ を結んでいます．このグラフは単純とは限りません．

このグラフの全域木の個数を $998244353$ で割った余りを求めてください．
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

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}

@{example.example_03}
