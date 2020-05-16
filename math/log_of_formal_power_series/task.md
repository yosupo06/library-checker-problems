## @{keyword.statement}

@{lang.en}

Given formal power series $f(x) = \sum_{i = 0}^{N - 1} a_i x^i$. Calculate first $N$ elements of $\log(f(x))$. In other words, print $g(x)$ s.t.

$$f(x) = \sum_{k = 0}^{N - 1}{\frac{g(x)^k}{k!}} \bmod (x^N)$$

is satisfied.

@{lang.ja}

母関数 $f(x) = \sum_{i = 0}^{N - 1} a_i x^i$ が与えられます。$\log(f(x))$ の先頭 $N$ 項を求めてください。つまり

$$f(x) = \sum_{k = 0}^{N - 1}{\frac{g(x)^k}{k!}} \bmod (x^N)$$

となる $g(x)$ を出力してください

@{lang.end}


## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $0 \leq a_i < @{param.MOD}$
- $a_0 = 1$

## @{keyword.input}

```
$N$
$a_0$ $a_1$ ... $a_{N - 1}$
```

## @{keyword.output}

```
$b_0$ $b_1$ ... $b_{N - 1}$
```

@{lang.en}
If we denote $g(x) = \sum_{i = 0}^{N - 1} b'_i x^i$, $b_i \equiv b'_i (\bmod @{param.MOD})$ is satisfied.
@{lang.ja}
ただし $g(x) = \sum_{i = 0}^{N - 1} b'_i x^i$ としたとき, $b_i \equiv b'_i (\bmod @{param.MOD})$ とする
@{lang.end}

## @{keyword.sample}

@{example.example_00}
