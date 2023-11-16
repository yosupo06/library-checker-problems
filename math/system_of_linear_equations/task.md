## @{keyword.statement}

@{lang.en}

Given $N \times M$ matrix $A$, a size $N$ vector $b$. Please calculate a (size $M$) vector $x$ s.t. $Ax = b$. We consider everything $\mathbb{F}_{998244353}$.

@{lang.ja}

$N \times M$ 行列 $A$, 長さ $N$ のベクトル $b$ が与えられます。$Ax = b$ を満たす(長さ $M$ の)ベクトル $x$ を求めてください。ただし全ての要素は $\mathbb{F}_{998244353}$ で考えることとします。

@{lang.end}

## @{keyword.constraints}

- $1 \leq N, M \leq 500$
- $0 \leq a_{ij} < 998244353$

## @{keyword.input}

```
$N$ $M$
$A_{0,0}$ $A_{0,1}$ ... $A_{0,M-1}$
$A_{1,0}$ $A_{1,1}$ ... $A_{1,M-1}$
:
$A_{N-1,0}$ $A_{N-1,1}$ ... $A_{N-1,M-1}$
$b_0$ $b_1$ ... $b_{N-1}$
```

## @{keyword.output}

@{lang.en}
If there is no solution, print
@{lang.ja}
解が存在しない場合
@{lang.end}

```
-1
```

@{lang.en}
and if exists, print as follows.
@{lang.ja}
と出力してください。存在する場合、
@{lang.end}


```
$R$
$c_0$ $c_1$ ... $c_{M-1}$
$d_{0,0}$ $d_{0,1}$ ... $d_{0,M-1}$
:
$d_{R-1,0}$ $d_{R-1,1}$ ... $d_{R-1,M-1}$
```

@{lang.en}
We note that $R$ is the rank of solution. $c_i$ is one of the solution. For each $j$, $d_{j,0}, ..., d_{j,M-1}$ is the basis of solution.
@{lang.ja}
と出力してください。ただし、$R$ は解空間の次元、$c_i$ は解のうち $1$ つとし、各 $j$ について、$d_{j,0}, ..., d_{j,M-1}$ は解空間の(それぞれ独立な)基底ベクトルとします。
@{lang.end}

## @{keyword.sample}

@{example.example_00}
