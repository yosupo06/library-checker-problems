## @{keyword.statement}

@{lang.ja}
$T$ 個のテストケースが与えられる。

正整数 $N$ に対し、 $Q_N=\lbrace {\lfloor {N \over x} \rfloor \colon x \in \mathbb{Z}, 1 \leq x \leq N} \rbrace$ 、$Q_N$ の要素を昇順に並べた列を $(a_0,a_1,\ldots,a_{k-1})$ と定義する。

数列 $f,g \colon \mathbb{N} \to \mathbb{Z}$ について、各 $x \in Q_N$ までの累積和
$$
f_x=\sum_{n=1}^x f(n) \\
g_x=\sum_{n=1}^x g(n)
$$

が与えられる。

Dirichlet積 $h=f*g$ に対する各 $x \in Q_N$ までの累積和
$$
h_x=\sum_{n=1}^x \sum_{ij=n} f(i)g(j) \bmod @{param.MOD}
$$

の値を全て求めよ。

@{lang.en}
There are $T$ testcases.

Given a positive integer $N$, define $Q_N=\lbrace {\lfloor {N \over x} \rfloor \colon x \in \mathbb{Z}, 1 \leq x \leq N} \rbrace$.

Let the elements of $ Q_N $ arranged in ascending order be denoted by the sequence $(a_0,a_1,\ldots,a_{k-1})$ .

For the sequences $ f, g \colon \mathbb{N} \to \mathbb{Z} $, define the cumulative sums up to each $ x \in Q_N $ as
$$
f_x = \sum_{n=1}^x f(n), \\
g_x = \sum_{n=1}^x g(n).
$$

Given these, compute the cumulative sums up to each $ x \in Q_N $ for the Dirichlet convolution $ h=f * g $, defined by
$$
h_x = \sum_{n=1}^x \sum_{ij = n} f(i)g(j) \bmod @{param.MOD}.
$$
@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $1 \leq f_x,g_x < @{param.MOD}$
- If $T>1$, then $T=10000$ and there is exactly one test case for each $N=1,2,\ldots,10000$.

## @{keyword.input}

```
$T$
$case_1$
$\vdots$
$case_T$
```

@{lang.ja}
各テストケースは以下の形式で与えられる。
@{lang.en}
Each test case is given in the following format.
@{lang.end}

```
$N$
$f_{a_0}$ $f_{a_1}$ $\ldots$ $f_{a_{k-1}}$
$g_{a_0}$ $g_{a_1}$ $\ldots$ $g_{a_{k-1}}$
```


## @{keyword.output}

```
$h_{a_0}$ $h_{a_1}$ $\ldots$ $h_{a_{k-1}}$
```


## @{keyword.sample}

@{example.example_00}