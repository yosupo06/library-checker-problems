Problem Statement (Japanese) / 問題文 (日本語)
---------
$N$個の正整数 $s_0,s_1,\ldots,s_{N-1}$ と正整数 $T$ が与えられます。

$t=1,2,...,T$ について、部分集合 $I \subseteq \{0,1,...,N-1\}$ のうち$\sum_{i \in I} s_i=t$となるものの個数を ${{param MOD}}$ で割った余り $p_t$ を求めてください。


Constraints / 制約
---------

- $1 \leq N \leq {{param N_MAX}}$
- $1 \leq T \leq {{param T_MAX}}$
- $1 \leq s_i \leq T$

Input / 入力
---------

```
$N$ $T$
$s_0$ $s_1$ ... $s_{N-1}$
```

Output / 出力
---------
```
$p_1$ $p_2$ ... $p_T$
```

Sample / サンプル
---------

{{example example_00}}
