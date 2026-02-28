#include "testlib.h"

#include <iostream>
#include <numeric>

#include "../bsdsdblib/basics.hpp"
#include "../bsdsdblib/numtheo/modint.hpp"
#include "../bsdsdblib/numtheo/pollard_rho.hpp"
#include "../bsdsdblib/numtheo/prim_root.hpp"

constexpr u32 N = 1000000, P = 1000000000;

int main(int argc, char **argv) {
	registerGen(argc, argv, 1);
	u32 p;
	do {
		p = rnd.next(u32(P * 0.999), P);
	} while (numtheo::miller_rabin(p) == false ||
		numtheo::miller_rabin(p / 2) == false ||
		numtheo::min_prim_root(p).value() != 2);
	u32 g = 2;
	u32 n = N;
	printf("%u %u %u\n", p, g, n);
	while (n--) {
		printf("%u\n", rnd.next(1u, p - 1));
	}
	return 0;
}
