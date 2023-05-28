## @{keyword.statement}

@{lang.en}

Given integers $n,k$ and a prime $m$, print $\binom{n}{k} \bmod m$.

Each test consists of $T$ cases, and $m$ is fixed in all cases.

@{lang.ja}

整数 $n,k$ と素数 $m$ が与えられます。$\binom{n}{k} \bmod m$ を計算してください。

この問題は $T$ ケースあります。また、$m$ は全てのケースで固定です。

@{lang.end}

## @{keyword.constraints}

- $1 \leq T \leq @{param.T_MAX}$
- $1 \leq m \leq @{param.M_MAX}$
- @{lang.en} $m$ is a prime @{lang.ja} $m$ は素数 @{lang.end}
- $0 \leq n, k \lt \min(m, @{param.N_MAX})$

## @{keyword.input}

```
$T\ m$
$n_0\ k_0$
$n_1\ k_1$
$\vdots$
$n_{T-1}\ k_{T-1}$
```

## @{keyword.output}

@{lang.en}
For each line, print $\binom{n}{k} \bmod m$.
@{lang.ja}
$\binom{n}{k} \bmod m$ を1行ずつ出力してください。
@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
