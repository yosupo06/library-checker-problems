## @{keyword.statement}
母関数 $f(x) = \sum_{i = 0}^{N - 1} a_i x^i$ が与えられます。$\sqrt{f(x)}$ の先頭 $N$ 項を求めてください。つまり

$$f(x) = g(x) \times g(x) \bmod (x^N)$$

となる $g(x)$ を出力してください。ただし係数は全て $\mathbb{Z}_{998244353}$ とします


## @{keyword.constraints}

- $1 \leq N \leq 500,000$
- $0 \leq a_i < 998244353$

## @{keyword.input}

```
$N$
$a_0$ $a_1$ ... $a_{N - 1}$
```

## @{keyword.output}

条件を満たす $g(x)$ が存在しない場合、

```
-1
```

と出力してください。

存在する場合、

```
$b_0$ $b_1$ ... $b_{N - 1}$
```

と出力してください。ただし $g(x) = \sum_{i = 0}^{N - 1} b_i x^i$ とします。

なお、条件を満たすものが複数ある場合、どれか 1 つを選び出力してください。


## @{keyword.sample}

@{example.example_00}

@{example.example_01}
