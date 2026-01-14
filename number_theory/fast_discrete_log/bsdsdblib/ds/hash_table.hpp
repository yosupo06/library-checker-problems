#pragma once

#include <array>
#include <bitset>
#include <random>

#include "../basics.hpp"

namespace ds {
	const u64 hash_rnum = 0x137891695f3759df;
	u64 hash64(u64 x) {
		x ^= (x >> 31);
		x *= (hash_rnum ^ 1145141919810);
		x ^= (x << 29);
		x *= (hash_rnum ^ 0x1145141919810);
		x ^= (x >> 23);
		x *= (x ^ hash_rnum);
		x ^= (x << 37);
		return x;
	}
	template<class T> u64 hash(T x) {
		if (std::is_same_v<T, __u128>) {
			return hash64(static_cast<u64>(x)) ^ hash64(static_cast<u64>(x >> 64));
		} else {
			return hash64(x);
		}
	}
	template<class key_t, class val_t, u32 N = 4194304> class hash_table {
	private:
		u32 _size;
		std::bitset<N> occupied;
		std::vector<key_t> key;
		std::vector<val_t> val;
		u32 id(u64 x) const {
			return (x & (N - 1));
		}
		u32 key_pos(key_t k) const {
			u32 ret = id(hash(k));
			while (occupied[ret] && key[ret] != k) {
				ret = ((ret + 1) & (N - 1));
			}
			return ret;
		}
	public:
		hash_table() : key(N), val(N) {}
		u32 size() const {
			return _size;
		}
		bool exists(key_t k) const {
			return key[key_pos(k)] == k;
		}
		val_t &operator[](key_t k) {
			u32 ind = key_pos(k);
			if (occupied[ind] == false) {
				occupied[ind] = true;
				++_size;
			}
			key[ind] = k;
			return val[ind];
		}
	};
}