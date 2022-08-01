## @{keyword.statement}

@{lang.en}
You are given an integer sequence $A$ with the length $N$. Find a longest increasing subsequence of $A$.
@{lang.ja}
長さ $N$ の数列 $A$ が与えられます。$A$ の最長増加部分列を一つ構築してください。
@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.A_MIN} \leq A_i \leq @{param.A_MAX}$

## @{keyword.input}

~~~
$N$
$A_0$ $A_1$ $\dots$ $A_{N - 1}$
~~~

## @{keyword.output}

@{lang.en}
On line $1$, output the maximum length $K$ of an increasing subsequence of $A$.
On line $2$, Print an increasing subsequence of length $K$. 
$i_k$ is the index of the kth element of the subsequence.
@{lang.ja}
$1$ 行目に $A$ の最長増加部分列の長さ $K$ を出力してください。
$2$ 行目に長さ $K$ の最長増加部分列を一つ以下の形式で出力してください。
$i_k$ は最長増加部分列の $k$ 番目の要素の添え字を表します。
@{lang.end}
```
$K$
$i_0$ $i_1$ $\dots$ $i_{K - 1}$
```


## @{keyword.sample}

@{example.example_00}
@{example.example_01}

