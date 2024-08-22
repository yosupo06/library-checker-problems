## @{keyword.statement}

@{lang.en}
Given integers $N, a, r$ and integer sequence $y_0, y_1, ..., y_{N - 1}$.
It is guaranteed that $ar^i\not\equiv ar^j\pmod{@{param.MOD}}$ for $0\leq i < j \leq N-1$. 

Calculate a polynomial $f(x) = \sum_{i = 0}^{N - 1} c_i x^i\in \mathbb{Z}[x]$ s.t. $f(ar^i) \equiv y_i \pmod{@{param.MOD}}$ is satisfied for each $i$.

Also, $0 \leq c_i < @{param.MOD}$ must be satisfied.

@{lang.ja}
整数 $N, a, r$ および整数列 $y_0, y_1, \ldots, y_{N-1}$ が与えられます。
$0\leq i < j \leq N-1$ に対して $ar^i \not\equiv ar^j\pmod{@{param.MOD}}$ であることが保証されます。

全ての $i$ について $f(ar^i) \equiv y_i \pmod{@{param.MOD}}$ を満たす多項式 $f(x) = \sum_{i = 0}^{N - 1} c_i x^i \in \mathbb{Z}[x]$ を求めてください。
ただし $0 \leq c_i < @{param.MOD}$ とします。
@{lang.end}


## @{keyword.constraints}

- $0 \leq N \leq @{param.MAX_N}$
- $0 \leq a < @{param.MOD}$
- $0 \leq r < @{param.MOD}$
- $0 \leq y_i < @{param.MOD}$
- $ar^i\not\equiv ar^j \pmod{@{param.MOD}}$ $(0\leq i < j \leq N-1)$

## @{keyword.input}

```
$N$ $a$ $r$
$y_0$ $y_1$ ... $y_{N-1}$
```

## @{keyword.output}

```
$c_0$ $c_1$ ... $c_{N -1}$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
