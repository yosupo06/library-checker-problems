## @{keyword.statement}

@{lang.en}
You are given a formal power series $f(x) = \sum_{i=0}^{N-1} a_i x^i \in \mathbb{Q}[[x]]$ with $a_0 = 1$.
Calculate the first $N$ terms of $\log(f(x)) = \sum_{i=0}^{\infty} b_i x^i$.
In other words, find $g(x) = \sum_{i=0}^{N-1} b_i x^i \in \mathbb{Q}[[x]]$ such that $b_0 = 0$ and

$$f(x) \equiv \sum_{k=0}^{N-1} \frac{g(x)^k}{k!} \pmod{x^N}.$$

Print the coefficients modulo $@{param.MOD}$.

@{lang.ja}
形式的冪級数 $f(x) = \sum_{i=0}^{N-1} a_i x^i \in \mathbb{Q}[[x]]$ が与えられます ($a_0 = 1$)。$\log(f(x)) = \sum_{i=0}^{\infty} b_i x^i$ の先頭 $N$ 項を求めてください。つまり、$b_0 = 0$ かつ

$$f(x) \equiv \sum_{k=0}^{N-1} \frac{g(x)^k}{k!} \pmod{x^N}$$

となる $g(x) = \sum_{i=0}^{N-1} b_i x^i \in \mathbb{Q}[[x]]$ を求めてください。係数を $\operatorname{mod} @{param.MOD}$ で出力してください。

@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $0 \leq a_i < @{param.MOD}$
- $a_0 = 1$

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
