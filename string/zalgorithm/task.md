## @{keyword.statement}

@{lang.en}

Given a length $N$ string $S$. Calculate array $a_0, a_1, ..., a_{N - 1}$ as follows:

- $a_i$ is the LCP(longest common prefix) of $S$ and $S.substr(i)$.

@{lang.ja}

長さ $N$ の文字列 $S$ が与えられます。以下の条件を満たす配列 $a_0, a_1, ..., a_{N - 1}$ を出力してください。

- $a_i$ は、$S$ と $S.substr(i)$ の LCP(longest common prefix)

@{lang.end}

## @{keyword.constraints}

@{lang.en}

- $1 \leq N \leq @{param.N_MAX}$
- Each character of $S$ is lowercase English letters.

@{lang.ja}

- $1 \leq N \leq @{param.N_MAX}$
- $S$ は英小文字からなる。

@{lang.end}

## @{keyword.input}

~~~
$S$
~~~

## @{keyword.output}

~~~
$a_0$ $a_1$ $a_2$ ... $a_{N-1}$
~~~

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}

@{example.example_03}
