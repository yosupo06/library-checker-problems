## {{keyword.statement}}
母関数 $f(x) = \sum_{i = 0}^{N - 1} a_i x^i$ が与えられます。$\log(f(x))$ の先頭 $N$ 項を求めてください。つまり

$$f(x) = \sum_{k = 0}^{N - 1}{\frac{g(x)^k}{k!}} \bmod (x^N)$$

となる $g(x)$ を出力してください


## {{keyword.constraints}}

- $1 \leq N \leq 500,000$
- $0 \leq a_i < 998244353$
- $a_0 = 1$

## {{keyword.input}}

```
$N$
$a_0$ $a_1$ ... $a_{N - 1}$
```

## {{keyword.output}}

```
$b_0$ $b_1$ ... $b_{N - 1}$
```

ただし $g(x) = \sum_{i = 0}^{N - 1} b'_i x^i$ としたとき, $b_i \equiv b'_i (\bmod 998244353)$ とする

## {{keyword.sample}}

{{example example_00}}
