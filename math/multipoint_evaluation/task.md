Problem Statement (Japanese) / 問題文 (日本語)
---------

多項式 $f(x) = \sum_{i = 0}^{N - 1} c_i x^i$, 整数列 $p_0, p_1, ..., p_{M - 1}$ が与えられます。
$f(p_i) \bmod 998244353$ を全ての$p_i$について求めてください。

Constraints / 制約
---------

- $1 \leq N, M \leq 2^{17}(=131072)$
- $0 \leq c_i, p_i < 998244353$
- $c_{N - 1} \neq 0$

Input / 入力
---------

```
$N$ $M$
$c_0$ $c_1$ ... $c_{N-1}$
$p_0$ $p_1$ ... $p_{M-1}$
```

Output / 出力
---------

```
$f(p_0)$ $f(p_1)$ ... $f(p_{M-1})$
```

Sample / サンプル
---------

{{example example_00}}

{{example example_01}}
