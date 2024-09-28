## @{keyword.statement}

@{lang.en}

Given $N \times M$ matrix $A$, a size $N$ vector $b$. Please calculate a (size $M$) vector $x$ s.t. $Ax = b$. We consider everything $\mathbb{F}_{2}$.

For the input and output of matrices and vectors, please treat each row as a string concatenated with its components ($0$ or $1$).
@{lang.ja}

$N \times M$ 行列 $A$, 長さ $N$ のベクトル $b$ が与えられます。$Ax = b$ を満たす(長さ $M$ の)ベクトル $x$ を求めてください。ただし全ての要素は $\mathbb{F}_{2}$ で考えることとします。

行列・ベクトルの入出力の際は，各行を成分（$0$ または $1$）を結合した文字列として扱ってください．
@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $1 \leq M \leq @{param.M_MAX}$
- $A_{ij} \in \lbrace 0,1\rbrace$
- $b_{i} \in \lbrace 0,1\rbrace$

## @{keyword.input}

```
$N$ $M$
$A_{0,0}A_{0,1}\cdots A_{0,M-1}$
$A_{1,0}A_{1,1}\cdots A_{1,M-1}$
$\vdots$
$A_{N-1,0}A_{N-1,1}\cdots A_{N-1,M-1}$
$b_0b_1\cdots b_{N-1}$
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
と出力してください．存在する場合，
@{lang.end}


```
$R$
$c_0c_1\cdots c_{M-1}$
$d_{0,0}d_{0,1}\cdots d_{0,M-1}$
$\vdots$
$d_{R-1,0}d_{R-1,1}\cdots d_{R-1,M-1}$
```

@{lang.en}
We note that $R$ is the rank of solution. $c_i$ is one of the solution. For each $j$, $d_{j,0}\cdots d_{j,M-1}$ is the basis of solution.
@{lang.ja}
と出力してください．ただし，$R$ は解空間の次元，$c_i$ は解のうち $1$ つとし，各 $j$ について，$d_{j,0}\cdots d_{j,M-1}$ は解空間の基底ベクトルとします．
@{lang.end}

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}
