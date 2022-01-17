#include <bits/stdc++.h>

using i64 = long long;
const i64 Inf = std::numeric_limits<i64>::max() / 3;

signed main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, m;
	std::cin >> n >> m;
	std::vector<int> a(n + 1);
	std::vector<i64> s(n + 1);
	std::vector<i64> f(n + 1), g(n + 1);
	for (int i = 1; i <= n; ++i)
		std::cin >> a[i], s[i] = s[i - 1] + a[i], f[i] = s[i] * s[i];
	std::function<void(int, int, int, int)> calc = [&](int l, int r, int dl, int dr) {
		if (l > r) return;
		int dm = -1, mid = (l + r) >> 1; i64 ret = Inf;
		for (int i = dl; i <= dr; ++i) {
			if (i > mid) break;
			i64 now = g[i - 1] + (s[mid] - s[i - 1]) * (s[mid] - s[i - 1]);
			if (now < ret) ret = now, dm = i;
		}
		f[mid] = ret;
		calc(l, mid - 1, dl, dm), calc(mid + 1, r, dm, dr);
	};
	for (int i = 2; i <= m; ++i) {
		f.swap(g);
		std::fill(f.begin() + 1, f.end(), Inf);
		calc(1, n, 1, n);
	}
	std::cout << f[n] * m - s[n] * s[n] << '\n';
}