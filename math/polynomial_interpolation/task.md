## @{keyword.statement}

@{lang.en}
Given integer sequences $x_0, x_1, ..., x_{N - 1}$ and $y_0, y_1, ..., y_{N - 1}$.

Calculate a polynomial $f(x) = \sum_{i = 0}^{N - 1} c_i x^i$ s.t. $f(x_i) \equiv y_i (\bmod 998244353)$ is satisfied for each $i$.

Also, $0 \leq c_i < 998244353$ must be satisfied.

@{lang.ja}
整数列 $x_0, x_1, ..., x_{N - 1}$、$y_0, y_1, ..., y_{N - 1}$ が与えられます。

全ての $i$ について $f(x_i) \equiv y_i (\bmod 998244353)$ を満たす多項式 $f(x) = \sum_{i = 0}^{N - 1} c_i x^i$ を求めてください。
ただし $0 \leq c_i < 998244353$ とします。
@{lang.end}


## @{keyword.constraints}

- $1 \leq N \leq 2^{17}(=131072)$
- $0 \leq x_i, y_i < 998244353$
- $x_i \neq x_j (i \neq j)$

## @{keyword.input}

```
$N$
$x_0$ $x_1$ ... $x_{N-1}$
$y_0$ $y_1$ ... $y_{N-1}$
```

## @{keyword.output}

```
$c_0$ $c_1$ ... $c_{N -1}$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
