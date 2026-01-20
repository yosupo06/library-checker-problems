## @{keyword.statement}

@{lang.en}
You are given a bivariate formal power series $f(x, y) = \sum_{i=0}^{N-1}\sum_{j=0}^{M-1} a_{i, j} x^iy^j \in \mathbb{F}\_{@{param.MOD}}[[x, y]]$ with $a_{0,0} \ne 0$.
Calculate the first $N \times M$ terms of $\frac{1}{f(x, y)} = \sum_{i=0}^{\infty} \sum_{j=0}^\infty b_{i,j} x^iy^j$.
In other words, find $g(x, y) = \sum_{i=0}^{N-1}\sum_{j=0}^{M-1} b_{i,j} x^iy^j \in \mathbb{F}\_{@{param.MOD}}[[x, y]]$ such that

$$f(x,y) g(x,y) \equiv 1 \pmod{(x^N, y^M)}.$$

@{lang.ja}
2変数の形式的冪級数 $f(x, y) = \sum_{i=0}^{N-1}\sum_{j=0}^{M-1} a_{i,j} x^iy^j \in \mathbb{F}\_{@{param.MOD}}[[x, y]]$ が与えられます ($a_{0,0} \ne 0$)。$\frac{1}{f(x, y)} = \sum_{i=0}^{\infty}\sum_{j=0}^{\infty} b_{i,j} x^iy^j$ の先頭 $N \times M$ 項を求めてください。つまり、

$$f(x,y) g(x,y) \equiv 1 \pmod{(x^N, y^M)}$$

となる $g(x, y) = \sum_{i=0}^{N-1}\sum_{j=0}^{M-1} b_{i,j} x^iy^j \in \mathbb{F}\_{@{param.MOD}}[[x, y]]$ を求めてください。

@{lang.end}

## @{keyword.constraints}

- $1 \leq N$
- $1 \leq M$
- $NM \leq @{param.NM_MAX}$
- $0 \leq a_{i,j} < @{param.MOD}$
- $a_{0,0} \neq 0$

## @{keyword.input}

```
$N$ $M$
$a_{0,0}$ $a_{0,1}$ $\cdots$ $a_{0,M - 1}$
$a_{1,0}$ $a_{1,1}$ $\cdots$ $a_{1,M - 1}$
$\vdots$
$a_{N-1,0}$ $a_{N-1,1}$ $\cdots$ $a_{N-1,M - 1}$
```

## @{keyword.output}

```
$b_{0,0}$ $b_{0,1}$ $\cdots$ $b_{0,M - 1}$
$b_{1,0}$ $b_{1,1}$ $\cdots$ $b_{1,M - 1}$
$\vdots$
$b_{N-1,0}$ $b_{N-1,1}$ $\cdots$ $b_{N-1,M - 1}$
```

## @{keyword.sample}

@{example.example_00}
