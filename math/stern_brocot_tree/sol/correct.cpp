#include "../lib/lib.hpp"

#include <cstdio>
#include <string>

int main() {
    using Int = long long;
    using Sbt = SbtOperators;

    int T; scanf("%d", &T);
    char QUERYNAMEBUF[100];

    while(T--){

        scanf("%s", QUERYNAMEBUF);
        std::string s(QUERYNAMEBUF);

        if(s == "END"){
            break;
        }
        else if(s == "ENCODE_PATH"){
            Int a, b; scanf("%lld%lld", &a, &b);
            auto t = Sbt::encode({ a, b });
            output_path(t);
            printf("\n");
        }
        else if(s == "DECODE_PATH"){
            auto path = input_path();
            auto q = Sbt::decode(path);
            printf("%lld %lld\n", q.a, q.b);
        }
        else if(s == "LCA"){
            Int a, b, c, d; scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
            auto q = Sbt::lca({a,b}, {c,d});
            printf("%lld %lld\n", q.a, q.b);
        }
        else if(s == "CHILD"){
            Int a, b; scanf("%lld%lld", &a, &b);
            auto [ql, qr] = Sbt::child({a,b});
            printf("%lld %lld %lld %lld\n", ql.a, ql.b, qr.a, qr.b);
        }
        else if(s == "ANCESTOR"){
            Int k, a, b; scanf("%lld%lld%lld", &k, &a, &b);
            auto q = Sbt::ancestor(k, {a,b});
            if(q.a == 0 && q.b == 0){
                printf("-1\n");
            }
            else{
                printf("%lld %lld\n", q.a, q.b);
            }
        }
        else if(s == "RANGE"){
            Int a, b; scanf("%lld%lld", &a, &b);
            auto [ql, qr] = Sbt::range({a,b});
            printf("%lld %lld %lld %lld\n", ql.a, ql.b, qr.a, qr.b);
        }
        else{
            puts("undefined command");
        }
    }
    return 0;
}
