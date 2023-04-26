## @{keyword.statement}

@{lang.en}

@{lang.ja}
形式的冪級数 $f(x) = \sum_{i=0}^{N-1} a_i x^i \in \mathbb{Q}[[x]]$ が与えられます ($a_0 = 0, a_1 \neq 0$)。
$f^{-1}(x) = \sum_{i=0}^{\infty} b_i x^i$ の先頭 $N$ 項を求めてください。

つまり、

$$
g(f(x))=x
$$

となる $g(x) = \sum_{i=0}^{N-1} b_i x^i \in \mathbb{Q}[[x]]$ を求めてください。係数を $@{param.MOD}$ で出力してください。

@{lang.end}

## @{keyword.constraints}

- $2 \leq N \leq 8000$
- $0 \leq a_i < 998244353$
- $a_0 = 0$
- $a_1  \neq 0$

## @{keyword.input}

```
$N$
$a_0$ $a_1$ $\cdots$ $a_{N - 1}$
```

## @{keyword.output}

```
$b_0$ $b_1$ $\cdots$ $b_{N - 1}$
```

## @{keyword.sample}

@{example.example_00}
