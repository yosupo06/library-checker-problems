Problem Statement / 問題文
---------

You are given an integer sequence $a_0, a_1, ..., a_{N-1}$ with the length $N$.
Process the following $Q$ queries in order:

- `$l_i$ $r_i$`: Print $\min(a_l, a_{l+1}, ..., a_{r_i - 1})$.

Problem Statement (Japanese) / 問題文 (日本語)
---------

長さ $N$ の数列 $a_0, a_1, ..., a_{N-1}$ に $Q$ 個のクエリが飛んできます。処理してください。

- `$l_i$ $r_i$`: $\min(a_l, a_{l+1}, ..., a_{r_i - 1})$ を出力する。

Constraints / 制約
---------

- $1 \leq N, Q \leq 500,000$
- $0 \leq a_i \leq 10^9$
- $0 \leq l_i < r_i \leq N$

Input / 入力
---------

~~~
$N$ $Q$
$a_0$ $a_1$ ... $a_{N - 1}$
$l_1$ $r_1$
$l_2$ $r_2$
:
$l_Q$ $r_Q$
~~~

{{example example_00}}
