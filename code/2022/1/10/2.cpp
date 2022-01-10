// Author: Z_char 

#include <bits/stdc++.h>

	// head...
	using i64 = long long; using u64 = unsigned long long; using u16 = unsigned short; using i16 = short; using u32 = unsigned int; using pii = std::pair<int, int>; using f64 = double; using f80 = long double;
	template<class T> using ve = std::vector<T>;
	template<class T> using fun = std::function<T>;
	template<class T1, class T2> using pr = std::pair<T1, T2>;
	template<class T> using pq = std::priority_queue<T>;
	template<class T> using lpq = std::priority_queue<T, std::vector<T>, std::greater<T>>;
	template<class T> using gpq = std::priority_queue<T, std::vector<T>, std::less<T>>;
	#define all(x) x.begin(), x.end()
	#define rg(v, l, r) &v[l], &v[r + 1]
	#define vrg(v, l, r) (v).begin() + l, (v).begin() + r + 1
	#define freop(x) (freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout))
	std::mt19937_64 seed(std::chrono::steady_clock::now().time_since_epoch().count());
	#define zxrnd(l, r) std::uniform_int_distribution<i64>(l, r)(seed)
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
		_Timer_check cktime;
	#else 
		u32 def_cnt = 0;
		#define frein(x) ++def_cnt
		#define freout(x) ++def_cnt
		#define debug_line(...) ++def_cnt
		#define debug(...) ++def_cnt
		#define debugpos ++def_cnt
		#define debugstop ++def_cnt
		#define dprint(...) ++def_cnt
		#define dwrite(...) ++def_cnt
		#define asert(...) ++def_cnt
		#define cktime(...) ++def_cnt
	#endif
	template<class T> void memset(int val, T& fir) { memset(fir, val, sizeof fir); }
	template<class T, class... args> void memset(int val, T& fir, args&... arg) { memset(fir, val, sizeof fir), memset(val, arg...); }
	template<class T> 
	inline T read() {
		T x = 0; int f = 1; char ch = getchar();
		for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
		for (;  isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
		return x * f;
	}
	template<class T> inline void read(T &x) { x = read<T>(); }
	template<class T, class... Args> inline void read(T &fir, Args&... args) { read(fir), read(args...); }
	template<class T> 
	inline void write(T x, char ch = '\n') {
		static int stk[32];
		if (x < 0) putchar('-'), x = -x;
		int top = 0;
		do stk[++top] = x % 10, x /= 10; while(x);
		while (top) putchar(stk[top--] + 48);
		putchar(ch);
	}
	template<class T, class... Args> inline void write(T fir, Args... args) { write(fir, ' '), write(args...); }
	// head...

const int N = 1e6 + 86;

namespace SuffixAutoMaton {
	int idx, lst, rt;
	struct sam_node {
		int ch[26], link, len;
		auto& operator[](const int x) { return ch[x]; }
	} tr[N * 2];
	inline void extend(int c) {
		int cur = ++idx;
		tr[cur].len = tr[lst].len + 1;
		while (lst && !tr[lst][c]) tr[lst][c] = cur, lst = tr[lst].link;
		if (lst) {
			int p = lst, q = tr[lst][c];
			if (tr[q].len != tr[p].len + 1) {
				int cp = ++idx;
				tr[cp] = tr[q];
				tr[cp].len = tr[p].len + 1;
				while (p && tr[p][c] == q) tr[p][c] = cp, p = tr[p].link;
				tr[cur].link = tr[q].link = cp;
			}
			else tr[cur].link = q;
		}
		else tr[cur].link = rt;
		lst = cur;
	}
}
using namespace SuffixAutoMaton;

int char_to_int[131];

const int D = 1e9 + 7;

int root[N];
i64 dp[N * 2];

signed main() {
	for (int i = 0; i < 26; ++i)
		char_to_int['a' + i] = i;
	int T = read<int>();
	for (int i = 1; i <= T; ++i) {
		root[i] = ++idx;
		lst = rt = root[i];
		static char str[N];
		scanf("%s", str + 1);
		for (int i = 1; str[i]; ++i)
			extend(char_to_int[int(str[i])]);
	}
	for (int i = T - 1; i >= 1; --i) {
		for (int j = root[i]; j < root[i + 1]; ++j) {
			for (int c = 0; c < 26; ++c) {
				if (!tr[j][c]) {
					tr[j][c] = tr[root[i + 1]][c];
				}
			}
		}
	}
	memset(dp, -1, sizeof dp);
	fun<void(int)> dfs = [&](int x) {
		if (~dp[x]) return;
		dp[x] = 0;
		for (int c = 0; c < 26; ++c) {
			if (tr[x][c]) {
				dfs(tr[x][c]);
				dp[x] += dp[tr[x][c]];
			}
		}
		++dp[x];
		if (dp[x] >= D) {
			if (dp[x] <= D + D) dp[x] -= D;
			else dp[x] %= D;
		}
	};
	dfs(1);
	write(dp[1]);
}
// St. JR bless you
