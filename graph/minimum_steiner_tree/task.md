## @{keyword.statement}

@{lang.en}

Given a connected, undirected graph with $N$ vertices and $M$ edges, where the $i$-th edge $(0 \le i < M)$ connects vertices $U_i$ and $V_i$ and has weight $W_i$.

Additionally, a subset $X = \{X_0, X_1, \ldots, X_{K - 1}\}$ of $V(G)$ is given. Among the subgraphs of $G$ in which the vertices in $X$ are pairwise connected, find one with the minimum sum of edge weights.

@{lang.ja}

$N$ 頂点 $M$ 辺の重み付き連結無向グラフ $G$ が与えられる。$i$ $(0 \le i < M)$ 番目の辺は頂点 $U_i$ と $V_i$ を結び、重みは $W_i$ である。

また、 $V(G)$ の部分集合 $X = \{X_0, X_1, \ldots, X_{K - 1}\}$ が与えられるので、$G$ の部分グラフで $X$ のどの 2 頂点間も連結であるようなもののうち、辺重みの総和が最小のものを求めよ。

@{lang.end}

## @{keyword.constraints}

@{lang.en} 

- $1 \leq N \leq @{param.N_MAX}$
- $N - 1 \leq M \leq @{param.M_MAX}$
- $0 \leq U_i, V_i < N$
- $@{param.W_MIN} \leq W_i \leq @{param.W_MAX}$
- $1 \leq K \leq \min(N, @{param.K_MAX})$
- $0 \le X_0 < X_1 < \ldots < X_{K - 1} < N$
- The given graph is connected. 

@{lang.ja}

- $1 \leq N \leq @{param.N_MAX}$
- $N - 1 \leq M \leq @{param.M_MAX}$
- $0 \leq U_i, V_i < N$
- $@{param.W_MIN} \leq W_i \leq @{param.W_MAX}$
- $1 \leq K \leq \min(N, @{param.K_MAX})$
- $0 \le X_0 < X_1 < \ldots < X_{K - 1} < N$
- 与えられるグラフは連結

@{lang.end}

## @{keyword.input}

~~~
$N$ $M$
$U_0$ $V_0$ $W_0$
$U_1$ $V_1$ $W_1$
:
$U_{M - 1}$ $V_{M - 1}$ $W_{M - 1}$
$K$
$X_0$ $X_1$ ... $X_{K - 1}$
~~~

## @{keyword.output}

~~~
$Y$ $Z$
$i_0$ $i_1$ ... $i_{Z - 1}$
~~~

@{lang.en}
$Y$ is the sum of the weights of the edges in the chosen subgraph and $Z$ is the number of chosen edges. $i_0, i_1, \ldots, i_{Z - 1}$ are the indices of the edges in the chosen subgraph.
If there are multiple correct output, print any of them.

@{lang.ja}

$Y$ は、選ばれた部分グラフに含まれる辺の重みの総和であり、$Z$ は選ばれた辺の本数である。
選ばれた部分グラフに含まれる辺のインデックスは $i_0, i_1, \ldots, i_{Z - 1}$ である。
解が複数存在する場合、どれを返しても構わない。

@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}

