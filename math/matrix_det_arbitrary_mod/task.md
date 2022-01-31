## @{keyword.statement}

@{lang.en}
Given $N \times N$ matrix $M = \lbrace a_{ij} \rbrace$ and an integer $m$. Print $\mathrm{det}(M) \bmod m$.
@{lang.ja}
$N \times N$ 正方行列 $M = \lbrace a_{ij} \rbrace$、整数 $m$ が与えられます。行列式を $\bmod m$ で求めてください。
@{lang.end}

## @{keyword.constraints}

- $0 \leq N \leq @{param.N_MAX}$
- $1 \lt m \leq @{param.M_MAX}$
- $0 \leq a_{ij} < m$

## @{keyword.input}

```
$N$ $m$
$a_{11}$ $a_{12}$ ... $a_{1N}$
$a_{21}$ $a_{22}$ ... $a_{2N}$
:
$a_{N1}$ $a_{N2}$ ... $a_{NN}$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}
