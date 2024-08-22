## @{keyword.statement}

@{lang.en}
Given sampling points $f(0), f(1), \ldots , f(N - 1)$ of polynomial $f(x) \in \mathbb{F}_{@{param.MOD}}[x]$ of degree less than $N$, compute $f(c ＋ i)$ for $i = 0, 1, \ldots , M - 1$.
@{lang.ja}
次数 $N$ 未満の多項式 $f(x) \in \mathbb{F}_{@{param.MOD}}[x]$ の標本点 $f(0), f(1), \ldots , f(N - 1)$ が与えられます。
$i = 0, 1, \ldots , M - 1$ に対して $f(c ＋ i)$ を計算してください。
@{lang.end}

## @{keyword.constraints}

- $1 \leq N,M \leq @{param.N_MAX}$
- $0 \leq c, f(i) < @{param.MOD}$

## @{keyword.input}

```
$N$ $M$ $c$
$f(0)$ $f(1)$ ... $f(N - 1)$
```

## @{keyword.output}

```
$f(c)$ $f(c + 1)$ ... $f(c + M - 1)$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
