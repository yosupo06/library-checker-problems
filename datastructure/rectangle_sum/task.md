## @{keyword.statement}
$2$ 次元平面上に重み付きの点が $N$ 個ある。$i$ 個目の座標は $(x_i, y_i)$ で、重みは $w_i$ である。
$Q$ 個のクエリを処理

- `$l$ $d$ $r$ $u$`: $l \leq x < r$, $d \leq y < u$ を満たす点について、重さの総和を求める

## @{keyword.constraints}

- $1 \leq N, Q \leq 200,000$
- $0 \leq x_i, y_i, w_i \leq 10^9$
- $0 \leq l_i < r_i \leq 10^9$
- $0 \leq d_i < u_i \leq 10^9$

## @{keyword.input}

~~~
$N$ $Q$
$x_0$ $y_0$ $w_0$
$x_1$ $y_1$ $w_1$
:
$x_{N - 1}$ $y_{N - 1}$ $w_{N - 1}$
$\textrm{Query}_0$
$\textrm{Query}_1$
:
$\textrm{Query}_{Q - 1}$
~~~

@{example.example_00}
