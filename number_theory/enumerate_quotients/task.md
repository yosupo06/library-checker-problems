## @{keyword.statement}

@{lang.en}

Consider the set of positive integers :

$$S=\left\lbrace \left\lfloor \frac{N}{x} \right\rfloor \middle\vert x \in \mathbb{Z} , 1 \leq x \leq N \right\rbrace .$$

Output the sequence $(a _ 0, a _ 1 , \ldots , a _ {k-1})$ which is obtained by sorting the elements of $S$ in ascending order.

@{lang.ja}

正整数からなる集合

$$S=\left\lbrace \left\lfloor \frac{N}{x} \right\rfloor \middle\vert x \in \mathbb{Z} , 1 \leq x \leq N \right\rbrace$$

の元を昇順に並べたものを $(a _ 0, a _ 1 , \ldots , a _ {k-1})$ とします。この数列を出力してください。

@{lang.end}

## @{keyword.constraints}

- $@{param.N_MIN} \le N \le @{param.N_MAX}$

## @{keyword.input}

~~~
$N$
~~~

## @{keyword.output}

~~~
$k$
$a _ 0$ $a _ 1$ $\ldots$ $a _ {k-1}$
~~~

@{example.example_00}
