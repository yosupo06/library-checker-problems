#include <iostream>

#include "../bsdsdblib/basics.hpp"
#include "../bsdsdblib/numtheo/modint.hpp"
#include "../bsdsdblib/numtheo/farey_tech.hpp"

using MIP = numtheo::ModIntPr32<-1>;

int main() {
	u32 p;
	scanf("%u", &p);
	u32 gval;
	scanf("%u", &gval);
	// For p = 3 the Farey approximation can have denominator p.
	if (p != 3) {
		MIP::set_mod(p);
		numtheo::fast_ln_preproc(MIP(gval));
	}
	u32 n;
	scanf("%u", &n);
	while (n--) {
		u32 xval;
		scanf("%u", &xval);
		// For p = 3 the only primitive root is 2: 2^0 = 1 and 2^1 = 2.
		std::cout << (p == 3 ? xval - 1 : numtheo::fast_dis_ln(MIP(xval))) << '\n';
	}
	return 0;
}
