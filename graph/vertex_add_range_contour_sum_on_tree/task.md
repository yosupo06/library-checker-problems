## @{keyword.statement}

@{lang.en}

Given a tree with $N$ vertices, where the $i$-th edge connects vertices $u_i$ and $v_i$. Value $a_i$ is written on the vertex $i$. Process the following $Q$ queries in order:

- `0 $p$ $x$`: $a_p \leftarrow a_p+x$
- `1 $p$ $l$ $r$`: Print the sum of the values written on the vertices whose distance from the vertex $p$ is in $[l,r)$.

@{lang.ja}

$N$ 頂点からなる木が与えられます。$i$ 番目の辺は $u_i$ と $v_i$ を結んでいます。頂点 $i$ には値 $a_i$ が書かれています。以下の形式で表される $Q$ 個のクエリを順番に処理してください。

- `0 $p$ $x$`: $a_p \leftarrow a_p+x$
- `1 $p$ $l$ $r$`: 頂点 $p$ からの距離が $l$ 以上 $r$ 未満であるような頂点に書かれた値の総和を出力。

@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $@{param.A_MIN} \leq a_i \leq @{param.A_MAX}$
- $0 \leq u_i, v_i \leq N-1$
- $0 \leq p \leq N-1$
- $0 \leq l \leq r \leq N$

## @{keyword.input}

~~~
$N$ $Q$
$a_0$ $\cdots$ $a_{N-1}$
$u_0$ $v_0$
$\vdots$
$u_{N-2}$ $v_{N-2}$
$\mathrm{Query}_0$
$\vdots$
$\mathrm{Query}_{Q-1}$
~~~

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
