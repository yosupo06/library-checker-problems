## @{keyword.statement}

@{lang.en}
Given $N \times N$ matrix $A = \lbrace a_{ij} \rbrace$ with entries in $\mathbb{Z}/@{param.MOD}\mathbb{Z}$, and a non-negative integer $K$. 
print $A^K = (b_{ij})_{i,j}$. 
@{lang.ja}
$\mathbb{Z}/@{param.MOD}\mathbb{Z}$ 成分の $N \times N$ 正方行列 $A=a_{ij}$ および非負整数 $K$ が与えられます．$A^K = (b_{ij})_{i,j}$ を求めてください．
@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $0 \leq K \leq @{param.K_MAX}$
- $0 \leq a_{ij} < @{param.MOD}$

## @{keyword.input}

```
$N$ $K$
$a_{11}$ $a_{12}$ ... $a_{1N}$
$a_{21}$ $a_{22}$ ... $a_{2N}$
:
$a_{N1}$ $a_{N2}$ ... $a_{NN}$
```

## @{keyword.output}

```
$b_{11}$ $b_{12}$ ... $b_{1N}$
$b_{21}$ $b_{22}$ ... $b_{2N}$
:
$b_{N1}$ $b_{N2}$ ... $b_{NN}$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
