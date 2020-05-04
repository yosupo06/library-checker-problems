## {{keyword.statement}}

{{lang.en}}
Let $G_{-1}$ be the graph which consists of $N$ vertices and no edges. Process $Q$ queries in order. The $i$-th query is given with the following format:

- `0 $k_{i}$ $u_{i}$ $v_{i}$`: Let $G\_{i}$ be the graph, which is made by adding an edge $\left( u, v \right)$ to $G\_{k\_{i}}$.
- `1 $k_{i}$ $u_{i}$ $v_{i}$`: If vertices $u, v$ in $G\_{k\_{i}}$ are connected, print $1$. Otherwise, print $0$.
{{lang.ja}}
$G_{-1}$ を、$N$ 個の頂点からなる、辺がひとつも存在しないグラフとします。$Q$ 個のクエリを処理してください。$i$ 個目のクエリは以下の形式で与えられます。

- `0 $k_{i}$ $u_{i}$ $v_{i}$`: $G\_{k\_{i}}$ に辺 $\left( u\_{i}, v\_{i} \right)$ を追加したグラフを $G\_{i}$ とする。
- `1 $k_{i}$ $u_{i}$ $v_{i}$`: グラフ $G\_{k\_{i}}$ において $u\_{i}, v\_{i}$ が連結ならば $1$ を、そうでなければ $0$ を出力する。
{{lang.end}}

## {{keyword.constraints}}

- $1 \leq N \leq {{param MAX_N}}$
- $1 \leq Q \leq {{param MAX_Q}}$
- $t\_{i} \in \left\\{ 0, 1 \right\\}$
- $-1 \leq k\_{i} < i$
- for all $k_i$, $k\_i = -1$ or $t\_{k\_{i}} = 0$ holds.
- $0 \leq u\_{i}, v\_{i} < N$

## {{keyword.input}}

```
$N$ $Q$
$t_0$ $k_0$ $u_0$ $v_0$
$\vdots$
$t_{Q-1}$ $k_{Q-1}$ $u_{Q-1}$ $v_{Q-1}$
```

## {{keyword.sample}}

{{example example_00}}

