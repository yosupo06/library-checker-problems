#include <cstdio>
#include <vector>
#include <cstdint>

using namespace std;
using ll = long long;

struct Point {
    ll x, y;
};

static inline ll sq(ll v) { return v * v; }

static inline ll distance_sq(const Point& a, const Point& b) {
    return sq(a.x - b.x) + sq(a.y - b.y);
}

static inline int ccw(const Point& a, const Point& b, const Point& c) {
    ll x1 = b.x - a.x, y1 = b.y - a.y;
    ll x2 = c.x - a.x, y2 = c.y - a.y;
    ll s = x1 * y2 - y1 * x2;
    if (s > 0) return 1;
    if (s < 0) return -1;
    return 0;
}

enum class Containment : int {
    OUTSIDE = -1,
    ON      =  0,
    INSIDE  =  1
};

static inline Containment containment_diameter(const Point& a, const Point& b, const Point& p) {
    ll ux = 2*p.x - a.x - b.x;
    ll uy = 2*p.y - a.y - b.y;
    ll lhs = sq(ux) + sq(uy);
    ll rhs = distance_sq(a, b);
    if (lhs < rhs)  return Containment::INSIDE;
    if (lhs == rhs) return Containment::ON;
    return Containment::OUTSIDE;
}

static inline ll incircle_det(const Point& a, const Point& b, const Point& c, const Point& p) {
    ll ax = a.x - p.x, ay = a.y - p.y;
    ll bx = b.x - p.x, by = b.y - p.y;
    ll cx = c.x - p.x, cy = c.y - p.y;
    ll A = sq(ax) + sq(ay);
    ll B = sq(bx) + sq(by);
    ll C = sq(cx) + sq(cy);
    ll det = ax * (by * C - cy * B) - ay * (bx * C - cx * B) + A * (bx * cy - by * cx);
    return det;
}

static inline Containment containment_circumcircle(const Point& a, const Point& b, const Point& c, const Point& p) {
    int s = ccw(a, b, c);
    if (s == 0) {
        ll dab = distance_sq(a, b), dbc = distance_sq(b, c), dac = distance_sq(a, c);
        if (dab >= dbc && dab >= dac) return containment_diameter(a, b, p);
        if (dbc >= dab && dbc >= dac) return containment_diameter(b, c, p);
        return containment_diameter(a, c, p);
    }
    ll det = incircle_det(a, b, c, p);
    ll val = (s > 0) ? det : -det;
    if (val > 0)  return Containment::INSIDE;
    if (val == 0) return Containment::ON;
    return Containment::OUTSIDE;
}

static inline uint64_t xs64(uint64_t& st) { st ^= st << 7; st ^= st >> 9; return st; }
template <class T>
static void deterministic_shuffle(std::vector<T>& a, uint64_t seed = 0x9E3779B97F4A7C15ULL) {
    if (a.size() <= 1) return;
    uint64_t s = seed;
    for (int i = (int)a.size() - 1; i >= 1; --i) {
        uint64_t r = xs64(s);
        int j = (int)(r % (uint64_t)(i + 1));
        if (i != j) { T tmp = a[i]; a[i] = a[j]; a[j] = tmp; }
    }
}

struct Support {
    int m = 0;
    Point a, b, c;
};

static inline Containment containment_by_support(const Support& S, const Point& p) {
    if (S.m == 0) return Containment::OUTSIDE;
    if (S.m == 1) {
        if (p.x == S.a.x && p.y == S.a.y) return Containment::ON;
        return Containment::OUTSIDE;
    }
    if (S.m == 2) return containment_diameter(S.a, S.b, p);
    return containment_circumcircle(S.a, S.b, S.c, p);
}

static inline void reduce_if_collinear(Support& S) {
    if (S.m != 3) return;
    if (ccw(S.a, S.b, S.c) != 0) return;
    ll dab = distance_sq(S.a, S.b);
    ll dbc = distance_sq(S.b, S.c);
    ll dac = distance_sq(S.a, S.c);
    if (dab >= dbc && dab >= dac) {
        S.m = 2; // a,b
    } else if (dbc >= dab && dbc >= dac) {
        S.m = 2; S.a = S.b; S.b = S.c;
    } else {
        S.m = 2; S.b = S.c;
    }
}

static Support mec_support(std::vector<Point> pts) {
    deterministic_shuffle(pts);

    Support S;
    for (int i = 0; i < (int)pts.size(); ++i) {
        if ((int)containment_by_support(S, pts[i]) >= 0) continue;
        S.m = 1; S.a = pts[i];
        for (int j = 0; j < i; ++j) {
            if ((int)containment_by_support(S, pts[j]) >= 0) continue;
            S.m = 2; S.a = pts[i]; S.b = pts[j];
            for (int k = 0; k < j; ++k) {
                if ((int)containment_by_support(S, pts[k]) >= 0) continue;
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
    std::vector<Point> pts(N);
    for (int i = 0; i < N; ++i) {
        int xi, yi;
        std::scanf("%d %d", &xi, &yi);
        pts[i] = Point{ (ll)xi, (ll)yi };
    }

    Support S = mec_support(pts);

    std::vector<char> out(N, '0');
    if (S.m == 1) {
        for (int i = 0; i < N; ++i) {
            if (pts[i].x == S.a.x && pts[i].y == S.a.y) out[i] = '1';
        }
    } else if (S.m == 2) {
        for (int i = 0; i < N; ++i) {
            if (containment_diameter(S.a, S.b, pts[i]) == Containment::ON) out[i] = '1';
        }
    } else {
        for (int i = 0; i < N; ++i) {
            if (containment_circumcircle(S.a, S.b, S.c, pts[i]) == Containment::ON) out[i] = '1';
        }
    }

    for (int i = 0; i < N; ++i) std::putchar(out[i]);
    std::putchar('\n');
    return 0;
}
