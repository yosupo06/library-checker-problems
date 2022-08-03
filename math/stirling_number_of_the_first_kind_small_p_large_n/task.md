## @{keyword.statement}

@{lang.en}
The signed Stirling numbers of the first kind $s(n, k)$ are defined as the coefficients in the identity
$$x (x - 1) \cdots (x - (n - 1)) = \sum_{k=0}^n s(n, k) x^k.$$

Given $n,k$ and $p$, where $p$ is a prime. Calculate $s(n, k) \bmod p$.

Each test consists of $T$ cases, and $p$ is fixed in all cases.

@{lang.ja}
符号付き第 $1$ 種スターリング数 $s(n,k)$ を次を満たす係数として定義します：
$$x (x - 1) \cdots (x - (n - 1)) = \sum_{k=0}^n s(n, k) x^k.$$

$n,k,p$ が与えられます。$s(n,k) \bmod p$を計算してください。

この問題は $T$ ケースあります。また、$p$ は全てのケースで固定です。

@{lang.end}

## @{keyword.constraints}

@{lang.en}
- $1 \leq T \leq @{param.T_MAX}$
- $@{param.P_MIN} \leq p \leq @{param.P_MAX}$
- $p$ is a prime.
- $0 \leq k \leq n \leq @{param.N_MAX}$
@{lang.ja}
- $1 \leq T \leq @{param.T_MAX}$
- $@{param.P_MIN} \leq p \leq @{param.P_MAX}$
- $p$ は素数
- $0 \leq k \leq n \leq @{param.N_MAX}$
@{lang.end}

## @{keyword.input}

```
$T\ p$
$n_0\ k_0$
$n_1\ k_1$
$\vdots$
$n_{T-1}\ k_{T-1}$
```

## @{keyword.output}

@{lang.en}
For each line, print $s(n,k) \bmod p$.
@{lang.ja}
$s(n,k) \bmod p$ を1行ずつ出力してください。
@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
