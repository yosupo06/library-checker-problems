## {{keyword.statement}}
この問題は $T$ ケース与えられます。

$Y, P(P: \textrm{prime})$ が与えられます。

$X^2 \equiv Y (\bmod P)$ なる $X$ を1つ求めてください。

## {{keyword.constraints}}

- $1 \leq T \leq 100,000$
- $2 \leq P \leq 10^9$
- $0 \leq Y < P$
- $P$ は素数

## {{keyword.input}}

```
$T$
$Y_0$ $P_0$
$Y_1$ $P_1$
:
$Y_{T-1}$ $P_{T-1}$
```

## {{keyword.output}}

各行に、$X$、もしくは条件を満たす $X$ が存在しないならば $-1$ を出力してください

## {{keyword.sample}}

{{example example_00}}
