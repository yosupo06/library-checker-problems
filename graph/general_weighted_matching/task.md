## @{keyword.statement}

@{lang.en}

Given a simple weighted undirected graph with $N$ vertices and $M$ edges. $i$-th edge is $(u_i, v_i)$ with a weight $w_i$.
Calculate the matching in which the sum of weights is maximized.

@{lang.ja}
$N$ 頂点 $M$ 辺からなる単純重み付き無向グラフが与えられます。$i$ 番目の辺は $(u_i, v_i)$ を結ぶ重み $w_i$ の辺です。
重みの総和が最大であるようなマッチングをひとつ求めてください。

@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq 500$
- $0 \leq M \leq \frac{N(N-1)}{2}$
- $0 \leq u_i, v_i < N$
- $1 \leq w_i \leq 1\,000\,000$

## @{keyword.input}

~~~
$N$ $M$
$u_0$ $v_0$ $w_0$
$u_1$ $v_1$ $w_1$
:
$u_{M - 1}$ $v_{M - 1}$ $w_{M-1}$
~~~

## @{keyword.output}

~~~
$X$ $W$
$a_0$ $b_0$
$a_1$ $b_1$
:
$a_{X - 1}$ $b_{X - 1}$
~~~

@{lang.en}

$X$ is the size of the maximum matching.
$W$ is the maximum matching weight.
$(a_i, b_i)$ is the edge of the matching.

@{lang.ja}

$X$ はマッチングの辺の個数、$W$ はマッチングの重みの総和、$(a_i, b_i)$ はマッチングの辺です。

@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
