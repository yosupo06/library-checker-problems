## @{keyword.statement}

母関数 $f(x) = \sum_{i = 0}^{N - 1} a_i x^i$ が与えられます。$\exp(f(x))$ の先頭 $N$ 項を求めてください。つまり

$$\sum_{k = 0}^{N - 1}{\frac{f(x)^k}{k!}} \bmod (x^N)$$

を出力してください

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $0 \leq a_i < @{param.MOD}$
- $a_0 = 0$

## @{keyword.input}

```
$N$
$a_0$ $a_1$ ... $a_{N - 1}$
```

## @{keyword.output}

```
$b_0$ $b_1$ ... $b_{N - 1}$
```

ただし $g(x) = \sum_{i = 0}^{N - 1} b'_i x^i$ としたとき, $b_i \equiv b'_i (\bmod @{param.MOD})$ とする

## @{keyword.sample}

@{example.example_00}
