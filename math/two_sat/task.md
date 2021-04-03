## @{keyword.statement}

@{lang.en}
Given 2-Sat with $N$ variables and $M$ clauses. Check the satisfiability and if satisfiable, construct the assignment of variables.
@{lang.ja}
$N$ 変数 $M$ 節の 2 Sat が与えられる。充足可能か判定し、可能ならば割り当てを一つ求めてください。
@{lang.end}


## @{keyword.constraints}

- $1 \leq N \leq 500,000$
- $1 \leq M \leq 500,000$

## @{keyword.input}

@{lang.en}
2-Sat is given as [DIMACS format](http://www.domagoj-babic.com/uploads/ResearchProjects/Spear/dimacs-cnf.pdf). Please see the samples.
@{lang.ja}
[DIMACS 標準形式](http://www.domagoj-babic.com/uploads/ResearchProjects/Spear/dimacs-cnf.pdf) で与えられる。
サンプルも参考にせよ
@{lang.end}

~~~
p cnf $N$ $M$
$a_1$ $b_1$ 0
$a_2$ $b_2$ 0
:
$a_M$ $b_M$ 0
~~~

## @{keyword.output}

@{lang.en}
If the input is satisfiable, print as follows:
@{lang.ja}
充足可能な場合は以下
@{lang.end}

```
s SATISFIABLE
v $x_1$ $x_2$ ... $x_N$ 0
```

@{lang.en}
If $i$-th variable is true, $x_i = i$, and is false, $x_i = -i$.

If the input is not satisfiable,print as follows:
@{lang.ja}
$x_i$ は、$i$ 番目の変数が真ならば $i$、偽ならば $-i$

充足不可能な場合は以下
@{lang.end}


~~~
s UNSATISFIABLE
~~~

## @{keyword.sample}

@{example.example_00}

@{lang.en}
This sample means as follows:
@{lang.ja}
この入力は
@{lang.end}

$$
    (x_1 \lor x_2) \land
    (\lnot x_3 \lor \lnot x_1) \land
    (\lnot x_4 \lor \lnot x_3) \land
    (x_2 \lor \lnot x_5) \land
    (x_5 \lor \lnot x_2) \land
    (x_1 \lor x_4)
$$

@{lang.ja}
を表す
@{lang.end}

@{example.example_01}
