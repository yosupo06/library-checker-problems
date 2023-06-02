## @{keyword.statement}
@{lang.en}
The signed Stirling numbers of the first kind $s(n, k)$ are defined as the coefficients in the identity
$$x (x - 1) \cdots (x - (n - 1)) = \sum_{k=0}^n s(n, k) x^k.$$

You are given two integers $N,K$.
Calculate $s(n, K) \bmod @{param.MOD}$ for $K \le n \le N$.

@{lang.ja}
符号付き第 $1$ 種スターリング数 $s(n,k)$ を次を満たす係数として定義します：
$$x (x - 1) \cdots (x - (n - 1)) = \sum_{k=0}^n s(n, k) x^k.$$

整数 $N,K$ が与えられます。$K\leq n\leq N$ に対して $s(n, K) \bmod @{param.MOD}$ を求めてください。

@{lang.end}

## @{keyword.constraints}

- $@{param.K_MIN} \le K \le N \le @{param.N_MAX}$

## @{keyword.input}

~~~
$N$ $K$
~~~

## @{keyword.output}

~~~
$s(K, K)$ $\cdots$ $s(N, K)$
~~~

## @{keyword.sample}

@{example.example_00}
