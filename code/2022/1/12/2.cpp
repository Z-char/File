#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;

namespace Z {
	const int D = 1e9 + 7;

	inline i64 pwer(i64 a, i64 b, i64 ret = 1) {
		for (; b; b >>= 1, a = a * a % D)
			if (b & 1) ret = ret * a % D;
		return ret;
	}

	struct mint {
		mint(i64 v = 0) : v(v) {}
		mint(const mint &a) { *this = a; }
		i64 v;
		friend i64 operator&(const mint &a) { return a.v; }
		friend mint pwer(const mint &a, int k) { return mint(pwer(a.v, k)); }
		friend mint operator+(const mint &a, const mint &b) { return mint(a.v + b.v >= D ? a.v + b.v - D : a.v + b.v); }
		friend mint operator-(const mint &a, const mint &b) { return mint(a.v - b.v < 0 ? a.v - b.v + D : a.v - b.v); }
		friend mint operator*(const mint &a, const mint &b) { return mint(a.v * b.v % D); }
		friend mint operator/(const mint &a, const mint &b) { return mint(a.v * pwer(b.v, D - 2) % D); }
		friend bool operator==(const mint &a, const mint &b) { return a.v == b.v; }
		friend bool operator!=(const mint &a, const mint &b) { return a.v != b.v; }
		friend mint operator-(const mint &a) { return mint(a.v ? D - a.v : 0); }
		friend mint& operator+=(mint &a, const mint &b) { a = a + b; return a; }
		friend mint& operator-=(mint &a, const mint &b) { a = a - b; return a; }
		friend mint& operator*=(mint &a, const mint &b) { a = a * b; return a; }
		friend mint& operator/=(mint &a, const mint &b) { a = a / b; return a; }
		friend mint operator""_mint(u64 val) { return mint(val); }
		friend std::istream& operator>>(std::istream &fin, mint &a) { fin >> a.v; return fin; }
		friend std::ostream& operator<<(std::ostream &fout, mint &a) { fout << a.v; return fout; }
	};
} using Z::mint;

const int M = 110;

struct mat {
	mat(int n = 0) : n(n), m(n) {}
	mat(int n, int m) : n(n), m(m) {}
	int n, m;
	mint a[M][M];
	auto& operator[](const int x) { return a[x]; }
	const auto& operator[](const int x) const { return a[x]; }
	friend mat operator*(const mat &a, const mat &b) {
		mat ret(a.n, b.m);
		for (int i = 0; i < ret.n; ++i) for (int k = 0; k < a.m; ++k) for (int j = 0; j < ret.m; ++j)
			ret[i][j] += a[i][k] * b[k][j];
		return ret;
	}
};

signed main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	i64 n; int m;
	std::cin >> n >> m;
	--n;
	mat f(1, m - 1), tr(m - 1, m - 1);
	f[0][0] = m;
	for (int j = 1; j < m; ++j) {
		if (j != m - 1) tr[j - 1][j - 1 + 1] = m - j;
		for (int k = j; k > 0; --k)
			tr[j - 1][k - 1] = 1;
	}
	for (; n; n >>= 1, tr = tr * tr)
		if (n & 1) f = f * tr;
	mint sum = 0;
	for (int j = 1; j < m; ++j)
		sum += f[0][j - 1];
	std::cout << sum << '\n';
}