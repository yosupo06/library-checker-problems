## @{keyword.statement}

@{lang.en}
This problem has $T$ cases.

Given $N$ 2D points $p _ i(x _ i , y _ i)$ ($0\leq i\leq N - 1$). Find a pair $(i,j)$, such that $i\neq j$ and $\mathrm{dist}(p _ i,p _ j) = \min_{i\neq j}\mathrm{dist}(p _ i,p _ j)$. 

Here, $\mathrm{dist}$ denotes the Euclidean distance between two points.

@{lang.ja}
この問題は $T$ ケースあります．

座標平面上の $N$ 個の点 $p _ i(x _ i, y _ i)$ ($0\leq i\leq N - 1$) が与えられます．組 $(i,j)$ であって，$i\neq j$ かつ $\mathrm{dist}(p _ i,p _ j) = \min_{i\neq j}\mathrm{dist}(p _ i,p _ j)$ を満たすものをひとつ出力してください．

ただし $\mathrm{dist}$ は 2 点の Euclid 距離とします．

@{lang.end}

## @{keyword.constraints}

@{lang.en}

- $1\leq T\leq 10^5$
- $2 \leq N \leq @{param.SUM_N_MAX}$
- $|x_i|, |y_i| \leq @{param.X_AND_Y_ABS_MAX}$
- $x_i, y_i$ are integers.
- The sum of $N$ over all test cases does not exceed $@{param.SUM_N_MAX}$

@{lang.ja}
- $1\leq T\leq 10^5$
- $2 \leq N \leq @{param.SUM_N_MAX}$
- $|x_i|, |y_i| \leq @{param.X_AND_Y_ABS_MAX}$
- $x_i, y_i$ は整数.
- 全てのテストケースに対する $N$ の総和は $@{param.SUM_N_MAX}$ を超えない

@{lang.end}

## @{keyword.input}

```
$T$
$N$
$x_0$ $y_0$
$x_1$ $y_1$
:
$x_{N - 1}$ $y_{N - 1}$
$N$
$x_0$ $y_0$
$x_1$ $y_1$
:
$x_{N - 1}$ $y_{N - 1}$
$\vdots$
```

## @{keyword.sample}

@{example.example_00}
