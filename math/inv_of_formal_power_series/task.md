## @{keyword.statement}

@{lang.en}
Given formal power series $f(x) = \sum_{i = 0}^{N - 1} a_i x^i$. Calculate first $N$ elements of $\frac{1}{f(x)}$. In other words, print $g(x)$ s.t.

$$1 = f(x)g(x) \bmod (x^N)$$

is satisfied.

@{lang.ja}
母関数 $f(x) = \sum_{i = 0}^{N - 1} a_i x^i$ が与えられます。$\frac{1}{f(x)}$ の先頭 $N$ 項を求めてください。つまり

$$1 = f(x)g(x) \bmod (x^N)$$

となる $g(x)$ を出力してください
@{lang.end}


## @{keyword.constraints}

- $1 \leq N \leq 500,000$
- $0 \leq a_i < 998244353$
- $a_0 \neq 0$

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
If we denote $g(x) = \sum_{i = 0}^{N - 1} b'_i x^i$, $b_i \equiv b'_i (\bmod 998244353)$ is satisfied.
@{lang.ja}
ただし $g(x) = \sum_{i = 0}^{N - 1} b'_i x^i$ としたとき, $b_i \equiv b'_i (\bmod 998244353)$ とする
@{lang.end}

## @{keyword.sample}

@{example.example_00}
