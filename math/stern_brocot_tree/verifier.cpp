#include <algorithm>
#include <string>
#include "testlib.h"
#include "params.h"

bool is_valid_positive_rational_number(long long a, long long b){
    if(a <= 0 || b <= 0) return false;
    while(b){
        a %= b;
        std::swap(a, b);
    }
    return a == 1;
}

int main() {
    registerValidation();

    int T = inf.readInt(T_MIN, T_MAX, "T");
    inf.readChar('\n');
    
    for(int t=0; t<T; t++){
        std::string q = inf.readToken();
        if(q == "DECODE_PATH"){
            inf.readChar(' ');
            int K = inf.readInt(0, 1000, "k_dec");
            char c_prev = 'k';
            long long a1 = 1, b1 = 0;
            long long a2 = 0, b2 = 0;
            for(int k=0; k<K; k++){
                inf.readChar(' ');
                char c = inf.readChar();
                inf.readChar(' ');
                int a = inf.readInt(1, TARGET_FRAC_MAX, "a_dec");
                ensure(c == 'L' || c == 'R');
                ensure(c != c_prev);
                if(c == 'L'){ a2 += a1 * a; b2 += b1 * a; }
                if(c == 'R'){ a1 += a2 * a; b1 += b2 * a; }
                ensure(a1 + a2 <= TARGET_FRAC_MAX);
                ensure(b1 + b2 <= TARGET_FRAC_MAX);
                c_prev = c;
            }
            inf.readChar('\n');
        }
        else if(q == "ENCODE_PATH"){
            inf.readChar(' ');
            int a = inf.readInt(1, TARGET_FRAC_MAX, "a_enc");
            inf.readChar(' ');
            int b = inf.readInt(1, TARGET_FRAC_MAX, "a_enc");
            inf.readChar('\n');
            ensure(is_valid_positive_rational_number(a, b));
        }
        else if(q == "LCA"){
            inf.readChar(' ');
            int a = inf.readInt(1, TARGET_FRAC_MAX, "a_lca");
            inf.readChar(' ');
            int b = inf.readInt(1, TARGET_FRAC_MAX, "b_lca");
            inf.readChar(' ');
            int c = inf.readInt(1, TARGET_FRAC_MAX, "c_lca");
            inf.readChar(' ');
            int d = inf.readInt(1, TARGET_FRAC_MAX, "d_lca");
            inf.readChar('\n');
            ensure(is_valid_positive_rational_number(a, b));
            ensure(is_valid_positive_rational_number(c, d));
        }
        else if(q == "ANCESTOR"){
            inf.readChar(' ');
            inf.readInt(K_MIN_ANCESTOR, K_MAX_ANCESTOR, "k_anc");
            inf.readChar(' ');
            int a = inf.readInt(1, TARGET_FRAC_MAX, "a_anc");
            inf.readChar(' ');
            int b = inf.readInt(1, TARGET_FRAC_MAX, "b_anc");
            inf.readChar('\n');
            ensure(is_valid_positive_rational_number(a, b));
        }
        /*
        else if(q == "CHILD"){
            inf.readChar(' ');
            int a = inf.readInt(1, TARGET_FRAC_MAX, "a_chi");
            inf.readChar(' ');
            int b = inf.readInt(1, TARGET_FRAC_MAX, "b_chi");
            inf.readChar('\n');
            ensure(is_valid_positive_rational_number(a, b));
        }
        */
        else if(q == "RANGE"){
            inf.readChar(' ');
            int a = inf.readInt(1, TARGET_FRAC_MAX, "a_ran");
            inf.readChar(' ');
            int b = inf.readInt(1, TARGET_FRAC_MAX, "b_ran");
            inf.readChar('\n');
            ensure(is_valid_positive_rational_number(a, b));
        }
        else{
            ensure(false);
        }
    }
    inf.readEof();
}
