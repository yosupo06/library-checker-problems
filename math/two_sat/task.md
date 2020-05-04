## {{keyword.statement}}
$N$ 変数 $M$ 節の 2 Sat が与えられる。充足可能か判定し、可能ならば割り当てを一つ求めてください。



## {{keyword.constraints}}

- $1 \leq N \leq 500,000$
- $1 \leq M \leq 500,000$

## {{keyword.input}}

[DIMACS 標準形式](http://www.domagoj-babic.com/uploads/ResearchProjects/Spear/dimacs-cnf.pdf) で与えられる。
サンプルも参考にせよ

~~~
p cnf $N$ $M$
$a_1$ $b_1$ 0
$a_2$ $b_2$ 0
:
$a_M$ $b_M$ 0
~~~

## {{keyword.output}}

充足可能な場合は以下

```
s SATISFIABLE
v $x_1$ $x_2$ ... $x_N$ 0
```

$x_i$ は、$i$ 番目の変数が真ならば $i$、偽ならば $-i$

充足不可能な場合は以下

~~~
s UNSATISFIABLE
~~~

## {{keyword.sample}}

{{example.example_00}}

この入力は

$$
    (x_1 \lor x_2) \land
    (\lnot x_3 \lor \lnot x_1) \land
    (\lnot x_4 \lor \lnot x_3) \land
    (x_2 \lor \lnot x_5) \land
    (x_5 \lor \lnot x_2) \land
    (x_1 \lor x_4)
$$

を表す

{{example.example_01}}
