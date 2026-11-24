
#include <cstdint>
#include <string>
#include <thread>
#include <limits>

#include "fastio.h"
#include "gtest/gtest.h"
#include "random.h"

using namespace library_checker;

TEST(FastIOTest, ScannerInt128) {
    auto tmpf = tmpfile();
    fputs("1234567890123456", tmpf);
    rewind(tmpf);
    Scanner sc(tmpf);
    __int128 x;
    sc.read(x);
    ASSERT_EQ(1234567890123456LL, x);
}

TEST(FastIOTest, ScannerInt) {
    auto tmpf = tmpfile();
    std::vector<int> v;
    for (int i = 0; i <= 123456; i++) {
        v.push_back(i);
        v.push_back(-i);
        v.push_back(std::numeric_limits<int>::min() + i);
        v.push_back(std::numeric_limits<int>::max() - i);
    }

    for (auto x : v) {
        fputs((std::to_string(x) + "\n").c_str(), tmpf);
    }
    rewind(tmpf);

    Scanner sc(tmpf);
    int y;
    for (auto x : v) {
        sc.read(y);
        ASSERT_EQ(x, y);
    }
}

TEST(FastIOTest, ScannerIntWin) {
    auto tmpf = tmpfile();
    std::vector<int> v;
    for (int i = 0; i <= 123456; i++) {
        v.push_back(i);
        v.push_back(-i);
    }

    for (auto x : v) {
        fputs((std::to_string(x) + "\r\n").c_str(), tmpf);
    }
    rewind(tmpf);

    Scanner sc(tmpf);
    int y;
    for (auto x : v) {
        sc.read(y);
        ASSERT_EQ(x, y);
    }
}

TEST(FastIOTest, ScannerIntMin) {
    {
        auto tmpf = tmpfile();
        fputs("-2147483648", tmpf);
        rewind(tmpf);
        Scanner sc(tmpf);
        int32_t x;
        sc.read(x);
        ASSERT_EQ(std::numeric_limits<int32_t>::min(), x);
    }
    {
        auto tmpf = tmpfile();
        fputs("-9223372036854775808", tmpf);
        rewind(tmpf);
        Scanner sc(tmpf);
        int64_t x;
        sc.read(x);
        ASSERT_EQ(std::numeric_limits<int64_t>::min(), x);
    }
}

TEST(FastIOTest, ScannerPreSpace) {
    auto tmpf = tmpfile();
    fputs(" 1234", tmpf);
    rewind(tmpf);
    Scanner sc(tmpf);
    int x;
    sc.read(x);
    ASSERT_EQ(1234, x);
}

TEST(FastIOTest, PrinterInt) {
    auto tmpf = tmpfile();
    std::vector<int> v;
    for (int i = 0; i <= 123456; i++) {
        v.push_back(i);
        v.push_back(-i);
        v.push_back(std::numeric_limits<int>::min() + i);
        v.push_back(std::numeric_limits<int>::max() - i);
    }

    Printer pr(tmpf);
    for (auto x : v) {
        pr.writeln(x);
    }
    pr.flush();

    rewind(tmpf);
    char buf[100];
    for (auto x : v) {
        fgets(buf, 100, tmpf);
        ASSERT_EQ(std::to_string(x) + "\n", std::string(buf));
    }
}

TEST(FastIOTest, PrinterUnsignedInt) {
    auto tmpf = tmpfile();
    std::vector<unsigned int> v;
    for (int i = 0; i < 100; i++) {
        v.push_back(i);
        v.push_back(std::numeric_limits<unsigned int>::max() - i);
    }
    for (int i = 1; i <= 9; i++) {
        unsigned int x = 1;
        for (int j = 0; j < i; j++) {
            x *= 10;
        }
        for (int j = -10; j < 10; j++) {
            v.push_back(x + j);
        }
    }

    Printer pr(tmpf);
    for (auto x : v) {
        pr.writeln(x);
    }
    pr.flush();

    rewind(tmpf);
    char buf[100];
    for (auto x : v) {
        fgets(buf, 100, tmpf);
        ASSERT_EQ(std::to_string(x) + "\n", std::string(buf));
    }
}

