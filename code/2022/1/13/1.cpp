#include <bits/stdc++.h>

	#ifdef Z_char
		template<class T> inline void debug_out(T x, char ch = '\n') { std::cerr << x << ' ' << ch; }
		template<class T, class... Args> inline void debug_out(T fir, Args... args) { debug_out(fir, ' '), debug_out(args...); }
		#define frein(x) freopen(#x".in", "r", stdin)
		#define freout(x) freopen(#x".out", "w", stdout)
		#define debug_line(...) std::cerr << "work[" << __LINE__ << "]" << ": " << "[" << #__VA_ARGS__ << "]" << " = ", debug_out(__VA_ARGS__)
		#define debug(...) std::cerr << "[" << #__VA_ARGS__ << "] = ", debug_out(__VA_ARGS__)
		#define debugpos std::cerr << "Running " << __FUNCTION__ << " on line " << __LINE__ << "..." << '\n'
		#define debugstop std::cerr << "Running " << __FUNCTION__ << " on line " << __LINE__ << "..." << '\n', system("pause")
		#define dprint(...) fprintf(stderr, __VA_ARGS__)
		#define dwrite(...) write(__VA_ARGS__)
		#define asert(...) assert(__VA_ARGS__)
		struct _Timer_check {
			clock_t val;
			void operator()(bool flg = false) {
				clock_t now = clock();
				if (!flg) debug((1.0 * now - val) / CLOCKS_PER_SEC);
				val = now;
			}
		};
		_Timer_check _CkTimer;
	#else 
		unsigned int def_cnt = 0;
		#define frein(x) ++def_cnt
		#define freout(x) ++def_cnt
		#define debug_line(...) ++def_cnt
		#define debug(...) ++def_cnt
		#define debugpos ++def_cnt
		#define debugstop ++def_cnt
		#define dprint(...) ++def_cnt
		#define dwrite(...) ++def_cnt
		#define asert(...) ++def_cnt
		#define _CkTimer(...) ++def_cnt
	#endif

using i64 = long long;
using poly = std::vector<i64>;

const i64 Inf = std::numeric_limits<i64>::max() / 3;
const int inf = std::numeric_limits<int>::max() / 3;

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
	poly ret(std::max(a.size(), b.size()), -Inf);
	for (size_t i = 0; i < a.size(); ++i) ret[i] = std::max(ret[i], a[i]);
	for (size_t i = 0; i < b.size(); ++i) ret[i] = std::max(ret[i], b[i]); // bug: a.size()
	return ret;
}
poly shift(poly a) {
	if (!a.size()) return poly();
	else return poly(a.begin() + 1, a.end());
}

const int N = 35010;

int n, q, a[N];

namespace seg {
	poly p[N * 4][2][2]; int lt[N * 4][2][2]; size_t ptr[N * 4][2][2];
	inline void pull(int x) {
		int ls = x << 1, rs = x << 1 | 1;
		for (int a = 0; a < 2; ++a) for (int b = 0; b < 2; ++b) for (int c = 0; c < 2; ++c) for (int d = 0; d < 2; ++d) {
			poly now = p[ls][a][b] + p[rs][c][d];
			p[x][a][d] = max(p[x][a][d], now);
			if (b && c) {
				now = shift(now);
				p[x][a][d] = max(p[x][a][d], now);
			}
		}
	}
	void build(int x, int l, int r) {
		if (l == r) {
			p[x][0][0] = {0}, p[x][1][1] = {-Inf, a[l]};
			return;
		}
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
		pull(x);
	}
	void collect(int x, int l, int r, int ql, int qr, std::vector<int> &nds) {
		if (ql <= l && r <= qr) return nds.push_back(x), void();
		int mid = (l + r) >> 1;
		if (qr <= mid) collect(x << 1, l, mid, ql, qr, nds);
		else if (mid < ql) collect(x << 1 | 1, mid + 1, r, ql, qr, nds);
		else collect(x << 1, l, mid, ql, qr, nds), collect(x << 1 | 1, mid + 1, r, ql, qr, nds);
	}
}

struct Yiw {
	int l, r, k, id; i64 ans;
	std::vector<int> nds;
	int el = -inf, er = inf;
	friend bool operator<(const Yiw &a, const Yiw &b) {
		return a.el + a.er < b.el + b.er;
	}
} yiw[N];

inline std::pair<i64, int> solv(int id, i64 add, int tim) {
	std::pair<i64, int> f[2] = {{0, 0}, {-Inf, 0}};
	std::pair<i64, int> g[2];
	for (const auto &tt : yiw[id].nds) {
		using namespace seg;
		g[0] = f[0], g[1] = f[1];
		f[0] = {-Inf, 0}, f[1] = {-Inf, 0};
		for (int a = 0; a < 2; ++a) {
			for (int b = 0; b < 2; ++b) {
				for (int c = 0; c < 2; ++c) {
					if (lt[tt][b][c] != tim) {
						lt[tt][b][c] = tim;
						ptr[tt][b][c] = 0;
					}
					auto &np = p[tt][b][c]; // bug: 犯了弱智错误, 复制 vector 的复杂度奇高无比
					auto &npt = ptr[tt][b][c];
					if (!np.size()) continue;
					while (npt < np.size() - 1 && np[npt + 1] - np[npt] >= -add) ++npt;
					f[c] = std::max(f[c], {g[a].first + np[npt] + npt * add, g[a].second + npt});
					if (a && b) {
						f[c] = std::max(f[c], {g[a].first + np[npt] + (npt - 1) * add, g[a].second + npt - 1});
					}
				}
			}
		}
	}
	return std::max(f[0], f[1]);
}

signed main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cin >> n >> q;
	for (int i = 1; i <= n; ++i)
		std::cin >> a[i];
	seg::build(1, 1, n);
	for (int i = 1; i <= q; ++i) {
		std::cin >> yiw[i].l >> yiw[i].r >> yiw[i].k, yiw[i].id = i;
		seg::collect(1, 1, n, yiw[i].l, yiw[i].r, yiw[i].nds);
	}
	int tim = 0;
	while (true) {
		int cnt = 0;
		++tim;
		std::sort(yiw + 1, yiw + q + 1);
		for (int i = 1; i <= q; ++i) {
			if (yiw[i].el > yiw[i].er) continue;
			++cnt;
			int mid = (yiw[i].el + yiw[i].er) >> 1;
			std::pair<i64, int> ret = solv(i, mid, tim);
			if (ret.second >= yiw[i].k) {
				yiw[i].ans = ret.first - yiw[i].k * mid; // bug: 里面忘记 + add 的影响 这里忘记 - add 的影响
				yiw[i].er = mid - 1;
			}
			else yiw[i].el = mid + 1;
		}
		if (!cnt) break;
	}
	std::sort(yiw + 1, yiw + q + 1, [&](Yiw a, Yiw b) { return a.id < b.id; });
	for (int i = 1; i <= q; ++i)
		std::cout << yiw[i].ans << '\n';
}
