# Library Checker Problems

[![CircleCI](https://circleci.com/gh/yosupo06/library-checker-problems/tree/master.svg?style=svg)](https://circleci.com/gh/yosupo06/library-checker-problems/tree/master)
[![Gitter](https://badges.gitter.im/library-checker-problems/community.svg)](https://gitter.im/library-checker-problems/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)

Source code of [https://judge.yosupo.jp](https://judge.yosupo.jp)

このリポジトリのコードを動かすことで、問題のテストケースを生成することができます。

## Requirements

- Linux / OS X
- python3.6+
- g++ / clang++ (--std=c++14, __int128_tが使える必要あり)

### (需要と余力があれば)対応予定

- Windows
- python3.5
- MSVC++
- __int128_tの除去

## How to Use

```sh
cd /path/to/library-checker-problems

pip3 install toml markdown
# or pip3 install -r requirements.txt

ulimit -s unlimited # for linux (don't need for os x)
./generate.py problems.toml # generate testcase of all problems
./generate.py problems.toml -p unionfind # generate testcase of unionfind
```

## Contributing(バグ報告などしていただける方へ)

不具合(テストケースが弱い, ジャッジが異常な挙動をする, 問題文にtypoを発見, などなど)を発見したとき、報告していただけるととっても助かります。
機能の追加要望などもなんでも歓迎です。

- githubはよくわからない！ / issueを立てるのがめんどくさい
  - [gitter](https://gitter.im/library-checker-problems/community) に書き込んでいただけると助かります
  - [twitter](https://twitter.com/yosupot) でも大丈夫です
- issueの立て方がわかる！
  - issueを立ててくれると助かります。適当で大丈夫です
  - [CONTRIBUTING](docs/CONTRIBUTING.md) を参考にしていただけるともっと助かりますが、熱意がある場合のみで大丈夫です

## library-checker-project

- problems: [library-checker-problems](https://github.com/yosupo06/library-checker-problems)
- judge: [library-checker-judge](https://github.com/yosupo06/library-checker-judge)
- frontend: [library-checker-frontend](https://github.com/yosupo06/library-checker-frontend)

## ディレクトリ構成

sample/aplusbを参考にしてください

- info.toml: 問題のさまざまな情報
- gen/: ケース生成スクリプト
- sol/: 回答コード
- checker.cpp: output_checker
- task.md: 問題文

## 問題の追加

- problems.tomlにいい感じに追加する
- sample/aplusbディレクトリを参考に、いい感じに

## Thanks

checker, validatorなどに [testlib](https://github.com/MikeMirzayanov/testlib) を使用しています。
