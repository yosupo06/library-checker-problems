#include <cstdio>
#include <map>

int main() {
    int q;
    scanf("%d", &q);
    std::map<long long, long long> mp;
    for (int i = 0; i < q; i++) {
        int type;
        scanf("%d", &type);
        if (type == 0) {
            long long key, val;
            scanf("%lld %lld", &key, &val);
            mp[key] = val;
        } else {
            long long key;
            scanf("%lld", &key);
            printf("%lld\n", mp[key]);
        }
    }
    return 0;
}
