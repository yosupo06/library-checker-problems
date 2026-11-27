## @{keyword.statement}

@{lang.en}
You are given a directed graph with $N$ vertices and $M$ edges.
The $i$-th edge is directed from vertex $u_i$ to vertex $v_i$ and has capacity $c_i$.
The graph may contain multiple edges and self-loops.

Find a maximum integer flow from vertex $S$ to vertex $T$ and a minimum $S$-$T$ cut.

@{lang.ja}
$N$ 頂点 $M$ 辺の有向グラフが与えられる。
$i$ 番目の辺は頂点 $u_i$ から頂点 $v_i$ に張られており、容量は $c_i$ である。
このグラフは多重辺や自己ループを含むことがある。

頂点 $S$ から頂点 $T$ への最大流（整数流）と最小 $S$-$T$ カットを求めよ。

@{lang.end}

## @{keyword.constraints}

- $2 \leq N \leq @{param.N_MAX}$
- $0 \leq M \leq @{param.M_MAX}$
- $0 \leq S, T \lt N$
- $S \neq T$
- $0 \leq u_i, v_i \lt N$
- $0 \leq c_i \leq @{param.C_MAX}$

## @{keyword.input}

~~~
$N$ $M$ $S$ $T$
$u_0$ $v_0$ $c_0$
$\vdots$
$u_{M - 1}$ $v_{M - 1}$ $c_{M - 1}$
~~~

## @{keyword.output}

~~~
$F$
$f_0$ $f_1$ $\cdots$ $f_{M - 1}$
$x$
~~~

@{lang.en}
$F$ is the maximum flow value, and $f_i$ is the integer flow on the $i$-th input edge.
$x$ is a binary string of length $N$ representing a minimum $S$-$T$ cut.
Vertices with $x_v = 0$ are on the source side, and vertices with $x_v = 1$ are on the sink side.
In particular, $x_S = 0$ and $x_T = 1$.
If there are multiple solutions, output any of them.

If $M = 0$, the second line is empty.

@{lang.ja}
$F$ は最大流の値、$f_i$ は入力の $i$ 番目の辺に流す整数流量である。
$x$ は最小 $S$-$T$ カットを表す長さ $N$ の 01 文字列である。
$x_v = 0$ の頂点を始点側、$x_v = 1$ の頂点を終点側とし、$x_S = 0$, $x_T = 1$ とする。
解が複数存在する場合、どれを出力しても構わない。

$M = 0$ のとき、2 行目は空行とする。

@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
