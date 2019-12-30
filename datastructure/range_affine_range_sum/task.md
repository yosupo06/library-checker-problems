問題文
---------

長さ $N$ の整数列 $a_0, a_1, \dots, a_{N - 1}$ が与えられる。$Q$ 個のクエリが飛んできます。処理してください。

- `0 $l$ $r$ $b$ $c$`: 各 $i = l, l+1, \dots, {r - 1}$ について、$a_i = b \times a_i + d$
- `1 $l$ $r$`: $a_l + a_{l + 1}, \dots, a_{r - 1} \bmod 998244353$ を出力する。

制約
---------

- $1 \leq N, Q \leq 500,000$
- $0 \leq a_i, c < 998244353$
- $1 \leq b < 998244353$
- $0 \leq l < r \leq N$

入力
---------

~~~
$N$ $Q$
$a_0$ $a_1$ \ldots $a_{N - 1}$
$\textrm{Query}_0$
$\textrm{Query}_1$
:
$\textrm{Query}_{Q - 1}$
~~~

{{example example_00}}
