## {{keyword.statement}}
$N \times N$ 正方行列 $M$ が与えられます。
$M$ は $K$ 個の要素のみが非零で、$i$ 個目は $M(a_i, b_i) = c_i$ です。
$M$ の行列式を $\bmod {{param MOD}}$ で求めてください。

## {{keyword.constraints}}

- $1 \leq N \leq {{param N_MAX}}$
- $1 \leq K \leq {{param M_MAX}}$
- $0 \leq a_i, b_i \leq N - 1$
- $(a_i, b_i)$ は全て異なる
- $1 \leq c_i < {{param MOD}}$

## {{keyword.input}}

```
$N$ $K$
$a_1$ $b_1$ $c_1$
$a_2$ $b_2$ $c_2$
:
$a_K$ $b_K$ $c_K$
```

## {{keyword.sample}}

{{example example_00}}

{{example example_01}}
