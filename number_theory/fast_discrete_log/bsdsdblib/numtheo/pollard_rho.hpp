#pragma once

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

#include "../basics.hpp"

namespace numtheo_n {
	bool miller_rabin(u64 x) {
		if (!(x & 1)) {
			return x == 2;
		}
		u64 t = __builtin_ctzll(x - 1), u = (x - 1) >> t;
		struct modx {
			u64 val, _mod;
			modx &operator*=(modx _x) {
				val = static_cast<u64>(static_cast<__uint128_t>(val) * _x.val % _mod);
				return *this;
			}
		};
		for (u64 a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
			a %= x;
			if (a == 0) {
				continue;
			}
			if (std::gcd(a, x) != 1) {
				return false;
			}
			modx v = qpow(modx{a, x}, u, modx{1, x});
			if (v.val == 1) {
				continue;
			}
			bool nfound = false;
			for (u32 s = 0; s < t; ++s) {
				if (v.val == x - 1) {
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
	u64 pollard_rho(u64 x) {
		if (!(x & 1)) {
			return 2;
		}
		u64 c;
		std::mt19937_64 rndc(std::random_device{}());
		while (true) {
			c = rndc() % (x - 1) + 1;
			auto f = [c, x](u64 _x)->u64 {
				return static_cast<u64>((static_cast<__uint128_t>(_x) * _x + c) % x);
			};
			u64 s = 0, t = 0, prod = 1;
			for (u32 k = 1;; ++k) {
				u32 counter = 0;
				for (u32 step = 0; !(step >> k); ++step) {
					t = f(t);
					prod = static_cast<u64>(
						(static_cast<__uint128_t>(prod)
						* (s < t ? t - s : s - t)) % x
					);
					++counter;
					if (counter == 128) {
						u64 g = std::gcd(prod, x);
						if (g == x) {
							goto newc;
						}
						if (g != 1) {
							return g;
						}
						counter = 0;
					}
				}
				u64 g = std::gcd(prod, x);
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
	void prime_factors(u64 x, std::vector<u64> &ret) {
		if (x <= 1) {
			return;
		}
		if (miller_rabin(x)) {
			ret.emplace_back(x);
			return;
		}
		u64 fact = pollard_rho(x);
		prime_factors(fact, ret);
		prime_factors(x / fact, ret);
		return;
	}
	std::vector<std::pair<u64, u32>> prime_factors(u64 x) {
		std::vector<u64> ret1;
		prime_factors(x, ret1);
		std::sort(ret1.begin(), ret1.end());
		std::vector<std::pair<u64, u32>> ret;
		for (u64 i : ret1) {
			if (ret.empty() || i != ret.back().first) {
				ret.emplace_back(i, 1);
			} else {
				++ret.back().second;
			}
		}
		return ret;
	}
}