TEST(FastIOTest, PrinterLongLong) {
    auto tmpf = tmpfile();
    std::vector<long long> v;    
    for (int i = 0; i <= 123456; i++) {
        v.push_back(i);
        v.push_back(-i);
        v.push_back(std::numeric_limits<long long>::min() + i);
        v.push_back(std::numeric_limits<long long>::max() - i);
    }
    for (int i = 0; i < 18; i++) {
        long long x = 1;
        for (int j = 0; j < i; j++) {
            x *= 10;
        }
        for (int j = -10; j < 10; j++) {
            v.push_back(x + j);
        }
    }

    Printer pr(tmpf);
    for (auto x : v) {
        pr.writeln(x);
    }
    pr.flush();

    rewind(tmpf);
    char buf[100];
    for (auto x : v) {
        fgets(buf, 100, tmpf);
        ASSERT_EQ(std::to_string(x) + "\n", std::string(buf));
    }
}

TEST(FastIOTest, PrinterUnsignedLongLong) {
    auto tmpf = tmpfile();
    std::vector<unsigned long long> v;
    for (int i = 0; i <= 123456; i++) {
        v.push_back(i);
        v.push_back(std::numeric_limits<unsigned long long>::max() - i);
    }

    for (int i = 1; i <= 19; i++) {
        unsigned long long x = 1;
        for (int j = 0; j < i; j++) {
            x *= 10;
        }
        for (int j = -10; j < 10; j++) {
            v.push_back(x + j);
        }
    }

    Printer pr(tmpf);
    for (auto x : v) {
        pr.writeln(x);
    }
    pr.flush();

    rewind(tmpf);
    char buf[100];
    for (auto x : v) {
        fgets(buf, 100, tmpf);
        ASSERT_EQ(std::to_string(x) + "\n", std::string(buf));
    }
}

TEST(FastIOTest, ScannerPrinterInt128) {
    std::vector<__int128> v;
    for (int i = 0; i < 1000; i++) {
        v.push_back(i);
        v.push_back(-i);
    }

    v.push_back(__int128(1) * 1234567890 * 1234567890 * 1234567890);

    auto tmpf = tmpfile();
    Printer pr(tmpf);

    for (auto x : v) {
        pr.writeln(x);
    }
    pr.flush();

    rewind(tmpf);

    Scanner sc(tmpf);
    for (auto x : v) {
        __int128 y;
        sc.read(y);
        ASSERT_EQ(x, y);
    }
}

TEST(FastIOTest, DecimalBlocksAndRefills) {
    for (int offset = 0; offset < 64; offset++) {
        auto fp = tmpfile();
        std::string input((1 << 15) - 64 + offset, ' ');
        std::vector<unsigned long long> values;
        unsigned long long power = 1;
        for (int digits = 1; digits <= 19; digits++) {
            values.push_back(power - 1);
            values.push_back(power);
            values.push_back(power + 1);
            power *= 10;
        }
        values.push_back(std::numeric_limits<unsigned long long>::max());
        for (auto value : values) input += std::to_string(value) + " ";
        input.pop_back();
        fputs(input.c_str(), fp);
        rewind(fp);
        {
            Scanner sc(fp);
            for (auto expected : values) {
                unsigned long long actual;
                sc.read(actual);
                ASSERT_EQ(expected, actual) << "offset=" << offset;
            }
        }
        fclose(fp);
    }
}

TEST(FastIOTest, MappedPageAlignedEnd) {
    auto fp = tmpfile();
    std::string value = "18446744073709551615";
    std::string input(4096 - value.size(), ' ');
    input += value;
    fputs(input.c_str(), fp);
    rewind(fp);
    {
        Scanner sc(fp);
        unsigned long long actual;
        sc.read(actual);
        EXPECT_EQ(actual, std::numeric_limits<unsigned long long>::max());
    }
    fclose(fp);
}

