## @{keyword.statement}

@{lang.en}

Given a weighted undirected graph with $N$ vertices and $M$ edges. $i$-th edge is $(a_i, b_i)$ and has a weight of $c_i$. This graph may not be simple.
Find the minimum spanning tree.

@{lang.ja}

$N$ 頂点 $M$ 辺の無向グラフが与えられる。$i$ 番目の辺は $(a_i, b_i)$ であり、重さ $c_i$ である。このグラフは単純とは限らない。
最小全域木を求めよ。

@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $N - 1 \leq M \leq @{param.N_MAX}$
- $0 \leq a_i, b_i < N$
- $0 \leq c_i \leq @{param.C_MAX}$
- @{lang.en} The given graph is connected. @{lang.ja} 与えられるグラフは連結 @{lang.end}

## @{keyword.input}

~~~
$N$ $M$
$a_0$ $b_0$ $c_0$
$a_1$ $b_1$ $c_1$
:
$a_{M - 1}$ $b_{M - 1}$ $c_{M - 1}$
~~~

## @{keyword.output}

~~~
$X$
$e_0$ $e_1$ $e_2$ ... $e_{N - 1}$
~~~

@{lang.en}
$X$ is the sum of the weights of the edges in the minimum spanning tree. $e_i$ is the index of the edge in the minimum spanning tree.
If there are multiple correct output, print any of them.

@{lang.ja}

ただし、$X$ は木の重みの総和であり、$e_i$ は最小全域木に含まれる辺の番号である。
解が複数存在する場合、どれを返しても構わない。

@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}
