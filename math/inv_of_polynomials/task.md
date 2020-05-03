Problem Statement (Japanese) / 問題文 (日本語)
---------

互いに素な多項式$f(x)=\sum_{i=0}^{N-1} a_i x^i$ と $g(x)=\sum_{i=0}^{M-1} b_i x^i$ が与えられます。

f(x)h(x) \equiv 1 \bmod g(x)

となる $h(x)$ を ${{param MOD}}$ で割った余り $\sum_{i=0}^{T-1} c_ix^i$ を出力してください。


Constraints / 制約
---------

- $1 \leq N \leq {{param N_MAX}}$
- $1 \leq M \leq {{param N_MAX}}$
- $0 \leq a_i < {{param MOD}}$
- $0 \leq b_i < {{param MOD}}$
- $a_{N-1} \neq 0$
- $b_{M-1} \neq 0$

Input / 入力
---------

```
$N$
$a_0$ $a_1$ \ldots $a_{N - 1}$
$b_0$ $b_1$ \ldots $b_{M - 1}$

```

Output / 出力
---------
$c_{T-1} \neq 0$ を満たす $T$ を一行目に出力してください。
```
$T$
$c_0$ $c_1$ ... $c_{T - 1}$
```

Sample / サンプル
---------

{{example example_00}}
