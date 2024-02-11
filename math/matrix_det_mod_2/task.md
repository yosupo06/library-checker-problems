## @{keyword.statement}

@{lang.en}
Given $N \times N$ matrix $M = \lbrace a_{ij} \rbrace$. Print $\mathrm{det}(M) \bmod 2$.

When dealing with matrix input and output, please treat each row as a string concatenated with its components ($0$ or $1$).
@{lang.ja}
$N \times N$ 正方行列 $a_{ij}$ が与えられます．行列式を $\mod 2$ で求めてください．

行列の入力の際は，各行を成分（$0$ または $1$）を結合した文字列として扱ってください．
@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $a_{ij} \in \lbrace 0,1\rbrace$

## @{keyword.input}

```
$N$
$a_{11}a_{12} \cdots a_{1N}$
$a_{21}a_{22} \cdots a_{2N}$
$\vdots$
$a_{N1}a_{N2} \cdots a_{NN}$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}
