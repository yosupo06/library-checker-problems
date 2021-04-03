#include <vector>
#include <utility>
#include <stdint.h>
#include <inttypes.h>
#include "testlib.h"

struct result {
    bool contain_cycle;
    std::vector<int> edges;
};

result read_solution(int M, InStream& stream) {
    int L = stream.readInt();
	if(L == -1) {
        stream.readChar('\n');
        stream.readEof();
        return result{false, {}};
    }
    else {
        stream.readChar('\n');
        std::vector<int> edges;
        for(int i=0; i<L; i++) {
            int id = stream.readInt(0, M-1);
            stream.readChar('\n');
            edges.emplace_back(id);
        }
        stream.readEof();
        return result{true, edges};
    }
}

int main(int argc, char *argv[]) {
	registerTestlibCmd(argc, argv);
	
	int N = inf.readInt(); (void)N;
	int M = inf.readInt();
    std::vector<int> U(M), V(M), cnt(M);
	for(int i=0; i<M; i++) {
        U[i] = inf.readInt();
        V[i] = inf.readInt();
	}
	
	auto res_correct = read_solution(M, ans);
	auto res_submitted = read_solution(M, ouf);
	if(res_submitted.contain_cycle != res_correct.contain_cycle) {
		quitf(_wa, "cycle existence differ - expected: %s, found: %s",
              res_correct.contain_cycle ? "Yes" : "No",
              res_submitted.contain_cycle ? "Yes" : "No");
	}
	auto edges_submitted = res_submitted.edges;
	if(res_submitted.contain_cycle) {
        if(edges_submitted.size() >= 2) {
            size_t L = edges_submitted.size();
            for(size_t i=0; i<L; i++) {
                if(++cnt[ edges_submitted[i] ] >= 2) {
                    quitf(_wa, "the edge (id = %d) appears twice",
                          edges_submitted[i]);
                }
                int v1 = V[ edges_submitted[i] ];
                int v2 = U[ edges_submitted[(i+1)%L] ];
                if(v1 != v2) {
                    quitf(_wa, "the given sequence is not cycle - %d is not equal to %d\n", v1, v2);
                }
            }
            
        }
        else {
            quitf(_wa, "cycle length < 2 is not permitted");
        }
    }
	quitf(_ok, "OK");
}
