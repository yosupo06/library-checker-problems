## @{keyword.statement}

@{lang.en}
You are given a formal power series $f(x) = \sum_{i=0}^{N-1} a_i x^i \in \mathbb{F}\_{@{param.MOD}}[[x]]$ with $a_0 = 0, a_1 \neq 0$.
Calculate the first $N$ terms of $f^{\langle -1 \rangle}(x) = \sum_{i=0}^{\infty} b_i x^i$ with $b_0 = 0$.
In other words, find $g(x) = \sum_{i=0}^{N-1} b_i x^i \in \mathbb{F}\_{@{param.MOD}}[[x]]$ such that

$$
f(g(x)) \equiv g(f(x)) \equiv x \pmod{x^{N}}
$$

Print the coefficients modulo $@{param.MOD}$.

@{lang.ja}

形式的冪級数 $f(x) = \sum_{i=0}^{N-1} a_i x^i \in \mathbb{F}\_{@{param.MOD}}[[x]]$ が与えられます ($a_0 = 0, a_1 \neq 0$)。
$f^{\langle -1 \rangle}(x) = \sum_{i=0}^{\infty} b_i x^i$ ($b_0 = 0$) の先頭 $N$ 項を求めてください。 

つまり、

$$
f(g(x)) \equiv g(f(x)) \equiv x \pmod{x^{N}}
$$

となる $g(x) = \sum_{i=0}^{N-1} b_i x^i \in \mathbb{F}\_{@{param.MOD}}[[x]]$ を求めてください。係数を $\operatorname{mod} @{param.MOD}$ で出力してください。

@{lang.end}

## @{keyword.constraints}

- $2 \leq N \leq @{param.N_MAX}$
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
