## @{keyword.statement}

@{lang.en}
Given a size $N$ 2D-point sequence $(x_0, y_0), (x_1, y_1), \dots, (x_{N - 1}, y_{N - 1})$.
Sort this by $\mathrm{atan2}(x, y)$. In other words, sort points in counter-clock-wise order that starts with a half line $x \le 0, y = 0$.

Note:

- $\mathrm{atan2}(x < 0, y = 0) = \pi$.
- $\mathrm{atan2}(0, 0) = 0$.
- We don't specify the order of same argument points.
- The precision of the 64bit floating-point type(C++: double) may not be enough. Please use an integer-type or the 80bit floating-point type(C++: long double).
@{lang.ja}
長さ $N$ の点列 $(x_0, y_0), (x_1, y_1), \dots, (x_{N - 1}, y_{N - 1})$ が与えられます。
これを $\mathrm{atan2}(x, y)$ でsortしてください。つまり $x \le 0, y = 0$ の半直線へと、反時計回りの順で点をsortしてください。

- $\mathrm{atan2}(x < 0, y = 0) = \pi$ とする
- $\mathrm{atan2}(0, 0) = 0$ とする
- 同じ角度の点同士の順番は任意
- 64bit浮動小数(double)を使うと誤差によりWAになるかもしれません、整数か80bit浮動小数(long double)を使ってください
@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $|x_i|, |y_i| \leq @{param.X_AND_Y_ABS_MAX}$
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

```
$x_0$ $y_0$
$x_1$ $y_1$
:
$x_{N - 1}$ $y_{N - 1}$
```

## @{keyword.sample}

@{example.example_00}
