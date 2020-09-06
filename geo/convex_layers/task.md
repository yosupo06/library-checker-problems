## @{keyword.statement}

@{lang.en}
You are given $N$ distinct 2D-points $(x_0, y_0), (x_1, y_1), \dots, (x_{N - 1}, y_{N - 1})$. While there are points remaining, remove all points on the boundary of the convex hull of the remaining points.
For each point, determine which iteration it was removed in.

Note:

- Points may be collinear

@{lang.ja}

二次元平面上の異なる $N$ 個の点 $(x_0, y_0), (x_1, y_1), \dots, (x_{N - 1}, y_{N - 1})$ が与えられます。凸包(及びその辺上)に含まれる点をすべて削除する、という操作を全ての点が消えるまで繰り返します。
各点について、何度目の操作で点が削除されるかを答えてください。

注意:

- 同一直線上に複数の点が存在している可能性もあります。

@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $0 \leq x_i, y_i \leq @{param.X_AND_Y_MAX}$
- $x_i, y_i$ are integers.

## @{keyword.input}

```
$N$
$x_0$ $y_0$
$x_1$ $y_1$
:
$x_{N - 1}$ $y_{N - 1}$
```

## @{keyword.output}

For each point, output which iteration it was removed in.

```
$l_0$
$l_1$
:
$l_{N - 1}$
```

$l_i$ represents the iteration the $i$th point was removed.

## @{keyword.sample}

@{example.example_00}
@{example.example_01}
@{example.example_02}
@{example.example_03}
@{example.example_04}
@{example.example_05}
