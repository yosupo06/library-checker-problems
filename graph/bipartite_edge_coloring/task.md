## @{keyword.statement}

@{lang.en}
Given a bipartite graph with $L + R$ vertices and $M$ edges. $i$-th edge is $(a_i, b_i)$.

Calculate the proper edge coloring which gives edge chromatic number.

@{lang.ja}

頂点数が $L, R$、辺が $M$ の二部グラフが与えられる。$i$ 番目の辺は $(a_i, b_i)$ である。
辺彩色数を与える辺彩色を構築せよ。

@{lang.end}

## @{keyword.constraints}

- $1 \leq L, R \leq @{param.L_MAX}$
- $1 \leq M \leq  @{param.M_MAX}$
- $0 \leq a_i < L$
- $0 \leq b_i < R$

## @{keyword.input}

~~~
$L$ $R$ $M$
$a_0$ $b_0$
$a_1$ $b_1$
$\vdots$
$a_{M - 1}$ $b_{M - 1}$
~~~

## @{keyword.output}
~~~
$K$
$c_0$ 
$c_1$
$\vdots$
$c_{M - 1}$
~~~
@{lang.en}
$K$ is the edge chromatic number, and $c_i$ is the integer which repersents the color of the i-th edge. $c_i$ should satisfy $0 \leq c_i < K$.
@{lang.ja}
$K$ は辺彩色数、$c_i$ は $i$ 番目の辺の色を表す整数。 $c_i$ は $0 \leq c_i < K$ を満たすとする。
@{lang.end}

## @{keyword.sample}

@{example.example_00}
