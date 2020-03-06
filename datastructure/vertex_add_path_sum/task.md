Problem Statement (Japanese) / 問題文 (日本語)
---------

$N$ 頂点の木が与えられる。辺は $(u_i, v_i)$。頂点 $i$ には値 $a_i$ が書かれている。

$Q$ 個のクエリが飛んでくるので処理。

- `0 $p$ $x$`: $a_p \gets a_p + x$
- `1 $u$ $v$`: $u, v$ 間のパス上の頂点(端点含む)に書かれた値の総和を出力

Constraints / 制約
---------

- $1 \leq N, Q \leq {{param N_AND_Q_MAX}}$
- $0 \leq a_i, x \leq {{param A_AND_X_MAX}}$
- $0 \leq p, u_i, v_i < N$
- $(u_i, v_i)$ は木

Input / 入力
---------

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

{{example example_00}}
