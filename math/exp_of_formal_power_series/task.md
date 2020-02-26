Problem Statement (Japanese) / 問題文 (日本語)
---------

母関数 $f(x) = \sum_{i = 0}^{N - 1} a_i x^i$ が与えられます。$\exp(f(x))$ の先頭 $N$ 項を求めてください。つまり

$$\sum_{k = 0}^{N - 1}{\frac{f(x)^k}{k!}} \bmod (x^N)$$

を出力してください


Constraints / 制約
---------

- $1 \leq N \leq 500,000$
- $0 \leq a_i < 998244353$
- $a_0 = 0$

Input / 入力
---------

```
$N$
$a_0$ $a_1$ ... $a_{N - 1}$
```

Output / 出力
---------

```
$b_0$ $b_1$ ... $b_{N - 1}$
```

ただし $g(x) = \sum_{i = 0}^{N - 1} b'_i x^i$ としたとき, $b_i \equiv b'_i (\bmod 998244353)$ とする

Sample / サンプル
---------

{{example example_00}}
