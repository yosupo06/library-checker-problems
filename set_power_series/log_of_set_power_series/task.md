## @{keyword.statement}

@{lang.en}

Given an $N$-variable polynomial $\displaystyle s(x _ 0, x _ 1, \dots, x _ {N - 1}) = \sum _ {i = 0} ^ {2 ^ N - 1} b _ i \prod _ {k = 0} ^ {N - 1} x _ k ^ {i _ k} \in \mathbb{F} _ {@{param.MOD}} \lbrack x _ 0, x _ 1, \dots, x _ {N - 1} \rbrack$.
Here, $i_k$ represents the number in the $2 ^ k$'s place when $i$ is expressed in binary.
Print $c _ 0, c _ 1, \dots, c _ {2 ^ N - 1} ~ (0 \leq c _ i \lt @{param.MOD})$ satisfying

$$\log(s(x _ 0, x _ 1, \dots, x _ {N - 1})) \equiv \sum _ {i = 0} ^ {2 ^ N - 1} c _ i \prod _ {k = 0} ^ {N - 1} x _ k ^ {i _ k} \pmod{(x _ 0 ^ 2, x _ 1 ^ 2, \dots, x _ {N - 1} ^ 2)}.$$

In other words, print $c _ 0, c _ 1, \dots, c _ {2 ^ N - 1} ~ (0 \leq c _ i \lt @{param.MOD})$ for $\displaystyle t(x _ 0, x _ 1, \dots, x _ {N - 1}) = \sum _ {i = 0} ^ {2 ^ N - 1} c _ i \prod _ {k = 0} ^ {N - 1} x _ k ^ {i _ k} \in \mathbb{F} _ {@{param.MOD}} \lbrack x _ 0, x _ 1, \dots, x _ {N - 1} \rbrack$ such that $c _ 0 = 0$ and

$$s(x _ 0, x _ 1, \dots, x _ {N - 1}) \equiv \sum _ {m = 0} ^ N \frac{t(x _ 0, x _ 1, \dots, x _ {N - 1})^m}{m!} \pmod{(x _ 0 ^ 2, x _ 1 ^ 2, \dots, x _ {N - 1} ^ 2)}.$$

@{lang.ja}

$N$ 変数多項式 $\displaystyle s(x _ 0, x _ 1, \dots, x _ {N - 1}) = \sum _ {i = 0} ^ {2 ^ N - 1} b _ i \prod _ {k = 0} ^ {N - 1} x _ k ^ {i _ k} \in \mathbb{F} _ {@{param.MOD}} \lbrack x _ 0, x _ 1, \dots, x _ {N - 1} \rbrack$ が与えられます。
ただし、$i _ k$ は $i$ を $2$ 進法で表した時の $2 ^ k$ の位の値を表します。

$$\log(s(x _ 0, x _ 1, \dots, x _ {N - 1})) \equiv \sum _ {i = 0} ^ {2 ^ N - 1} c _ i \prod _ {k = 0} ^ {N - 1} x _ k ^ {i _ k} \pmod{(x _ 0 ^ 2, x _ 1 ^ 2, \dots, x _ {N - 1} ^ 2)}$$

を満たす $c _ 0, c _ 1, \dots, c _ {2 ^ N - 1} ~ (0 \leq c _ i \lt @{param.MOD})$ を出力してください。つまり、$c _ 0 = 0$ かつ

$$s(x _ 0, x _ 1, \dots, x _ {N - 1}) \equiv \sum _ {m = 0} ^ N \frac{t(x _ 0, x _ 1, \dots, x _ {N - 1})^m}{m!} \pmod{(x _ 0 ^ 2, x _ 1 ^ 2, \dots, x _ {N - 1} ^ 2)}$$

を満たす $\displaystyle t(x _ 0, x _ 1, \dots, x _ {N - 1}) = \sum _ {i = 0} ^ {2 ^ N - 1} c _ i \prod _ {k = 0} ^ {N - 1} x _ k ^ {i _ k} \in \mathbb{F} _ {@{param.MOD}} \lbrack x _ 0, x _ 1, \dots, x _ {N - 1} \rbrack$ についての $c _ 0, c _ 1, \dots, c _ {2 ^ N - 1} ~ (0 \leq c _ i \lt @{param.MOD})$ を出力してください。

@{lang.end}

## @{keyword.constraints}

- $0 \leq N \leq @{param.N_MAX}$
- $0 \leq b_i \lt @{param.MOD}$
- $b_0 = 1$

## @{keyword.input}

```
$N$
$b_0$ $b_1$ $\cdots$ $b_{2^N-1}$
```

## @{keyword.output}

```
$c_0$ $c_1$ $\cdots$ $c_{2^N-1}$
```

## @{keyword.sample}

@{example.example_00}
