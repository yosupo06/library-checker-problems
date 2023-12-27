## @{keyword.statement}

@{lang.en}
Given 2D-points $A _ k=(x _ k, y _ k)$ $(k=0,1,\ldots ,N-1)$ and 2D-points $B _ k=(p _ k, q _ k)$ $(k=0,1,\ldots ,M-1)$ . Process the following $Q$ queries in order.

* Given $a$ , $b$ , $c$ . Please output the number of points in $B _ 0,B _ 1,\ldots ,B _ {M-1}$ included in the convex hull of $3$ points $A _ a,A _ b,A _ c$ (**exclude border**) .

@{lang.ja}
2D の点 $A _ k=(x _ k, y _ k)$ $(k=0,1,\ldots ,N-1)$ と 2D の点 $B _ k=(p _ k, q _ k)$ $(k=0,1,\ldots ,M-1)$ が与えられます。以下の $Q$ 個のクエリに順に答えてください。

* $a$ , $b$ , $c$ が与えられます。 $B _ 0,B _ 1,\ldots ,B _ {M-1}$ のうち、 $3$ 点 $A _ a,A _ b,A _ c$ の凸包の内部 (**境界を除く**) にあるものの個数を出力してください。
@{lang.end}

## @{keyword.constraints}

@{lang.en}
- $1 \leq N \leq @{param.N_MAX}$
- $1 \leq M \leq @{param.M_MAX}$
- $|x _ i|, |y _ i| \leq @{param.X_AND_Y_ABS_MAX}$
- $|p _ i|, |q _ i| \leq @{param.X_AND_Y_ABS_MAX}$
- $1 \leq Q \leq @{param.Q_MAX}$
- $0 \leq a,b,c \leq N-1$
- They are all integers.
@{lang.ja}
- $1 \leq N \leq @{param.N_MAX}$
- $1 \leq M \leq @{param.M_MAX}$
- $|x _ i|, |y _ i| \leq @{param.X_AND_Y_ABS_MAX}$
- $|p _ i|, |q _ i| \leq @{param.X_AND_Y_ABS_MAX}$
- $1 \leq Q \leq @{param.Q_MAX}$
- $0 \leq a,b,c \leq N-1$
- これらはすべて整数
@{lang.end}

## @{keyword.input}

```
$N$
$x _ 0$ $y _ 0$
$x _ 1$ $y _ 1$
$\ \vdots$
$x _ {N-1}$ $y _ {N-1}$
$M$
$p _ 0$ $q _ 0$
$p _ 1$ $q _ 1$
$\ \vdots$
$p _ {M-1}$ $q_{M-1}$
$Q$
$a$ $b$ $c$
$\ \vdots$
$a$ $b$ $c$
```

## @{keyword.sample}

@{example.example_00}
