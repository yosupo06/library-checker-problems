Problem Statement (Japanese) / 問題文 (日本語)
---------

長さ $N$ の点列 $(x_0, y_0), (x_1, y_1), \dots, (x_{N - 1}, y_{N - 1})$ が与えられます。
これを $\mathrm{atan2}(x, y)$ でsortしてください。つまり $x \le 0, y = 0$ の半直線へと、反時計回りの順で点をsortしてください。

- $\mathrm{atan2}(x < 0, y = 0) = \pi$ とする
- $\mathrm{atan2}(0, 0) = 0$ とする
- 同じ角度の点同士の順番は任意
- 64bit浮動小数(double)を使うと誤差によりWAになるかもしれません、整数か80bit浮動小数(long double)を使ってください

Constraints / 制約
---------

- $1 \leq N \leq {{param N_MAX}}$
- $|x_i|, |y_i| \leq {{param X_AND_Y_ABS_MAX}}$

Input / 入力
---------

```
$N$
$x_0$ $y_0$
$x_1$ $y_1$
:
$x_{N - 1}$ $y_{N - 1}$
```

Output / 出力
---------

```
$x_0$ $y_0$
$x_1$ $y_1$
:
$x_{N - 1}$ $y_{N - 1}$
```

Sample / サンプル
---------

{{example example_00}}
