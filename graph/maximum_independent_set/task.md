## {{keyword.statement}}
$N$ 頂点 $M$ 辺の単純な無向グラフが与えられる。辺は $(u_i, v_i)$。

最大独立点集合を出力してください。

## {{keyword.constraints}}

- $1 \leq N \leq 40$
- $1 \leq M \leq N(N - 1) / 2$
- $0 \leq u_i, v_i < N$
- $u_i \neq v_i$
- $(u_i, v_i) \neq (u_j, v_j)$

## {{keyword.input}}

~~~
$N$ $M$
$u_0$ $v_0$
$u_1$ $v_1$
:
$u_{M - 1}$ $v_{M - 1}$
~~~

## {{keyword.output}}

~~~
$X$
$p_0$ $p_1$ ... $p_{X - 1}$
~~~

$X$ は最大独立点集合のサイズ、$p_i$ は最大独立点集合

## {{keyword.sample}}

{{example.example_00}}

{{example.example_01}}
