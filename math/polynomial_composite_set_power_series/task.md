## @{keyword.statement}

@{lang.en}

Given a polynomial $\displaystyle f(x) = \sum _ {i = 0} ^ {M - 1} a _ i x ^ i \in \mathbb{F} _ {@{param.MOD}} \lbrack x \rbrack$ and an $N$-variable polynomial $\displaystyle s(x _ 0, x _ 1, \dots, x _ {N - 1}) = \sum _ {i = 0} ^ {2 ^ N - 1} b _ i \prod _ {k = 0} ^ {N - 1} x _ k ^ {i _ k} \in \mathbb{F} _ {@{param.MOD}} \lbrack x _ 0, x _ 1, \dots, x _ {N - 1} \rbrack$.
Here, $i_k$ represents the number in the $2 ^ k$'s place when $i$ is expressed in binary.
Print $c _ 0, c _ 1, \dots, c _ {2 ^ N - 1} ~ (0 \leq c _ i \lt @{param.MOD})$ satisfying

$$f(s(x _ 0, x _ 1, \dots, x _ {N - 1})) \equiv \sum _ {i = 0} ^ {2 ^ N - 1} c _ i \prod _ {k = 0} ^ {N - 1} x _ k ^ {i _ k} \pmod{(x _ 0 ^ 2, x _ 1 ^ 2, \dots, x _ {N - 1} ^ 2)}$$

.

@{lang.ja}

多項式 $\displaystyle f(x) = \sum _ {i = 0} ^ {M - 1} a _ i x ^ i \in \mathbb{F} _ {@{param.MOD}} \lbrack x \rbrack$ と $N$ 変数多項式 $\displaystyle s(x _ 0, x _ 1, \dots, x _ {N - 1}) = \sum _ {i = 0} ^ {2 ^ N - 1} b _ i \prod _ {k = 0} ^ {N - 1} x _ k ^ {i _ k} \in \mathbb{F} _ {@{param.MOD}} \lbrack x _ 0, x _ 1, \dots, x _ {N - 1} \rbrack$ が与えられます。
ただし、$i _ k$ は $i$ を $2$ 進法で表した時の $2 ^ k$ の位の値を表します。

$$f(s(x _ 0, x _ 1, \dots, x _ {N - 1})) \equiv \sum _ {i = 0} ^ {2 ^ N - 1} c _ i \prod _ {k = 0} ^ {N - 1} x _ k ^ {i _ k}  \pmod{(x _ 0 ^ 2, x _ 1 ^ 2, \dots, x _ {N - 1} ^ 2)}$$

を満たす $c _ 0, c _ 1, \dots, c _ {2 ^ N - 1} ~ (0 \leq c _ i \lt @{param.MOD})$ を出力してください。

@{lang.end}

## @{keyword.constraints}

- $0 \leq M \leq @{param.M_MAX}$
- $0 \leq N \leq @{param.N_MAX}$
- $0 \leq a_i, b_i \lt @{param.MOD}$

## @{keyword.input}

```
$M$ $N$
$a_0$ $a_1$ $\cdots$ $a_{M-1}$
$b_0$ $b_1$ $\cdots$ $b_{2^N-1}$
```

## @{keyword.output}

```
$c_0$ $c_1$ $\cdots$ $c_{2^N-1}$
```

## @{keyword.sample}

@{example.example_00}
