## @{keyword.statement}

@{lang.en}

Given $N \times M$ matrix $A$. Please calculate the rank of $A$. We consider everything $\mathbb{F}_{@{param.MOD}}$.

@{lang.ja}

$N \times M$ 行列 $A$ が与えられます．$A$ の階数を求めてください．ただし全ての要素は $\mathbb{F}_{@{param.MOD}}$ で考えることとします．

@{lang.end}

## @{keyword.constraints}

- $0 \leq N, M \leq @{param.NM_MAX}$
- $NM\leq @{param.NM_MAX}$
- $0 \leq A_{ij} < @{param.MOD}$

## @{keyword.input}

```
$N$ $M$
$A_{0,0}$ $A_{0,1}$ ... $A_{0,M-1}$
$A_{1,0}$ $A_{1,1}$ ... $A_{1,M-1}$
:
$A_{N-1,0}$ $A_{N-1,1}$ ... $A_{N-1,M-1}$
```

## @{keyword.output}

@{lang.en}
Output the rank of $A$. 
@{lang.ja}
$A$ の階数を出力してください．
@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}

@{example.example_03}
