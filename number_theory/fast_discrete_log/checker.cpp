#include "testlib.h"

#include "./bsdsdblib/basics.hpp"

int main(int argc, char **argv) {
	registerTestlibCmd(argc, argv);
	u32 p = inf.readInt(2, 1000000000);
	inf.readInt(1, p - 1);
	u32 n = inf.readInt(1, 1000000);
	for (u32 i = 0; i < n; ++i) {
		u32 jans = ans.readInt(0, p - 1);
		u32 pans = ouf.readInt(0, p - 1);
		if (jans != pans) {
			quitf(_wa, "wrong on %uth token (b_%u): found %u, expected %u", i + 1, i, pans, jans);
		}
		ans.readEoln();
		ouf.readEoln();
	}
	ans.readEof();
	ouf.readEof();
	quitf(_ok, "Accepted");
	return 0;
}