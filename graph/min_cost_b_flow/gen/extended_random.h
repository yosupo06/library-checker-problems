#ifndef MIN_COST_B_FLOW_GEN_EXTENDED_RANDOM_H
#define MIN_COST_B_FLOW_GEN_EXTENDED_RANDOM_H

#include "random.h"

struct Rng : public Random {
    Rng(const long long int &seed) : Random(seed) {
    }

    // log-uniform distribution [1, upper)
    template<class T> T log_uniform1(const T upper) {
        const T ret = (T) pow((double) upper, uniform01());
        if (ret < 1) return 1;
        if (ret >= upper) return upper - 1;
        return ret;
    }

    // returns [0, upper], skewed to the lower value.
    template<class T> T skewed(const T upper) {
        return log_uniform1(upper + 2) - 1;
    }
    // returns [lower, upper], skewed to the middle.
    template<class T> T skewed(const T lower, const T middle, const T upper) {
        assert(lower <= middle && middle <= upper);
        if (lower == middle) return lower + skewed(upper - lower);
        if (upper == middle) return upper - skewed(upper - lower);
        if (uniform_bool()) {
            return skewed(middle, middle, upper);
        } else {
            return skewed(lower, middle, middle);
        }
    }
    int signum() {
        return uniform_bool() ? 1 : -1;
    }
};

#endif // MIN_COST_B_FLOW_GEN_EXTENDED_RANDOM_H
