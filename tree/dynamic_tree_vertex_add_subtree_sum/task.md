## @{keyword.statement}

@{lang.en}
You are given a tree with $N$ vertices. Its edges are $(u_i, v_i)$. Its $i$-th vertex has a value $a_i$ written on it.

Process $Q$ queries. It is guaranteed that the graph is a tree after each query.

- `0 $u$ $v$ $w$ $x$`: Remove an edge $(u, v)$ and add an edge $(w, x)$.
- `1 $p$ $x$`: $a_p \gets a_p + x$
- `2 $v$ $p$`: For an edge $(v, p)$ where $p$ is considered the parent, output the sum of weights of all vertices in the subtree of $v$.
@{lang.ja}
$N$ 頂点の木が与えられる。辺は $(u_i, v_i)$。頂点 $i$ には値 $a_i$ が書かれている。

$Q$ 個のクエリが飛んでくるので処理。ただし, クエリ処理後もグラフが木であることが保証される.

- `0 $u$ $v$ $w$ $x$`: 辺$(u, v)$を削除, 辺$(w, x)$を作成。
- `1 $p$ $x$`: $a_p \gets a_p + x$
- `2 $v$ $p$`: 辺$(v, p)$について, 頂点$p$を親としたときの頂点$v$の部分木に含まれる頂点の重みの総和を出力。
@{lang.end}

## @{keyword.constraints}

@{lang.en}
- $1 \leq N, Q \leq 200,000$
- $0 \leq a_i, x \leq 10^9$
- $0 \leq p, u_i, v_i < N$
- $(u_i, v_i)$ is a tree
@{lang.ja}
- $1 \leq N, Q \leq 200,000$
- $0 \leq a_i, x \leq 10^9$
- $0 \leq p, u_i, v_i < N$
- $(u_i, v_i)$ は木
@{lang.end}

## @{keyword.input}

~~~
$N$ $Q$
$a_0$ $a_1$ ... $a_{N - 1}$
$u_0$ $v_0$
$u_1$ $v_1$
:
$u_{N - 2}$ $v_{N - 2}$
$\textrm{Query}_0$
$\textrm{Query}_1$
:
$\textrm{Query}_{Q - 1}$
~~~

@{example.example_00}
