#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cassert>
#include "../params.h"
#include "random.h"

struct Point { int x, y; };

static void out_points(const std::vector<Point>& S) {
    std::printf("%d\n", (int)S.size());
    for (const auto& p : S) std::printf("%d %d\n", p.x, p.y);
}

int main(int argc, char** argv) {
    if (argc < 2) return 0; // seed 必須
    long long seed = std::atoll(argv[1]);
    Random gen(seed);

    const int LIM = X_AND_Y_ABS_MAX;                 // 例: 10000
    const int N   = gen.uniform<int>(N_MAX*49/50, N_MAX);

    // x を [-LIM, LIM] にほぼ等間隔で割り当て（整数除算により重複 x が生じ得る）
    std::vector<int> xs;
    xs.reserve(N);
    const long long denom = (N - 1) ? (N - 1) : 1;
    for (int i = 0; i < N; ++i) {
        long long xi = -1LL * LIM + ( (2LL * LIM) * i ) / denom;
        assert(xi >= -LIM && xi <= LIM);
        xs.push_back((int)xi);
    }

    // y の基準列（凸形状）： y_raw(i) = floor(i^2 / D) + i を用い、[-LIM, LIM] に収める
    const long long MARGIN = 16;
    const long long i_max  = (long long)N - 1;
    const long long target = 2LL * LIM - MARGIN;
    long long D;
    if (target - i_max <= 0) {
        // これ以上小さくできない領域：floor(i^2/D) を 0 近傍に抑える
        D = i_max * i_max + 1; // 十分大
    } else {
        long long den = target - i_max;
        long long num = i_max * i_max;
        D = num / den + (num % den != 0); // ceil
        if (D < 1) D = 1;
    }
    const long long bmax   = i_max + (i_max * i_max) / D;
    const long long yshift = -(bmax / 2);

    std::vector<int> y_base(N);
    y_base.reserve(N);
    for (int i = 0; i < N; ++i) {
        long long ii = i;
        long long yi = (ii * ii) / D + ii; // 単調増加
        yi += yshift;
        if (yi < -LIM) yi = -LIM;
        if (yi >  LIM) yi =  LIM;
        y_base[i] = (int)yi;
    }

    // 出力順序：交互 or そのまま
    std::vector<int> order;
    order.reserve(N);
    if (gen.uniform_bool()) {
        int l = 0, r = N - 1;
        while (l <= r) {
            order.push_back(l++);
            if (l <= r) order.push_back(r--);
        }
    } else {
        order.resize(N);
        for (int i = 0; i < N; ++i) order[i] = i;
    }

    // ---- 厳密な重複排除（他の x へ逃がさない）----
    // 1) 各 x の出現回数を数える
    const int XSPAN = 2 * LIM + 1; // x = [-LIM, LIM]
    auto xindex = [](int x) -> int { return x + LIM; };

    std::vector<int> cnt(XSPAN, 0);
    for (int idx : order) {
        int xi = xindex(xs[idx]);
        ++cnt[xi];
    }
    // 任意の x における出現回数は 2LIM+1 を超えない前提（超えると同一 x に置ける y が尽きる）
    for (int xi = 0; xi < XSPAN; ++xi) {
        assert(cnt[xi] <= 2 * LIM + 1);
    }

    // 2) 各 x について、長さ m=cnt[x] の連続区間 [low, high] を [-LIM, LIM] 内で確保
    //    区間は、order における最初の出現の y_base を中心にできるだけ近くなるように配置
    std::vector<int> first_seen_y(XSPAN, 0);
    std::vector<char> seen(XSPAN, 0);
    for (int idx : order) {
        int xi = xindex(xs[idx]);
        if (!seen[xi]) {
            seen[xi] = 1;
            first_seen_y[xi] = y_base[idx];
        }
    }

    std::vector<int> low(XSPAN, 0), high(XSPAN, -1), center(XSPAN, 0);
    for (int xi = 0; xi < XSPAN; ++xi) {
        int m = cnt[xi];
        if (m == 0) continue;
        int yref = first_seen_y[xi];
        // 区間長 m を確保
        int L = yref - (m - 1) / 2;
        int H = L + (m - 1);
        if (L < -LIM) { L = -LIM; H = L + (m - 1); }
        if (H >  LIM) { H =  LIM; L = H - (m - 1); }
        // 念のため境界再調整
        if (L < -LIM) L = -LIM;
        if (H >  LIM) H = LIM;
        // 区間長の保証
        assert(H - L + 1 == m);

        low[xi] = L;
        high[xi] = H;
        // 中心は区間内で yref に最も近い点
        if (yref < L) center[xi] = L;
        else if (yref > H) center[xi] = H;
        else center[xi] = yref;
    }

    // 3) 各 x に対し、中心から「左・右」を交互に使って m 個の y を割り当てるためのポインタ
    std::vector<int> nextL(XSPAN, 0), nextR(XSPAN, 0);
    std::vector<char> takeLeft(XSPAN, 1);
    for (int xi = 0; xi < XSPAN; ++xi) {
        if (cnt[xi] == 0) continue;
        nextL[xi] = center[xi];
        nextR[xi] = center[xi] + 1;
        takeLeft[xi] = 1; // まず中心（left）から
    }

    auto take_next_y = [&](int xi) -> int {
        // 区間 [low, high] を使い切るまで、left, right を交互に消費
        int L = low[xi], H = high[xi];
        int& l = nextL[xi];
        int& r = nextR[xi];
        char& tl = takeLeft[xi];

        int y;
        if (tl) {
            // 左（<= center）側
            if (l >= L) { y = l; --l; tl = 0; return y; }
            // 左が尽きたら右
            if (r <= H) { y = r; ++r; tl = 1; return y; }
        } else {
            // 右（> center）側
            if (r <= H) { y = r; ++r; tl = 1; return y; }
            // 右が尽きたら左
            if (l >= L) { y = l; --l; tl = 0; return y; }
        }
        // ここには到達しない（m 回ちょうどで尽きるはず）
        assert(false);
        return 0;
    };

    // 4) 割り当て実施（order を保ちつつ、各 x で一意な y を配分）
    std::vector<Point> S;
    S.reserve(N);
    // xi ごとの消費カウンタ（確認用）
    std::vector<int> used_count(XSPAN, 0);

    for (int idx : order) {
        int xi = xindex(xs[idx]);
        if (cnt[xi] == 0) continue; // 念のため
        int y = take_next_y(xi);
        ++used_count[xi];
        S.push_back(Point{ xs[idx], y });
    }
    // 区間をちょうど使い切ったか検証
    for (int xi = 0; xi < XSPAN; ++xi) {
        assert(used_count[xi] == cnt[xi]);
    }

    // (x,y) が一意であることの最終確認（同一 x で y を連続区間から重複なく割り当てているため理論上 OK）
    // 追加の set チェックは不要（厳密保証）

    out_points(S);
    return 0;
}
