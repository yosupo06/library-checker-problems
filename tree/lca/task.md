## @{keyword.statement}

@{lang.en}

Given a rooted tree with $N$ vertices. The root is vertex $0$ and a parent of a vertex $i$ is $p_i$. Process $Q$ queries as follows:

- `$u$ $v$`: Print LCA of vertex $u$ and $v$.

@{lang.ja}

$N$ 頂点からなる根付き木が与えられる。根は頂点 $0$ で、頂点 $i$ の親は $p_i$ である。$Q$ 個のクエリが飛んできます。処理してください。

- `$u$ $v$`: 頂点 $u$, $v$ のLCAを出力する

@{lang.end}


## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $0 \leq p_i < i$
- $0 \leq u < v \leq N - 1$

## @{keyword.input}

~~~
$N$ $Q$
$p_1$ $p_2$ ... $p_{N-1}$
$u_0$ $v_0$
$u_1$ $v_1$
:
$u_{Q - 1}$ $v_{Q - 1}$
~~~

## @{keyword.sample}

@{example.example_00}
