## @{keyword.statement}

@{lang.en}
The number of ways to partition a set of $n$ elements into non-empty subsets is called the Bell number $B_n$. 
Given $N$, output the remainders of $B_0, \ldots, B_N$ when divided by $@{param.MOD}$.

@{lang.ja}
$n$ 元集合を空でない部分集合に分割する方法の個数 $B_n$ をベル数といいます．
$N$ が与えられるので $B_0, \ldots, B_N$ を $@{param.MOD}$ で割った余りを出力してください．
@{lang.end}

## @{keyword.constraints}

- $0 \leq N \leq @{param.N_MAX}$

## @{keyword.input}

```
$N$
```

## @{keyword.output}

```
$B_0$ $B_1$ ... $B_N$
```

## @{keyword.sample}

@{example.example_00}
