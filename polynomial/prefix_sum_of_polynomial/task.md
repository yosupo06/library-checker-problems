## @{keyword.statement}

@{lang.en}
Given polynomial $f(x) = \sum_{i = 0}^{N - 1} a_i x^i \in \mathbb{F}_{@{param.MOD}}[x]$. Print $g(x) = \sum_{i = 0}^{N} g_i x^i \in \mathbb{F}_{@{param.MOD}}[x]$ such that

$$g(n) = \sum_{i = 0}^{n - 1} f(i)$$

for any non-negative integer $n$.
@{lang.ja}
多項式 $f(x) = \sum_{i = 0}^{N - 1} a_i x^i \in \mathbb{F}_{@{param.MOD}}[x]$ が与えられます. 任意の非負整数 $n$ に対して以下の式が成り立つの多項式 $g(x) = \sum_{i = 0}^{N} g_i x^i \in \mathbb{F}_{@{param.MOD}}[x]$ を求めてください.

$$g(n) = \sum_{i = 0}^{n - 1} f(i)$$
@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $0 \leq f_i < @{param.MOD}$

## @{keyword.input}

```
$N$
$f_0$ $f_1$ ... $f_{N - 1}$
```

## @{keyword.output}

```
$g_0$ $g_1$ ... $g_N$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
