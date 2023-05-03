## @{keyword.statement}

@{lang.en}

Given an $N$-variable power series $\displaystyle s(x _ 0, x _ 1, \dots, x _ {N - 1}) = \sum _ {i = 0} ^ {2 ^ N - 1} b _ i \prod _ {k = 0} ^ {N - 1} x _ k ^ {i _ k} \in \mathbb{F} _ {@{param.MOD}} [[ x _ 0, x _ 1, \dots, x _ {N - 1} ]]$.
Here, $i_k$ represents the number in the $2 ^ k$'s place when $i$ is expressed in binary.
Print $c _ 0, c _ 1, \dots, c _ {2 ^ N - 1} ~ (0 \leq c _ i \lt @{param.MOD})$ satisfying

$$\exp(s(x _ 0, x _ 1, \dots, x _ {N - 1})) := \sum _ {m = 0} ^ \infty \frac{s(x _ 0, x _ 1, \dots, x _ {N - 1})^m}{m!} \equiv \sum _ {i = 0} ^ {2 ^ N - 1} c _ i \prod _ {k = 0} ^ {N - 1} x _ k ^ {i _ k} \pmod{(x _ 0 ^ 2, x _ 1 ^ 2, \dots, x _ {N - 1} ^ 2)}$$

.

@{lang.ja}

$N$ 変数冪級数 $\displaystyle s(x _ 0, x _ 1, \dots, x _ {N - 1}) = \sum _ {i = 0} ^ {2 ^ N - 1} b _ i \prod _ {k = 0} ^ {N - 1} x _ k ^ {i _ k} \in \mathbb{F} _ {@{param.MOD}} [[ x _ 0, x _ 1, \dots, x _ {N - 1} ]]$ が与えられます。
ただし、$i _ k$ は $i$ を $2$ 進法で表した時の $2 ^ k$ の位の値を表します。

$$\exp(s(x _ 0, x _ 1, \dots, x _ {N - 1})) := \sum _ {m = 0} ^ \infty \frac{s(x _ 0, x _ 1, \dots, x _ {N - 1})^m}{m!} \equiv \sum _ {i = 0} ^ {2 ^ N - 1} c _ i \prod _ {k = 0} ^ {N - 1} x _ k ^ {i _ k} \pmod{(x _ 0 ^ 2, x _ 1 ^ 2, \dots, x _ {N - 1} ^ 2)}$$

を満たす $c _ 0, c _ 1, \dots, c _ {2 ^ N - 1} ~ (0 \leq c _ i \lt @{param.MOD})$ を出力してください。

@{lang.end}

## @{keyword.constraints}

- $0 \leq N \leq @{param.N_MAX}$
- $0 \leq b_i \lt @{param.MOD}$
- $b_0 = 0$

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
