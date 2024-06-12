## @{keyword.statement}

@{lang.en}
There's an undirected graph $G$ with $N$ vertices and $0$ edges, along with a sequence of integers $x_0, \ldots, x_{N-1}$. Please process $Q$ queries of the following format:

- `$k$ $a$ $b$`: Add edge $(a + i, b + i)$ to $G$ for each $i=0,1,\ldots,k-1$.

For each query, output the remainder when $X$ defined below modulo $@{param.MOD}$:

- Define $\mathrm{same}(i,j)$ as $1$ if vertices $i$ and $j$ belong to the same connected component in $G$, and $0$ otherwise, for $0\leq i,j \leq N-1$.
- Define $X = \sum_{0\leq i<j\leq N-1}\mathrm{same}(i,j)x_ix_j$.

@{lang.ja}
$N$ 頂点 $0$ 辺の無向グラフ $G$ および，整数列 $x_0, \ldots, x_{N-1}$ があります．次の形式の $Q$ 個のクエリを処理してください．

- `$k$ $a$ $b$`: 各 $i=0,1,\ldots,k-1$ に対して $G$ に辺 $(a + i, b + i)$ を追加する．

各クエリを処理した後に，次で定義される $X$ を $@{param.MOD}$ で割った余りを出力してください：
- $0\leq i,j \leq N-1$ に対して，$\mathrm{same}(i,j)$ を，頂点 $i,j$ が $G$ において同一の連結成分に属するならば $1$，そうでないならば $0$ と定義する．
- $X = \sum_{0\leq i<j\leq N-1}\mathrm{same}(i,j)x_ix_j$ と定義する．
@{lang.end}

## @{keyword.constraints}

- $@{param.MIN_N} \leq N \leq @{param.MAX_N}$
- $@{param.MIN_Q} \leq Q \leq @{param.MAX_Q}$
- $0 \leq x_i < @{param.MOD}$
- $0 \leq k\leq N$
- $0 \leq a,b \leq N-k$

## @{keyword.input}

~~~
$N$ $Q$
$x_0$ $\cdots$ $x_{N-1}$
$k$ $a$ $b$
$\vdots$
$k$ $a$ $b$
~~~

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
