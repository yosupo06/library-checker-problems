Problem Statement
---------

Given an $N$ vertices tree. Edges are $(u_i, v_i)$ and a linear function $f_i(x) = a_i x + b_i$ is written on the vertex $i$ for each $i$. Process $Q$ queries as follows:

- `0 $p$ $c$ $d$`: Set $f_p = cx + d$
- `1 $u$ $v$ $x$`: Let vertices on the path between $u$ and $v$ be $p_1 = u, p_2, ..., p_k = v$. Print $f_{p_k}(...f_{p_2}(f_{p_1}(x))) \bmod {{param MOD}}$


Problem Statement (Japanese) / 問題文 (日本語)
---------

$N$ 頂点の木が与えられる。辺は $(u_i, v_i)$。頂点 $i$ には一次関数 $f_i(x) = a_i x + b_i$ が書かれている。

$Q$ 個のクエリが飛んでくるので処理。

- `0 $p$ $c$ $d$`: $f_p = cx + d$ に変更
- `1 $u$ $v$ $x$`: $u, v$ 間のパス上の頂点(端点含む)を$p_1 = u, p_2, ..., p_k = v$ として、$f_{p_k}(...f_{p_2}(f_{p_1}(x))) \bmod {{param MOD}}$ を出力

Constraints / 制約
---------

- $1 \leq N, Q \leq {{param N_AND_Q_MAX}}$
- $1 \leq a_i, c < {{param MOD}}$
- $0 \leq b_i, d, x < {{param MOD}}$
- $0 \leq p < N$
- $0 \leq u, v < N$

Input / 入力
---------

~~~
$N$ $Q$
$a_0$ $b_0$
$a_1$ $b_1$
:
$a_{N - 1}$ $b_{N - 1}$
$u_0$ $v_0$
$u_1$ $v_1$
:
$u_{N - 2}$ $v_{N - 2}$
$\textrm{Query}_0$
$\textrm{Query}_1$
:
$\textrm{Query}_{Q - 1}$
~~~

{{example example_00}}
