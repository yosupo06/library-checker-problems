## {{keyword.statement}}
この問題は $T$ ケース与えられます。

$K, Y, P(P: \textrm{prime})$ が与えられます。

$X^K \equiv Y \pmod{P}$ なる $X$ を1つ求めてください。

ただし $0^0\equiv 1 \pmod{P}$ とします。

## {{keyword.constraints}}

- $1 \leq T \leq {{param T_MAX}}$
- $0 \leq K \leq {{param K_MAX}}$
- $2 \leq P \leq {{param P_MAX}}$
- $0 \leq Y  < P$
- $P$ は素数

## {{keyword.input}}

```
$T$
$K_0$ $Y_0$ $P_0$
$K_1$ $Y_1$ $P_1$
$\vdots$
$K_{T-1}$ $Y_{T-1}$ $P_{T-1}$
```

## {{keyword.output}}

各行に、$X$、もしくは条件を満たす $X$ が存在しないならば $-1$ を出力してください。

## {{keyword.sample}}

{{example example_00}}
