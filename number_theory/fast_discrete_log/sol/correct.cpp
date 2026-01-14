#include <iostream>

#include "../bsdsdblib/basics.hpp"
#include "../bsdsdblib/numtheo/modint.hpp"
#include "../bsdsdblib/numtheo/farey_tech.hpp"

using MIP = numtheo::ModIntPr32<-1>;

int main() {
	u32 p;
	scanf("%u", &p);
	MIP::set_mod(p);
	u32 gval;
	scanf("%u", &gval);
	numtheo::fast_ln_preproc(MIP(gval));
	u32 n;
	scanf("%u", &n);
	while (n--) {
		u32 xval;
		scanf("%u", &xval);
		std::cout << numtheo::fast_dis_ln(MIP(xval)) << '\n';
	}
	return 0;
}