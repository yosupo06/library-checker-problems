## @{keyword.statement}

@{lang.en}

Given a polynomial $f(x) = \sum_{i = 0}^{N - 1} c_i x^i\in \mathbb{Z}[x]$ and integers $M, a, r$. 
Print $f(ar^i) \bmod @{param.MOD}$ for each $0\leq i < M$.

@{lang.ja}

多項式 $f(x) = \sum_{i = 0}^{N - 1} c_i x^i \in \mathbb{Z}[x]$, および整数 $M, a, r$ が与えられます。
$f(ar^i) \bmod @{param.MOD}$ を $0\leq i < M$ について求めてください。

@{lang.end}

## @{keyword.constraints}

- $1 \leq N, M \leq @{param.NM_MAX}$
- $0 \leq a, r < @{param.MOD}$

## @{keyword.input}

```
$N$ $M$ $a$ $r$
$c_0$ $c_1$ ... $c_{N-1}$
```

## @{keyword.output}

```
$f(ar^0)$ $f(ar^1)$ ... $f(ar^{M-1})$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
