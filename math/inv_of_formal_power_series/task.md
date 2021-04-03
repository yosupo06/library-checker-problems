## @{keyword.statement}

@{lang.en}
You are given a formal power series $f(x) = \sum_{i=0}^{N-1} a_i x^i \in \mathbb{F}\_{@{param.MOD}}[[x]]$ with $a_0 \ne 0$.
Calculate the first $N$ terms of $\frac{1}{f(x)} = \sum_{i=0}^{\infty} b_i x^i$.
In other words, find $g(x) = \sum_{i=0}^{N-1} b_i x^i \in \mathbb{F}\_{@{param.MOD}}[[x]]$ such that

$$f(x) g(x) \equiv 1 \pmod{x^N}.$$

@{lang.ja}
形式的冪級数 $f(x) = \sum_{i=0}^{N-1} a_i x^i \in \mathbb{F}\_{@{param.MOD}}[[x]]$ が与えられます ($a_0 \ne 0$)。$\frac{1}{f(x)} = \sum_{i=0}^{\infty} b_i x^i$ の先頭 $N$ 項を求めてください。つまり、

$$f(x) g(x) \equiv 1 \pmod{x^N}$$

となる $g(x) = \sum_{i=0}^{N-1} b_i x^i \in \mathbb{F}\_{@{param.MOD}}[[x]]$ を求めてください。

@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $0 \leq a_i < @{param.MOD}$
- $a_0 \neq 0$

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
