## @{keyword.statement}

@{lang.en}
Given $N$ 2D-points. $i$-th is $(x _ i, y _ i)$.

For each $i$ , $j$, we add edge between them and whose weight is $\sqrt{(x _ i - x _ j)^2 + (y _ i - y _ j)^2}$.

Calculate a minimum spanning tree of this graph.

@{lang.ja}
2次元平面上に $N$ 個の点が与えられる。$i$ 個目の頂点の座標は $(x _ i, y _ i)$ である。

2点間の距離をユークリッド距離、つまり $\sqrt{(x _ i - x _ j)^2 + (y _ i - y _ j)^2}$ で定義するときの、最小全域木を求めよ。
@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $|x _ i|, |y _ i| \leq @{param.X_AND_Y_ABS_MAX}$

## @{keyword.input}

~~~
$N$
$x _ 0$ $y _ 0$
$x _ 1$ $y _ 1$
:
$x _ {N - 1}$ $y _ {N - 1}$
~~~

## @{keyword.output}

~~~
$u _ 0$ $v _ 0$
$u _ 1$ $v _ 1$
:
$u _ {N - 2}$ $v _ {N - 2}$
~~~

@{lang.en}
Output all those $N-1$ pairs of $u _ i$ , $v _ i$ as the indices of the points that are the terminals of the edges in a minimum spanning tree.

If there are multiple solutions, print any of them.
@{lang.ja}
最小全域木の辺が結ぶ点の番号を $u _ i$ , $v _ i$ として、それら $N-1$ 組をすべて出力せよ。

解が複数存在する場合、どれを返しても構わない。
@{lang.end}


## @{keyword.sample}

@{example.example_00}
