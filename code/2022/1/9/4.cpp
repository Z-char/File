#include <bits/stdc++.h>

using i64 = int64_t;
using ii = __int128;
const int N = 1e5 + 5;
const i64 Inf = std::numeric_limits<i64>::max();

int n, k;
int L[N], R[N], q[N], hh, tt, bd[N][2];
i64 s[N];
ii f[N];

struct cmp {
	cmp(int id = 0) : id(id) {}
	int id;
	bool operator()(int i, int j) {
		if (!id) return bd[i][id] <= bd[j][id];
		else return bd[i][id] >= bd[j][id];
	}
};

ii calc(int i, int j) {
	return f[j] + (ii)(s[i] - s[j]) * (s[i] - s[j]);
}
ii Y(int i) { return f[i] + (ii)s[i] * s[i]; } // bug: 忘记是 s[i] * s[i], 只写了一个 s[i]
i64 X(int i) { return s[i]; }

bool solv(i64 add, int id) {
	q[hh = tt = 1] = 0;
	for (int i = 1; i <= n; ++i) {
		while (hh < tt) {
			ii A = calc(i, q[hh + 1]), B = calc(i, q[hh]);
			if (A < B) ++hh;
			else if (A == B && cmp(id)(q[hh + 1], q[hh])) ++hh;
			else break;
		}
		f[i] = calc(i, q[hh]) + add, bd[i][id] = bd[q[hh]][id] + 1;
		while (hh < tt) {
			ii A = Y(i) - Y(q[tt - 1]), B = X(i) - X(q[tt - 1]), C = Y(q[tt]) - Y(q[tt - 1]), D = X(q[tt]) - X(q[tt - 1]);
			if (A * D < B * C) --tt;
			else break;
		}
		q[++tt] = i;
		// bug: 忘记 ++tt
	}
	return bd[n][id] >= k;
}

signed main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	std::cin >> n >> k;
	for (int i = 1; i <= n; ++i)
		std::cin >> s[i], s[i] += s[i - 1];
	i64 l = 0, r = Inf, ansk = -1;
	while (l <= r) {
		i64 mid = l + ((r - l) >> 1);
		if (solv(mid, 1)) ansk = mid, l = mid + 1;
		else r = mid - 1;
	}
	solv(ansk, 0), solv(ansk, 1);
	for (int i = 1; i <= n; ++i)
		L[i] = bd[i][0], R[i] = bd[i][1];
	std::vector<int> ans;
	int now = k - 1, lst = n;
	for (int j = n - 1; j >= 1; --j) {
		if (calc(lst, j) + ansk == f[lst] && L[j] <= now && now <= R[j]) {
			ans.push_back(j);
			--now;
			lst = j;
			if (!now) break;
		}
	}
	std::reverse(ans.begin(), ans.end());
	std::cout << "Yes" << '\n';
	for (auto it : ans)
		std::cout << it << ' ';
	std::cout << '\n';
}
