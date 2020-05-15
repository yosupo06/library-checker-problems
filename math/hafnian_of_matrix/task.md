## @{keyword.statement}

@{lang.en}
Given $N \times N$ zero diagonal symmetric matrix $A = (a_{i,j})$. Print the hafnian of $A$ modulo $@{param.MOD}$.
@{lang.ja}
対角成分が $0$ の $N \times N$ 対称行列 $A = (a_{i,j})$ が与えられます。$A$ のハフニアンを mod $@{param.MOD}$ で求めてください。
@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \le N \le @{param.N_MAX}$
- $N \bmod 2 = 0$
- $0 \le a_{ij} \lt @{param.MOD}$
- $a_{i,i} = 0$
- $a_{i,j} = a_{j,i}$

## @{keyword.input}

```
$N$
$a_{0,0}$ $a_{0,1}$ $\ldots$ $a_{0,N-1}$
$a_{1,0}$ $a_{1,1}$ $\ldots$ $a_{1,N-1}$
$\vdots$
$a_{N-1,0}$ $a_{N-1,1}$ $\ldots$ $a_{N-1,N-1}$
```

## @{keyword.sample}

@{example.example_00}
