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

const int N = 1e5 + 5;

int n, a[N];

signed main() {
	// freopen("data.in", "r", stdin);
	std::cin.tie(nullptr)->sync_with_stdio(false);

	// std::cin >> n;
	n = read<int>();
	std::fill_n(a + 1, n, 2);
	for (int i = 1; i < n; ++i) {
		int u, v;
		// std::cin >> u >> v;
		read(u, v);
		--a[u], --a[v];
	}
	std::priority_queue<int> pq;
	for (int i = 1; i <= n; ++i)
		pq.push(a[i]);
	int sum[2] = {}, cur = 0;
	while (pq.size()) sum[cur] += pq.top(), pq.pop(), cur ^= 1;
	std::cout << (sum[0] - sum[1]) / 2 << '\n';
}
