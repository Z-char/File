// Author: Z_char 

#include <bits/stdc++.h>

	// head...
	using ll = long long; using ull = unsigned long long; using us = unsigned short; using ui = unsigned int; using pii = std::pair<int, int>; using db = double; using ld = long double;
	using i64 = long long; using u64 = unsigned long long; using u16 = unsigned short; using u32 = unsigned int; using f64 = double; using f80 = long double;
	template<class T> using ve = std::vector<T>;
	template<class T> using fun = std::function<T>;
	template<class T1, class T2> using pr = std::pair<T1, T2>;
	template<class T> using priq = std::priority_queue<T>;
	template<class T> using Lpq = std::priority_queue<T, std::vector<T>, std::greater<T>>;
	template<class T> using Gpq = std::priority_queue<T, std::vector<T>, std::less<T>>;
	#define gtt(x, i) std::get<i>(x)
	#define all(x) x.begin(), x.end()
	#define rg(v, l, r) &v[l], &v[r + 1]
	#define vrg(v, l, r) (v).begin() + l, (v).begin() + r + 1
	#define freop(x) (freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout))
	std::mt19937_64 mt_rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	#define zxrnd(l, r) std::uniform_int_distribution<i64>(l, r)(mt_rnd)
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

const int N = 1e5 + 5;
const int LOG = 62;

int n;
i64 a[N], xor_sum;
i64 bit[LOG + 1];
i64 b[LOG + 1]; int bcnt = 0;

inline void ins(i64 x) {
	for (int i = 0; i < bcnt; ++i) {
		if (x & b[i]) {
			if (bit[i]) x ^= bit[i];
			else return bit[i] = x, void();
		}
	}
}
i64 get_max() {
	i64 ret = 0;
	for (int i = 0; i < bcnt; ++i) {
		if (!(ret & b[i])) ret ^= bit[i];
	}
	return ret;
}

signed main() {
	n = read<int>();
	for (int i = 1; i <= n; ++i) a[i] = read<i64>(), xor_sum ^= a[i];
	for (int i = LOG; i >= 0; --i) if (!((xor_sum >> i) & 1)) b[bcnt++] = 1ll << i;
	for (int i = LOG; i >= 0; --i) if ((xor_sum >> i) & 1) b[bcnt++] = 1ll << i;
	for (int i = 1; i <= n; ++i) ins(a[i]);
	i64 s2 = get_max(), s1 = xor_sum ^ s2;
	write(s1);
}
// St. JR bless you
