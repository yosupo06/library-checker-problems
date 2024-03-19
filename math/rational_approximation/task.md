## @{keyword.statement}

@{lang.en}

You are given $T$ test cases. For each case, solve the following problem.

You are given positive integers $N, x, y$.
Let $S$ be the set of irreducible fractions whose numerator and denominator are both positive integers less than or equal to $N$.
Determine the maximum value in $S$ that is less than or equal to $x/y$ ($0/1$ if not exist) and the minimum value in $S$ that is greater than or equal to $x/y$ ($1/0$ if not exist).

@{lang.ja}

$T$ 個のテストケースが与えられます。それぞれについて、以下の問題の答えを求めてください。

正整数 $N, x, y$ が与えられます。
分子と分母が共に $N$ 以下の正整数である既約分数の集合を $S$ とします。
$S$ に含まれる元のうち、 $x/y$ 以下であるものの最大値（存在しない場合は$0/1$）および $x/y$ 以上であるものの最小値（存在しない場合は$1/0$）を求めてください。

@{lang.end}

## @{keyword.constraints}

- $1 \leq T \leq @{param.MAX_T}$
- $1 \leq N, x, y \leq @{param.MAX_N}$

## @{keyword.input}

```
$T$
$N_0$ $x_0$ $y_0$
$N_1$ $x_1$ $y_1$
$\vdots$
$N_{T-1}$ $x_{T-1}$ $y_{T-1}$
```

## @{keyword.output}

@{lang.en}
Print $T$ lines. When the values are $a/b$ and $c/d$, output as follows for each line.
@{lang.ja}
$T$ 行出力してください。求めたものが $a/b$ および $c/d$ であれば、各行では次のように出力してください。
@{lang.end}

```
$a$ $b$ $c$ $d$
```

## @{keyword.sample}

@{example.example_00}
