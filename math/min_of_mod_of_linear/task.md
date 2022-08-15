## @{keyword.statement}

@{lang.en}
Each test case consists of $T$ cases.

Given $N, M, A, B$. Print $\min_{0\leq i < N}\bigl((A\times i + B)\bmod M\bigr)$. 

@{lang.ja}
この問題は $T$ ケース与えられます。

$N, M, A, B$ が与えられます。
$\min_{0\leq i < N}\bigl((A\times i + B)\bmod M\bigr)$ を求めてください。

@{lang.end}


## @{keyword.constraints}

- $@{param.T_MIN} \leq T \leq @{param.T_MAX}$
- $@{param.NM_MIN} \leq N, M \leq @{param.NM_MAX}$
- $0 \leq A, B < M$

## @{keyword.input}

```
$T$
$N_0$ $M_0$ $A_0$ $B_0$
$N_1$ $M_1$ $A_1$ $B_1$
:
$N_{T - 1}$ $M_{T - 1}$ $A_{T - 1}$ $B_{T - 1}$
```

## @{keyword.sample}

@{example.example_00}
