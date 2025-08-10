#include <cstdio>
#include <vector>
#include <cstdint>

// ---- Integer-only MEC via Welzl-like incremental (exact; no EPS, no __int128) ----

struct P { int x, y; };

// 基本ユーティリティ
static inline long long sq(long long v) { return v * v; }
static inline long long dist_sq(const P& a, const P& b) {
    return sq((long long)a.x - b.x) + sq((long long)a.y - b.y);
}

// ccw: a->b と a->c の向き
//  >0: 反時計回り, <0: 時計回り, =0: 共線
static inline long long ccw_val(const P& a, const P& b, const P& c) {
    long long x1 = (long long)b.x - a.x;
    long long y1 = (long long)b.y - a.y;
    long long x2 = (long long)c.x - a.x;
    long long y2 = (long long)c.y - a.y;
    return x1 * y2 - y1 * x2;
}
static inline int ccw(const P& a, const P& b, const P& c) {
    long long s = ccw_val(a, b, c);
    if (s > 0) return 1;
    if (s < 0) return -1;
    return 0;
}

// 2点円（直径円）に対する内外判定（中心や半径を使わない）
// (2p - a - b) の二乗長 ≤ |a-b|^2
static inline bool in_or_on_diameter(const P& a, const P& b, const P& p) {
    long long ux = 2LL * p.x - a.x - b.x;
    long long uy = 2LL * p.y - a.y - b.y;
    return sq(ux) + sq(uy) <= dist_sq(a, b);
}
static inline bool on_diameter(const P& a, const P& b, const P& p) {
    long long ux = 2LL * p.x - a.x - b.x;
    long long uy = 2LL * p.y - a.y - b.y;
    return sq(ux) + sq(uy) == dist_sq(a, b);
}

// InCircle 行列式（p を原点に平行移動）。4次式（64bitで収まる）
static inline long long incircle_det_translated(const P& a, const P& b, const P& c, const P& p) {
    long long ax = (long long)a.x - p.x, ay = (long long)a.y - p.y;
    long long bx = (long long)b.x - p.x, by = (long long)b.y - p.y;
    long long cx = (long long)c.x - p.x, cy = (long long)c.y - p.y;
    long long A = sq(ax) + sq(ay);
    long long B = sq(bx) + sq(by);
    long long C = sq(cx) + sq(cy);
    // det = ax*(by*C - cy*B) - ay*(bx*C - cx*B) + A*(bx*cy - by*cx)
    long long t1 = ax * (by * C - cy * B);
    long long t2 = ay * (bx * C - cx * B);
    long long t3 = A  * (bx * cy - by * cx);
    return t1 - t2 + t3;
}

// 3点で決まる外接円に対して p が内側/境界か
static inline bool in_or_on_circumcircle(const P& a, const P& b, const P& c, const P& p) {
    int s = ccw(a, b, c);
    if (s == 0) {
        // 共線：外接円は未定義 → 最遠ペアの直径円で代用
        long long dab = dist_sq(a, b), dbc = dist_sq(b, c), dac = dist_sq(a, c);
        if (dab >= dbc && dab >= dac) return in_or_on_diameter(a, b, p);
        if (dbc >= dab && dbc >= dac) return in_or_on_diameter(b, c, p);
        return in_or_on_diameter(a, c, p);
    }
    long long det = incircle_det_translated(a, b, c, p);
    return (s > 0) ? (det >= 0) : (det <= 0);
}
static inline bool on_circumcircle(const P& a, const P& b, const P& c, const P& p) {
    int s = ccw(a, b, c);
    if (s == 0) {
        long long dab = dist_sq(a, b), dbc = dist_sq(b, c), dac = dist_sq(a, c);
        if (dab >= dbc && dab >= dac) return on_diameter(a, b, p);
        if (dbc >= dab && dbc >= dac) return on_diameter(b, c, p);
        return on_diameter(a, c, p);
    }
    return incircle_det_translated(a, b, c, p) == 0;
}

// 決定的シャッフル（固定シード xorshift64）
static inline uint64_t xs64(uint64_t& s) { s ^= s << 7; s ^= s >> 9; return s; }
template <class T>
static void det_shuffle(std::vector<T>& a) {
    uint64_t s = 0x9E3779B97F4A7C15ULL;
    for (int i = (int)a.size() - 1; i >= 1; --i) {
        uint64_t r = xs64(s);
        int j = (int)(r % (uint64_t)(i + 1));
        T tmp = a[i]; a[i] = a[j]; a[j] = tmp;
    }
}

// 支持集合（円を決める点集合；最大3点）
struct Support {
    int m = 0;
    P a, b, c;
};

static inline bool contains_by_support(const Support& S, const P& p) {
    if (S.m == 0) return false;
    if (S.m == 1) return (S.a.x == p.x && S.a.y == p.y); // 半径0
    if (S.m == 2) return in_or_on_diameter(S.a, S.b, p);
    return in_or_on_circumcircle(S.a, S.b, S.c, p);
}

// 3点が共線なら最遠ペアの2点に縮約
static inline void reduce_if_collinear(Support& S) {
    if (S.m != 3) return;
    if (ccw(S.a, S.b, S.c) != 0) return;
    long long dab = dist_sq(S.a, S.b), dbc = dist_sq(S.b, S.c), dac = dist_sq(S.a, S.c);
    if (dab >= dbc && dab >= dac) { S.m = 2; /* a,b */ }
    else if (dbc >= dab && dbc >= dac) { S.m = 2; S.a = S.b; S.b = S.c; }
    else { S.m = 2; S.b = S.c; /* a,c */ }
}

// Welzl 型 MEC（期待 O(n)）：中心は持たず支持集合のみ更新
static Support mec_support(std::vector<P> pts) {
    det_shuffle(pts);  // 決定的擬似乱択

    Support S;
    for (int i = 0; i < (int)pts.size(); ++i) {
        if (contains_by_support(S, pts[i])) continue;
        S.m = 1; S.a = pts[i];
        for (int j = 0; j < i; ++j) {
            if (contains_by_support(S, pts[j])) continue;
            S.m = 2; S.a = pts[i]; S.b = pts[j];
            for (int k = 0; k < j; ++k) {
                if (contains_by_support(S, pts[k])) continue;
                S.m = 3; S.a = pts[i]; S.b = pts[j]; S.c = pts[k];
                reduce_if_collinear(S);
            }
        }
    }
    return S;
}

int main() {
    int N;
    if (std::scanf("%d", &N) != 1) return 0;
    std::vector<P> pts(N);
    for (int i = 0; i < N; ++i) {
        std::scanf("%d %d", &pts[i].x, &pts[i].y);
    }

    // MEC を決める支持集合を構築
    Support S = mec_support(pts);

    // 円周上を厳密に判定して 0/1 文字列を出力
    std::vector<char> out(N, '0');
    if (S.m == 2) {
        for (int i = 0; i < N; ++i) if (on_diameter(S.a, S.b, pts[i])) out[i] = '1';
    } else if (S.m == 3) {
        for (int i = 0; i < N; ++i) if (on_circumcircle(S.a, S.b, S.c, pts[i])) out[i] = '1';
    } else { // 半径0（N>=2, 全点相異なら実質起こらないが安全のため）
        for (int i = 0; i < N; ++i) if (pts[i].x == S.a.x && pts[i].y == S.a.y) out[i] = '1';
    }

    for (int i = 0; i < N; ++i) std::putchar(out[i]);
    std::putchar('\n');
    return 0;
}
