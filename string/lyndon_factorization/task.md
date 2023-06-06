## @{keyword.statement}

@{lang.en}

For a string $X = X _ 0 X _ 1 X _ 2 \cdots $ , we denote its substring $X _ a X _ {a+1} \cdots X _ {b-1}$ as $X[a,b)$ .

Given a string $S = S _ 0 S _ 1 S _ 2 \cdots S _ {N-1}$ of length $N$ . Find an array of integers $0 = a _ 0 \lt a _ 1 \lt a _ 2 \lt \ldots \lt a _ k = N$ so that $S[a _ 0 , a _ 1) , S[a _ 1 , a _ 2) , \ldots , S[a _ {k-1} , a _ k)$ is the Lyndon Factorization of $S$ .

@{lang.ja}

文字列 $X = X _ 0 X _ 1 X _ 2 \cdots $ に対して、その部分文字列 $X _ a X _ {a+1} \cdots X _ {b-1}$ を $X[a,b)$ で表します。

長さ $N$ の文字列 $S$ が与えられます。整数の列 $0 = a _ 0 \lt a _ 1 \lt a _ 2 \lt \ldots \lt a _ k = N$ であって、 $S[a _ 0 , a _ 1) , S[a _ 1 , a _ 2) , \ldots , S[a _ {k-1} , a _ k)$ が $S$ の Lyndon Factorization をなすようなものを求めてください。

@{lang.end}

## @{keyword.constraints}

@{lang.en}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- Each character of $S$ is a lowercase English letter.

@{lang.ja}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $S$ は英小文字からなる。

@{lang.end}

## @{keyword.input}

~~~
$S$
~~~

## @{keyword.output}

~~~
$a _ 0$ $a _ 1$ $a _ 2$ $\cdots$ $a _ k$
~~~

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
