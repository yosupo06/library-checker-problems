## @{keyword.statement}
@{lang.en}
Given $N$ rectangles : the $i$-th rectangle is represented by $\lbrace (x,y):l_i \leq x \leq r_i,d_i \leq y \leq u_i \rbrace$. Output the area of the union set of these rectangles.

@{lang.ja}
$N$ 個の長方形が与えられます。 $i$ 番目の長方形は $\lbrace (x,y):l_i \leq x \leq r_i,d_i \leq y \leq u_i\rbrace$ で表されます。これらの長方形の和集合の面積を出力してください。

@{lang.end}

## @{keyword.constraints}
@{lang.en}

 - $1 \le N \le @{param.N_MAX}$
 - $0 \le l_i < r_i \le @{param.COORD_MAX}$
 - $0 \le d_i < u_i \le @{param.COORD_MAX}$

@{lang.ja}

 - $1 \le N \le @{param.N_MAX}$
 - $0 \le l_i < r_i \le @{param.COORD_MAX}$
 - $0 \le d_i < u_i \le @{param.COORD_MAX}$

@{lang.end}

## @{keyword.input}
~~~
$N$
$l_0$ $d_0$ $r_0$ $u_0$
$l_1$ $d_1$ $r_1$ $u_1$
$\vdots$
$l_{N-1}$ $d_{N-1}$ $r_{N-1}$ $u_{N-1}$
~~~

@{example.example_00}