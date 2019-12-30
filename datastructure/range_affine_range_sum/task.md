問題文
---------

長さ $N$ の整数列 $a_0, a_1, \dots, a_{N - 1}$ が与えられる。$Q$ 個のクエリが飛んできます。処理してください。

- `0 $l$ $r$ $b$ $c$`: 各 $i = l, l+1, \dots, {r - 1}$ について、$a_i = b \times a_i + c$
- `1 $l$ $r$`: $\sum_{i = l}^{r - 1} a_i \bmod {{param MOD}}$ を出力する。

制約
---------

- $1 \leq N, Q \leq {{param N_AND_Q_MAX}}$
- $0 \leq a_i, c < {{param MOD}}$
- $1 \leq b < {{param MOD}}$
- $0 \leq l < r \leq N$

入力
---------

~~~
$N$ $Q$
$a_0$ $a_1$ ... $a_{N - 1}$
$\textrm{Query}_0$
$\textrm{Query}_1$
:
$\textrm{Query}_{Q - 1}$
~~~

{{example example_00}}
