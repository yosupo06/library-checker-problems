## @{keyword.statement}

@{lang.en}
Let the prime numbers be $p_0 < p_1 < p_2 < \cdots$ (i.e. $p_0 = 2$, $p_1 = 3$, $p_2 = 5$, and so on).

You are given integers $N$, $A$ and $B$.
Find $\pi(N)$ (the number of primes no greater than $N$),
and print $p_{Ai+B}$ for nonnegative integers $i$ with $p_{Ai+B} \le N$.

@{lang.ja}
素数列を $p_0 < p_1 < p_2 < \cdots$ とします。 (すなわち、 $p_0 = 2$, $p_1 = 3$, $p_2 = 5$, など)。

整数 $N$, $A$, $B$ が与えられます。
$N$ 以下の素数の個数 $\pi(N)$ ( $\pi()$ は素数計数関数 ) と、
$p_{Ai+B} \le N$ を満たす各非負整数 $i$ に対して $p_{Ai+B}$ を出力してください。

@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \le N \le @{param.N_MAX}$
- $0 \le B < A \le N$
- $@{param.X_MIN} \le X \le @{param.X_MAX}$ where $X = \\#\\{ i \in \mathbb{Z}\_{\ge 0} \mid p_{Ai+B} \le N \\}$

## @{keyword.input}

~~~
$N$ $A$ $B$
~~~

## @{keyword.output}

~~~
$\pi(N)$ $X$
$p_{B}$ $p_{A+B}$ $\cdots$ $p_{A(X-1)+B}$
~~~

@{example.example_00}
