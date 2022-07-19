## @{keyword.statement}

@{lang.en}

Given a tree with $N$ vertices, where the $i$-th edge connects vertex $a_i$ and $b_i$. Process $Q$ queries as follows:

- `$s$ $t$ $i$`: Print $v_i$, where the minimum path on the tree is $(v_0, v_1, \ldots, v_k)$ ($v_0 = s$, $v_k = t$). If $i>k$, print `-1`.

@{lang.ja}

$N$ 頂点からなる木が与えられる。$i$ 番目の辺は $a_i$ と $b_i$ を結ぶ。$Q$ 個のクエリを処理してください。

- `$s$ $t$ $i$`: 頂点 $s$ から $t$ までの木上の最短路が $(v_0, v_1, \ldots, v_k)$ （$v_0 = s$, $v_k = t$）であるとき、$v_i$ を出力する。ただし $i > k$ のときには `-1` を出力する。

@{lang.end}


## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $0 \leq a_i, b_i < N$
- $a_i \neq b_i$
- $0 \leq s, t \leq N - 1$
- $0 \leq i \leq N - 1$

## @{keyword.input}

~~~
$N$ $Q$
$a_0$ $b_0$
$\vdots$
$a_{N-2}$ $b_{N-2}$
$s_0$ $t_0$ $i_0$
$\vdots$
$s_{Q-1}$ $t_{Q-1}$ $i_{Q-1}$
~~~

## @{keyword.sample}

@{example.example_00}
