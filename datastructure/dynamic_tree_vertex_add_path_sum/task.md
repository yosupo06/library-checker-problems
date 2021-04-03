## @{keyword.statement}

@{lang.en}
Given tree of $N$ vertices. Edges are $(u_i, v_i)$. Value $a_i$ is written on vertex $i$.

Process the following $Q$ queries in order. You can assume that the graph is always the tree while processing the queries.

- `0 $u$ $v$ $w$ $x$`: Delete a edge $(u, v)$, and add $(w, x)$.
- `1 $p$ $x$`: $a_p \gets a_p + x$
- `2 $u$ $v$`: Print the sum of values of vertices of the path between $u$ and $v$ (inclusive).
@{lang.ja}
$N$ 頂点の木が与えられる。辺は $(u_i, v_i)$。頂点 $i$ には値 $a_i$ が書かれている。

$Q$ 個のクエリが飛んでくるので処理。ただし, クエリ処理後もグラフが木であることが保証される.

- `0 $u$ $v$ $w$ $x$`: 辺$(u, v)$を削除, 辺$(w, x)$を作成。
- `1 $p$ $x$`: $a_p \gets a_p + x$
- `2 $u$ $v$`: $u, v$ 間のパス上の頂点(端点含む)に書かれた値の総和を出力
@{lang.end}

## @{keyword.constraints}

@{lang.en}

- $1 \leq N, Q \leq 200,000$
- $0 \leq a_i, x \leq 10^9$
- $0 \leq p, u_i, v_i < N$
- $(u_i, v_i)$ is tree.
- for type 0 queries, there is a edge $(u, v)$.
- The graph is always tree.

@{lang.ja}

- $1 \leq N, Q \leq 200,000$
- $0 \leq a_i, x \leq 10^9$
- $0 \leq p, u_i, v_i < N$
- $(u_i, v_i)$ は木
- type 0のクエリについて、必ず辺 $(u, v)$ は存在する
- グラフはクエリ処理中ずっと木

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
