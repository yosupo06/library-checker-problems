## @{keyword.statement}

@{lang.en}
Given a tree of $N$ vertices. Edges are $(u_i, v_i)$. Value $a_i$ is written on the vertex $i$.

Process the following $Q$ queries in order:

- `0 $p$ $x$`: $a_p \gets a_p + x$
- `1 $u$ $v$`: Print the sum of the values of vertices of the path between vertex $u$ and $v$ (inclusive).
@{lang.ja}
$N$ 頂点の木が与えられる。辺は $(u_i, v_i)$。頂点 $i$ には値 $a_i$ が書かれている。

$Q$ 個のクエリが飛んでくるので処理。

- `0 $p$ $x$`: $a_p \gets a_p + x$
- `1 $u$ $v$`: $u, v$ 間のパス上の頂点(端点含む)に書かれた値の総和を出力
@{lang.end}

## @{keyword.constraints}

- $1 \leq N, Q \leq @{param.N_AND_Q_MAX}$
- $0 \leq a_i, x \leq @{param.A_AND_X_MAX}$
- $0 \leq p, u_i, v_i < N$
- @{lang.en} $(u_i, v_i)$ @{lang.ja} $(u_i, v_i)$ は木 @{lang.end}

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
