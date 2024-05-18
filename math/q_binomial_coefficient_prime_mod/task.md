## @{keyword.statement}

@{lang.en}

Given integers $n,k,q$ and a prime $m$, print $\binom{n}{k}_q \bmod m$.

Here, $\binom{n}{k}_q$ denotes the $q$-binomial coefficient. 
For the definition of $q$-binomial coefficient, see the [Gaussian binomial coefficient](https://en.wikipedia.org/wiki/Gaussian_binomial_coefficient).

Each test consists of $T$ cases, and $q$ and $m$ are fixed in all cases.

@{lang.ja}

整数 $n,k,q$ と素数 $m$ が与えられます．$\binom{n}{k}_q \bmod m$ を計算してください．

ここで，$\binom{n}{k}_q$ は $q$ 二項係数を表します．$q$ 二項係数の定義については [Gaussian binomial coefficient](https://en.wikipedia.org/wiki/Gaussian_binomial_coefficient) を参照してください．

この問題は $T$ ケースあります．また，$q,m$ は全てのケースで固定です．

@{lang.end}

## @{keyword.constraints}

@{lang.en}

- $1 \leq T \leq @{param.T_MAX}$
- $1 \leq m \leq @{param.M_MAX}$
- $m$ is a prime
- $0\leq q \lt m$
- $0 \leq n, k \lt \min(m, @{param.N_MAX})$

@{lang.ja}

- $1 \leq T \leq @{param.T_MAX}$
- $1 \leq m \leq @{param.M_MAX}$
- $m$ は素数
- $0\leq q \lt m$
- $0 \leq n, k \lt \min(m, @{param.N_MAX})$

@{lang.end}

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
For each line, print $\binom{n}{k}_q \bmod m$.
@{lang.ja}
$\binom{n}{k}_q \bmod m$ を1行ずつ出力してください．
@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}
