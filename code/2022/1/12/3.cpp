#include <bits/stdc++.h>

template<class T> 
inline T read() {
	T x = 0; int f = 1; char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
	for (;  isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
	return x * f;
}
template<class T> inline void read(T &x) { x = read<T>(); }
template<class T, class... Args> inline void read(T &fir, Args&... args) { read(fir), read(args...); }

using i64 = long long;

const int N = 2e5 + 5;

int n, m, fa[N], son[N], top[N];
i64 sum[N], pre_ans[N], pre_pre[N], sz[N];
std::vector<int> G[N];

void dfs(int x) {
	sz[x] = 1, pre_ans[x] = -sum[x], pre_pre[x] = -1;
	for (const auto &y : G[x]) {
		dfs(y);
		fa[y] = x, sz[x] += sz[y], sum[x] += sum[y];
		if (sz[y] > sz[son[x]]) son[x] = y;
		pre_ans[x] -= sz[y] * sum[y], pre_pre[x] -= sz[y] * sz[y];
	}
	pre_ans[x] += sz[x] * sum[x], pre_pre[x] += sz[x] * sz[x];
}

int dfn[N], idfn[N], dtot;

void dcs(int x, int topf) {
	dfn[++dtot] = x, idfn[x] = dtot, top[x] = topf;
	if (son[x]) dcs(son[x], topf);
	for (const auto &y : G[x]) {
		if (y ^ son[x]) {
			dcs(y, y);
		}
	}
}

namespace seg {
	i64 ans[N], pre[N][2], tag[N * 4][3];
	void build(int x, int l, int r) {
		if (l == r) {
			pre[l][0] = pre_pre[dfn[l]], pre[l][1] = sz[dfn[l]] - sz[dfn[l + 1]];
			ans[l] = pre_ans[dfn[l]];
			return;
		}
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	inline void pushdown(int x) {
		if (tag[x][0]) {
			tag[x << 1][0] += tag[x][0], tag[x << 1 | 1][0] += tag[x][0];
			tag[x][0] = 0;
		}
		if (tag[x][1]) {
			tag[x << 1][1] += tag[x][1], tag[x << 1 | 1][1] += tag[x][1];
			tag[x][1] = 0;
		}
		if (tag[x][2]) {
			tag[x << 1][2] += tag[x][2], tag[x << 1 | 1][2] += tag[x][2];
			tag[x][2] = 0;
		}
	}
	i64 qry(int x, int l, int r, int p) {
		if (l == r) {
			if (tag[x][0]) ans[l] += pre[l][0] * tag[x][0], tag[x][0] = 0;
			if (tag[x][1]) ans[l] += pre[l][1] * tag[x][1], tag[x][1] = 0;
			if (tag[x][2]) ans[l] += tag[x][2], tag[x][2] = 0;
			return ans[l];
		}
		pushdown(x);
		int mid = (l + r) >> 1;
		if (p <= mid) return qry(x << 1, l, mid, p);
		else return qry(x << 1 | 1, mid + 1, r, p);
	}
	void upd(int x, int l, int r, int ql, int qr, int id, i64 v) {
		if (ql > qr) return;
		if (ql <= l && r <= qr) {
			tag[x][id] += v;
			return;
		}
		int mid = (l + r) >> 1;
		if (qr <= mid) upd(x << 1, l, mid, ql, qr, id, v);
		else if (mid < ql) upd(x << 1 | 1, mid + 1, r, ql, qr, id, v);
		else upd(x << 1, l, mid, ql, qr, id, v), upd(x << 1 | 1, mid + 1, r, ql, qr, id, v);
	}
}

inline void upd_point(int x, i64 v) {
	seg::upd(1, 1, n, idfn[x], idfn[x], 2, (sz[x] - 1) * v);
	while (top[x] != 1) {
		seg::upd(1, 1, n, idfn[top[x]], idfn[fa[x]], 1, v);
		x = top[x];
		seg::upd(1, 1, n, idfn[fa[x]], idfn[fa[x]], 2, (sz[fa[x]] - sz[x]) * v);
		x = fa[x];
	}
	seg::upd(1, 1, n, idfn[1], idfn[fa[x]], 1, v);
}
inline void upd_sub(int x, i64 v) {
	seg::upd(1, 1, n, idfn[x], idfn[x] + sz[x] - 1, 0, v);
	v *= sz[x];
	while (top[x] != 1) {
		seg::upd(1, 1, n, idfn[top[x]], idfn[fa[x]], 1, v);
		x = top[x];
		seg::upd(1, 1, n, idfn[fa[x]], idfn[fa[x]], 2, (sz[fa[x]] - sz[x]) * v);
		x = fa[x];
	}
	seg::upd(1, 1, n, idfn[1], idfn[fa[x]], 1, v);
}

signed main() {
	read(n, m);
	for (int i = 1; i <= n; ++i)
		read(sum[i]);
	for (int i = 2; i <= n; ++i) {
		int fa = read<int>();
		G[fa].push_back(i);
	}
	dfs(1), dcs(1, 1);
	seg::build(1, 1, n);
	for (int _ = 1; _ <= m; ++_) {
		int opt = read<int>();
		if (opt == 1) {
			int x = read<int>(); i64 y = read<i64>();
			upd_point(x, y);
		}
		else if (opt == 2) {
			int x = read<int>(); i64 y = read<i64>();
			upd_sub(x, y);
		}
		else {
			int x = read<int>();
			i64 ret = seg::qry(1, 1, n, idfn[x]);
			std::cout << ret << '\n';
		}
	}
}
