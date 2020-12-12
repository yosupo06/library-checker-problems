## @{keyword.statement}

@{lang.en}

Given a simple weighted directed graph with $N$ vertices and $M$ edges. $i$-th edge is $(a_i, b_i)$ and has a weight of $c_i$.

Find the directed minimum spanning tree whose root is the vertex $S$ (it means that all the vertices have to be reachable from $S$).

@{lang.ja}

$N$ 頂点 $M$ 辺の単純な重み付き有向グラフが与えられる。$i$ 番目の辺は頂点 $a_i$ から $b_i$ に貼られており、重さ $c_i$ である。

頂点 $S$ を根とする(根から全ての頂点に到達できる)有向最小全域木を求めよ。

@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq 200,000$
- $N - 1 \leq M \leq 200,000$
- $0 \leq S < N$
- $0 \leq a_i, b_i < N$
- $a_i \neq b_i$
- $(a_i, b_i) \neq (a_j, b_j) (i \neq j)$
- $0 \leq c_i \leq 10^9$
- @{lang.en} All the vertices are reachable from the vertex $S$ @{lang.ja} 頂点 $S$ から全ての頂点へ到達可能 @{lang.end}

## @{keyword.input}

~~~
$N$ $M$ $S$
$a_0$ $b_0$ $c_0$
$a_1$ $b_1$ $c_1$
:
$a_{M - 1}$ $b_{M - 1}$ $c_{M - 1}$
~~~

## @{keyword.output}

~~~
$X$
$p_0$ $p_1$ $p_2$ ... $p_{N - 1}$
~~~

@{lang.en}
$X$ is the sum of the weights of the edges in the directed MST. $p_i$ is the parent of the vertex $i$ or $p_S = S$.

If there are multiple correct output, print any of them.

@{lang.ja}

ただし、$X$ は木の重みの総和であり、$p_i$ は頂点 $i$ の親である。$p_S = S$ とすること。
解が複数存在する場合、どれを返しても構わない。

@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
