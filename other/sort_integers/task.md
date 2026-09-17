## @{keyword.statement}

@{lang.en}
Given an array $A$ of $N$ nonnegative integers, sort it in nondecreasing order.
There are $T$ test cases in one input.
@{lang.ja}
$N$ 個の非負整数からなる配列 $A$ が与えられます。$A$ を広義単調増加になるようにソートしてください。
$1$ つの入力に $T$ 個のテストケースが与えられます。
@{lang.end}

## @{keyword.constraints}

- $1 \leq T \leq @{param.T_MAX}$
- $1 \leq N$
- $0 \leq A_i < 2^{64}$
@{lang.en}
- The sum of $N$ over all test cases is at most $@{param.N_SUM_MAX}$.
@{lang.ja}
- 全テストケースにおける $N$ の総和は $@{param.N_SUM_MAX}$ 以下です。
@{lang.end}

## @{keyword.input}

```
$T$
$\mathrm{case}_0$
$\vdots$
$\mathrm{case}_{T-1}$
```

@{lang.en}
Each test case is given in the following format:
@{lang.ja}
各テストケースは以下の形式で与えられます。
@{lang.end}

```
$N$
$A_0$ $A_1$ ... $A_{N-1}$
```

## @{keyword.output}

@{lang.en}
For each test case, output the sorted array on one line.
@{lang.ja}
各テストケースについて、ソートされた配列を $1$ 行に出力してください。
@{lang.end}

## @{keyword.sample}

@{example.example_00}
@{example.example_01}

## C++ (Function)

```cpp
void solve(std::vector<uint64_t>& a);
```

@{lang.en}
Sort `a` in nondecreasing order without changing its length. The grader calls this function once per test case.
The grader reports the total time spent calling `solve` to standard error, excluding input and output. The judge's time limit still applies to the entire program.
@{lang.ja}
`a` の長さを変えずに、広義単調増加になるようにソートしてください。各テストケースについて、この関数が一度呼び出されます。
グレーダーは、入出力を除いた `solve` の呼び出しにかかった合計時間を標準エラー出力に表示します。制限時間はプログラム全体に適用されます。
@{lang.end}
