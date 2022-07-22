#include <vector>
#include <utility>
#include <stdint.h>
#include <inttypes.h>
#include "testlib.h"
using namespace std;

pair<int, vector<int>> read_ans(int N, InStream& stream) {
    int K = stream.readInt(1, N);
	vector<int> LIS;
	for(int i = 0; i < K; i++){
		int a = stream.readInt(0, N - 1);
		LIS.push_back(a);
	}
	return {K, LIS};
}

int main(int argc, char *argv[]) {
	registerTestlibCmd(argc, argv);
	
	int N = inf.readInt();
	vector<int> A(N);
	for(int i = 0; i < N; i++){
		A[i] = inf.readInt();
	}
	
	auto res_correct = read_ans(N, ans);
	auto res_submitted = read_ans(N, ouf);
	auto K_correct = res_correct.first;
	auto LIS_correct = res_correct.second;
	auto K_submitted = res_submitted.first;
	auto LIS_submitted = res_submitted.second;

	if(K_correct != K_submitted){
		quitf(_wa, "the size of LIS is incorrect : submitted : %d, judge : %d", K_correct, K_submitted);
	}

	for(int i = 0; i < K_submitted - 1; i++){
		if(LIS_submitted[i] >= LIS_submitted[i + 1]){
			quitf(_wa, "an element of LIS is incorrect; the index order is wrong." );
		}
		if(A[LIS_submitted[i]] >= A[LIS_submitted[i + 1]]){
			quitf(_wa, "submitted sequence is not an IS." );
		}
	}
	
	quitf(_ok, "OK");
}
