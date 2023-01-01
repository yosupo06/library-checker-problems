## @{keyword.statement}

@{lang.en}
$N$ polynomials $f_i(x) = \sum_{j=0}^{d_j} a_{i,j} x^{j}$ ($i=0,\ldots,N-1$) are given. 
Compute $f(x) = \prod_{i=0}^{N-1} f_i(x)$ modulo $@{param.MOD}$. 

@{lang.ja}
$N$ 個の多項式 $f_i(x) = \sum_{j=0}^{d_j} a_{i,j} x^{j}$ ($i=0,\ldots,N-1$) が与えられます。
$f(x) = \prod_{i=0}^{N-1} f_i(x)$ を $\mod @{param.MOD}$ で求めてください。
@{lang.end}

## @{keyword.constraints}

- $0 \leq N \leq @{param.N_MAX}$
- $0 \leq d_{i}$ and $\sum_{i=0}^{N-1} d_i \leq @{param.D_MAX}$
- $0 \leq a_{i,j} < @{param.MOD}$
- $a_{i, d_i}\neq 0$

## @{keyword.input}

```
$N$
$d_0$ $a_{0,0}$ $\ldots$ $a_{0,d_0}$
$\vdots$
$d_{N-1}$ $a_{N-1,0}$ $\ldots$ $a_{N-1,d_{N-1}}$
```

## @{keyword.output}

```
$a_0$ $a_1$ ... $a_{D}$
```

Here $D = \sum_{i=0}^{N-1} d_i$ and $f(x) = \sum_{j=0}^{D} a_jx^j \pmod{@{param.MOD}}$. 

## @{keyword.sample}

@{example.example_00}

$f(x) = 2(1+2x)(3+2x+x^2) = 6+16x+10x^2+4x^3$. 

@{example.example_01}

@{example.example_02}
