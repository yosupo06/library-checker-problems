Problem Statement (Japanese) / 問題文 (日本語)
---------

長さ $N$ の(一次)関数列 $f_0, f_1, ..., f_{N-1}$ が与えられる。$f_i(x) = a_i x + b_i$ である。 $Q$ 個のクエリが飛んできます。処理してください。

- `0 $p$ $c$ $d$`: $f_p = cx + d$ に変更
- `1 $l$ $r$ $x$`: $f_{r-1}(f_{r-2}(...f_l(x))) \bmod 998244353$ を出力する。

Constraints / 制約
---------

- $1 \leq N, Q \leq 500,000$
- $1 \leq a_i, c < 998244353$
- $0 \leq b_i, d, x < 998244353$
- $0 \leq p < N$
- $0 \leq l < r \leq N$

Input / 入力
---------

~~~
$N$ $Q$
$a_0$ $b_0$
$a_1$ $b_1$
:
$a_{N - 1}$ $b_{N - 1}$
$\textrm{Query}_0$
$\textrm{Query}_1$
:
$\textrm{Query}_{Q - 1}$
~~~

{{example example_00}}
