## @{keyword.statement}

@{lang.en}
You are given a formal power series $f(x) = \sum_{i=0}^{N-1} a_i x^i \in \mathbb{F}\_{@{param.MOD}}[[x]]$.
Calculate the first $N$ terms of a square root of $f(x)$.
In other words, find $g(x) = \sum_{i=0}^{N-1} b_i x^i \in \mathbb{F}\_{@{param.MOD}}[[x]]$ such that

$$f(x) \equiv g(x)^2 \pmod{x^N}.$$

@{lang.ja}
形式的冪級数 $f(x) = \sum_{i=0}^{N-1} a_i x^i \in \mathbb{F}\_{@{param.MOD}}[[x]]$ が与えられます。$f(x)$ の平方根の $1$ つの先頭 $N$ 項を求めてください。つまり、

$$f(x) \equiv g(x)^2 \pmod{x^N}$$

となる $g(x) = \sum_{i=0}^{N-1} b_i x^i \in \mathbb{F}\_{@{param.MOD}}[[x]]$ を求めてください。

@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $0 \leq a_i < @{param.MOD}$

## @{keyword.input}

```
$N$
$a_0$ $a_1$ $\cdots$ $a_{N - 1}$
```

## @{keyword.output}

@{lang.en}
If there are no $g(x)$ satisfying the condition, print
@{lang.ja}
条件を満たす $g(x)$ が存在しない場合、
@{lang.end}

```
-1
```

@{lang.en}
and if such $g(x)$ exists, choose any and print
@{lang.ja}
と出力してください。

存在する場合、どれか $1$ つを選び、
@{lang.end}

```
$b_0$ $b_1$ $\cdots$ $b_{N - 1}$
```

@{lang.ja}
と出力してください。
@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
