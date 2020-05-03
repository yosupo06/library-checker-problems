Problem Statement (Japanese) / 問題文 (日本語)
---------
$\mathbb{Z}/{{param MOD}}\mathbb{Z}$ 係数の多項式 $f(x)=\sum_{i=0}^{N-1} a_ix^i ,g(x)=\sum_{i=0}^{M-1}b_ix^i$ が与えられます。
$\deg(h) < \deg(g)$ かつ 
$$f(x)h(x)\equiv1\pmod {g(x)}$$
を満たす$\mathbb{Z}/{{param MOD}}\mathbb{Z}$ 係数の多項式 $h(x)=\sum_{i=0}^{T-1}c_ix^i$ を求めてください。
ただし $\deg(0)=-\infty$とします。
このような $h(x)$ は存在するならば一意に定まることが示せます。
$h(x)$ が存在しないときは$-1$を出力してください。

Constraints / 制約
---------

- $1 \leq N \leq {{param N_MAX}}$
- $1 \leq M \leq {{param N_MAX}}$
- $0 \leq a_i < {{param MOD}}$
- $0 \leq b_i < {{param MOD}}$
- $a_{N-1} \neq 0$
- $b_{M-1} \neq 0$
- $g(x) \neq 0$
Input / 入力
---------

```
$N M$
$a_0$ $a_1$ $\ldots$ $a_{N - 1}$
$b_0$ $b_1$ $\ldots$ $b_{M - 1}$

```

Output / 出力
---------
$h(x)$ が存在しないときは一行に $-1$ を出力してください。
$h(x)$ が存在するときは一行目に $T$ ($c_{T-1} \neq 0$) を出力してください。ただし $h(x)=0$ のときは $T=0$ としてください。
$h(x)$ が存在するときは二行目に $c0,c1,\ldots,c_{T-1}$ を空白区切りで出力してください。
```
$T$
$c_0$ $c_1$ $\ldots$ $c_{T - 1}$
```

Sample / サンプル
---------

{{example example_00}}
