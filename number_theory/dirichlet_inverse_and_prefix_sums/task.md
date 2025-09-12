## @{keyword.statement}

@{lang.ja}
$T$ 個のテストケースが与えられる。

正整数 $N$ に対し、 $Q_N=\lbrace {\lfloor {N \over x} \rfloor \colon x \in \mathbb{Z}, 1 \leq x \leq N} \rbrace$ 、$Q_N$ の要素を昇順に並べた列を $(a_0,a_1,\ldots,a_{k-1})$ と定義する。

数列 $f \colon \mathbb{N} \to \mathbb{F} _ {@{param.MOD}}$ について、各 $x \in Q_N$ までの累積和

$$f_x=\sum_{n=1}^x f(n)$$

が与えられる。ここで $f_1\neq 0$ であることが保証される。

Dirichlet積に関する $f$ の逆元 $g$ とする。つまり任意の正整数 $n$ について $\sum_{ij=n}f(i)g(j)=\delta_{1,n}$ が成り立つとする。$g$ の各 $x \in Q_N$ までの累積和

$$
g_x=\sum_{n=1}^x g(n) \in \mathbb{F}_{@{param.MOD}}
$$

の値を全て求めよ。

@{lang.en}
There are $T$ testcases.

Given a positive integer $N$, define $Q_N=\lbrace {\lfloor {N \over x} \rfloor \colon x \in \mathbb{Z}, 1 \leq x \leq N} \rbrace$.

Let the elements of $ Q_N $ arranged in ascending order be denoted by the sequence $(a_0,a_1,\ldots,a_{k-1})$ .

For the sequence $f \colon \mathbb{N} \to \mathbb{F} _ {@{param.MOD}}$, define the cumulative sums up to each $ x \in Q_N $ as

$$
f_x = \sum_{n=1}^x f(n)
$$

Given these, let $g$ be the inverse of $f$ with respect to the Dirichlet Convolution. That is, $\sum_{ij=n}f(i)g(j)=\delta_{1,n}$ holds. Compute the cumulative sums
$$
g_x=\sum_{n=1}^x g(n) \in \mathbb{F}_{@{param.MOD}}
$$
for each $ x \in Q_N $. 
@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $0 \leq f_x < @{param.MOD}$
- $f_1\neq 0$
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
```


## @{keyword.output}

```
$g_{a_0}$ $g_{a_1}$ $\ldots$ $g_{a_{k-1}}$
```


## @{keyword.sample}

@{example.example_00}

@{example.example_01}
