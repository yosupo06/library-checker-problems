## @{keyword.statement}

@{lang.en}
Given a multiplicative function $f(x)$, satisfying $f(p^e) = ae + bp$. Print $\displaystyle \sum_{i=1}^N f(i) \bmod @{param.MOD}$.  
($@{param.MOD}$ is used instead of $998244353$ because it's easier to compute very long convolutions.)  
There are $T$ testcases.
@{lang.ja}  
$f(p^e) = ae + bp$ を満たす乗法的関数 $f(x)$ が与えられます。$\displaystyle \sum_{i=1}^N f(i) \bmod @{param.MOD}$ を出力してください。    
($@{param.MOD}$ が $998244353$ の代わりに使われているのは、非常に長い畳み込みの計算を簡単にするためです。)  
$T$ 個のテストケースが与えられます。
@{lang.end}

## @{keyword.constraints}

- $1 \leq T \leq @{param.T_MAX}$
- If $T = 1$, $1 \leq N \leq @{param.N_MAX}$. Otherwise, $1 \leq T \sqrt{N} \leq @{param.T_sqrtN_MAX}$.
- $0 \leq a, b \lt @{param.MOD}$

## @{keyword.input}

```
$T$
$N$ $a$ $b$
$N$ $a$ $b$
$\vdots$
$N$ $a$ $b$
```

## @{keyword.sample}

@{example.example_00}
@{example.example_01}
@{example.example_02}
