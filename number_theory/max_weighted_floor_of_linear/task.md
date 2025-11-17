## @{keyword.statement}

@{lang.en}
Each test case consists of $T$ cases.

Given $N, M, A, B, C, D$. Print $\max\bigg\lbrace A x + B \bigg\lfloor\dfrac{C x + D}{M}\bigg\rfloor\mathrel{\bigg\vert} 0 \leq x \lt N\bigg\rbrace$. 

@{lang.ja}
この問題は $T$ ケース与えられます。

$N, M, A, B, C, D$ が与えられます。
$\max\bigg\lbrace A x + B \bigg\lfloor\dfrac{C x + D}{M}\bigg\rfloor\mathrel{\bigg\vert} 0 \leq x \lt N \bigg\rbrace$ を求めてください。

@{lang.end}


## @{keyword.constraints}

- $@{param.T_MIN} \leq T \leq @{param.T_MAX}$
- $@{param.NM_MIN} \leq N, M \leq @{param.NM_MAX}$
- $@{param.AB_MIN} \leq A, B \leq @{param.AB_MAX}$
- $0 \leq C, D \lt M$

## @{keyword.input}

```
$T$
$N_0$ $M_0$ $A_0$ $B_0$ $C_0$ $D_0$
$N_1$ $M_1$ $A_1$ $B_1$ $C_1$ $D_1$
:
$N_{T - 1}$ $M_{T - 1}$ $A_{T - 1}$ $B_{T - 1}$ $C_{T - 1}$ $D_{T - 1}$
```

## @{keyword.sample}

@{example.example_00}
