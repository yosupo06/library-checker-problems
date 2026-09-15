#pragma once

#include <unistd.h>
#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <cctype>
#include <cstring>
#include <cstdint>
#include <cerrno>
#include <cstdlib>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/mman.h>
#include <sys/stat.h>
#endif
#if defined(__SSSE3__)
#include <tmmintrin.h>
#endif
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

    Scanner(FILE* fp) : fd(fileno(fp)) {
#if defined(__unix__) || defined(__APPLE__)
        struct stat info {};
        off_t offset = ::lseek(fd, 0, SEEK_CUR);
        if (offset >= 0 && ::fstat(fd, &info) == 0 && S_ISREG(info.st_mode) &&
            info.st_size > offset) {
            mapping_size = size_t(info.st_size);
            void* address = ::mmap(nullptr, mapping_size, PROT_READ, MAP_PRIVATE, fd, 0);
            if (address != MAP_FAILED) {
                mapping = static_cast<const char*>(address);
                current = mapping + offset;
                end = mapping + mapping_size;
                eof = true;
            }
        }
#endif
    }
    ~Scanner() {
#if defined(__unix__) || defined(__APPLE__)
        if (mapping) ::munmap(const_cast<char*>(mapping), mapping_size);
#endif
    }

    void read() {}
    template <class H, class... T> void read(H& h, T&... t) {
        bool ok = read_single(h);
        assert(ok);
        (void)ok;
        read(t...);
    }

  private:
    static constexpr size_t BUF_SIZE = 1 << 16;
    int fd;
    std::array<char, BUF_SIZE + 64> buffer{};
    const char* current = buffer.data();
    const char* end = buffer.data();
    const char* mapping = nullptr;
    size_t mapping_size = 0;
    bool eof = false;

    // Mapped tails are copied before SIMD reads, including page-aligned EOF.
    void refill() {
        size_t remaining = size_t(end - current);
        std::memmove(buffer.data(), current, remaining);
#if defined(__unix__) || defined(__APPLE__)
        // The input is consumed before solve(); do not retain its resident pages.
        if (mapping) {
            ::munmap(const_cast<char*>(mapping), mapping_size);
            mapping = nullptr;
        }
#endif
        current = buffer.data();
        while (remaining < 64 && !eof) {
            ssize_t count;
            do {
                count = ::read(fd, buffer.data() + remaining, BUF_SIZE - remaining);
            } while (count < 0 && errno == EINTR);
            if (count < 0) std::abort();
            remaining += size_t(count);
            eof = count == 0;
        }
        end = buffer.data() + remaining;
        std::memset(buffer.data() + remaining, 0, 64);
    }

    bool prepare() {
        if (end - current < 64) refill();
        while (*current <= ' ') {
            if (current == end) return false;
            ++current;
            if (end - current < 64) refill();
        }
        return true;
    }

#if defined(__SSSE3__)
    alignas(16) inline static constexpr auto align_digits = [] {
        std::array<std::array<unsigned char, 16>, 16> table{};
        for (int n = 0; n < 16; ++n)
            for (int j = 0; j < 16; ++j)
                table[n][j] = j < 16 - n ? 128 : static_cast<unsigned char>(j - 16 + n);
        return table;
    }();

    static uint64_t decimal16(__m128i digits) {
        auto pairs = _mm_maddubs_epi16(digits, _mm_set1_epi16(0x010a));
        auto quads = _mm_madd_epi16(pairs, _mm_set1_epi32(0x00010064));
        auto octets = _mm_madd_epi16(_mm_packs_epi32(quads, _mm_setzero_si128()),
                                   _mm_set1_epi32(0x00012710));
        return uint64_t(uint32_t(_mm_cvtsi128_si32(octets))) * 100000000 +
               uint32_t(_mm_cvtsi128_si32(_mm_srli_si128(octets, 4)));
    }
