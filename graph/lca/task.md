Problem Statement / 問題文
---------

木が与えられる。頂点 $i$ の親は $p_i$ である。$Q$ 個のクエリが飛んできます。処理してください。

- `$u$ $v$`: 頂点 $u$, $v$ のLCAを出力する

Constraints / 制約
---------

- $2 \leq N \leq 500,000$
- $1 \leq Q \leq 500,000$
- $0 \leq p_i < i$
- $0 \leq u < v \leq N - 1$

Input / 入力
---------

~~~
$N$ $Q$
$p_1$ $p_2$ ... $p_{N-1}$
$u_0$ $v_0$
$u_1$ $v_1$
:
$u_{Q - 1}$ $v_{Q - 1}$
~~~

Sample / サンプル
---------

{{example example_00}}
