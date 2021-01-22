## @{keyword.statement}

@{lang.en}

An integer sequence $(a_i)$ satisfies the following linear recurrence:

$$a_{i} \equiv \sum_{j=1}^{d} c_j a_{i - j} \pmod{@{param.MOD}},\  i\geq d$$

Given $a_0,a_1,\ldots,a_{d-1}$, print $a_k \bmod @{param.MOD}$.
@{lang.ja}
$$a_{i} \equiv \sum_{j=1}^{d} c_j a_{i - j} \pmod{@{param.MOD}},\  i\geq d$$

を満たす数列$a$の初めの$d$項が与えられる。$a_k \bmod @{param.MOD}$を求めよ。

@{lang.end}

## @{keyword.constraints}

- $1 \leq d \leq @{param.D_MAX}$
- $0 \leq k \leq @{param.K_MAX}$
- $0 \leq a_i \lt @{param.MOD}\ (0 \leq i \leq d-1)$
- $0 \leq c_i \lt @{param.MOD}\ (1 \leq i \leq d)$

## @{keyword.input}

```
$d$ $k$
$a_0$ $a_1$ $\ldots$ $a_{d-1}$
$c_1$ $c_2$ $\ldots$ $c_d$
```

## @{keyword.output}

```
$a_k$
```

## @{keyword.sample}

@{example.example_00}
