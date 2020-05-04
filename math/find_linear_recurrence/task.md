Problem Statement / ## {{keyword.statement}}
You are given a sequence of integers $a_0, \ldots, a_{N-1}$.

Find a sequence of integers $c_1, \ldots, c_d$ of the minimum length $d \ge 0$ such that
$0 \le c_j < {{param MOD}}$ for $1 \le j \le d$ and
$$a_i \equiv \sum_{j=1}^d c_j a_{i-j} \pmod{{{param MOD}}} \quad \text{for} \quad d \le i < N.$$

## {{keyword.constraints}}

- ${{param N_MIN}} \le N \le {{param N_MAX}}$
- $0 \le a_i < {{param MOD}}$

## {{keyword.input}}

~~~
$N$
$a_0$ $\ldots$ $a_{N-1}$
~~~

## {{keyword.output}}

~~~
$d$
$c_1$ $\ldots$ $c_d$
~~~

If there are multiple answers minimizing $d$, output any of them.

## {{keyword.sample}}

{{example example_00}}

{{example example_01}}

{{example example_02}}

{{example example_03}}
