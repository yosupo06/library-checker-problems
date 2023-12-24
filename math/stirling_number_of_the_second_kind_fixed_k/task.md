## @{keyword.statement}
@{lang.en}
The Stirling numbers of the second kind $S(n, k)$ are defined as the coefficients in the identity
$$x^n = \sum_{k=0}^n S(n, k) x (x - 1) \cdots (x - (k - 1)).$$

You are given two integers $N,K$.
Calculate $S(n, K) \bmod @{param.MOD}$ for $K \le n \le N$.

@{lang.ja}
第 $2$ 種スターリング数 $S(n,k)$ を次を満たす係数として定義します：
$$x^n = \sum_{k=0}^n S(n, k) x (x - 1) \cdots (x - (k - 1)).$$

整数 $N,K$ が与えられます。$K\leq n\leq N$ に対して $S(n, K) \bmod @{param.MOD}$ を求めてください。

@{lang.end}

## @{keyword.constraints}

- $@{param.K_MIN} \le K \le N \le @{param.N_MAX}$

## @{keyword.input}

~~~
$N$ $K$
~~~

## @{keyword.output}

~~~
$S(K, K)$ $\cdots$ $S(N, K)$
~~~

## @{keyword.sample}

@{example.example_00}
