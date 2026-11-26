## @{keyword.statement}

@{lang.en}
You are given a simple bipartite graph with $L$ left vertices and $R$ right vertices.
Left vertices are numbered from $0$ to $L-1$, and right vertices from $L$ to $L+R-1$.
For each of the $M$ input pairs $(a_i,b_i)$, there is an edge between vertices $a_i$ and $L+b_i$.

Find a largest set of vertices containing no two adjacent vertices.
@{lang.ja}
左側に $L$ 頂点、右側に $R$ 頂点を持つ単純二部グラフが与えられます。
左側の頂点には $0$ から $L-1$、右側の頂点には $L$ から $L+R-1$ の番号が付いています。
入力の $M$ 個の組 $(a_i,b_i)$ はそれぞれ、頂点 $a_i$ と頂点 $L+b_i$ を結ぶ辺を表します。

どの $2$ 頂点も隣接しないような頂点集合のうち、要素数が最大のものを求めてください。
@{lang.end}

## @{keyword.constraints}

- $1 \leq L \leq @{param.L_MAX}$
- $1 \leq R \leq @{param.R_MAX}$
- $1 \leq M \leq @{param.M_MAX}$
- $0 \leq a_i < L$
- $0 \leq b_i < R$
- $(a_i,b_i) \neq (a_j,b_j)$ $(i \neq j)$

## @{keyword.input}

~~~
$L$ $R$ $M$
$a_0$ $b_0$
$\vdots$
$a_{M-1}$ $b_{M-1}$
~~~

## @{keyword.output}

~~~
$K$
$v_0$ $v_1$ $\ldots$ $v_{K-1}$
~~~

@{lang.en}
Print the size $K$ of a maximum independent set and the numbers of its vertices in any order.
If there are multiple maximum independent sets, print any one of them.
@{lang.ja}
最大独立集合の要素数 $K$ と、その集合に含まれる頂点の番号を任意の順序で出力してください。
最大独立集合が複数存在する場合は、どれを出力しても構いません。
@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
