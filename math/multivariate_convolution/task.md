## @{keyword.statement}

$\mathbb{Z}/@{param.MOD}\mathbb{Z}$ 係数の $K$ 変数の多項式 $f(x_1, x_2, ..., x_K)$, $g(x_1, x_2, ..., x_K)$ が与えられます。
$f, g$ の積を、$\bmod (x_1^{N_1}, x_2^{N_2}, ..., x_K^{N_K})$ で求めてください。

## @{keyword.constraints}

- $0 \leq K \leq @{param.MAX_K}$
- $\prod N_i \leq @{param.MAX_PROD_N}$
- $2 \leq N_i$

## @{keyword.input}

```
$K$
$N_1$ $N_2$ ... $N_K$
$f$
$g$
```

ここで、$f$, $g$ は共に長さ $\prod N_i$ の配列であり、$i = i_1 + i_2 N_1 + ... + i_K N_1 N_2 ... N_{K-1}$ 番目の要素が $(x_1^{i_1}, x_2^{i_2}, ..., x_K^{i_K})$ の係数を表す。

## @{keyword.output}

```
$fg$
```

ここで、$fg$ は $f, g$ の積を表す長さ $\prod N_i$ の配列であり、$i = i_1 + i_2 N_1 + ... + i_K N_1 N_2 ... N_{K-1}$ 番目の要素が $(x_1^{i_1}, x_2^{i_2}, ..., x_K^{i_K})$ の係数を表す。

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
