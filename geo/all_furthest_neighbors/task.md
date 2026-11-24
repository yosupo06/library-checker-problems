## @{keyword.statement}

@{lang.en}
This problem has $T$ cases.

You are given the vertices $p_i(x_i, y_i)$ ($0 \leq i < N$) of a strictly convex polygon in counterclockwise order.

For every $i$, find an index $f_i$ ($0 \leq f_i < N$) such that

$$
\operatorname{dist}(p_i, p_{f_i}) = \max_{0 \leq j < N}\operatorname{dist}(p_i, p_j).
$$

Here, $\operatorname{dist}$ denotes the Euclidean distance. If there are multiple possible $f_i$, you may output any of them.

@{lang.ja}
この問題は $T$ ケースあります．

狭義凸多角形の頂点 $p_i(x_i, y_i)$ ($0 \leq i < N$) が反時計回りに与えられます．

各 $i$ について，

$$
\operatorname{dist}(p_i, p_{f_i}) = \max_{0 \leq j < N}\operatorname{dist}(p_i, p_j)
$$

を満たす添字 $f_i$ ($0 \leq f_i < N$)  を求めてください．

ただし，$\operatorname{dist}$ は $2$ 点間の Euclid 距離を表します．条件を満たす $f_i$ が複数存在する場合，そのうちどれを出力しても構いません．

@{lang.end}

## @{keyword.constraints}

@{lang.en}

- $1 \leq T \leq @{param.T_MAX}$
- $3 \leq N \leq @{param.SUM_N_MAX}$
- $|x_i|, |y_i| \leq @{param.X_AND_Y_ABS_MAX}$
- All input values are integers.
- $p_0, p_1, \dots, p_{N-1}$ are the distinct vertices of a strictly convex polygon in counterclockwise order.
- The sum of $N$ over all test cases does not exceed $@{param.SUM_N_MAX}$.

@{lang.ja}

- $1 \leq T \leq @{param.T_MAX}$
- $3 \leq N \leq @{param.SUM_N_MAX}$
- $|x_i|, |y_i| \leq @{param.X_AND_Y_ABS_MAX}$
- 入力される値はすべて整数
- $p_0, p_1, \dots, p_{N-1}$ は相異なり，狭義凸多角形の頂点を反時計回りに並べたものである
- 全テストケースに対する $N$ の総和は $@{param.SUM_N_MAX}$ 以下

@{lang.end}

## @{keyword.input}

```
$T$
$N$
$x_0$ $y_0$
$x_1$ $y_1$
$\vdots$
$x_{N-1}$ $y_{N-1}$
$\vdots$
```

## @{keyword.output}

@{lang.en}
For each test case, output the answer in the following format.
@{lang.ja}
各テストケースについて，答えを以下の形式で出力してください．
@{lang.end}

```
$f_0$ $f_1$ $\ldots$ $f_{N-1}$
```

## @{keyword.sample}

@{example.example_00}
