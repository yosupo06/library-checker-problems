#include "testlib.h"

#include <iostream>
#include <numeric>

#include "../bsdsdblib/basics.hpp"
#include "../bsdsdblib/numtheo/modint.hpp"
#include "../bsdsdblib/numtheo/pollard_rho.hpp"
#include "../bsdsdblib/numtheo/prim_root.hpp"

u32 randroot(u32 p) {
	using MI = numtheo::ModInt32<-1>;
	MI::set_mod(p);
	u32 pp = p - 1;
	u32 mg = numtheo::min_prim_root(p).value();
	u32 pw;
	do {
		pw = rnd.next(1u, pp - 1);
	} while (std::gcd(pw, pp) != 1);
	return qpow(MI(mg), pw).value();
}

int main(int argc, char **argv) {
	registerGen(argc, argv, 1);
	u32 p = 999999937;
	u32 g = randroot(p);
	u32 n = 1000000;
	printf("%u %u %u\n", p, g, n);
	while (n--) {
		printf("%u\n", rnd.next(1u, p - 1));
	}
	return 0;
}
