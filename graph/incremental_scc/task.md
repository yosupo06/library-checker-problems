## @{keyword.statement}

@{lang.en}

There is a $N$ vertices and $0$ edges directed graph $G$, and an integer sequence $x_0, \ldots, x_{N-1}$.

Add $M$ directed edges to $G$. The $i$-th edge is directed from $a_i$ to $b_i$.

After adding each edge, output the remainder when $X$ defined below modulo $@{param.MOD}$:

- Define $\mathrm{same}(i,j)$ as $1$ if vertices $i$ and $j$ belong to the same strongly connected component in $G$, and $0$ otherwise, for $0\leq i,j \leq N-1$.
- Define $X = \sum_{0\leq i<j\leq N-1}\mathrm{same}(i,j)x_ix_j$.

@{lang.ja}

$N$ 頂点 $0$ 辺の有向グラフ $G$ および，整数列 $x_0, \ldots, x_{N-1}$ があります．

$G$ に $M$ 辺の有向辺を追加します．$i$ 番目の辺は $a_i$ から $b_i$ に向けて張られています．

各辺を追加した後に，次で定義される $X$ を $@{param.MOD}$ で割った余りを出力してください：
- $0\leq i,j \leq N-1$ に対して，$\mathrm{same}(i,j)$ を，頂点 $i,j$ が $G$ において同一の強連結成分に属するならば $1$，そうでないならば $0$ と定義する．
- $X = \sum_{0\leq i<j\leq N-1}\mathrm{same}(i,j)x_ix_j$ と定義する．

@{lang.end}


## @{keyword.constraints}

- $@{param.MIN_N} \leq N \leq @{param.MAX_N}$
- $@{param.MIN_M} \leq M \leq @{param.MAX_M}$
- $0 \leq x_i \leq @{param.MOD} - 1$
- $0 \leq a_i, b_i < N$
## @{keyword.input}

~~~
$N$ $M$
$x_0$ $\ldots$ $x_{N-1}$
$a_0$ $b_0$
$a_1$ $b_1$
$\vdots$
$a_{M - 1}$ $b_{M - 1}$
~~~

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}
