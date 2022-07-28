## @{keyword.statement}

@{lang.en}
You are given two formal power series $f(x) = \sum_{i=0}^{N-1} a_i x^i \in \mathbb{F}\_{@{param.MOD}}[[x]]$ and $g(x) = \sum_{i=0}^{N-1} b_i x^i \in \mathbb{F}\_{@{param.MOD}}[[x]]$ with $b_0 \ne 0$.
Calculate the first $N$ terms of $f(g(x)) = \sum_{i=0}^{\infty} c_i x^i$.
In other words, find $h(x) = \sum_{i=0}^{N-1} c_i x^i \in \mathbb{F}\_{@{param.MOD}}[[x]]$ such that

$$h(x) \equiv \sum_{i=0}^{N-1} a_i g(x)^i \pmod{x^N}.$$

@{lang.ja}
形式的冪級数 $f(x) = \sum_{i=0}^{N-1} a_i x^i \in \mathbb{F}\_{@{param.MOD}}[[x]]$ と $g(x) = \sum_{i=0}^{N-1} b_i x^i \in \mathbb{F}\_{@{param.MOD}}[[x]]$ が与えられます ($b_0 = 0$)。$f(g(x)) = \sum_{i=0}^{\infty} c_i x^i$ の先頭 $N$ 項を求めてください。つまり、

$$h(x) \equiv \sum_{i=0}^{N-1} a_i g(x)^i \pmod{x^N}$$

となる $h(x) = \sum_{i=0}^{N-1} c_i x^i \in \mathbb{F}\_{@{param.MOD}}[[x]]$ を求めてください。

@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $0 \leq a_i, b_i < @{param.MOD}$
- $b_0 = 0$
## @{keyword.input}

```
$N$
$a_0$ $a_1$ $\cdots$ $a_{N - 1}$
$b_0$ $b_1$ $\cdots$ $b_{N - 1}$
```

## @{keyword.output}

```
$c_0$ $c_1$ $\cdots$ $c_{N - 1}$
```

## @{keyword.sample}

@{example.example_00}
