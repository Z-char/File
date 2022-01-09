#include <bits/stdc++.h>

using f80 = long double;

const f80 eps = 1e-12;
const int N = 1e5 + 5;

int n, k;
f80 f[N + 5];
int g[N + 5], q[N + 5];

inline f80 slope(int x, int y) { return (x[f] - y[f]) / (x - y); };

inline bool check(f80 add) {
	int hh = 1, tt = 1;
	q[tt] = 0;
	for (int i = 1; i <= n; ++i) {
		while (hh < tt && slope(q[hh], q[hh + 1]) - 1.0 / i > eps) ++hh;
		f[i] = f[q[hh]] + f80(i - q[hh]) / i + add, g[i] = g[q[hh]] + 1;
		while (hh < tt && slope(q[tt], i) - slope(q[tt - 1], q[tt]) > eps) --tt;
		q[++tt] = i;
	} return g[n] >= k;
}

signed main() {
	std::cin.tie(0)->sync_with_stdio(false);
	std::cin >> n >> k;
	f80 l = -1e6, r = 1e6;
	for (int i = 1; i <= 100; ++i) {
		f80 mid = (l + r) / 2;
		if (check(mid)) r = mid;
		else l = mid;
	} check(r), printf("%.9Lf\n", f[n] - k * r);
}
