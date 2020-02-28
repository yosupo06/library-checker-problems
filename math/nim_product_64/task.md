Problem Statement / 問題文
---------

There are $T$ test cases.

For each test case, you are given two nonnegative integers $A$ and $B$.
Calculate the nim product $A \otimes B$.

The nim sum and the nim product for nonnegative integers are defined recursively as follows:

- $a \oplus b = \operatorname{mex}(\{ a' \oplus b \mid a' < a \} \cup \{ a \oplus b' \mid b' < b \})$
- $a \otimes b = \operatorname{mex}\{ (a' \otimes b) \oplus (a \otimes b') \oplus (a' \oplus b') \mid a' < a, b' < b \}$

Constraints / 制約
---------

- ${{param T_MIN}} \le T \le {{param T_MAX}}$
- $0 \le A < 2^{64}$
- $0 \le B < 2^{64}$

Input / 入力
---------

~~~
$T$
$A_0$ $B_0$
$\vdots$
$A_{T-1}$ $B_{T-1}$
~~~

{{example example_00}}
