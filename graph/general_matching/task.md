## @{keyword.statement}

@{lang.en}

Given a simple undirected graph with $N$ vertices and $M$ edges. $i$-th edge is $(u_i, v_i)$.

Calculate the maximum matching.

@{lang.ja}
$N$ 頂点 $M$ 辺の単純な無向グラフが与えられる。辺は $(u_i, v_i)$。

最大マッチングを出力してください。
@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq 500$
- $0 \leq M \leq \frac{N(N-1)}{2}$
- $0 \leq u_i, v_i < N$

## @{keyword.input}

~~~
$N$ $M$
$u_0$ $v_0$
$u_1$ $v_1$
:
$u_{M - 1}$ $v_{M - 1}$
~~~

## @{keyword.output}

~~~
$X$
$a_0$ $b_0$
$a_1$ $b_1$
:
$a_{X - 1}$ $b_{X - 1}$
~~~

@{lang.en}

$X$ is the size of the maximum matching.

@{lang.ja}

$X$ は最大マッチングのサイズ

@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
