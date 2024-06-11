## @{keyword.statement}

@{lang.en}
Given integers $N,M$ and two non-negative integer sequences $A = \left( A_0, A_1, \cdots, A_{N-1} \right), B = \left( B_0, B_1, \cdots, B_{N-1} \right)$.

Find the number of a non-negative integer sequences $x = \left( x_0, x_1, \cdots, x_{N-1} \right)$ which satisfies the following conditions, and print it $\bmod \ @{param.MOD}$.

- $0 \leq x_0 \leq \cdots \leq x_{N-1} < M$
- $A_i \leq x_i < B_i$

@{lang.ja}
整数 $N,M$ と長さ $N$ の非負整数列 $A = \left( A_0, A_1, \cdots, A_{N-1} \right), B = \left( B_0, B_1, \cdots, B_{N-1} \right)$ が与えられます。非負整数列 $x = \left( x_0, x_1, \cdots, x_{N-1} \right)$ で以下の条件を満たすものの個数を $\bmod \ @{param.MOD}$ で求めてください。

- $0 \leq x_0 \leq \cdots \leq x_{N-1} < M$
- $A_i \leq x_i < B_i$
@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_M_MAX}$
- $1 \leq M \leq @{param.N_M_MAX}$
- $0 \leq A_i < B_i \leq M$ ($0 \leq i \leq N - 1$)

## @{keyword.input}

```
$N$ $M$
$A_0$ $A_1$ $\cdots$ $A_{N-1}$
$B_0$ $B_1$ $\cdots$ $B_{N-1}$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}
