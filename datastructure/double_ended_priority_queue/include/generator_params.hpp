#ifndef INCLUDE_GEN_PARAMS_DEPQ
#define INCLUDE_GEN_PARAMS_DEPQ

#include <cassert>

#include "../params.h"

struct GeneratorParams {
    int n, q;
    int add_query_percent;
    int min_query_percent;
    int max_query_percent;
    int min_val;
    int max_val;

    GeneratorParams(
        int n, int q,
        int add_query_percent, int min_query_percent, int max_query_percent,
        int min_val, int max_val
    ) : n(n), q(q),
        add_query_percent(add_query_percent), min_query_percent(min_query_percent), max_query_percent(max_query_percent),
        min_val(min_val), max_val(max_val) {
        
        validate();
    }

private:
    void validate() const {
        assert(N_MIN <= n);
        assert(n <= N_MAX);
        assert(Q_MIN <= q);
        assert(q <= Q_MAX);
        assert(V_MIN <= min_val);
        assert(min_val <= max_val);
        assert(max_val <= V_MAX);
        assert(0 <= add_query_percent);
        assert(0 <= min_query_percent);
        assert(0 <= max_query_percent);
        assert(add_query_percent + min_query_percent + max_query_percent == 100);
    }
};

#endif // INCLUDE_GEN_PARAMS_DEPQ