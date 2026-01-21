#pragma once

#include <numeric>
#include <vector>

#include "../basics.hpp"

namespace numtheo {
	std::vector<u32> primes, mpf;
	u32 enumerated_prime;
	void euler_sieve(u32 N) {
		if (mpf.size() > N) {
			return;
		}
		primes.clear();
		mpf.resize(N + 1);
		std::iota(mpf.begin(), mpf.end(), 0);
		enumerated_prime = N;
		for (u32 i = 2; i <= N; ++i) {
			if (mpf[i] == i) {
				primes.emplace_back(i);
			}
			for (u32 j : primes) {
				u64 k = static_cast<u64>(i) * j;
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
