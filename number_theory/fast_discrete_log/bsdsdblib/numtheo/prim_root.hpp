#pragma once

#include <numeric>
#include <optional>
#include <vector>

#include "../basics.hpp"
#include "pollard_rho.hpp"
#include "prod_funcs.hpp"

namespace numtheo_n {
	bool is_prim_root(u64 x, u64 m, u64 phim, const std::vector<std::pair<u64, u32>> &phim_fact) {
		if (std::gcd(x, m) != 1) {
			return false;
		}
		struct modm {
			u64 val, _mod;
			modm &operator*=(modm _x) {
				val = static_cast<u64>(static_cast<__uint128_t>(val) * _x.val % _mod);
				return *this;
			}
		};
		for (auto i : phim_fact) {
			if (qpow(modm{x, m}, phim / i.first, modm{1, m}).val == 1) {
				return false;
			}
		}
		return true;
	}
	bool is_prim_root(u64 x, u64 m) { return is_prim_root(x, m, phi(m), prime_factors(phi(m))); }
	std::optional<u64> min_prim_root(
		u64 m, u64 phim, const std::vector<std::pair<u64, u32>> &phim_fact
	) {
		if (m == 2) {
			return 1;
		}
		if (m == 4) {
			return 3;
		}
		// check
		u64 _m = m;
		if (!(_m & 1)) {
			_m /= 2;
		}
		if (!(_m & 1) || prime_factors(_m).size() != 1) {
			return std::nullopt;
		}
		// calculate
		for (u64 i = 1;; ++i) {
			if (is_prim_root(i, m, phim, phim_fact)) {
				return i;
			}
		}
	}
	std::optional<u64> min_prim_root(u64 m) {
		return min_prim_root(m, phi(m), prime_factors(phi(m)));
	}
	std::vector<u64> prim_roots(u64 m) {
		if (m == 2) {
			return {1};
		}
		if (m == 4) {
			return {3};
		}
		u64 phim = phi(m);
		auto phim_fact = prime_factors(phim);
		std::optional<u64> min_pr = min_prim_root(m, phim, phim_fact);
		if (min_pr.has_value() == false) {
			return std::vector<u64>();
		}
		std::vector<u64> ret;
		u64 g_to_k = 1;
		for (u64 k = 1; k <= phim; ++k) {
			g_to_k = g_to_k * min_pr.value() % m;
			if (std::gcd(k, phim) == 1) {
				ret.emplace_back(g_to_k);
			}
		}
		std::sort(ret.begin(), ret.end());
		return ret;
	}
}