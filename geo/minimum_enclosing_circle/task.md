## @{keyword.statement}

@{lang.en}
Given $N$ 2D points $p_i(x_i , y_i)$ ($0\leq i\leq N - 1$).

Let $C$ be the minimum enclosing circle of the $N$ points.

For each $i = 0, 1, \dots, N-1$, determine whether $p_i$ lies on the circumference (boundary) of $C$.

@{lang.ja}
座標平面上の $N$ 個の点 $p_i(x_i, y_i)$ ($0\leq i\leq N - 1$) が与えられます．

$N$ 個の点の最小包含円を $C$ とします．

$i = 0, 1, \dots, N-1$ について，$p_i$ が $C$ の円周上にあるか判定してください．

@{lang.end}

## @{keyword.constraints}

@{lang.en}
- $2 \leq N \leq @{param.N_MAX}$
- $|x_i|, |y_i| \leq @{param.X_AND_Y_ABS_MAX}$
- $N$ points are all different.
- The values in input are all integers．

@{lang.ja}
- $2 \leq N \leq @{param.N_MAX}$
- $|x_i|, |y_i| \leq @{param.X_AND_Y_ABS_MAX}$
- $N$ 点は全て異なる．
- 入力は全て整数．

@{lang.end}

## @{keyword.input}

~~~
$N$
$x_0$ $y_0$
$x_1$ $y_1$
:
$x_{N - 1}$ $y_{N - 1}$
~~~

## @{keyword.output}

~~~
$T$
~~~

@{lang.en}
Output a 0/1 string $T$ of length $N$.

For each $i = 0, 1, \dots, N-1$, set $T[i] = 1$ if $p_i$ lies on the the circumference of $C$; otherwise set $T[i] = 0$.

@{lang.ja}
長さ $N$ の 0/1 文字列 $T$ を出力せよ．

$i = 0, 1, \dots, N-1$ について，$p_i$ が $C$ の円周上にあるとき $T[i] = 1$, そうでないとき $T[i] = 0$ とする．
@{lang.end}

## @{keyword.sample}

@{example.example_00}