TEST(FastIOTest, Int128Extrema) {
    auto fp = tmpfile();
    unsigned __int128 umax = ~static_cast<unsigned __int128>(0);
    __int128 smax = static_cast<__int128>(umax >> 1);
    __int128 smin = -smax - 1;
    {
        Printer pr(fp);
        pr.writeln(umax);
        pr.writeln(smax);
        pr.write(smin);
    }
    rewind(fp);
    {
        Scanner sc(fp);
        unsigned __int128 u;
        __int128 positive, negative;
        sc.read(u, positive, negative);
        EXPECT_EQ(u, umax);
        EXPECT_EQ(positive, smax);
        EXPECT_EQ(negative, smin);
    }
    fclose(fp);
}

TEST(FastIOTest, PipeSplitTokens) {
    int descriptors[2];
    ASSERT_EQ(pipe(descriptors), 0);
    FILE* fp = fdopen(descriptors[0], "r");
    ASSERT_NE(fp, nullptr);
    std::thread writer([fd = descriptors[1]] {
        const std::string input = " \r\n-9223372036854775808\t18446744073709551615 12345678901234567890123456789012345678";
        for (char c : input) {
            if (::write(fd, &c, 1) != 1) break;
        }
        close(fd);
    });
    {
        Scanner sc(fp);
        long long a;
        unsigned long long b;
        __int128 c;
        sc.read(a, b, c);
        EXPECT_EQ(a, std::numeric_limits<long long>::min());
        EXPECT_EQ(b, std::numeric_limits<unsigned long long>::max());
        EXPECT_EQ(c, static_cast<__int128>(1234567890123456789LL) *
                     10000000000000000000ULL + 123456789012345678ULL);
    }
    writer.join();
    fclose(fp);
}

TEST(FastIOStrings, MappedAndBufferedRoundTrip) {
    const std::vector<std::string> values = {"a", std::string(65535, 'b'),
                                             std::string(65536, 'c'),
                                             std::string(131073, 'd'), "last"};
    FILE *fp = tmpfile();
    ASSERT_NE(fp, nullptr);
    {
        Printer pr(fp);
        for (const auto &x : values)
            pr.writeln(x);
    }
    rewind(fp);
    {
        Scanner sc(fp);
        for (const auto &expected : values) {
            std::string actual;
            sc.read(actual);
            EXPECT_EQ(actual, expected);
        }
    }
    fclose(fp);
}
TEST(FastIOStrings, PipeBoundaryAndNumericSuffix) {
    int fds[2];
    ASSERT_EQ(pipe(fds), 0);
    FILE *fp = fdopen(fds[0], "r");
    ASSERT_NE(fp, nullptr);
    const std::string token(196609, 'q');
    std::thread writer([&] {
        std::string input = token + "\r\n-42 z";
        std::size_t at = 0;
        while (at < input.size()) {
            auto n = ::write(fds[1], input.data() + at,
                             std::min(std::size_t(997), input.size() - at));
            if (n <= 0)
                break;
            at += n;
        }
        close(fds[1]);
    });
    {
        Scanner sc(fp);
        std::string a, b;
        int n;
        sc.read(a, n, b);
        EXPECT_EQ(a, token);
        EXPECT_EQ(n, -42);
        EXPECT_EQ(b, "z");
    }
    writer.join();
    fclose(fp);
}
TEST(FastIOStrings, PageAlignedNoNewline) {
    FILE *fp = tmpfile();
    ASSERT_NE(fp, nullptr);
    std::string token(8192, 'x');
    ASSERT_EQ(fwrite(token.data(), 1, token.size(), fp), token.size());
    rewind(fp);
    {
        Scanner sc(fp);
        std::string result;
        sc.read(result);
        EXPECT_EQ(result, token);
    }
    fclose(fp);
}
