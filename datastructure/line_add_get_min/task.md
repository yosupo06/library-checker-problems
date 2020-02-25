Problem Statement (Japanese) / 問題文 (日本語)
---------

$N$ 本の直線 $y = a_i x + b_i$ が存在します。 $Q$ 個のクエリを処理してください。

- `0 $a$ $b$`: 直線 $y = ax + b$ を追加
- `1 $p$`: $x = p$ での $y$ 座標の最小を求める。

Constraints / 制約
---------

- ${{param N_AND_Q_MIN}} \leq N, Q \leq {{param N_AND_Q_MAX}}$
- $|a_i|, |p| \leq {{param A_ABS_MAX}}$
- $|b_i| \leq {{param B_ABS_MAX}}$

Input / 入力
---------

~~~
$N$ $Q$
$a_0$ $b_0$
$a_1$ $b_1$
:
$a_{N-1}$ $b_{N-1}$
$\textrm{Query}_0$
$\textrm{Query}_1$
:
$\textrm{Query}_{Q - 1}$
~~~

{{example example_00}}
