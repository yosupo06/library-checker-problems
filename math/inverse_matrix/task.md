## @{keyword.statement}

@{lang.en}
Given $N \times N$ matrix $A = \lbrace a_{ij} \rbrace$ with entries in $\mathbb{Z}/@{param.MOD}\mathbb{Z}$, print $A^{-1} = \lbrace b_{ij} \rbrace$. If it doesn't exist, print `-1`.
@{lang.ja}
$\mathbb{Z}/@{param.MOD}\mathbb{Z}$ 成分の $N \times N$ 正方行列 $A=a_{ij}$ が与えられます。$A^{-1} = \lbrace b_{ij} \rbrace$を求めてください。逆行列が存在しない場合は`-1`を出力してください。
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
If there are no matrices satisfying the condition, print
@{lang.ja}
条件を満たす行列が存在しない場合、
@{lang.end}

```
-1
```

@{lang.en}
and if such matrix exists, print
@{lang.ja}
と出力してください。存在する場合
@{lang.end}

```
$b_{11}$ $b_{12}$ ... $b_{1N}$
$b_{21}$ $b_{22}$ ... $b_{2N}$
:
$b_{N1}$ $b_{N2}$ ... $b_{NN}$
```

@{lang.ja}
と出力してください。
@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}
