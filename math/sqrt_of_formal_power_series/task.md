## @{keyword.statement}

@{lang.en}
Given formal power series $f(x) = \sum_{i = 0}^{N - 1} a_i x^i$. Calculate first $N$ elements of $\sqrt{f(x)}$. In other words, print $g(x)$ s.t.

$$f(x) = g(x) \times g(x) \bmod (x^N)$$

is satisfied. We consider everything in $\mathbb{Z}_{@{param.MOD}}$.

@{lang.ja}
母関数 $f(x) = \sum_{i = 0}^{N - 1} a_i x^i$ が与えられます。$\sqrt{f(x)}$ の先頭 $N$ 項を求めてください。つまり

$$f(x) = g(x) \times g(x) \bmod (x^N)$$

となる $g(x)$ を出力してください。ただし係数は全て $\mathbb{Z}_{@{param.MOD}}$ とします
@{lang.end}


## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $0 \leq a_i < @{param.MOD}$

## @{keyword.input}

```
$N$
$a_0$ $a_1$ ... $a_{N - 1}$
```

## @{keyword.output}

@{lang.en}
If there are no $g(x)$, print
@{lang.ja}
条件を満たす $g(x)$ が存在しない場合、
@{lang.end}

```
-1
```

@{lang.en}

and if exists, print

@{lang.ja}
と出力してください。

存在する場合、
@{lang.end}

```
$b_0$ $b_1$ ... $b_{N - 1}$
```

@{lang.en}
We denote $g(x) = \sum_{i = 0}^{N - 1} b_i x^i$.

If there are multiple solutions, print any of them.
@{lang.ja}
と出力してください。ただし $g(x) = \sum_{i = 0}^{N - 1} b_i x^i$ とします。

なお、条件を満たすものが複数ある場合、どれか 1 つを選び出力してください。
@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
