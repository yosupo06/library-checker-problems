#pragma once
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdint>
#include <type_traits>

struct FastI {
	char buf[1000000];
	char *ptr = buf, *end = buf;
	void read_() { end = (ptr = buf) + fread(buf, 1, sizeof(buf) - 1, stdin); }
	void inc() { if (++ptr == end) read_(); }
	template<typename value_t> value_t read() {
		if (ptr == end) read_();
		bool neg = false;
		value_t res = 0;
		while ((*ptr < '0' || *ptr > '9') && *ptr != '-') inc();
		if (*ptr == '-') neg = true, inc();
		while (*ptr >= '0' && *ptr <= '9') res = res * 10 + *ptr - '0', inc();
		return neg ? -res : res;
	}
} fasti;
#define ri fasti.read<int>
#define rs64 fasti.read<int64_t>

struct FastO {
	char buf[1000000];
	char *ptr = buf;
	void write_() { fwrite(buf, 1, ptr - buf, stdout); ptr = buf; }
	~FastO () { write_(); }
	void print(char c) { *ptr = c; if (++ptr == std::end(buf)) write_(); }
	void print(const std::string &s) { for (auto c : s) print(c); }
	template<typename str_t> auto print(str_t s) -> decltype(std::string(s), void()) { print(std::string(s)); }
	template<typename value_t> typename std::enable_if_t<std::is_integral<value_t>::value> print(value_t val) {
		static char tmp_buf[32];
		if (val < 0) print('-'), val = -val;
		char *head = std::end(tmp_buf);
		if (val == 0) *--head = '0';
		else while (val) *--head = '0' + val % 10, val /= 10;
		int size = std::end(tmp_buf) - head;
		if (std::end(buf) - ptr <= size) write_();
		memcpy(ptr, head, size);
		ptr += size;
	}
	template<typename A, typename... B> void print(A a, B... b) { print(a); print(b...); }
	template<typename... A> void println(A... a) { print(a..., '\n'); }
} fasto;
#define print fasto.print
#define println fasto.println
