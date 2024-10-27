## @{keyword.statement}

@{lang.en}
Given $N \times N$ matrix $A = \lbrace a_{ij} \rbrace$ with entries in $\mathbb{Z}/@{param.MOD}\mathbb{Z}$, print $\operatorname{adj} A = \lbrace (-1)^{i+j}M_{ji} \rbrace$, where $M_{ij}$ is the determinant of the matrix that is obtained from $A$ by removing its $i$-th row and $j$-th column. 
@{lang.ja}

@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
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

@{lang.en}
Print $b_{ij} = (-1)^{i+j} M_{ji}$:
@{lang.ja}

@{lang.end}

```
$b_{11}$ $b_{12}$ ... $b_{1N}$
$b_{21}$ $b_{22}$ ... $b_{2N}$
:
$b_{N1}$ $b_{N2}$ ... $b_{NN}$
```

@{lang.ja}

@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}
