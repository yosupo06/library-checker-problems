## @{keyword.statement}

@{lang.en}

You are given a simple undirected graph with $N$ vertices and $M$ edges. The $i$-th edge is $(a_i,b_i)$. Decompose the complement graph of $G$ into connected components.

@{lang.ja}

$N$ 頂点 $M$ 辺の単純無向グラフ $G$ が与えられる。$i$ 番目の辺は $(a_i,b_i)$ である。$G$ の補グラフを連結成分分解せよ。

@{lang.end}

## @{keyword.constraints}

@{lang.en}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.M_MIN} \leq M \leq @{param.M_MAX}$
- $0 \leq a_i, b_i < N$
- The given graph is simple

@{lang.ja}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.M_MIN} \leq M \leq @{param.M_MAX}$
- $0 \leq a_i, b_i < N$
- 与えられるグラフは単純

@{lang.end}

## @{keyword.input}

~~~
$N$ $M$
$a_0$ $b_0$
$a_1$ $b_1$
$\vdots$
$a_{M-1}$ $b_{M-1}$
~~~

## @{keyword.output}

@{lang.en}

Print the number of connected components $K$ in the first line. In the next $K$ lines, print as follows. $l$ is the number of vertices of a connected component and $v_i$ is a vertex index.

@{lang.ja}

$K$ を連結成分の個数として、$1+K$ 行出力する。最初の行には $K$ を出力し、その後 $K$ 行では以下のように出力する。$l$ は連結成分の頂点数であり、$v_i$ はその頂点番号である。

@{lang.end}

~~~
$l$ $v_0$ $v_1$ ... $v_{l-1}$
~~~

@{lang.en}
If there are multiple solutions, you may print any of them.
@{lang.ja}
正しい出力が複数存在する場合は、どれを出力しても構わない。
@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}
