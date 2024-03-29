## @{keyword.statement}

@{lang.en}
Given $N \times N$ matrix $a_{ij}$.
Calculate a permutation $p_i$ that minimize $\sum_{i = 0}^{N - 1} a_{ip_i}$.

If there is multiple solutions, print any of them.

@{lang.ja}
$N \times N$ の行列 $a_{ij}$ が与えられる。
$\sum_{i = 0}^{N - 1} a_{ip_i}$ を最小化する順列 $p_i$ を構成してください。

解が複数あるときはどれを出力してもいいです。
@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $|a_{ij}| \leq @{param.A_ABS_MAX}$

## @{keyword.input}

~~~
$N$
$a_{00}$ $a_{01}$ ... $a_{0,{N-1}}$
$a_{10}$ $a_{11}$ ... $a_{1,{N-1}}$
:
$a_{ {N-1}, 0 }$ $a_{ {N-1}, 1 }$ ... $a_{ {N-1}, {N-1} }$
~~~

## @{keyword.output}

~~~
$X$
$p_0$ $p_1$ ... $p_{N-1}$
~~~

$X = \sum_{i = 0}^{N - 1} a_{ip_i}$

## @{keyword.sample}

@{example.example_00}
