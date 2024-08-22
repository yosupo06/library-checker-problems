## @{keyword.statement}

@{lang.en}

Given $Q$ cases. For each case, given a prime $p$. Print a primitive root modulo $p$. 

@{lang.ja}

クエリが $Q$ 個与えられます。各クエリでは素数 $p$ が与えられるので、その原始根をひとつ出力してください。

@{lang.end}

## @{keyword.constraints}

@{lang.en}
- $@{param.MIN_Q} \leq Q \leq @{param.MAX_Q}$
- $@{param.MIN_P} \leq p \leq @{param.MAX_P}$
- $p$ is a prime
@{lang.ja}
- $@{param.MIN_Q} \leq Q \leq @{param.MAX_Q}$
- $@{param.MIN_P} \leq p \leq @{param.MAX_P}$
- $p$ は素数
@{lang.end}
## @{keyword.input}

```
$Q$
$p_0$
$p_1$
:
$p_{Q - 1}$
```

## @{keyword.output}

@{lang.en}
Print $Q$ lines. For each line, print a primitive root $r$ ($0 \leq r < p$) of $p$. 
@{lang.ja}
$Q$ 行出力する。各行では $p$ の原始根 $r$ ($0\leq r < p$) を出力せよ。
@{lang.end}


## @{keyword.sample}

@{example.example_00}

@{example.example_01}
