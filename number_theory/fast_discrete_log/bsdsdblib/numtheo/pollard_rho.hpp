#pragma once

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

#include "../basics.hpp"
#include "modint.hpp"

namespace numtheo {
	template<class T> bool miller_rabin(T x) {
		using MI = ModInt<modint_inner + 3, std::is_same_v<T, u64>>; // mod : x
		MI::set_mod(x);
		if (x == 1) {
			return false;
		}
		if (!(x & 1)) {
			return x == 2;
		}
		T t = (std::is_same_v<T, u64> ? __builtin_ctzll(x - 1) : __builtin_ctz(x - 1)), u = (x - 1) >> t;
		std::vector<T> a_list;
		if (std::is_same_v<T, u64>) {
			a_list = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
		} else {
			a_list = {2, 7, 61};
		}
		for (T a : a_list) {
			a %= x;
			if (a == 0) {
				continue;
			}
			if (std::gcd(a, x) != 1) {
				return false;
			}
			MI v = qpow(MI(a, false), u, MI(1, false));
			if (v.value() == 1) {
				continue;
			}
			bool nfound = false;
			for (u32 s = 0; s < t; ++s) {
				if (v.value() == x - 1) {
					nfound = true;
					break;
				}
				v *= v;
			}
			if (nfound == false) {
				return false;
			}
		}
		return true;
	}
	template<class T> T pollard_rho(T x) {
		using MI = ModInt<modint_inner + 4, std::is_same_v<T, u64>>; // mod : x
		MI::set_mod(x);
		if (!(x & 1)) {
			return 2;
		}
		MI c;
		std::conditional_t<std::is_same_v<T, u64>, std::mt19937_64, std::mt19937> rndc(std::random_device{}());
		while (true) {
			c = MI(rndc() % (x - 1) + 1, false);
			auto f = [c, x](MI _x)->MI {
				return _x * _x + c;
			};
			MI s = MI(0, false), t = MI(0, false), prod = MI(1, false);
			for (u32 k = 1;; ++k) {
				u32 counter = 0;
				for (u32 step = 0; !(step >> k); ++step) {
					t = f(t);
					prod *= s - t;
					++counter;
					if (counter == 128) {
						T g = std::gcd(prod.value(), x);
						if (g == x) {
							goto newc;
						}
						if (g != 1) {
							return g;
						}
						counter = 0;
					}
				}
				T g = std::gcd(prod.value(), x);
				if (g == x) {
					goto newc;
				}
				if (g != 1) {
					return g;
				}
				s = t;
			}
			newc:;
		}
	}
	template<class T> void prime_factors(T x, std::vector<T> &ret) {
		if (x <= 1) {
			return;
		}
		if (miller_rabin(x)) {
			ret.emplace_back(x);
			return;
		}
		T fact = pollard_rho(x);
		prime_factors(fact, ret);
		prime_factors(x / fact, ret);
		return;
	}
	template<class T> std::vector<std::pair<T, u32>> prime_factors(T x) {
		std::vector<T> ret1;
		prime_factors(x, ret1);
		std::sort(ret1.begin(), ret1.end());
		std::vector<std::pair<T, u32>> ret;
		for (T i : ret1) {
			if (ret.empty() || i != ret.back().first) {
				ret.emplace_back(i, 1);
			} else {
				++ret.back().second;
			}
		}
		return ret;
	}
}
