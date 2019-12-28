問題文
---------

$N$ 本の線分 $y = a_i x + b_i$ (ただし $x \in [l_i, r_i)$) が存在します。 $Q$ 個のクエリを処理してください。

- `0 $l$ $r$ $a$ $b$`: 線分 $y = ax + b$ (ただし $x \in [l, r)$) を追加
- `1 $p$`: $x = p$ での $y$ 座標の最小を求める。そのような座標がなければ `INFINITY` を出力

制約
---------

- ${{param N_AND_Q_MIN}} \leq N, Q \leq {{param N_AND_Q_MAX}}$
- $-{{param A_ABS_MAX}} \leq l_i \lt r_i \leq {{param A_ABS_MAX}}$
- $|a_i|, |p| \leq {{param A_ABS_MAX}}$
- $|b_i| \leq {{param B_ABS_MAX}}$

入力
---------

~~~
$N$ $Q$
$l_0$ $r_0$ $a_0$ $b_0$
$l_1$ $r_1$ $a_1$ $b_1$
:
$l_{N-1}$ $r_{N-1}$ $a_{N-1}$ $b_{N-1}$
$\textrm{Query}_0$
$\textrm{Query}_1$
:
$\textrm{Query}_{Q - 1}$
~~~

{{example example_00}}

{{example example_01}}
