#include <bits/stdc++.h>

using ll = long long;
const int N = 1e6 + 86;

int n, m;
std::basic_string<int> G[N];
int dfn[N], fat[N], siz[N], dsu[N];
// std::set<std::pair<ll, int>> set;
std::priority_queue<std::pair<ll, int>, std::vector<std::pair<ll, int>>, std::greater<std::pair<ll, int>>> set;
std::vector<std::pair<std::pair<int, int>, int>> ask;
ll ans[N], v[N];
int del[N];

int find(int x) { return x == dsu[x] ? x : dsu[x] = find(dsu[x]); }

struct FenwickTree {
	ll c[N];
	void upd(int x, ll v) {
		if (!x) return;
		x = dfn[x];
		for (; x <= n; x += x & -x)
			c[x] += v;
	}
	ll _qry(int x, ll ret = 0) {
		for (; x; x -= x & -x)
			ret += c[x];
		return ret;
	}
	ll qry(int x) {
		return _qry(dfn[x] + siz[x] - 1) - _qry(dfn[x] - 1);
	}
} sum, sz;

void dfs(int x) {
	dfn[x] = ++dfn[0], siz[x] = 1;
	for (auto it : G[x])
		fat[it] = x, dfs(it), siz[x] += siz[it];
}
ll X;

ll f(int x) {
	return sum.qry(x) + X * sz.qry(x);
}

void link(int x) {
	if (x == 1) return;
	// auto it = set.find({v[x], x});
	// set.erase(it);
	del[x] = true;
	dsu[x] = fat[x];
	ll nowsiz = sz.qry(x), nowsum = sum.qry(x);
	int fafa = find(fat[x]);
	sum.upd(fat[x], nowsum), sum.upd(fat[fafa], -nowsum);
	sz.upd(fat[x], nowsiz), sz.upd(fat[fafa], -nowsiz);
	if (f(fafa) >= 0 || fafa == 1) {
		link(fafa);
	}
	else {
		// auto it = set.find({v[fafa], fafa});
		// set.erase(it);
		v[fafa] = std::ceil(-1.0 * sum.qry(fafa) / sz.qry(fafa));
		// set.insert({v[fafa], fafa});
		set.push({v[fafa], fafa});
	}
}

signed main() {
	scanf("%d%d", &n, &m);

	for (int i = 2; i <= n; ++i) {
		int fa;
		scanf("%d", &fa);
		G[fa] += i;
	}
	dfs(1);

	for (int i = 1; i <= n; ++i) {
		dsu[i] = i;
		int v;
		scanf("%d", &v);
		sum.upd(i, v), sum.upd(fat[i], -v), sz.upd(i, 1), sz.upd(fat[i], -1);
		::v[i] = -v;
		// if (i != 1) set.insert({::v[i], i}); // 什么时候和父亲连接
		if (i != 1) set.push({::v[i], i});
	}
	for (int i = 1; i <= m; ++i) {
		int x, u;
		scanf("%d%d", &u, &x);
		ask.push_back({{x, u}, i});
	}
	std::sort(ask.begin(), ask.end());
	for (int _ = 0; _ < m; ++_) {
		X = ask[_].first.first; int id = ask[_].second, u = ask[_].first.second;
		while (set.size() && set.top().first <= X) {
			int x = set.top().second; set.pop();
			if (del[x]) continue;
			link(x);
			// auto it = set.begin();
			// link(it->second);
		}
		ans[id] = f(u);
	}
	for (int i = 1; i <= m; ++i) 
		printf("%lld\n", ans[i]);
}