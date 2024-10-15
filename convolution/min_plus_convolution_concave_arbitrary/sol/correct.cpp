#include <cstdio>
#include <vector>
#include <cassert>
#include <limits>
#include <functional>

using namespace std;


template <class FUNC>
vector<int> monotone_minima(int h, int w, const FUNC& a) {
	vector<int> j_min(h);

	for (int di = 1 << 20; di > 0; di >>= 1) {
		int di2 = 2 * di;
		for (int i = di; i <= h; i += di2) {
			int jL = (i - di > 0 ? j_min[i - di - 1] : 0);
			int jR = (i + di <= h ? j_min[i + di - 1] : w - 1);

			int a_min = numeric_limits<int>::max();
			for (int j = jL; j <= jR; j++) {
				int val = a(i - 1, j);
				
				if (a_min > val) {
					a_min = val;
					j_min[i - 1] = j;
				}
			}
		}
	}

	return j_min;
}


vector<int> semiconcave_min_plus_convolution(const vector<int>& a, const vector<int>& b) {
	int n = (int)a.size(), m = (int)b.size();
	
	// b is concave
	for (int i = 0; i < m - 2; ++i) assert(b[i] + b[i + 2] <= 2 * b[i + 1]);

	int h = n + m - 1, w = n;

	vector<int> y_min(h, 0), y_max(h, w - 1);
	for (int x = m; x <= h - 1; x++) y_min[x] = x - m + 1;
	for (int x = 0; x <= h - m; x++) y_max[x] = x;

	vector<int> x_min(w), x_max(w);
	for (int y = 0; y < w; y++) {
		x_min[y] = y;
		x_max[y] = m - 1 + y;
	}

	vector<int> c(h, numeric_limits<int>::max());

	function<void(int, int, int, int)> rf = [&](int x1, int x2, int y1, int y2) {
		if (y_max[x1] >= y2 && y1 >= y_min[x2]) {
			auto A = [&](int i, int j) {
				return a[y2 - j] + b[(x1 + i) - (y2 - j)];
			};

			auto j_min = monotone_minima(x2 - x1 + 1, y2 - y1 + 1, A);

			for (int i = x1; i <= x2; i++) {
				int val = A(i - x1, j_min[i - x1]);
				if (c[i] > val) c[i] = val;
			}

			return;
		}

		if ((long long)(x2 - x1) * (y2 - y1) < 1000) {
			for (int x = x1; x <= x2; x++) {
				int y_from = max(y_min[x], y1);
				int y_to = min(y_max[x], y2);
				for (int y = y_from; y <= y_to; y++) {
					int val = a[y] + b[x - y];
					if (c[x] > val) c[x] = val;
				}
			}
			return;
		}

		if (x2 - x1 > y2 - y1) {
			int xm = (x1 + x2) / 2;

			int ny2 = min(y_max[xm], y2);
			if (y1 <= ny2) rf(x1, xm, y1, ny2);

			int ny1 = max(y_min[xm], y1);
			if (ny1 <= y2) rf(xm + 1, x2, ny1, y2);
		}
		else {
			int ym = (y1 + y2) / 2;

			int nx2 = min(x_max[ym], x2);
			if (x1 <= nx2) rf(x1, nx2, y1, ym);

			int nx1 = max(x_min[ym], x1);
			if (nx1 <= x2) rf(nx1, x2, ym + 1, y2);
		}
	};
	rf(0, h - 1, 0, w - 1);

	return c;
}


int main() {
	int n, m;
	scanf("%d %d", &n, &m);

	vector<int> a(n), b(m);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	for (int j = 0; j < m; j++) scanf("%d", &b[j]);

	vector<int> c = semiconcave_min_plus_convolution(b, a);

	int K = n + m - 1;
	for (int k = 0; k < K; k++) {
		printf("%d", c[k]);

		if (k < K - 1) printf(" ");
		else printf("\n");
	}

	return 0;
}
