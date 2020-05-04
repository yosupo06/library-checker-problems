Problem Statement / ## {{keyword.statement}}
Let $\widetilde{r}$ be a rational number such that $-1 < \widetilde{r} < 1$ and $\widetilde{r} \equiv r \pmod{{{param MOD}}}$.
Given integers $r$ and $d$, calculate $\sum_{i=0}^{\infty} \widetilde{r}^i i^d$ modulo ${{param MOD}}$.
The answer is well-defined under the constraints of this problem.
We define $0^0 = 1$.

## {{keyword.constraints}}

- $0 \le r < {{param MOD}}$
- $r \ne 1$
- ${{param D_MIN}} \le d \le {{param D_MAX}}$

## {{keyword.input}}

~~~
$r$ $d$
~~~

## {{keyword.output}}

~~~
$\mathit{answer}$
~~~

## {{keyword.sample}}

{{example example_00}}
