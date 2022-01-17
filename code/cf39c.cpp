#include <bits/stdc++.h>

int n;

signed main() {
	std::cin >> n;
	std::vector<int> disc;
	std::vector<std::pair<int, int>> p(n + 1);
	for (int i = 1; i <= n; ++i) {
		int c, r;
		std::cin >> c >> r;
		disc.push_back(c - r), disc.push_back(c + r);
		p[i].first = c - r, p[i].second = c + r;
	}
	std::sort(disc.begin(), disc.end()), disc.erase(std::unique(disc.begin(), disc.end()), disc.end());
	int len = int(disc.size());
	std::vector<std::vector<std::pair<int, int>>> lpos(len + 1);
	std::map<std::pair<int, int>, int> set;
	for (int i = 1; i <= n; ++i) {
		p[i].first = std::lower_bound(disc.begin(), disc.end(), p[i].first) - disc.begin() + 1;
		p[i].second = std::lower_bound(disc.begin(), disc.end(), p[i].second) - disc.begin() + 1;
		lpos[p[i].first].push_back({p[i].second, i});
		set[p[i]] = i;
	}
	std::vector<std::vector<int>> f(len + 1, std::vector<int>(len + 1, -1)), did(len + 1, std::vector<int>(len + 1));
	std::function<int(int, int)> dp = [&](int l, int r) {
		if (l > r) return 0;
		if (~f[l][r]) return f[l][r];
		f[l][r] = dp(l + 1, r);
		for (const auto &[k, id] : lpos[l]) {
			if (k >= r) continue;
			if (f[l][r] < dp(l, k) + dp(k, r)) {
				f[l][r] = f[l][k] + f[k][r];
				did[l][r] = k;
			}
		}
		if (set.count({l, r})) ++f[l][r];
		return f[l][r];
	};
	std::cout << dp(1, len) << '\n';
	// puts("");
	std::function<void(int, int)> dfs = [&](int l, int r) {
		if (l > r) return;
		if (set.count({l, r})) std::cout << set[{l, r}] << ' ';
		// std::cout << l << ' ' << r << '\n';
		if (did[l][r]) /*std::cout << did[l][r] << ' ',*/ dfs(l, did[l][r]), dfs(did[l][r], r);
		else dfs(l + 1, r);
	};
	dfs(1, len);
	puts("");
}