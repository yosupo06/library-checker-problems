## @{keyword.statement}

@{lang.en}
Given $N \times M$ matrix $A = \lbrace a_{ij} \rbrace$ with entries in $\mathbb{Z}/@{param.MOD}\mathbb{Z}$, print the matrix rank of $A$. 

When dealing with matrix input, please treat each row as a string concatenated with its components ($0$ or $1$).
@{lang.ja}
$\mathbb{Z}/@{param.MOD}\mathbb{Z}$ 成分の $N \times M$ 正方行列 $A = \lbrace a_{ij} \rbrace$ が与えられます．$A$ の階数を出力してください．

行列の入力の際は，各行を成分（$0$ または $1$）を結合した文字列として扱ってください．
@{lang.end}


## @{keyword.constraints}

- $0 \leq N, M \leq @{param.NM_MAX}$
- $0 \leq NM \leq @{param.NM_MAX}$
- $0 \leq a_{ij} < @{param.MOD}$

## @{keyword.input}

```
$N$
$a _ {11} \cdots a _ {1M}$
$\vdots$
$a _ {N1} \cdots a _ {NM}$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
