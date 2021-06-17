## @{keyword.statement}

@{lang.en}
Given $N \times N$ matrix $A = \lbrace a_{ij} \rbrace$. Print $A^{-1} \bmod @{param.MOD}$. If it doesn't exist, print `-1`.
@{lang.ja}
$N \times N$ 正方行列 $A=a_{ij}$ が与えられます。$A^{-1} \bmod @{param.MOD}$を求めてください。逆行列が存在しない場合は`-1`を出力してください。
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

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}
