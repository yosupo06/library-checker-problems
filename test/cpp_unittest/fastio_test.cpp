
#include <cstdint>
#include <string>

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
