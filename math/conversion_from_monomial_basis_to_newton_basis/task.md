## @{keyword.statement}

@{lang.en}
You are given a polynomial $\displaystyle f(x) = \sum_{i=0}^{N-1} a_i x^i$ and integers $p_0, p_1, \ldots, p_{N-2}$.

Print $b_0, b_1, \ldots, b_{N-1} ~ (0 \leq b_i \lt @{param.MOD})$ such that

$$f(x) = \sum_{i=0}^{N-1} b_i \prod_{j=0}^{i-1} (x-p_j)$$

.

@{lang.ja}
多項式 $\displaystyle f(x) = \sum_{i=0}^{N-1} a_i x^i$ と整数 $p_0, p_1, \ldots, p_{N-2}$ が与えられます。

$$f(x) = \sum_{i=0}^{N-1} b_i \prod_{j=0}^{i-1} (x-p_j)$$

を満たす $b_0, b_1, \ldots, b_{N-1} ~ (0 \leq b_i \lt @{param.MOD})$ を出力してください。
@{lang.end}

## @{keyword.constraints}

- $0 \leq N \leq @{param.N_MAX}$
- $0 \leq a_i, p_i \lt @{param.MOD}$

## @{keyword.input}

```
$N$
$a_0$ $a_1$ $\cdots$ $a_{N-1}$
$p_0$ $p_1$ $\cdots$ $p_{N-2}$
```

## @{keyword.output}

```
$b_0$ $b_1$ $\cdots$ $b_{N-1}$
```

## @{keyword.sample}

@{example.example_00}
