#pragma once

#include <unistd.h>
#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <cctype>
#include <cstring>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

namespace library_checker {

template <class T> struct make_unsigned {
    using type = std::make_unsigned_t<T>;
};

template <> struct make_unsigned<__int128> {
    using type = unsigned __int128;
};

template <class T> using make_unsigned_t = typename make_unsigned<T>::type;

// TODO: migrate to std::bit after C++20
int countl_zero(unsigned int n) { return __builtin_clz(n); }
int countl_zero(unsigned long n) { return __builtin_clzl(n); }
int countl_zero(unsigned long long n) { return __builtin_clzll(n); }

struct Scanner {
  public:
    Scanner(const Scanner&) = delete;
    Scanner& operator=(const Scanner&) = delete;

    Scanner(FILE* fp) : fd(fileno(fp)) { buf[0] = 127; }

    void read() {}
    template <class H, class... T> void read(H& h, T&... t) {
        bool f = read_single(h);
        assert(f);
        read(t...);
    }

  private:
    bool read_single(int& v) { return read_signed(v); }
    bool read_single(long& v) { return read_signed(v); }
    bool read_single(long long& v) { return read_signed(v); }
    bool read_single(__int128& v) { return read_signed(v); }

    bool read_single(unsigned int& v) { return read_unsigned(v); }
    bool read_single(unsigned long& v) { return read_unsigned(v); }
    bool read_single(unsigned long long& v) { return read_unsigned(v); }
    bool read_single(unsigned __int128& v) { return read_unsigned(v); }

    static constexpr int BUF_SIZE = 1 << 15;

    int fd;  // file descriptor
    std::array<char, BUF_SIZE + 1> buf;
    int st = 0, ed = 0;  // available range of buf. buf[ed] must be 127.
    bool eof = false;

    template <class T> bool read_signed(T& v) {
        if (!skip_blanks<50>()) return false;

        bool neg = false;
        if (buf[st] == '-') {
            neg = true;
            st++;
        }

        make_unsigned_t<T> v2;
        read_unsigned_internal(v2);
        v = (neg) ? -v2 : v2;

        return true;
    }

    template <class T> bool read_unsigned(T& v) {
        if (!skip_blanks<50>()) return false;

        read_unsigned_internal(v);

        return true;
    }

    template <class T> void read_unsigned_internal(T& v) {
        v = 0;
        do {
            v = 10 * v + (buf[st++] & 0x0f);
        } while (is_digit(buf[st]));
    }

    void read_input() {
        assert(!eof);

        std::memmove(buf.data(), buf.data() + st, ed - st);
        ed -= st;
        st = 0;

        int u = int(::read(fd, buf.data() + ed, BUF_SIZE - ed));
        if (u == 0) {
            eof = true;
            buf[ed] = '\0';
            ed++;
        }
        ed += u;

        buf[ed] = 127;
    }

    // skip blanks and assume next token is in buffer
    template <int MAX_TOKEN_LEN> bool skip_blanks() {
        while (true) {
            while (is_blank(buf[st])) st++;
            if (ed - st > MAX_TOKEN_LEN) return true;
            // std::cerr << st << " " << ed << " " << eof << std::endl;
            if (eof) return (st < ed);
            read_input();
        }
    }

    static bool is_blank(char c) { return c <= ' '; }
    static bool is_digit(char c) { return c >= '0'; }
};

struct Printer {
  public:
    Printer(const Printer&) = delete;
    Printer& operator=(const Printer&) = delete;

    Printer(FILE* _fp) : fd(fileno(_fp)) {}
    ~Printer() { flush(); }

    void write() {}
    template <class H, class... T> void write(const H& h, const T&... t) {
        write_single(h);
        write(t...);
    }
    template <class... T> void writeln(const T&... t) {
        write(t...);
        write_single('\n');
    }

    void flush() {
        if (pos) {
            auto res = ::write(fd, buf.data(), pos);
            assert(res != -1);
            pos = 0;
        }
    }

  private:
    static std::array<std::array<char, 2>, 100>
        small;                                       // small[i] = to_string(i)
    static std::array<unsigned long long, 20> tens;  // tens[i] = 10^i

