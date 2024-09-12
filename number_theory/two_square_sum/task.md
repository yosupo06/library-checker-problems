## @{keyword.statement}

@{lang.en}

Given $Q$ cases. 

For each case, you are given an integer $N_i$. Find all pairs of non-negative integers (a,b) statisfying $N_i=a^2+b^2$. 

@{lang.ja}

クエリが $Q$ 個与えられます．

各クエリでは整数 $N_i$ が与えられるので，非負整数の組 $(a,b)$ であって $N_i=a^2+b^2$ を満たすものをすべて求めてください．

@{lang.end}

## @{keyword.constraints}

- $1 \leq Q \leq @{param.MAX_Q}$
- $0 \leq N_i \leq @{param.MAX_A}$

## @{keyword.input}

```
$Q$
$N_0$
$N_1$
$\vdots$
$N_{Q - 1}$
```

## @{keyword.output}

@{lang.en}
For each test case, let $n$ be the number of pairs $(a,b)$ that satisfy the condition. Output a total of $n+1$ lines in the following format. The output order can be arbitrary.
@{lang.ja}
テストケースごとに，条件を満たす組 $(a,b)$ の個数を $n$ として次の形式で合計 $n+1$ 行出力してください．どのような順番で出力してもよいです．
@{lang.end}

```
$n$
$a$ $b$
$\vdots$
$a$ $b$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
