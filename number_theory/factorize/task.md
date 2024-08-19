## @{keyword.statement}

@{lang.en}

Given $Q$ cases. For each case, given integer $a_i$. Please factorize it.

@{lang.ja}

クエリが $Q$ 個与えられます。各クエリでは整数 $a_i$ が与えられるので、これを素因数分解してください。

@{lang.end}

## @{keyword.constraints}

- $1 \leq Q \leq @{param.MAX_Q}$
- $1 \leq a_i \leq @{param.MAX_A}$

## @{keyword.input}

```
$Q$
$a_0$
$a_1$
:
$a_{Q - 1}$
```

## @{keyword.output}

@{lang.en}
Print $Q$ lines. For each line, print as follows. $k$ is the number of factors and $x_i$ is the factors in __ascending__ order.
@{lang.ja}
$Q$ 行出力する。各行では以下のように出力する。$k$ は素因数の個数であり、$x_i$ は素因数を __昇順__ に並べたもの。
@{lang.end}

```
$k$ $x_0$ $x_1$ ... $x_{k - 1}$
```

## @{keyword.sample}

@{example.example_00}
