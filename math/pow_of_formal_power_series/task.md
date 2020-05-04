## {{keyword.statement}}$f(x):=\sum_{i=0}^{N-1} a_i x^i$ とします。
$f(x)^M \bmod x^{N}$を${{param.MOD}}$で割った余り$\sum_{i=0}^{N-1} b_i x^i$を求めてください。

## {{keyword.constraints}}

- $1 \leq N \leq {{param.N_MAX}}$
- $1 \leq M \leq {{param.M_MAX}}$
- $0 \leq a_i < {{param.MOD}}$

## {{keyword.input}}

```
$N$ $M$
$a_0$ $a_1$ $\ldots$ $a_{N-1}$
```

## {{keyword.sample}}

{{example.example_00}}

{{example.example_01}}
