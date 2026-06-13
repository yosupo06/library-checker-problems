## @{keyword.statement}

@{lang.en}
Given a prime number $p$ and a monic polynomial

$$
f(x)=\sum_{i=0}^{N} a_i x^i \in \mathbb{F}_p[x].
$$

Factorize $f(x)$ into monic irreducible polynomials.
@{lang.ja}
素数 $p$ と monic な多項式

$$
f(x)=\sum_{i=0}^{N} a_i x^i \in \mathbb{F}_p[x]
$$

が与えられます。$f(x)$ を monic な既約多項式の積に因数分解してください。
@{lang.end}

## @{keyword.input}

```
$N$ $p$
$a_0$ $a_1$ ... $a_N$
```

## @{keyword.output}

@{lang.en}
Print the number of distinct irreducible factors $K$.
For each factor　$g_i$, print its multiplicity $e_i$, degree $d_i$, and coefficients
$b_{i,0}, b_{i,1}, \ldots, b_{i,d_i}$ of

$$
g_i(x)=\sum_{j=0}^{d_i} b_{i,j}x^j.
$$

The output must satisfy:

- $e_i \geq 1$
- $d_i \geq 1$
- $b_{i,d_i}=1$
- each $g_i(x)$ is irreducible over $\mathbb{F}_p$
- the $g_i(x)$ are pairwise distinct
- $\prod_i g_i(x)^{e_i}=f(x)$

The factors may be printed in any order. If $f(x)=1$, print $K=0$.
@{lang.ja}
$f(x)$ に含まれる相異なる既約因子の個数を $K$ とします。
各因子 $g_i$ について、重複度 $e_i$、次数 $d_i$、および

$$
g_i(x)=\sum_{j=0}^{d_i} b_{i,j}x^j
$$

の係数 $b_{i,0}, b_{i,1}, \ldots, b_{i,d_i}$ を出力してください。

出力は以下を満たす必要があります。

- $e_i \geq 1$
- $d_i \geq 1$
- $b_{i,d_i}=1$
- 各 $g_i(x)$ は $\mathbb{F}_p$ 上既約
- $g_i(x)$ は互いに相異なる
- $\prod_i g_i(x)^{e_i}=f(x)$

因子の順序は任意です。$f(x)=1$ の場合は $K=0$ と出力してください。
@{lang.end}

```
$K$
$e_1$ $d_1$ $b_{1,0}$ $b_{1,1}$ ... $b_{1,d_1}$
$\vdots$
$e_K$ $d_K$ $b_{K,0}$ $b_{K,1}$ ... $b_{K,d_K}$
```

## @{keyword.constraints}

@{lang.en}

- $2 \leq p \leq @{param.P_MAX}$
- $p$ is prime.
- $0 \leq N \leq @{param.N_MAX}$
- $0 \leq a_i < p$
- $a_N=1$

@{lang.ja}

- $2 \leq p \leq @{param.P_MAX}$
- $p$ は素数
- $0 \leq N \leq @{param.N_MAX}$
- $0 \leq a_i < p$
- $a_N=1$

@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}

@{example.example_03}
