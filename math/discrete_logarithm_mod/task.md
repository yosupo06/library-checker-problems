## @{keyword.statement}

@{lang.en}
Each test case consist of $T$ cases.

Given $X, Y, M$. Print the minimum non-negative integer $K$ s.t. $X^K \equiv Y (\bmod M)$, or $-1$ if there is no such $K$.

We note that $0^0 = 1$ in this problem.

@{lang.ja}
この問題は $T$ ケース与えられる。

$X, Y, M$ が与えられる。$X^K \equiv Y (\bmod M)$ なる非負整数 $K$ のうち、最小を答えよ(存在しない場合は-1)。

なお、$0^0 = 1$ とします。
@{lang.end}

## @{keyword.constraints}

- $1 \leq T \leq 100$
- $0 \leq X, Y < M$
- $1 \leq M \leq 10^9$

## @{keyword.input}

```
$T$
$X_0$ $Y_0$ $M_0$
$X_1$ $Y_1$ $M_1$
:
$X_{T - 1}$ $Y_{T - 1}$ $M_{T - 1}$
```

## @{keyword.output}

@{lang.en}
For each line, print answer.
@{lang.ja}
各行に各ケースの答えを出力
@{lang.end}

## @{keyword.sample}

@{example.example_00}
