## @{keyword.statement}

@{lang.en}
Given $N \times M$ matrix $A$ and $M \times K$ matrix $B$, print $C = AB \bmod @{param.MOD}$. 

When dealing with matrix input and output, please treat each row as a string concatenated with its components ($0$ or $1$).
@{lang.ja}
$N \times M$ 行列 $A$ と $M \times K$ 行列 $B$ が与えられます． $C = A B \bmod @{param.MOD}$を求めてください．

行列の入出力の際は，各行を成分（$0$ または $1$）を結合した文字列として扱ってください．
@{lang.end}

## @{keyword.constraints}

- $1 \leq N,M,K \leq @{param.N_MAX}$
- $a_{ij},b_{ij} \in \lbrace 0,1\rbrace$

## @{keyword.input}

```
$N\ M\ K$
$a_{11}a_{12} \cdots a_{1M}$
$a_{21}a_{22} \cdots a_{2M}$
$\vdots$
$a_{N1}a_{N2} \cdots a_{NM}$
$b_{11}b_{12} \cdots b_{1K}$
$b_{21}b_{22} \cdots b_{2K}$
$\vdots$
$b_{M1}b_{M2} \cdots b_{MK}$
```

## @{keyword.output}
```
$c_{11}c_{12} \cdots c_{1K}$
$c_{21}c_{22} \cdots c_{2K}$
\vdots
$c_{N1}c_{N2} \cdots c_{NK}$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}
