## @{keyword.statement}

@{lang.en}

Given $N \times N$ matrix $M = \lbrace a_{ij} \rbrace$. Print its (monic) characteristic polynomial $p(x)$ where

$$p(x) = \det (xI - M) = \sum_{i = 0}^N p_i x^i$$

and $I$ denotes the $N \times N$ identity matrix. The determinant of $0 \times 0$ matrix is equal to $1$. We consider everything $\mathbb{Z}/@{param.MOD}\mathbb{Z}$.

@{lang.ja}

$N \times N$ 正方行列 $M = \lbrace a_{ij} \rbrace$ が与えられます。$M$ の(モニック)特性多項式 $p(x)$ を求めてください。

$$p(x) = \det (xI - M) = \sum_{i = 0}^N p_i x^i$$

ここで、$I$ は $N \times N$ の単位行列です。$0 \times 0$ 正方行列の行列式は $1$ です。全ての要素は $\mathbb{Z}/@{param.MOD}\mathbb{Z}$ で考えることとします。

@{lang.end}

## @{keyword.constraints}

- $0 \leq N \leq @{param.N_MAX}$
- $0 \leq a_{ij} < @{param.MOD}$

## @{keyword.input}

```
$N$
$a_{11}$ $a_{12}$ ... $a_{1N}$
$a_{21}$ $a_{22}$ ... $a_{2N}$
:
$a_{N1}$ $a_{N2}$ ... $a_{NN}$
```

## @{keyword.output}

```
$p_0$ $p_1$ ... $p_N$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}
