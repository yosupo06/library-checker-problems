## @{keyword.statement}

@{lang.en}
Given $N$ 2D-points. $i$-th is $(x_i, y_i)$.

For each $i, j$, we add edge between them and whose weight is $|x_i - x_j| + |y_i - y_j|$.

Calculate MST of this graph.

@{lang.ja}
2次元平面上に $N$ 個の点が与えられる。$i$ 個目の頂点の座標は $(x_i, y_i)$ である。

2点間の距離をマンハッタン距離、つまり $|x_i - x_j| + |y_i - y_j|$ で定義するときの、MSTを求めよ。
@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq 200,000$
- $0 \leq x_i, y_i \leq 10^9$

## @{keyword.input}

~~~
$N$
$x_0$ $y_0$
$x_1$ $y_1$
:
$x_{N - 1}$ $y_{N - 1}$
~~~

## @{keyword.output}

~~~
$X$
$u_0$ $v_0$
$u_1$ $v_1$
:
$u_{N - 2}$ $v_{N - 2}$
~~~

@{lang.en}
$X$ is the sum of weight of tree.
If there are multiple solutions, print any of them.
@{lang.ja}
ただし、$X$ は木の重みの総和。
解が複数存在する場合、どれを返しても構わない。
@{lang.end}


## @{keyword.sample}

@{example.example_00}
