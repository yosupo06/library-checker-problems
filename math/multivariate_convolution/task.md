## @{keyword.statement}

@{lang.en}
The polynomials in $K$ variables over $\mathbb{Z}/@{param.MOD}\mathbb{Z}$, $f(x_1, x_2, ..., x_K)$ and $g(x_1, x_2, ..., x_K)$ are given.
Calculate a product of $f$ and $g$ with $\bmod (x_1^{N_1}, x_2^{N_2}, ..., x_K^{N_K})$.
@{lang.ja}
$\mathbb{Z}/@{param.MOD}\mathbb{Z}$ 係数の $K$ 変数の多項式 $f(x_1, x_2, ..., x_K)$, $g(x_1, x_2, ..., x_K)$ が与えられます。
$f, g$ の積を、$\bmod (x_1^{N_1}, x_2^{N_2}, ..., x_K^{N_K})$ で求めてください。
@{lang.end}

## @{keyword.constraints}

- $0 \leq K \leq @{param.K_MAX}$
- $\prod N_i \leq @{param.PROD_N_MAX}$
- $2 \leq N_i$

## @{keyword.input}

```
$K$
$N_1$ $N_2$ ... $N_K$
$f$
$g$
```

@{lang.en}
$f$, $g$ is the integer array of length $\prod N_i$. $i = i_1 + i_2 N_1 + ... + i_K N_1 N_2 ... N_{K-1}$-th element is corresponded to the coefficient of the $(x_1^{i_1}, x_2^{i_2}, ..., x_K^{i_K})$.
@{lang.ja}
ここで、$f$, $g$ は共に長さ $\prod N_i$ の配列であり、$i = i_1 + i_2 N_1 + ... + i_K N_1 N_2 ... N_{K-1}$ 番目の要素が $(x_1^{i_1}, x_2^{i_2}, ..., x_K^{i_K})$ の係数を表す。
@{lang.end}

## @{keyword.output}

```
$fg$
```

@{lang.en}
$fg$ is the integer array of length $\prod N_i$. As the same with input format, $i = i_1 + i_2 N_1 + ... + i_K N_1 N_2 ... N_{K-1}$-th element is corresponded to the coefficient of the $(x_1^{i_1}, x_2^{i_2}, ..., x_K^{i_K})$.
@{lang.ja}
ここで、$fg$ は $f, g$ の積を表す長さ $\prod N_i$ の配列であり、$i = i_1 + i_2 N_1 + ... + i_K N_1 N_2 ... N_{K-1}$ 番目の要素が $(x_1^{i_1}, x_2^{i_2}, ..., x_K^{i_K})$ の係数を表す。
@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}
