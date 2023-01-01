## @{keyword.statement}

@{lang.en}
A prime $p$, and polynomials in $K$ variables over $\mathbb{Z}/p\mathbb{Z}$, $f(x_1, x_2, ..., x_K)$ and $g(x_1, x_2, ..., x_K)$ are given.
Calculate a product of $f$ and $g$ with $\bmod (1-x_1^{N_1}, 1-x_2^{N_2}, ..., 1-x_K^{N_K})$.
Here, $N_i$ is a divisor of $p-1$. 

@{lang.ja}
素数 $p$ および $\mathbb{Z}/p\mathbb{Z}$ 係数の $K$ 変数の多項式 $f(x_1, x_2, ..., x_K)$, $g(x_1, x_2, ..., x_K)$ が与えられます。
$f, g$ の積を、$\bmod (1-x_1^{N_1}, 1-x_2^{N_2}, ..., 1-x_K^{N_K})$ で求めてください。
ただし、$N_i$ は $p-1$ の約数であるものとします。
@{lang.end}

## @{keyword.constraints}

@{lang.en}
- $2 \leq p \leq @{param.P_MAX}$
- $p$ is a prime
- $0 \leq K \leq @{param.K_MAX}$
- $\prod N_i \leq @{param.PROD_N_MAX}$
- $2 \leq N_i$
- $N_i$ is a divisor of $p-1$
@{lang.ja}
- $2 \leq p \leq @{param.P_MAX}$
- $p$ は素数
- $0 \leq K \leq @{param.K_MAX}$
- $\prod N_i \leq @{param.PROD_N_MAX}$
- $2 \leq N_i$
- $N_i$ は $p-1$ の約数
@{lang.end}

## @{keyword.input}

```
$P$ $K$
$N_1$ $N_2$ ... $N_K$
$f$
$g$
```

@{lang.en}
$f$, $g$ is the integer array of length $\prod N_i$ consisting of integers between $0$ and $p-1$.
$i = i_1 + i_2 N_1 + ... + i_K N_1 N_2 ... N_{K-1}$-th element is corresponded to the coefficient of the $(x_1^{i_1}, x_2^{i_2}, ..., x_K^{i_K})$.
@{lang.ja}
ここで、$f$, $g$ は共に $0$ 以上 $p-1$ 以下の整数からなる長さ $\prod N_i$ の配列である。
$i = i_1 + i_2 N_1 + ... + i_K N_1 N_2 ... N_{K-1}$ 番目の要素が $(x_1^{i_1}, x_2^{i_2}, ..., x_K^{i_K})$ の係数を表す。
@{lang.end}

## @{keyword.output}

```
$fg$
```

@{lang.en}
$fg$ is the integer array of length $\prod N_i$ consisting of integers between $0$ and $p-1$. 
As the same with input format, $i = i_1 + i_2 N_1 + ... + i_K N_1 N_2 ... N_{K-1}$-th element is corresponded to the coefficient of the $(x_1^{i_1}, x_2^{i_2}, ..., x_K^{i_K})$.
@{lang.ja}
ここで、$fg$ は $0$ 以上 $p-1$ 以下の整数からなる長さ $\prod N_i$ の配列である。
$i = i_1 + i_2 N_1 + ... + i_K N_1 N_2 ... N_{K-1}$ 番目の要素が $(x_1^{i_1}, x_2^{i_2}, ..., x_K^{i_K})$ の係数を表す。
@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}
