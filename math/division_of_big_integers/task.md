## @{keyword.statement}

@{lang.en}
This problem has $T$ cases.  
Given a non-negative integer $A$ and a positive integer $B$, print integers $q, r$ satisfying the following equation:

@{lang.ja}
この問題は $T$ ケースあります。  
非負整数 $A$ と正整数 $B$ が与えられます。次の式を満たす整数 $q, r$ を出力してください。

@{lang.end}

- $q = \left \lfloor \frac{A}{B} \right \rfloor$
- $A = qB + r$

## @{keyword.constraints}

- $1 \leq T \leq @{param.T_MAX}$
- $0 \leq A \leq 10^{@{param.LOG_10_A_AND_B_MAX}}$
- $1 \leq B \leq 10^{@{param.LOG_10_A_AND_B_MAX}}$
- @{lang.en}The sum of (the number of characters in $A$) $+$ (the number of characters in $B$) over all test cases does not exceed $@{param.SUM_OF_CHARACTER_LENGTH}$.@{lang.ja}全てのテストケースに対する ($A$ の文字数) $+$ ($B$ の文字数) の総和は $@{param.SUM_OF_CHARACTER_LENGTH}$ を超えない。@{lang.end}

## @{keyword.input}

```
$T$
$A$ $B$
 $\vdots$
$A$ $B$
```

## @{keyword.output}

```
$q$ $r$
 $\vdots$
$q$ $r$
```

## @{keyword.sample}

@{example.example_00}
