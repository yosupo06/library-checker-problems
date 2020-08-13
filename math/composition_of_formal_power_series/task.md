## @{keyword.statement}

@{lang.en}
Given formal power series $f(x) = \sum_{i = 0}^{N - 1} a_i x^i$ and $g(x) = \sum_{i = 0}^{N - 1} b_i x^i$.
Calculate first $N$ terms of $f(g(x))$,in other words, find

$h(x)=\sum_{i=0}^{N-1} a_i g(x)^i \bmod (x^N)$ and output the coefficients modulo $@{param.MOD}$.

@{lang.ja}
形式的冪級数 $f(x) = \sum_{i = 0}^{N - 1} a_i x^i$ と $g(x) = \sum_{i = 0}^{N - 1} b_i x^i$ が与えられます。
$f(g(x))$ の先頭$N$項を求めてください。つまり

$h(x)=\sum_{i=0}^{N-1} a_i g(x)^i \bmod (x^N)$となる$h(x)$を求めて、係数を modulo $@{param.MOD}$ で出力してください


@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $0 \leq a_i, b_i < @{param.MOD}$
- $b_0 = 0$
## @{keyword.input}

```
$N$
$a_0$ $a_1$ ... $a_{N - 1}$
$b_0$ $b_1$ ... $b_{N - 1}$
```

## @{keyword.output}

```
$c_0$ $c_1$ ... $c_{N - 1}$
```
@{lang.en}
If we denote $h(x)=\sum_{i = 0}^{(N - 1)} c'_i x^i$,$c_i \equiv c'_i(\bmod{@{param.MOD}})$ is satisfied.
@{lang.ja}
ただし、$h(x)=\sum_{i = 0}^{(N - 1)} c'_i x^i$とした時$c_i \equiv c'_i(\bmod @{param.MOD})$である。
@{lang.end}

## @{keyword.sample}

@{example.example_00}
