## @{keyword.statement}

@{lang.en}
You are given polynomials $f(x)=\sum_{i=0}^{N-1} f_ix^i$ and $g(x)=\sum_{i=0}^{M-1}g_ix^i$. Calculate polynomials $q(x)$ and $r(x)$ such that 

- $f(x) = q(x)g(x) + r(x)$ and 
- $\deg(r) \lt \deg(g)$. 

Print the coefficients modulo $@{param.MOD}$.

@{lang.ja}
多項式 $f(x)=\sum_{i=0}^{N-1} f_ix^i ,g(x)=\sum_{i=0}^{M-1}g_ix^i$ が与えられます。次の条件を満たす多項式$q(x),r(x)$を求めて、係数を$\bmod @{param.MOD}$で出力してください。

- $f(x) = q(x)g(x) + r(x)$
- $\deg(r) \lt \deg(g)$

@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $1 \leq M \leq @{param.N_MAX}$
- $0 \leq f_i < @{param.MOD}$
- $0 \leq g_i < @{param.MOD}$
- $f_{N-1} \neq 0$
- $g_{M-1} \neq 0$  

## @{keyword.input}

```
$N\ M$
$f_0\ f_1\ \ldots\ f_{N - 1}$
$g_0\ g_1\ \ldots\ g_{M - 1}$
```

## @{keyword.output}

@{lang.en}
Print $u=\deg(q)+1$ and $v=\deg(r)+1$ in the first line. Let $u = 0$ instead if $q(x) = 0$. (The same is true for $r(x)$.)

Print the coefficients of $q(x)$ in the second line and $r(x)$ in the third line.

@{lang.ja}
1行目には$u = \deg(q) + 1, v = \deg(r) + 1$を出力してください。ただし、$q(x) = 0$のときは$u = 0$としてください。($r(x)$についても同様です。)

2行目には$q(x)$の係数を、3行目には$r(x)$の係数を以下の形式で出力してください。

@{lang.end}

```
$u\ v$
$q_0\ q_1\ \ldots\ q_{u-1}$
$r_0\ r_1\ \ldots\ r_{v-1}$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}

@{example.example_03}
