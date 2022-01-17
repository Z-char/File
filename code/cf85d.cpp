#include <bits/stdc++.h>

using i64 = long long;

struct SegmentTree {
	SegmentTree(int n) : n(n), tr(n * 4) {}
	int n;
	struct Node {
		Node() : cnt(0), sum{} {}
		int cnt; i64 sum[5];
		friend Node operator+(const Node &a, const Node &b) {
			Node ret;
			ret.cnt = a.cnt + b.cnt;
			for (int i = 0; i < 5; ++i)
				ret.sum[i] = a.sum[i] + b.sum[(i + 5 - a.cnt % 5) % 5];
			return ret;
		}
		inline void apply(int x, int v) {
			cnt += x, sum[1] += v;
		}
	};
	std::vector<Node> tr;
	void upd(int x, int l, int r, int p, int v) {
		if (l == r) return tr[x].apply(v >= 0 ? 1 : -1, v), void();
		int mid = (l + r) >> 1;
		if (p <= mid) upd(x << 1, l, mid, p, v);
		else upd(x << 1 | 1, mid + 1, r, p, v);
		tr[x] = tr[x << 1] + tr[x << 1 | 1];
	}
	inline void upd(int p, int x) { ++p, upd(1, 1, n, p, x); }
	inline i64 qry() { return n ? tr[1].sum[3] : 0; }
};

struct Operation {
	Operation(int id = 0, int x = 0) : id(id), x(x) {}
	int id, x;
};

signed main() {
	int n;
	std::cin >> n;
	std::vector<int> nums;
	std::vector<Operation> opt;
	for (int i = 1; i <= n; ++i) {
		std::string str; int op;
		std::cin >> str;
		if (str != "sum") std::cin >> op;
		if (str == "add") opt.push_back({0, op}), nums.push_back(op);
		else if (str == "del") opt.push_back({1, op});
		else opt.push_back({2, 0});
	}
	std::sort(nums.begin(), nums.end()), nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
	SegmentTree seg(n);
	for (int i = 0; i < n; ++i) {
		int id = opt[i].id;
		if (id == 2) std::cout << seg.qry() << '\n';
		else {
			opt[i].x = std::lower_bound(nums.begin(), nums.end(), opt[i].x) - nums.begin();
			seg.upd(opt[i].x, (opt[i].id == 0) ? nums[opt[i].x] : -nums[opt[i].x]);
		}
	}
}