## @{keyword.statement}

@{lang.en}
Each test case consists of $T$ cases.

Given $K, Y, P(P: \textrm{prime})$.

Print any $X$ s.t. $X^K \equiv Y \pmod{P}$, or $-1$ if there is no such $X$.

We note that $0^0\equiv 1 \pmod{P}$ in this problem.
@{lang.ja}
この問題は $T$ ケース与えられます。

$K, Y, P(P: \textrm{prime})$ が与えられます。

$X^K \equiv Y \pmod{P}$ なる $X$ を1つ求めてください。

ただし $0^0\equiv 1 \pmod{P}$ とします。
@{lang.end}

## @{keyword.constraints}

@{lang.en}

- $1 \leq T \leq @{param.T_MAX}$
- $0 \leq K \leq @{param.K_MAX}$
- $2 \leq P \leq @{param.P_MAX}$
- $0 \leq Y  < P$
- $P$ is prime.

@{lang.ja}

- $1 \leq T \leq @{param.T_MAX}$
- $0 \leq K \leq @{param.K_MAX}$
- $2 \leq P \leq @{param.P_MAX}$
- $0 \leq Y  < P$
- $P$ は素数

@{lang.end}

## @{keyword.input}

```
$T$
$K_0$ $Y_0$ $P_0$
$K_1$ $Y_1$ $P_1$
$\vdots$
$K_{T-1}$ $Y_{T-1}$ $P_{T-1}$
```

## @{keyword.output}

@{lang.en}
For each line, print $X$ or $-1$.
@{lang.ja}
各行に、$X$、もしくは条件を満たす $X$ が存在しないならば $-1$ を出力してください。
@{lang.end}

## @{keyword.sample}

@{example.example_00}
