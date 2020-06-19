# How to create testcases

Overview:

1. Make generators
1. Registor generators into `{problem_dir}/info.toml`
1. Run `generate.py`

## Make generators (cpp)

There are many generators already, you can refer these.

Important points are:

- Don't use `rand()` or `uniform_int_distribution`. You should `#include "random.h"`, it includes [`common/random.h`](https://github.com/yosupo06/library-checker-problems/blob/master/common/random.h), and use `struct Random`
- Use `argv[1]` to seed
- For large output file, you should use `printf`, not `cout`.

[sample/aplusb/gen/random.cpp](../sample/aplusb/gen/random.cpp) is useful for the sample generator.

Coding rules:

- C++
- You can use your template, but please avoid tons of unused template
- Don't ignore warnings (`-Wall -Wextra -Werror -Wno-unused-result`)
- Don't print space into line end (`1_2_3` is okay, `1_2_3_` is bad.)

## Generators (txt)

If the input file is small (e.g. less than 20 integers), you can prepare text files as input.

## Register generators

Put your generators into `{problem_dir}/gen` and write `info.toml` as follows:

```toml
[[tests]]
    name = "my_generator.cpp"
    number = 2
```

Of course, you can refer `aplusb/info.toml` or other problems.

- Please avoid many random cases (2~5 is good)

## Run

Please refer how to use of [README](../README.md).
