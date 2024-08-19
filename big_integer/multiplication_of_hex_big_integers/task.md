## @{keyword.statement}

@{lang.en}
This problem has $T$ cases.  
Given hexadecimal integers $A$ and $B$, print hexadecimal integer $AB$. 

@{lang.ja}
この問題は $T$ ケースあります。  
16 進整数 $A, B$ が与えられます。16 進整数 $AB$ を出力してください。

@{lang.end}

## @{keyword.constraints}

@{lang.en}

- $1 \leq T \leq @{param.T_MAX}$
- $0 \leq |A|, |B| < 16^{@{param.LOG_16_A_AND_B_MAX}}$
- The sum of (the number of characters in $A$) $+$ (the number of characters in $B$) over all test cases does not exceed $@{param.SUM_OF_CHARACTER_LENGTH}$.

@{lang.ja}

- $1 \leq T \leq @{param.T_MAX}$
- $0 \leq |A|, |B| < 16^{@{param.LOG_16_A_AND_B_MAX}}$
- 全てのテストケースに対する ($A$ の文字数) $+$ ($B$ の文字数) の総和は $@{param.SUM_OF_CHARACTER_LENGTH}$ を超えない。

@{lang.end}

## @{keyword.input}

```
$T$
$A$ $B$
 $\vdots$
$A$ $B$
```

## @{keyword.output}

```
$AB$
 $\vdots$
$AB$
```

## @{keyword.sample}

@{example.example_00}
