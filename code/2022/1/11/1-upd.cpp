#include <bits/stdc++.h>

#define dbg(x) std::cerr << #x << " = " << x << '\n'
#define dpt(...) fprintf(stderr, __VA_ARGS__)
using i64 = long long;

const int N = 2e5 + 5;
const i64 Inf = std::numeric_limits<i64>::max() / 3;

struct Edge {
	Edge() { to = nxt = w = 0; }
	Edge(int to, int nxt, int w) : to(to), nxt(nxt), w(w) {}
	int to, nxt, w;
} e[N * 2];

int n, h[N], etot = 1;
inline void add(int u, int v, int w) {
	e[++etot] = Edge(v, h[u], w), h[u] = etot;
	e[++etot] = Edge(u, h[v], w), h[v] = etot;
}

using poly = std::vector<i64>;

poly operator+(poly a, poly b) {
	if (!a.size() || !b.size()) return poly();
	poly ret;
	ret.reserve(a.size() + b.size());
	ret.push_back(a[0] + b[0]);
	size_t p = 1, q = 1; i64 w = a[0] + b[0];
	while (p < a.size() && q < b.size()) {
		if (a[p] - a[p - 1] > b[q] - b[q - 1]) ret.push_back(w += a[p] - a[p - 1]), ++p;
		else ret.push_back(w += b[q] - b[q - 1]), ++q;
	}
	while (p < a.size()) ret.push_back(w += a[p] - a[p - 1]), ++p;
	while (q < b.size()) ret.push_back(w += b[q] - b[q - 1]), ++q;
	return ret;
}
poly max(poly a, poly b) {
	poly c(std::max(a.size(), b.size()), -Inf);
	for (size_t i = 0; i < a.size(); ++i) c[i] = std::max(c[i], a[i]);
	for (size_t i = 0; i < b.size(); ++i) c[i] = std::max(c[i], b[i]);
	return c;
}
poly apply(poly a, i64 add) {
	a.insert(a.begin(), -Inf);
	for (size_t i = 1; i < a.size(); ++i) a[i] += add; // bug: 福至心灵？从上往下瞎看觉得这部分随便写突然发现 i 从 0 开始
	return a;
}

int sz[N], son[N], fa[N]; i64 val[N];
poly f[N][2];

struct mat {
	mat() {}
	mat(int x) { for (int c : {0, 1}) g[c][c] = f[x][c], g[c][c ^ 1] = {-Inf}; }
	poly g[2][2];
	auto& operator[](const int x) { return g[x]; }
	const auto& operator[](const int x) const { return g[x]; }
};

mat smwc(int l, int r, const std::vector<int> &s) {
	if (l == r) return mat(s[l]);
	int mid = (l + r) >> 1;
	mat ls = smwc(l, mid, s), rs = smwc(mid + 1, r, s);
	mat ret;
	for (int a = 0; a < 2; ++a) for (int b = 0; b < 2; ++b) for (int c = 0; c < 2; ++c) for (int d = 0; d < 2; ++d) {
		poly now = ls[a][b] + rs[c][d];
		ret[a][d] = max(ret[a][d], now);
		if (!b && !c) {
			int _a = a, _d = d; // bug: 不要做出修改循环变量的蠢事啊混蛋!
			if (l == mid) _a = 1;
			if (mid + 1 == r) _d = 1;
			ret[_a][_d] = max(ret[_a][_d], apply(now, val[s[mid + 1]]));
		}
	}
	return ret;
}

inline mat mwc(int x) { // merge wight chain
	std::vector<int> s;
	for (; x; x = son[x]) s.push_back(x);
	return smwc(0, s.size() - 1, s);
}

struct lmat {
	lmat() {}
	lmat(int x) {
		mat ret = mwc(x);
		h[0] = {0}, h[1] = {-Inf}; // 这里的 0/1 表示父亲是否被匹配
		for (int a = 0; a < 2; ++a) for (int b = 0; b < 2; ++b) {
			h[0] = max(h[0], ret[a][b]);
			if (!a) h[1] = max(h[1], apply(ret[a][b], val[x]));
		}
	}
	poly h[2];
	auto& operator[](const int x) { return h[x]; }
	const auto& operator[](const int x) const { return h[x]; }
};

lmat smls(int l, int r, std::vector<int> &s) {
	if (l == r) return lmat(s[l]);
	int mid = (l + r) >> 1;
	lmat ls = smls(l, mid, s), rs = smls(mid + 1, r, s);
	lmat ret;
	for (int a = 0; a < 2; ++a) for (int b = 0; b < 2; ++b) {
		if (a && b) continue;
		ret[a | b] = max(ret[a | b], ls[a] + rs[b]);
	}
	return ret;
}

inline void mls(int x) { // merge light sons, 表示这个点目前和所有轻子树合并为一个点
	std::vector<int> s;
	for (int p = h[x], y; p && (y = e[p].to, true); p = e[p].nxt)
		if (y != fa[x] && y != son[x]) s.push_back(y);
	if (!s.size()) { // bug: 忽略没有轻儿子的情况 忽略没有轻儿子也需要更新 f 的情况
		f[x][0] = {0}, f[x][1] = {-Inf};
		return;
	}
	lmat ret = smls(0, s.size() - 1, s);
	f[x][0] = ret[0], f[x][1] = ret[1];
}

void dfs(int x, int fax) {
	sz[x] = 1, fa[x] = fax;
	for (int p = h[x], y; p && (y = e[p].to, true); p = e[p].nxt) {
		if (y != fa[x]) {
			dfs(y, x);
			sz[x] += sz[y], val[y] = e[p].w;
			if (sz[y] > sz[son[x]]) son[x] = y;
		}
	}
	mls(x);
}

signed main() {
	std::cin >> n;
	for (int i = 1; i < n; ++i) {
		int u, v, w;
		std::cin >> u >> v >> w;
		add(u, v, w);
	}
	dfs(1, 0);
	mat lst = mwc(1);
	poly ret;
	for (int a = 0; a < 2; ++a) for (int b = 0; b < 2; ++b) 
		ret = max(ret, lst[a][b]);
	for (int i = 1; i < n; ++i) {
		if (i < int(ret.size())) std::cout << ret[i];
		else std::cout << '?';
		std::cout << " \n"[i == n - 1];
	}
}
