# How to create the problem

Obliviously, we have to make folder at first. The path of folder is `library-checker-problems/{Genre}/{Problem ID}`, e.g. `sample/aplusb` or `datastructure/unionfind`.

Problem ID should be decided in the talking of issues. Genre isn't so important, but there are many problems and you can find good one probably.

## Directory Structure

Overview of directory is as follows:

- aplusb/
  - info.toml : information of the problem
  - checker.cpp : output checker
  - verifier.cpp : input checker
  - hash.json : hash of in/out files
  - (params.h : the file that generated automatically contains the constants, N_MAX, D_MAX, ...
  - sol/
    - correct.cpp : author's solution
    - wa.cpp
    - ...
  - gen/
    - example_00.in : sample file
    - random.cpp
    - ...
  - (in/) : Directory of outfiles, automatically generated
    - example_00.in
    - random_00.in
    - ...
  - (out/) : Directory of outfiles, automatically generated
    - example_00.out

You have to prepare following files.

- info.toml
- task.md : task statement
- sol/correct.cpp : author solution
- verifier.cpp : input checker
- checker.cpp : output checker
- gen/example_00.in, gen/example_01.in, gen/random.cpp, and so on : test case generator

### info.toml

info.toml contains many informations of the problem. You have to learn [toml](https://github.com/toml-lang/toml) format but it is quite easy, don't worry.

```toml
timelimit = 2.0

[[tests]]
    name = "example.in"
    number = 2
[[tests]]
    name = "random.cpp"
    number = 10

[[solutions]]
    name = "wa.cpp"
    wrong = true

[params]
    A_AND_B_MAX = 1_000_000_000
```

- `timelimit`: Timelimit(sec) Usually 5sec or 10sec, though aplusb is 2sec...
- `[[tests]]`: Each `[[tests]]` correspond to an 1 testcase generator
  - `name`: File name
  - `number`: The number of cases that this gagenerate
- `[[solutions]]`: Each `[[solutions]]` correspond to an 1 solution file. (You don't needs to write `correct.cpp`)
  - `name`: File name
  - `wrong`: This solution is expected to WA
  - `allow_tle`: TLE is allowed or not
- `[params]`: Constraints. Those constraints output into `params.h` automatically.
  - You can use params from `task.md` as `@{param.A_AND_B_MAX}`.

## task.md(Problem statements)

You can copy this file from other problems.

- @{lang.en}, @{lang.ja}, @{lang.end} : Language selector
- @{example.example_00} : Insert `gen/example_00.in`
- @{param.A_AND_B_MAX} : Insert `[params]` that specified by info.toml

## sol/correct.cpp(Author solution)

Basically, you can prepare the same file usually (get input from stdin and print to stdout). You have to keep following constraints.

- C++
- You can use your template, but please avoid to a tons of unused template
- Please use `scanf / printf` or fast something instead of `cin / cout`
- Don't ignore warning
- You cannot use `params.h`
- Avoid environment dependency(checked in CI). You should avoid
  - `bits/stdc++.h`
  - Some functions: `rand()`, `uniform_int_distribution`, `shuffle`, ...
    - if you want to use random, please copy the contents of `common/random.h`. `uniform_int_distribution` has environment dependency.

## verifier.cpp(input checker)

[https://codeforces.com/blog/entry/18426](https://codeforces.com/blog/entry/18426)

## checker.cpp(output checker)

参加者の出力が、条件を満たしているか判定するコードです。

If you want to use normal judge, please copy `library-checker-problems/sample/aplusb/checker.cpp`

For special judge: [https://codeforces.com/blog/entry/18431](https://codeforces.com/blog/entry/18431)

- You can not use `%lld` in quitf(because, MinGW...)
  - Please use `quitf(_wa, "long long value(" I64 ")", x)` instead of `quitf(_wa, "long long value(%lld)", x)` 


## gen/example_00.in, gen/example_01.in, gen/random.cpp...(Generator)

You can refer [テストケースの作り方](generator.md) (TODO! translation...)

- Please prepare example_00.in as sample
- Weak test cases is okay, we can add testcases in later

## Running your problem

```sh
./generate.py sample/aplusb/info.toml --dev
```

### hash.json(automatically generated)

```json
{
  "example_00.in": "346a847f5875beb74d494de0680a81fc2ff840b12f79de30dc7ef3a798d23c28",
  "example_00.out": "d6e0da7b83d84fac4d6a6bd11ad0b0e6ea72351748b4f6a277b9762d9d0eb159",
  "example_01.in": "0073cf03577a737756752129cc3abcb9f5a4069c705321ee2115574cc31c59f9",
  "example_01.out": "6f2264250160ee91b20af64f30128e3787fcf641f1c504f7ac752597e7d2cc09"
}
```

You can view hash.json if everything is okay. You have to commit this file.
