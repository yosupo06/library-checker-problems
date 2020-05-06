## @{keyword.statement}

@{lang.en}

Given a undirected graph with $N$ vertices and $M$ edges. $i$-th edge is $(a_i, b_i)$. This graph may not be simple.
Please decompose this graph into two-edge-connected components.

@{lang.ja}

$N$ 頂点 $M$ 辺の無向グラフが与えられる。$i$ 番目の辺は $(a_i, b_i)$ である。このグラフは単純とは限らない。
このグラフを二辺連結成分分解してください。

@{lang.end}


## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.M_MIN} \leq M \leq @{param.M_MAX}$
- $0 \leq a_i, b_i < N$

## @{keyword.input}

~~~
$N$ $M$
$a_0$ $b_0$
$a_1$ $b_1$
:
$a_{M - 1}$ $b_{M - 1}$
~~~

## @{keyword.output}

@{lang.en}

Print the number of two-edge-connected components $K$ in the first line.
Following $K$ lines, print as follows. $l$ is the number of vertices of two-edge-connected components and $v_i$ is a vertex index.

@{lang.ja}

$K$ を二辺連結成分の個数として、$1 + K$ 行出力する。
最初の行には $K$ を出力し、その後 $K$ 行では以下のように出力する。$l$ は二辺連結成分の頂点数であり、$v_i$ はその頂点番号である。

@{lang.end}

~~~
$l$ $v_0$ $v_1$ ... $v_{l-1}$
~~~

@{lang.en}
If there is multiple solutions, print any of them.
@{lang.ja}
正しい出力が複数存在する場合は、どれを出力しても構わない。
@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}
