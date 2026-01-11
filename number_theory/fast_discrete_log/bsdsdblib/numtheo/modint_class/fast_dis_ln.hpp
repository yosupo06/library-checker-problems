#pragma once

#include "../../basics.hpp"

namespace numtheo_n {
	template<i32 P> void MIP<P>::dis_ln_preproc(MIP<P> g) {
		u32 sqrtP = static_cast<u32>(std::sqrt(mod())) + 2;
		if (mpf.size() <= sqrtP) {
			euler_sieve(sqrtP);
		}
		std::vector<MIP<P>> prs;
		for (u32 i = 2; i <= sqrtP; ++i) {
			if (mpf[i] == i) {
				prs.emplace_back(i, false);
			}
		}
		auto prln = dis_logs(g, prs);
		lesqrt_ln.resize(sqrtP + 1);
		for (u32 i = 0; i < prs.size(); ++i) {
			if (prln[i].has_value() == false) {
				throw std::invalid_argument(
					"template<i32 P> MIP<P>::static void dis_ln_preproc(MIP<P>) "
					": g not primitive root"
				);
			}
			lesqrt_ln[prs[i].val] = prln[i].value();
		}
		lesqrt_ln[1] = 0;
		for (u32 i = 4; i <= sqrtP; ++i) {
			lesqrt_ln[i] = lesqrt_ln[mpf[i]] + lesqrt_ln[i / mpf[i]];
			if (lesqrt_ln[i] >= mod() - 1) {
				lesqrt_ln[i] -= mod() - 1;
			}
		}
	}
	template<i32 P> u32 fast_dis_ln(MIP<P> x) {
		if (x.val < MIP<P>::lesqrt_ln.size()) {
			return MIP<P>::lesqrt_ln[x.val];
		}
		u32 k = MIP<P>::mod() / x.val, r = MIP<P>::mod() % x.val;
		if (r <= x.val - r) {
			u64 ret = static_cast<u64>((MIP<P>::mod() - 1) >> 1)
				+ fast_dis_ln(MIP<P>(r, false)) + (MIP<P>::mod() - 1)
				- MIP<P>::lesqrt_ln[k];
			if (ret >= MIP<P>::mod() - 1) {
				ret -= MIP<P>::mod() - 1;
				if (ret >= MIP<P>::mod() - 1) {
					ret -= MIP<P>::mod() - 1;
				}
			}
			return static_cast<u32>(ret);
		} else {
			u32 ret = fast_dis_ln(MIP<P>(x.val - r, false)) + (MIP<P>::mod() - 1) - MIP<P>::lesqrt_ln[k + 1];
			if (ret >= MIP<P>::mod() - 1) {
				ret -= MIP<P>::mod() - 1;
			}
			return ret;
		}
	}
}