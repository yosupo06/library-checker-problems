## @{keyword.statement}
@{lang.en}
The Stirling numbers of the second kind $S(n, k)$ are defined as the coefficients in the identity
$$x^n = \sum_{k=0}^n S(n, k) x (x - 1) \cdots (x - (k - 1)).$$

You are given an integer $N$.
Calculate $S(N, k) \bmod @{param.MOD}$ for $0 \le k \le N$.
@{lang.ja}
第 $2$ 種スターリング数 $S(n,k)$ を次を満たす係数として定義します：
$$x^n = \sum_{k=0}^n S(n, k) x (x - 1) \cdots (x - (k - 1)).$$

整数 $N$ が与えられます。$0\leq k\leq N$ に対して $S(N, k) \bmod @{param.MOD}$ を求めてください。

@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \le N \le @{param.N_MAX}$

## @{keyword.input}

~~~
$N$
~~~

## @{keyword.output}

~~~
$S(N, 0)$ $\cdots$ $S(N, N)$
~~~

## @{keyword.sample}

@{example.example_00}
