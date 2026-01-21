#pragma once

#include <algorithm>
#include <cstdint>
#include <string>
#include <iostream>
#include <type_traits>

using u8 = uint8_t;
using i8 = int8_t;
using u16 = uint16_t;
using i16 = int16_t;
using u32 = uint32_t;
using i32 = int32_t;
using u64 = uint64_t;
using i64 = int64_t;
using __u128 = __uint128_t;
using __i128 = __int128_t;

std::ostream &operator<<(std::ostream &out, __u128 x) {
	if (x == 0) {
		out << "0";
		return out;
	}
	std::string _o;
	while (x != 0) {
		_o += char((x % 10) | 48);
		x /= 10;
	}
	std::reverse(_o.begin(), _o.end());
	out << _o;
	return out;
}
std::ostream &operator<<(std::ostream &out, __i128 x) {
	if (x < 0) {
		out << "-";
		x *= -1;
	}
	out << static_cast<__u128>(x);
	return out;
}

namespace i128 {
	// type traits
	template<class T> struct make_unsigned {
		using type = std::make_unsigned_t<T>;
	};
	template<> struct make_unsigned<__int128_t> {
		using type = __uint128_t;
	};
	template<class T> using make_unsigned_t = typename make_unsigned<T>::type;
	template<class T> struct make_signed {
		using type = std::make_signed_t<T>;
	};
	template<> struct make_signed<__uint128_t> {
		using type = __int128_t;
	};
	template<class T> using make_signed_t = typename make_signed<T>::type;
	template<class T> struct up {
		using type = void;
	};
	template<> struct up<u8> {
		using type = u16;
	};
	template<> struct up<u16> {
		using type = u32;
	};
	template<> struct up<u32> {
		using type = u64;
	};
	template<> struct up<u64> {
		using type = __u128;
	};
	template<> struct up<i8> {
		using type = i16;
	};
	template<> struct up<i16> {
		using type = i32;
	};
	template<> struct up<i32> {
		using type = i64;
	};
	template<> struct up<i64> {
		using type = __i128;
	};
	template<class T> using up_t = typename up<T>::type;
}

template<class T, class U> T qpow(T x, U y, const T &mul_iden = 1) {
	T ret = mul_iden;
	while (y) {
		if (y & 1) {
			ret *= x;
		}
		x *= x;
		y >>= 1;
	}
	return ret;
}

#define __func_str__ static_cast<std::string>(__func__)