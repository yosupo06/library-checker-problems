#pragma once

#include "../basics.hpp"
#include "pollard_rho.hpp"

namespace numtheo {
	template<class T> T phi(T x) {
		auto prf = prime_factors(x);
		for (auto i : prf) {
			x = x / i.first * (i.first - 1);
		}
		return x;
	}
}
