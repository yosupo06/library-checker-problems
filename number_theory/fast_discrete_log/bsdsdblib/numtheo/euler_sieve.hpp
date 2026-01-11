#pragma once

#include <numeric>
#include <vector>

#include "../basics.hpp"

namespace numtheo_n {
	std::vector<u32> primes, mpf;
	void euler_sieve(u32 N) {
		primes.clear();
		mpf.resize(N + 1);
		std::iota(mpf.begin(), mpf.end(), 0);
		for (u32 i = 2; i <= N; ++i) {
			if (mpf[i] == i) {
				primes.emplace_back(i);
			}
			for (u32 j : primes) {
				u32 k = i * j;
				if (k > N) {
					break;
				}
				mpf[k] = j;
				if (i % j == 0) {
					break;
				}
			}
		}
	}
}