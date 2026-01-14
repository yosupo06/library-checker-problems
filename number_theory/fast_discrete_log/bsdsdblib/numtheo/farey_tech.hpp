#pragma once

#include <cmath>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

#include "../basics.hpp"
#include "dis_log.hpp"
#include "euler_sieve.hpp"
#include "modint.hpp"

namespace farey_tech_hpp {
	template<i64 P, bool _64> struct aux {
		using val_t = std::conditional_t<_64, u64, u32>;
		inline static u32 cbrt_log, cbrt, cbrt2;
		inline static bool enable = false;
		inline static std::vector<std::pair<u32, u32>> far, pre, suc;
		static void preproc() {
			using MIP = numtheo::ModIntPr<P, _64>;
			if (enable == true) {
				return;
			}
			enable = true;
			cbrt_log = (31 ^ __builtin_clz(static_cast<u32>(std::cbrt(MIP::mod()) + 1))) + 1;
			cbrt = 1 << cbrt_log, cbrt2 = 1 << (cbrt_log << 1);
			far.assign(cbrt2 + 1, std::make_pair(0, 0));
			for (u32 p = 0; p <= cbrt; ++p) {
				for (u32 q = (p == 1 ? 1 : p + 1); q <= cbrt; ++q) {
					u32 cur = static_cast<u32>((static_cast<u64>(p) << (aux::cbrt_log << 1)) / q);
					if (aux::far[cur].second == 0) {
						aux::far[cur] = std::make_pair(p, q);
					}
				}
			}
			pre = far;
			for (auto it = pre.begin(); it != pre.end(); ++it) {
				if (it->second == 0) {
					*it = *std::prev(it);
				}
			}
			suc = far;
			for (auto it = std::prev(suc.end()); it != std::prev(suc.begin()); --it) {
				if (it->second == 0) {
					*it = *std::next(it);
				}
			}
		}
		static std::pair<u32, i32> get(val_t x) {
			using MIP = numtheo::ModIntPr<P, _64>;
			u32 cur = static_cast<u32>((static_cast<u64>(x) << (cbrt_log << 1)) / MIP::mod());
			u32 q;
			i32 t = static_cast<i32>(static_cast<i64>(x) * pre[cur].second - static_cast<i64>(MIP::mod()) * pre[cur].first);
			if (static_cast<u32>(std::abs(t)) <= cbrt2) {
				q = pre[cur].second;
			} else {
				q = suc[cur].second;
				t = static_cast<i32>(static_cast<i64>(x) * q - static_cast<i64>(MIP::mod()) * suc[cur].first);
			}
			return std::make_pair(q, t);
		}
		inline static std::vector<numtheo::ModIntPr<P, _64>> inv_v;
		inline static std::vector<val_t> ln_table;
		inline static numtheo::ModIntPr<P, _64> g;
	};
}

namespace numtheo {
	template<i64 P, bool _64> void fast_ln_preproc(ModIntPr<P, _64> g) {
		using MIP = ModIntPr<P, _64>;
		using aux = farey_tech_hpp::aux<P, _64>;
		aux::preproc();
		aux::g = g;
		// ln for <=sqrt primes
		aux::ln_table.resize(aux::cbrt2 + 1);
		u32 sqrtP = static_cast<u32>(std::sqrt(MIP::mod())) + 2;
		euler_sieve(sqrtP);
		std::vector<MIP> pr;
		for (u32 i : primes) {
			if (i <= sqrtP) {
				pr.emplace_back(i);
			} else {
				break;
			}
		}
		auto prln = dis_logs(g, pr);
		for (u32 i = 0; i < pr.size(); ++i) {
			if (prln[i].has_value() == false) {
				throw std::invalid_argument(__func_str__ + " : g is not a primitive root");
			}
			aux::ln_table[primes[i]] = prln[i].value();
		}
		aux::ln_table[1] = 0;
		// ln for <=sqrt
		for (u32 i = 4; i <= sqrtP; ++i) {
			if (mpf[i] == i) {
				continue;
			}
			aux::ln_table[i] = aux::ln_table[mpf[i]] + aux::ln_table[i / mpf[i]];
			if (aux::ln_table[i] >= MIP::mod() - 1) {
				aux::ln_table[i] -= MIP::mod() - 1;
			}
		}
		// ln for <=cbrt2
		for (u32 i = sqrtP + 1; i <= aux::cbrt2; ++i) {
			u32 k = MIP::mod() / i, r = MIP::mod() % i;
			aux::ln_table[i] = static_cast<typename MIP::val_t>((static_cast<u64>((MIP::mod() - 1) >> 1) + aux::ln_table[r] + (MIP::mod() - 1) - aux::ln_table[k]) % (MIP::mod() - 1));
		}
	}
	template<i64 P, bool _64> std::conditional_t<_64, u64, u32> fast_dis_ln(ModIntPr<P, _64> x) {
		using MIP = ModIntPr<P, _64>;
		using aux = farey_tech_hpp::aux<P, _64>;
		auto [q, t] = aux::get(x.value());
		return static_cast<typename MIP::val_t>((static_cast<u64>(t > 0 ? aux::ln_table[t] : ((MIP::mod() - 1) >> 1) + aux::ln_table[-t]) + (MIP::mod() - 1) - aux::ln_table[q]) % (MIP::mod() - 1));
	}
}
