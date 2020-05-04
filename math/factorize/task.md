## {{keyword.statement}}
クエリが $Q$ 個与えられます。各クエリでは整数 $a_i$ が与えられるので、これを素因数分解してください。

## {{keyword.constraints}}

- $1 \leq Q \leq 100$
- $1 \leq a_i \leq 10^{18}$

## {{keyword.input}}

```
$Q$
$a_0$
$a_1$
:
$a_{Q - 1}$
```

## {{keyword.output}}

$Q$ 行出力する。各行では以下のように出力する。$k$ は素因数の個数であり、$x_i$ は素因数を __昇順__ に並べたもの。

```
$k$ $x_0$ $x_1$ ... $x_{k - 1}$
```

## {{keyword.sample}}

{{example example_00}}
