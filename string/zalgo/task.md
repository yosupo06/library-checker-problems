問題文
---------

長さ $N$ の文字列 $S$ が与えられます。以下の条件を満たす配列 $a_0, a_1, ..., a_N$ を出力してください。

- $a_i$ は、$S$ と $S.substr(i)$ の LCP(longest common prefix)


制約
---------

- $1 \leq N \leq 500,000$
- $S$ は英小文字のみからなる

入力
---------

~~~
$S$
~~~

出力
---------

末尾に空白を付けると落ちます [Issue #2](https://github.com/yosupo06/library-checker-problems/issues/2)

~~~
$a_0$ $a_1$ $a_2$ ... $a_N$
~~~
