Problem Statement (Japanese) / 問題文 (日本語)
---------

この問題は $T$ ケース与えられます。

$K, Y, P(P: \textrm{prime})$ が与えられます。

$X^K \equiv Y (\bmod P)$ なる $X$ を1つ求めてください。

Constraints / 制約
---------

- $1 \leq T \leq {{T_MAX}}$
- $2 \leq P \leq {{P_MAX}}$
- $0 \leq Y \leq {{K_MAX}}$
- $P$ は素数

Input / 入力
---------

```
$T$
$K_0$ $Y_0$ $P_0$
$K_1$ $Y_1$ $P_1$
$\vdots$
$K_{T-1}$ $Y_{T-1}$ $P_{T-1}$
```

Output / 出力
---------

各行に、$X$、もしくは条件を満たす $X$ が存在しないならば $-1$ を出力してください

Sample / サンプル
---------

{{example example_00}}
