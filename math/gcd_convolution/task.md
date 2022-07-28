## @{keyword.statement}

@{lang.en}
Given integer sequences $a_1, ..., a_{N}$ and $b_1, ..., b_{N}$. 
Calculate an integer sequence $c_1, ..., c_{N}$ as follows:

$$c_k = \sum_{\gcd(i,j)=k} a_ib_j \bmod @{param.MOD}$$

@{lang.ja}
整数列 $a_1, ..., a_{N}$、$b_1, ..., b_{N}$ が与えられます。整数列 $c_1, ..., c_{N}$ を求めてください。ただし、

$$c_k = \sum_{\gcd(i,j)=k} a_ib_j \bmod @{param.MOD}$$

です
@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $0 \leq a_i, b_i < @{param.MOD}$

## @{keyword.input}

```
$N$
$a_1$ ... $a_{N}$
$b_1$ ... $b_{N}$
```

## @{keyword.output}

```
$c_1$ ... $c_{N}$
```

## @{keyword.sample}

@{example.example_00}
