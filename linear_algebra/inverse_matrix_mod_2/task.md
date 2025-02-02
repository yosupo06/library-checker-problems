## @{keyword.statement}

@{lang.en}
Given $N \times N$ matrix $A = \lbrace a_{ij} \rbrace$ with entries in $\mathbb{Z}/@{param.MOD}\mathbb{Z}$, print $A^{-1} = \lbrace b_{ij} \rbrace$. If it doesn't exist, print `-1`.

When dealing with matrix input and output, please treat each row as a string concatenated with its components ($0$ or $1$).
@{lang.ja}
$\mathbb{Z}/@{param.MOD}\mathbb{Z}$ 成分の $N \times N$ 正方行列 $A=a_{ij}$ が与えられます。$A^{-1} = \lbrace b_{ij} \rbrace$を求めてください。逆行列が存在しない場合は`-1`を出力してください。

行列の入出力の際は，各行を成分（$0$ または $1$）を結合した文字列として扱ってください．
@{lang.end}


## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $0 \leq a_{ij} < @{param.MOD}$

## @{keyword.input}

```
$N$
$a _ {11} \cdots a _ {1N}$
$\vdots$
$a _ {N1} \cdots a _ {NN}$
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
$b _ {11} \cdots b _ {1N}$
$\vdots$
$b _ {N1} \cdots b _ {NN}$
```

@{lang.ja}
と出力してください。
@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}
