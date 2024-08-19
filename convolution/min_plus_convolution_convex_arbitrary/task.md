## @{keyword.statement}

@{lang.en}
Given integer sequences $a_0, a_1, ..., a_{N - 1}$ and $b_0, b_1, ..., b_{M - 1}$. Here, $a$ is convex. Calculate an integer sequence $c_0, c_1, ..., c_{(N - 1) + (M - 1)}$ defined as follows:

$$c_k = \min_{i+j=k} (a_i+b_j)$$

@{lang.ja}
整数列 $a_0, a_1, ..., a_{N - 1}$、$b_0, b_1, ..., b_{M - 1}$ が与えられます。ここで $a$ は凸です。次のように定義される整数列 $c_0, c_1, ..., c_{(N - 1) + (M - 1)}$ を求めてください。

$$c_k = \min_{i+j=k} (a_i+b_j)$$

@{lang.end}

## @{keyword.constraints}

@{lang.ja}
- $1 \leq N, M \leq @{param.N_MAX}$
- $0 \leq a_i, b_i \leq @{param.A_MAX}$
- $a$ は凸である。つまり $0\leq i < N - 2$ に対して $a_{i+1}-a_i\leq a_{i+2}-a_{i+1}$ が成り立つ。
@{lang.en}
- $1 \leq N, M \leq @{param.N_MAX}$
- $0 \leq a_i, b_i \leq @{param.A_MAX}$
- $a$ is convex. i.e. $a_{i+1}-a_i\leq a_{i+2}-a_{i+1}$ holds for $0\leq i < N - 2$. 
@{lang.end}
## @{keyword.input}

```
$N$ $M$
$a_0$ $a_1$ ... $a_{N-1}$
$b_0$ $b_1$ ... $b_{M-1}$
```

## @{keyword.output}

```
$c_0$ $c_1$ ... $c_{(N - 1) + (M - 1)}$
```

## @{keyword.sample}

@{example.example_00}
