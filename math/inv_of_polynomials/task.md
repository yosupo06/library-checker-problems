## @{keyword.statement}

@{lang.en}

We consider polynomials over $\mathbb{F}_{@{param.MOD}}$ in this problem.

Given polynomials $f(x)=\sum_{i=0}^{N-1} a_ix^i$ and $g(x)=\sum_{i=0}^{M-1}b_ix^i$.
Calculate a polynomial $h(x)=\sum_{i=0}^{T-1}c_ix^i$ s.t.

- $\deg(h) < \deg(g)$ and
- $f(x)h(x)\equiv1\pmod {g(x)}$

is satisfied.

We note that $\deg(0)=-\infty$ in this problem.
We can prove $h(x)$ is unique if it exists.
Print $-1$ if it doesn't exist.

@{lang.ja}
この問題では $\mathbb{F}_{@{param.MOD}}$ 係数の多項式を考えます。

多項式 $f(x)=\sum_{i=0}^{N-1} a_ix^i ,g(x)=\sum_{i=0}^{M-1}b_ix^i$ が与えられます。
$\deg(h) < \deg(g)$ かつ 
$$f(x)h(x)\equiv1\pmod {g(x)}$$
を満たす多項式 $h(x)=\sum_{i=0}^{T-1}c_ix^i$ を求めてください。
ただし $\deg(0)=-\infty$とします。
このような $h(x)$ は存在するならば一意に定まることが示せます。
$h(x)$ が存在しないときは$-1$を出力してください。
@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $1 \leq M \leq @{param.N_MAX}$
- $0 \leq a_i < @{param.MOD}$
- $0 \leq b_i < @{param.MOD}$
- $a_{N-1} \neq 0$
- $b_{M-1} \neq 0$

## @{keyword.input}

```
$N$ $M$
$a_0$ $a_1$ $\ldots$ $a_{N - 1}$
$b_0$ $b_1$ $\ldots$ $b_{M - 1}$
```

## @{keyword.output}

@{lang.en}

If $h(x)$ doesn't exist, print $-1$.

If $h(x)$ exists, print $T$ ($c_{T-1} \neq 0$) in first line, or $T = 0$ when $h(x)=0$.
Print $c_0, c_1, \ldots, c_{T-1}$ in next line.

@{lang.ja}

$h(x)$ が存在しないときは一行に $-1$ を出力してください。
$h(x)$ が存在するときは一行目に $T$ ($c_{T-1} \neq 0$) を出力してください。ただし $h(x)=0$ のときは $T=0$ としてください。
$h(x)$ が存在するときは二行目に $c_0,c_1,\ldots,c_{T-1}$ を空白区切りで出力してください。

@{lang.end}

```
$T$
$c_0$ $c_1$ $\ldots$ $c_{T - 1}$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}
