# Library Checker Problems

![CI](https://github.com/yosupo06/library-checker-problems/workflows/Diff/badge.svg)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://github.com/yosupo06/library-checker-problems/blob/master/LICENSE)

[![Discord Banner](https://discordapp.com/api/guilds/1087310259447681114/widget.png?style=banner2)](https://discordapp.com/channels/1087310259447681114/1087410091730423889/1087411950218129509)

Source code of [https://judge.yosupo.jp](https://judge.yosupo.jp). You can get test cases of problems from this repository.

## Requirements

- Linux / OS X / Windows(MinGW-w64)
- python3.6+
- g++ / clang++ (Needs --std=c++17 and __int128_t)

## How to Use

```sh
cd /path/to/library-checker-problems

pip3 install -r requirements.txt
# or pip3 install colorlog

ulimit -s unlimited # for linux (doesn't need for OS X and WSL)

./generate.py -p unionfind # generate testcases of unionfind
# or ./generate.py datastructure/unionfind/info.toml

ls datastructure/unionfind/in/ # testcases of unionfind
ls datastructure/unionfind/out/ # solutions of unionfind
file datastructure/unionfind/checker # binary of output checker
```

### For developer

```sh
./generate.py -p unionfind --dev # developer mode
./generate.py -p unionfind --test # test mode (for developer, exec this command before PR)

./generate.py $(find . -name "info.toml" -not -path "./test/*") # generate all testcases
```

## Test your solutions in local / CI

- If you want to test your solutions on your computer, [Online Judge Tools](https://github.com/online-judge-tools/oj) is useful.
- If you want to use Github Actions for testing your library by our problems, [Online Judge Verify Helper](https://github.com/online-judge-tools/verification-helper) is useful.

## If you have any trouble

- Create issue: we are very happy if you report any of our mistakes (e.g. test cases are weak, strange behavior of the site, English of statements is bad, ...). Anything others are also welcome.
- Codeforces: https://codeforces.com/blog/entry/76945
- Twitter: if you tweet your trouble with hashtag \#LibraryChecker, we are going to help you. The account of admin is [@yosupot](https://twitter.com/yosupot).

## 困ったときは(If you have any trouble - Japanese edition)

- issueを立てる: githubにはissueというTODOやバグなどをメモっておく機能があります。上の Issues → New issueから作成できます。
- Twitter で \#LibraryChecker というハッシュタグをつけて呟いてくれると、助けに行きます。[@yosupot](https://twitter.com/yosupot) へリプライ / DM でも大丈夫です。

## Contributing

We are welcome any issues and PRs! Except minor change (e.g. add test cases, fix statements), please create an issue first.

## Contributing - Japanese Edition

不具合(テストケースが弱い, ジャッジが異常な挙動をする, 問題文にtypoを発見, などなど)を発見したとき、報告していただけるととっても助かります。

基本的には上に書いたようにissueを立ててもらえると助かります。
熱意がある人は[CONTRIBUTING](docs/CONTRIBUTING.md) を参考にPull requestを送っていただけるととても助かります。

競プロerは必ずしもgithubに慣れているとは限らず、issue / pull request を送ったことがない人も少なくはないというのを理解しています。どれだけめちゃくちゃなものを送ってきても怒ったりこのリポジトリが壊れたりすることはないので、githubの練習がてら挑戦してみるというのもアリです(頑張ってサポートします)。

## File structure / How to create the problem

[guideline(en)](docs/guideline.en.md)

[guideline(日本語)](docs/guideline.md)

## library-checker-project

- problems: [library-checker-problems](https://github.com/yosupo06/library-checker-problems)
- judge: [library-checker-judge](https://github.com/yosupo06/library-checker-judge)
- frontend: [library-checker-frontend](https://github.com/yosupo06/library-checker-frontend)

## Thanks

We use [testlib](https://github.com/MikeMirzayanov/testlib) for verifier(input-checker) and output-checker.
We use [toml](https://github.com/uiri/toml) as toml paser.
