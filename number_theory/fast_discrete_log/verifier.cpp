#include "testlib.h"

#include "./bsdsdblib/basics.hpp"
#include "./bsdsdblib/numtheo/pollard_rho.hpp"
#include "./bsdsdblib/numtheo/prim_root.hpp"

constexpr u32 N = 1000000, P = 1000000000;

int main(int argc, char **argv) {
	registerValidation(argc, argv);
	u32 p = inf.readInt(2, P, "p");
	ensuref(numtheo_n::miller_rabin(p), "p not prime");
	inf.readSpace();
	u32 g = inf.readInt(1, p, "g");
	ensuref(numtheo_n::is_prim_root(g, p), "g is not a primitive root of p");
	inf.readSpace();
	u32 n = inf.readInt(1, N, "n");
	inf.readChar('\n');
	while (n--) {
		inf.readInt(1, p - 1, "a");
		inf.readChar('\n');
	}
	inf.readEof();
	return 0;
}
