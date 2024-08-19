#include <vector>
#include <cstdio>

#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char *argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 38;
    vector<vector<int>> a(n, vector<int>(n));

	auto fix=[&](int i,int j,int v){
		assert(i!=j);
		a[i][j]=a[j][i]=v;
	};
	const int m = 998244353;
	for (int x=0;x<2;x++) for (int y=2;y<4;y++) {
		fix(x,y,m-1);
		for(int z=4;z<n;z+=2){
			fix(y,z+1,1);
			if(z>4)fix(z-1,z,1);
			fix(z,z+1,gen.uniform<int>(0,m-1));
		}
		fix(x,4,m-1);
	}
    std::printf("%d\n", n);
    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != n; ++j) {
            std::printf("%d%c", a[i][j], " \n"[j + 1 == n]);
        }
    }
}
