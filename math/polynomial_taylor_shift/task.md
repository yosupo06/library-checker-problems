Problem Statement / 問題文
---------

A Polynomial $f(x) = \sum_{i=0}^{N-1} a_ix^i$ and an integer $c$ is given.
Compute the sequence $b_0, b_1, \ldots, b_{N-1}$ satisfying $f(x+c) = \sum_{i=0}^{N-1}b_ix^i$, and print it modulo ${{param MOD}}$.

Problem Statement (Japanese) / 問題文 (日本語)
---------

多項式 $f(x) = \sum_{i=0}^{N-1} a_ix^i$, 整数 $c$ が与えられます。
$f(x+c) = \sum_{i=0}^{N-1}b_ix^i$ を満たす数列 $b_0, b_1, \ldots, b_{N-1}$ を $\bmod {{param MOD}}$ で計算してください。

Constraints / 制約
---------

- $1 \leq N \leq {{param N_AND_M_MAX}}$
- $0 \leq c, a_i < {{param MOD}}$

Input / 入力
---------

```
$N$
$c$
$a_0$ $a_1$ ... $a_{N-1}$
```

Output / 出力
---------

```
$b_0$ $b_1$ ... $b_{(N - 1)$
```

Sample / サンプル
---------

{{example example_00}}

{{example example_01}}
