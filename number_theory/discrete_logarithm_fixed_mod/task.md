## @{keyword.statement}

@{lang.en}

Given a prime $P$ and one of its primitive roots $g$, and $n$ positive integers $\lbrace a_i\rbrace_{i=0}^{n-1}$, for each $a_i$ output the minimum non-negative integer $b_i$ that satisfies $g^{b_i}\equiv a_i\pmod P$.

@{lang.ja}

素数 $P$ とその原始根の一つ $g$、および $n$ 個の正整数 $\lbrace a_i\rbrace_{i=0}^{n-1}$ が与えられる。各 $a_i$ に対して、$g^{b_i}\equiv a_i\pmod P$ を満たす最小の非負整数 $b_i$ を出力せよ。

@{lang.end}

## @{keyword.constraints}

@{lang.en}

- $2\le P\le10^9$
- $P$ is a prime
- $1\le n\le10^6$
- $1\le a_i<P$

@{lang.ja}

- $2\le P\le10^9$
- $P$ は素数
- $1\le n\le10^6$
- $1\le a_i<P$

@{lang.end}

## @{keyword.input}

```
$P$ $g$ $n$
$a_0$
$a_1$
:
$a_{n-1}$
```

## @{keyword.output}

```
$b_0$
$b_1$
:
$b_{n-1}$
```

## @{keyword.sample}

@{example.example_00}
