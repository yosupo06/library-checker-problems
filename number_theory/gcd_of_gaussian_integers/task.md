## @{keyword.statement}

@{lang.en}
In this problem, $i$ represents the imaginary unit.

Given Gaussian integers $a_1+b_1i$ and $a_2+b_2i$, find one of their greatest common divisors.

Please refer to the following definitions for Gaussian integers and their greatest common divisors:

- An element of $\mathbb{Z}[i] = \lbrace a+bi\mid a,b\in \mathbb{Z}\rbrace$ is called a Gaussian integer.

- For $x, y \in \mathbb{Z}[i]$, we define $x\mid y$ if there exists a $z$ in $\mathbb{Z}[i]$ such that $y = xz$.

- A Gaussian integer $g$ is a greatest common divisor of $x, y\in \mathbb{Z}[i]$ if, for any $z$ in $\mathbb{Z}[i]$, the condition $z\mid g$ is equivalent to $z\mid x$ and $z\mid y$. Such a $g$ is uniquely determined except for multiples of $\pm 1$ and $\pm i$.

You have $T$ test cases to solve.

@{lang.ja}
この問題において，$i$ は虚数単位を表します．

Gauss 整数 $a_1+b_1i, a_2+b_2i$ が与えられるので，その最大公約数（のひとつ）を求めてください．

Gauss 整数やその最大公約数については以下の定義を参考にしてください．

- $\mathbb{Z}[i] = \lbrace a+bi\mid a,b\in \mathbb{Z} \rbrace$ の元を Gauss 整数という．
- $x,y \in \mathbb{Z}[i]$ に対し，$y=xz$ となる $z \in \mathbb{Z}[i]$ が存在するとき $x\mid y$ であると定義する．
- $g \in \mathbb{Z}[i]$ が $x,y \in \mathbb{Z}[i]$ の最大公約数であるとは，任意の $z\in \mathbb{Z}[i]$ に対して，$z\mid g$ であることと $z\mid x$ かつ $z\mid y$ であることが同値になることをいう．このような $g$ は，$\pm 1$, $\pm i$ 倍の不定性を除き一意に定まる．

$T$ 個のテストケースが与えられるので，それぞれについて答えを求めてください．

@{lang.end}

## @{keyword.constraints}
- $1 \leq T \leq @{param.T_MAX}$
- $@{param.MIN} \leq a_1, b_1, a_2, b_2 \leq @{param.MAX}$

## @{keyword.input}

```
$T$
$a_1$ $b_1$ $a_2$ $b_2$
$\vdots$
$a_1$ $b_1$ $a_2$ $b_2$
```

## @{keyword.output}
@{lang.ja}
$a_1+b_1i$ と $a_2+b_2i$ の最大公約数が $a+bi$ であるとき，$a, b$ を出力してください．
@{lang.en}
When $a+bi$ is a greatest common divisor of $a_1+b_1i$ and $a_2+b_2i$, output $a$ and $b$. 
@{lang.end}

```
$a$ $b$
```

## @{keyword.sample}

@{example.example_00}

@{lang.ja}
$1$ つめのテストケースについて，`2 0` の他に，`-2 0`, `0 2`, `0 -2` も正答となります．
@{lang.en}
For the first test case, in addition to `2 0`, the following answers are also correct: `-2 0`, `0 2`, and `0 -2`.
@{lang.end}
