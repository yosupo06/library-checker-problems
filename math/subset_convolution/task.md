Problem Statement (Japanese) / 問題文 (日本語)
---------

長さ $2^N$ の整数列 $a_0, a_1, \dots, a_{2^N - 1}$, $b_0, b_1, \dots, b_{2^N - 1}$ が与えられます。以下の数列 $c_0, c_1, \dots, c_{2^N - 1}$ を $\bmod {{param MOD}}$ で計算してください。

$c_k = \sum_{i, j, i \& j = 0, i | j = k} a_i b_j$

ただし $i \& j, i | j$ はそれぞれbitwise-AND, bitwise-ORとします


Constraints / 制約
---------

- $0 \leq N \leq {{param N_MAX}}$
- $0 \leq a_i < {{param MOD}}$
- $0 \leq b_i < {{param MOD}}$


Input / 入力
---------

```
$N$
$a_0$ $a_1$ ... $a_{2^N - 1}$
$b_0$ $b_1$ ... $b_{2^N - 1}$
```

Output / 出力
---------

```
$c_0$ $c_1$ ... $c_{2^N - 1}$
```

Sample / サンプル
---------

{{example example_00}}