    static constexpr size_t BUF_SIZE = 1 << 15;
    int fd;
    std::array<char, BUF_SIZE> buf;
    size_t pos = 0;  // buf[0..pos) is used

    // char
    template <class T, std::enable_if_t<std::is_same_v<char, T>>* = nullptr>
    void write_single(const T& v) {
        if (pos == BUF_SIZE) flush();
        buf[pos++] = v;
    }

    // signed int
    template <class T, std::enable_if_t<std::is_same_v<int, T>>* = nullptr>
    void write_single(const T& v) {
        write_signed(v);
    }
    template <class T, std::enable_if_t<std::is_same_v<long, T>>* = nullptr>
    void write_single(const T& v) {
        write_signed(v);
    }
    template <class T,
              std::enable_if_t<std::is_same_v<long long, T>>* = nullptr>
    void write_single(const T& v) {
        write_signed(v);
    }
    template <class T, std::enable_if_t<std::is_same_v<__int128, T>>* = nullptr>
    void write_single(const T& v) {
        write_signed(v);
    }

    // unsigned int
    template <class T,
              std::enable_if_t<std::is_same_v<unsigned int, T>>* = nullptr>
    void write_single(const T& v) {
        write_unsigned(v);
    }
    template <class T,
              std::enable_if_t<std::is_same_v<unsigned long, T>>* = nullptr>
    void write_single(const T& v) {
        write_unsigned(v);
    }
    template <
        class T,
        std::enable_if_t<std::is_same_v<unsigned long long, T>>* = nullptr>
    void write_single(const T& v) {
        write_unsigned(v);
    }
    template <class T,
              std::enable_if_t<std::is_same_v<unsigned __int128, T>>* = nullptr>
    void write_single(const T& v) {
        write_unsigned(v);
    }

    template <class T> void write_signed(const T& v) {
        if (pos > BUF_SIZE - 50) flush();

        if (v == T(0)) {
            write_single('0');
            return;
        }

        make_unsigned_t<T> uv = v;
        if (v < 0) {
            write_single('-');
            uv = -uv;
        }

        write_unsigned_internal(uv);
    }

    template <class T> void write_unsigned(const T& v) {
        if (pos > BUF_SIZE - 50) flush();

        if (v == T(0)) {
            write_single('0');
            return;
        }

        write_unsigned_internal(v);
    }

    template <class U, std::enable_if_t<8 >= sizeof(U)>* = nullptr>
    void write_unsigned_internal(U v) {
        size_t len = to_string_size(v);
        pos += len;

        char* ptr = buf.data() + pos;
        while (v >= 100) {
            ptr -= 2;
            memcpy(ptr, small[v % 100].data(), 2);
            v /= 100;
        }
        if (v >= 10) {
            memcpy(ptr - 2, small[v].data(), 2);
        } else {
            *(ptr - 1) = char('0' + v);
        }
    }

    // TODO: optimize
    template <class U, std::enable_if_t<16 == sizeof(U)>* = nullptr>
    void write_unsigned_internal(U v) {
        static std::array<char, 50> buf2;

        size_t len = 0;
        while (v > 0) {
            buf2[len++] = char((v % 10) + '0');
            v /= 10;
        }
        std::reverse(buf2.begin(), buf2.begin() + len);
        memcpy(buf.data() + pos, buf2.data(), len);
        pos += len;
    }

    // to_string_size(v) = to_string(v).size()
    template <class U> int to_string_size(const U& v) {
        static_assert(sizeof(U) <= 8);
        int i = (int)((8 * sizeof(U) - 1 - countl_zero(v)) * 3 + 3) / 10;
        if (v < tens[i])
            return i;
        else
            return i + 1;
    }
};

std::array<std::array<char, 2>, 100> Printer::small = [] {
    std::array<std::array<char, 2>, 100> table;
    for (int i = 0; i <= 99; i++) {
        table[i][1] = char('0' + (i % 10));
        table[i][0] = char('0' + (i / 10 % 10));
    }
    return table;
}();
std::array<unsigned long long, 20> Printer::tens = [] {
    std::array<unsigned long long, 20> table;
    for (int i = 0; i < 20; i++) {
        table[i] = 1;
        for (int j = 0; j < i; j++) {
            table[i] *= 10;
        }
    }
    return table;
}();

}  // namespace library_checker
