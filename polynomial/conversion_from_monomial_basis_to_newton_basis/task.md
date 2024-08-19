## @{keyword.statement}

@{lang.en}
You are given a polynomial $\displaystyle f(x) = \sum_{i=0}^{N-1} a_i x^i \in \mathbb{Z}[x]$ and integers $p_0, p_1, \ldots, p_{N-1}$.

Find $b_0, b_1, \ldots, b_{N-1}$ such that $\displaystyle f(x) = \sum_{i=0}^{N-1} b_i \prod_{j=0}^{i-1} (x-p_j)$ and print them modulo $@{param.MOD}$.

@{lang.ja}
多項式 $\displaystyle f(x) = \sum_{i=0}^{N-1} a_i x^i \in \mathbb{Z}[x]$ と整数 $p_0, p_1, \ldots, p_{N-1}$ が与えられます。

$\displaystyle f(x) = \sum_{i=0}^{N-1} b_i \prod_{j=0}^{i-1} (x-p_j)$ を満たす $b_0, b_1, \ldots, b_{N-1}$ を $\operatorname{mod} @{param.MOD}$ で出力してください。
@{lang.end}

## @{keyword.constraints}

- $0 \leq N \leq @{param.N_MAX}$
- $0 \leq a_i, p_i \lt @{param.MOD}$

## @{keyword.input}

```
$N$
$a_0$ $a_1$ $\cdots$ $a_{N-1}$
$p_0$ $p_1$ $\cdots$ $p_{N-1}$
```

## @{keyword.output}

```
$b_0$ $b_1$ $\cdots$ $b_{N-1}$
```

## @{keyword.sample}

@{example.example_00}
