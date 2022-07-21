## @{keyword.statement}

@{lang.en}
You are given a formal power series $f(x) = \sum_{i=0}^{N-1} a_i x^i \in \mathbb{Q}[[x]]$ with $a_0 = 1$.
Only $K$ coefficients of $f$ are non-zero, and only such coefficients $a_{i_k}$ are given from input. 

Calculate the first $N$ terms of $\log(f(x)) = \sum_{i=0}^{\infty} b_i x^i$.
In other words, find $g(x) = \sum_{i=0}^{N-1} b_i x^i \in \mathbb{Q}[[x]]$ such that $b_0 = 0$ and 

$$f(x) \equiv \sum_{k=0}^{N-1} \frac{g(x)^k}{k!} \pmod{x^N}.$$

Print the coefficients modulo $@{param.MOD}$.

@{lang.ja}
形式的冪級数 $f(x) = \sum_{i=0}^{N-1} a_i x^i \in \mathbb{Q}[[x]]$ が与えられます ($a_0 = 1$)。
$f$ は $K$ 個の係数のみが非零で、非零であるような係数 $a_{i_k}$ だけが入力で与えられます。

$\log(f(x)) = \sum_{i=0}^{\infty} b_i x^i$ の先頭 $N$ 項を求めてください。つまり、$b_0 = 0$ かつ

$$f(x) \equiv \sum_{k=0}^{N-1} \frac{g(x)^k}{k!} \pmod{x^N}$$

となる $g(x) = \sum_{i=0}^{N-1} b_i x^i \in \mathbb{Q}[[x]]$ を求めてください。係数を $\operatorname{mod} @{param.MOD}$ で出力してください。

@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.K_MIN} \leq K \leq @{param.K_MAX}$
- $0 = i_0 < \cdots < i_{K-1} \leq N - 1$
- $1 \leq a_{i_k} < @{param.MOD}$
- $a_0 = 1$

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
