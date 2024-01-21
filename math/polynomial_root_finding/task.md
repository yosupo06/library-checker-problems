## @{keyword.statement}

@{lang.en}
Given a polynomial $f(x) = \sum_{i=0}^Nf_ix^i\in \mathbb{F}_{998244353}[x]$ of degree $N$. 
Find all $a\in \mathbb{F}_{998244353}$ satisfying $f(a)=0$.

@{lang.ja}
次数 $N$ の多項式 $f(x) \in \mathbb{F}_{998244353}[x]$ が与えられます．
$f(a)=0$ を満たす $a\in \mathbb{F}_{998244353}$ をすべて求めてください．

@{lang.end}

## @{keyword.constraints}

- $0\leq N\leq @{param.N_MAX}$
- $0\leq f_i < @{param.MOD}$
- $f_N\neq 0$

## @{keyword.input}

```
$N$
$f_0$ $\cdots$ $f_N$
```

## @{keyword.output}

@{lang.en}
Print all $a$ satisfying $f(a)=0$ in the following format. 

@{lang.ja}
$f(a)=0$ を満たす $a$ 全体を次の形式で出力してください．

@{lang.end}

```
$n$
$a_0$ $\cdots$ $a_{n-1}$
```

@{lang.en}
$a_i$ should be printed as an non-negative integer less than $@{param.MOD}$. 
The order in which $a_i$ is output can be arbitrary.

@{lang.ja}
$a_i$ は $@{param.MOD}$ 未満の非負整数として出力してください．
$a_i$ はどのような順序で出力してもよいです. 

@{lang.end}


## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}

@{example.example_03}