#endif

    template <class U> U magnitude() {
        U value = 0;
#if defined(__SSSE3__)
        while (true) {
            auto digits = _mm_sub_epi8(_mm_loadu_si128(
                reinterpret_cast<const __m128i*>(current)), _mm_set1_epi8('0'));
            unsigned mask = unsigned(_mm_movemask_epi8(digits));
            if (mask) {
                int length = __builtin_ctz(mask);
                digits = _mm_shuffle_epi8(digits, _mm_load_si128(
                    reinterpret_cast<const __m128i*>(align_digits[length].data())));
                static constexpr auto powers = [] {
                    std::array<uint64_t, 16> result{};
                    result[0] = 1;
                    for (int i = 1; i < 16; ++i) result[i] = result[i - 1] * 10;
                    return result;
                }();
                uint64_t scale = 1;
                // Only long integers need to append a second/third chunk.
                if constexpr (sizeof(U) > 4) {
                    if (value) {
                        scale = powers[length];
                        value *= scale;
                    }
                }
                value += U(decimal16(digits));
                current += length;
                return value;
            }
            value = value * U(10000000000000000ULL) + U(decimal16(digits));
            current += 16;
            if constexpr (sizeof(U) <= 8) {
                while (*current >= '0' && *current <= '9')
                    value = U(value * 10 + unsigned(*current++ - '0'));
                return value;
            }
        }
#else
        while (*current >= '0' && *current <= '9')
            value = U(value * 10 + unsigned(*current++ - '0'));
        return value;
#endif
    }

    bool read_single(std::string& value) {
        if (!prepare()) return false;
        value.clear();
        while (true) {
            const char* begin = current;
            while (current != end && *current > ' ') ++current;
            value.append(begin, size_t(current - begin));
            if (current != end) {
                ++current;
                if (mapping && end - current < 64) refill();
                return true;
            }
            if (eof) {
                if (mapping) refill();
                return true;
            }
            refill();
        }
    }

    template <class T> bool read_single(T& value) {
        if (!prepare()) return false;
        if constexpr (std::is_signed_v<T> || std::is_same_v<T, __int128>) {
            bool negative = *current == '-';
            current += negative;
            auto x = magnitude<make_unsigned_t<T>>();
            value = T(negative ? -x : x);
        } else {
            value = magnitude<T>();
        }
        if (current != end) ++current;
        return true;
    }
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
            size_t written = 0;
            while (written < pos) {
                auto count = ::write(fd, buf.data() + written, pos - written);
                if (count < 0 && errno == EINTR) continue;
                if (count <= 0) std::abort();
                written += size_t(count);
            }
            pos = 0;
        }
    }

  private:
    static std::array<std::array<char, 4>, 10000> groups;
    inline static const auto leading = [] {
        std::array<std::array<char, 4>, 10000> table{};
        for (int value = 0; value < 10000; ++value) {
            int length = 1 + (value >= 10) + (value >= 100) + (value >= 1000);
            int x = value;
            for (int i = length - 1; i >= 0; --i) {
                table[value][i] = char('0' + x % 10);
                x /= 10;
            }
        }
        return table;
    }();
    inline static const auto lengths = [] {
        std::array<unsigned char, 10000> table{};
        for (int value = 0; value < 10000; ++value)
            table[value] = static_cast<unsigned char>(1 + (value >= 10) + (value >= 100) + (value >= 1000));
        return table;
    }();
    static std::array<std::array<char, 2>, 100>
        small;                                       // small[i] = to_string(i)
    static std::array<unsigned long long, 20> tens;  // tens[i] = 10^i

    static constexpr size_t BUF_SIZE = 1 << 19;
    int fd;
    std::array<char, BUF_SIZE> buf;
    size_t pos = 0;  // buf[0..pos) is used

    void write_single(const std::string& value) {
        size_t copied = 0;
        while (copied < value.size()) {
            size_t count = std::min(value.size() - copied, BUF_SIZE - pos);
            std::memcpy(buf.data() + pos, value.data() + copied, count);
            copied += count;
            pos += count;
            if (pos == BUF_SIZE) flush();
        }
    }

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

    void padded4(uint32_t value) {
        std::memcpy(buf.data() + pos, groups[value].data(), 4);
        pos += 4;
    }
    void padded8(uint32_t value) {
        padded4(value / 10000);
        padded4(value % 10000);
    }
    void leading4(uint32_t value) {
        std::memcpy(buf.data() + pos, leading[value].data(), 4);
        pos += lengths[value];
    }
    void leading8(uint32_t value) {
        if (value >= 10000) {
            leading4(value / 10000);
            padded4(value % 10000);
        } else {
            leading4(value);
        }
    }
    template <class U, std::enable_if_t<8 >= sizeof(U)>* = nullptr>
    void write_unsigned_internal(U value) {
        if constexpr (sizeof(U) > 4) {
            if (value >= 10000000000000000ULL) {
                leading8(uint32_t(value / 10000000000000000ULL));
                padded8(uint32_t(value / 100000000 % 100000000));
                padded8(uint32_t(value % 100000000));
                return;
            }
        }
        if (value >= 100000000) {
            leading8(uint32_t(value / 100000000));
            padded8(uint32_t(value % 100000000));
        } else {
            leading8(uint32_t(value));
        }
    }
    template <class U, std::enable_if_t<16 == sizeof(U)>* = nullptr>
    void write_unsigned_internal(U value) {
        if (value <= UINT64_MAX) {
            write_unsigned_internal(uint64_t(value));
            return;
        }
        constexpr uint64_t base = 10000000000000000ULL;
        U high = value / base;
        uint64_t low = uint64_t(value % base);
        if (high > UINT64_MAX) {
            write_unsigned_internal(uint64_t(high / base));
            uint64_t middle = uint64_t(high % base);
            padded8(uint32_t(middle / 100000000));
            padded8(uint32_t(middle % 100000000));
        } else {
            write_unsigned_internal(uint64_t(high));
        }
        padded8(uint32_t(low / 100000000));
        padded8(uint32_t(low % 100000000));
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

std::array<std::array<char, 4>, 10000> Printer::groups = [] {
    std::array<std::array<char, 4>, 10000> table{};
    for (int i = 0; i < 10000; i++) {
        int v = i;
        for (int j = 3; j >= 0; j--) {
            table[i][j] = char('0' + v % 10);
            v /= 10;
        }
    }
    return table;
}();
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
