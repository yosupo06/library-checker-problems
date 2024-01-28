## @{keyword.statement}

@{lang.en}

Given a prime $P$ and integer sequences $a_0, a_1, ..., a_{P - 1}$ and $b_0, b_1, ..., b_{P - 1}$. Calculate an integer sequence $c_0, c_1, ..., c_{P - 1}$ as follows:

$$c_k = \sum_{i \times j \equiv k \pmod{P}} a_i b_j \bmod @{param.MOD}$$

@{lang.ja}

素数 $P$ と整数列 $a_0, a_1, ..., a_{P - 1}$、$b_0, b_1, ..., b_{P - 1}$ が与えられます。整数列 $c_0, c_1, ..., c_{P - 1}$ を求めてください。

ただし、

$$c_k = \sum_{i \times j \equiv k \pmod{P}} a_i b_j \bmod @{param.MOD}$$

です

@{lang.end}

## @{keyword.constraints}

@{lang.en}

- $@{param.P_MIN} \leq P \leq @{param.P_MAX}$
- $P$ is a prime
- $0 \leq a_i, b_i < @{param.MOD}$

@{lang.ja}

- $@{param.P_MIN} \leq P \leq @{param.P_MAX}$
- $P$ は素数
- $0 \leq a_i, b_i < @{param.MOD}$

@{lang.end}

## @{keyword.input}

```
$P$
$a_0$ $a_1$ ... $a_{P - 1}$
$b_0$ $b_1$ ... $b_{P - 1}$
```

## @{keyword.output}

```
$c_0$ $c_1$ ... $c_{P - 1}$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
