#pragma once

#include <cstdint>

using u32 = uint32_t;
using i32 = int32_t;
using u64 = uint64_t;
using i64 = int64_t;

template<class T> T qpow(T x, u64 y, const T &mul_iden = 1) {
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