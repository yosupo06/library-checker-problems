#include <set>
#include <tuple>
#include "testlib.h"
#include "./params.h"
using namespace::std;

int main(int argc, char* argv[]) {
	registerValidation(argc, argv);
	int n = inf.readInt(N_AND_M_MIN,N_AND_M_MAX, "n");
	inf.readSpace();
	int m = inf.readInt(N_AND_M_MIN,N_AND_M_MAX,"m");
	inf.readSpace();
	inf.readInt(K_MIN,K_MAX,"k");
	inf.readSpace();
	inf.readInt(0,n-1,"s");
	inf.readSpace();
	inf.readInt(0,n-1,"t");
	inf.readChar('\n');
	for(int i=0;i<m;i++) {
		inf.readInt(0,n-1,"u");
		inf.readSpace();
		inf.readInt(0,n-1,"v");
		inf.readSpace();
		inf.readInt(C_MIN,C_MAX,"c");
		inf.readChar('\n');
	}
	inf.readEof();
}