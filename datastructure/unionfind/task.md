Problem Statement / 問題文
---------

We have an undirected graph with $N$ vertices and $0$ edges.
Process the following $Q$ queries in order:

- `$t_i$ = 0 $u_i$ $v_i$`: Add an edge $(u, v)$.
- `$t_i$ = 1 $u_i$ $v_i$`: If vertices $u, v$ are connected, print $1$. Otherwise, print $0$.

Problem Statement (Japanese) / 問題文 (日本語)
---------

$N$ 頂点 $0$ 辺の無向グラフに $Q$ 個のクエリが飛んできます。処理してください。


- `$t_i$ = 0 $u_i$ $v_i$`: 辺$(u, v)$を追加する。
- `$t_i$ = 1 $u_i$ $v_i$`: $u, v$ が連結ならば $1$、そうでないなら $0$ を出力する。

Constraints / 制約
---------

- $1 \leq N \leq 200,000$
- $1 \leq Q \leq 200,000$
- $0 \leq u_i, v_i \lt N$

Input / 入力
---------

~~~
$N$ $Q$
$t_1$ $u_1$ $v_1$
$t_2$ $u_2$ $v_2$
:
$t_Q$ $u_Q$ $v_Q$
~~~

Sample / サンプル
---------

{{example example_00}}
