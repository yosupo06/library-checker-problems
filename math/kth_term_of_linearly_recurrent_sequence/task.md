## @{keyword.statement}

@{lang.en}

An integer sequence $(a_i)$ satisfies the following linear recurrence:

$$a_{i} \equiv \sum_{j=1}^{N} c_j a_{i - j}\pmod{998244353},\  i\geq N$$

Given $a_0,$ $a_1,$ $\ldots$ $,a_{N-1}$. Print $a_K \pmod{998244353}$.
@{lang.ja}
$$a_{i} \equiv \sum_{j=1}^{N} c_j a_{i - j}\pmod{998244353},\  i\geq N$$

を満たす数列$a$の初め$N$項が与えられる。$a_K \pmod{998244353}$を求めよ。

@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq 10 ^ 5$
- $0 \leq K \leq 10^{18}$
- $0 \leq a_i \leq 998244352\ (0 \leq i \leq N-1)$
- $0 \leq c_i \leq 998244352\ (1 \leq i \leq N)$

## @{keyword.input}

```
$N$ $K$
$a_0$ $a_1$ $\ldots$ $a_{N-1}$
$c_1$ $c_2$ $\ldots$ $c_N$
```

## @{keyword.output}

```
$a_N$
```

## @{keyword.sample}

@{example.example_00}
