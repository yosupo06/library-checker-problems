## @{keyword.statement}

@{lang.en}
You are given a formal power series $f(x) = \sum_{i=0}^{N-1} a_i x^i \in \mathbb{F}\_{@{param.MOD}}[[x]]$ with $a_0 \ne 0$.
Only $K$ coefficients of $f$ are non-zero, and only such coefficients $a_{i_k}$ are given from input. 

Calculate the first $N$ terms of $\frac{1}{f(x)} = \sum_{i=0}^{\infty} b_i x^i$.
In other words, find $g(x) = \sum_{i=0}^{N-1} b_i x^i \in \mathbb{F}\_{@{param.MOD}}[[x]]$ such that

$$f(x) g(x) \equiv 1 \pmod{x^N}.$$

@{lang.ja}
形式的冪級数 $f(x) = \sum_{i=0}^{N-1} a_i x^i \in \mathbb{F}\_{@{param.MOD}}[[x]]$ ($a_0 \ne 0$) が与えられます。
$f$ は $K$ 個の係数のみが非零で、非零であるような係数 $a_{i_k}$ だけが入力で与えられます。

$\frac{1}{f(x)} = \sum_{i=0}^{\infty} b_i x^i$ の先頭 $N$ 項を求めてください。つまり、

$$f(x) g(x) \equiv 1 \pmod{x^N}$$

となる $g(x) = \sum_{i=0}^{N-1} b_i x^i \in \mathbb{F}\_{@{param.MOD}}[[x]]$ を求めてください。


@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.K_MIN} \leq K \leq @{param.K_MAX}$
- $0 = i_0 < \cdots < i_{K-1} \leq N - 1$
- $1 \leq a_{i_k} < @{param.MOD}$

## @{keyword.input}

```
$N$ $K$
$i_0$ $a_{i_0}$
$\vdots$
$i_{K-1}$ $a_{i_{K-1}}$
```

## @{keyword.output}

```
$b_0$ $b_1$ $\cdots$ $b_{N - 1}$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
