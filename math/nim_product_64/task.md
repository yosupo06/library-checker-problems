## @{keyword.statement}
There are $T$ test cases.

For each test case, you are given two nonnegative integers $A$ and $B$.
Calculate the nim product $A \otimes B$.

The nim sum and the nim product for nonnegative integers are defined recursively as follows:

- $a \oplus b = \operatorname{mex}(\lbrace a' \oplus b \mid a' < a \rbrace \cup \lbrace a \oplus b' \mid b' < b \rbrace)$
- $a \otimes b = \operatorname{mex}\lbrace (a' \otimes b) \oplus (a \otimes b') \oplus (a' \otimes b') \mid a' < a,\, b' < b \rbrace$

## @{keyword.constraints}

- $@{param.T_MIN} \le T \le @{param.T_MAX}$
- $0 \le A < 2^{64}$
- $0 \le B < 2^{64}$

## @{keyword.input}

~~~
$T$
$A_0$ $B_0$
 $\vdots$
$A_{T-1}$ $B_{T-1}$
~~~

## @{keyword.output}

~~~
$\mathit{answer}_0$
 $\vdots$
$\mathit{answer}_{T-1}$
~~~

@{example.example_00}
