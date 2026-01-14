#pragma once

#include <cmath>
#include <numeric>
#include <optional>
#include <vector>

#include "../basics.hpp"
#include "../ds/hash_table.hpp"
#include "modint.hpp"
#include "prod_funcs.hpp"

namespace numtheo {
	template<i64 P, bool _64>
	std::optional<std::conditional_t<_64, u64, u32>> dis_log(ModIntPr<P, _64> a, ModIntPr<P, _64> b) {
		using MIP = ModIntPr<P, _64>;
		using val_t = typename MIP::val_t;
		using mul_t = typename MIP::mul_t;
		u32 B = static_cast<u32>(std::sqrt(MIP::mod())) + 2;
		MIP a_to_y = 1;
		ds::hash_table<val_t, val_t> bay2y;
		for (u32 y = 0; y < B; ++y, a_to_y *= a) {
			bay2y[(b * a_to_y).value()] = y;
		}
		MIP a_to_B = a_to_y, a_to_B_to_x = a_to_B;
		for (u32 x = 1; x <= B; ++x, a_to_B_to_x *= a_to_B) {
			if (bay2y.exists(a_to_B_to_x.value()) == true) {
				return static_cast<mul_t>(B) * x - bay2y[a_to_B_to_x.value()];
			}
		}
		return std::nullopt;
	}
	template<i64 P, bool _64> std::vector<std::optional<std::conditional_t<_64, u64, u32>>>
	dis_logs(ModIntPr<P, _64> a, const std::vector<ModIntPr<P, _64>> &b) {
		using MIP = ModIntPr<P, _64>;
		using val_t = typename MIP::val_t;
		using mul_t = typename MIP::mul_t;
		u32 B = static_cast<u32>(std::sqrt(MIP::mod() / b.size())) + 2;
		u32 xlim = static_cast<u32>(MIP::mod() / B) + 3;
		MIP a_to_B = qpow(a, B, MIP(1, false)), a_to_B_to_x = a_to_B;
		ds::hash_table<val_t, val_t> aBx2x;
		for (u32 x = 1; x <= xlim; ++x, a_to_B_to_x *= a_to_B) {
			if (aBx2x.exists(a_to_B_to_x.value()) == false) {
				aBx2x[a_to_B_to_x.value()] = x;
			}
		}
		std::vector<std::optional<val_t>> ret(b.size(), std::nullopt);
		MIP a_to_y = 1;
		for (u32 y = 0; y < B; ++y, a_to_y *= a) {
			for (u32 i = 0; i < ret.size(); ++i) {
				val_t bayv = (b[i] * a_to_y).value();
				if (aBx2x.exists(bayv) == false) {
					continue;
				}
				val_t cura = static_cast<val_t>(static_cast<mul_t>(aBx2x[bayv]) * B - y);
				if (ret[i].has_value() == false) {
					ret[i] = cura;
				} else {
					ret[i] = std::min(ret[i].value(), cura);
				}
			}
		}
		return ret;
	}
}
