## @{keyword.statement}

@{lang.en}
Given $Q$ cases. For each case, an integer $N_i$ is given. Please find its prime factorization.
@{lang.ja}
$Q$ 個のケースが与えられます。それぞれのケースについて、整数 $N_i$ を素因数分解してください。
@{lang.end}

## @{keyword.constraints}

- $1 \leq Q \leq @{param.MAX_Q}$
- $1 \leq N_i \leq 10^{38}$

## @{keyword.input}

~~~
$Q$
$N_0$
$N_1$
:
$N_{Q-1}$
~~~

## @{keyword.output}

For each case, print its prime factorization in ascending order, prefixed by the number of factors $k$.

~~~
$k$ $p_1$ $p_2$ ... $p_k$
~~~

## @{keyword.sample}

@{example.example_00}
