#pragma once

#include "../basics.hpp"
#include "pollard_rho.hpp"

namespace numtheo_n {
	u64 phi(u64 x) {
		auto prf = prime_factors(x);
		for (auto i : prf) {
			x = x / i.first * (i.first - 1);
		}
		return x;
	}
}