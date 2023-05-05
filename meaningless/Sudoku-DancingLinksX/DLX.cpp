#include <bits/stdc++.h>

struct DLX {
	// from 0 to m column.
	DLX(int _n, int _m) : n(_n), m(_m), hd(_m + 1), pl(_n * _m), lst(_n + 1, -1) {
		for (int i = 0; i < m; ++i) {
			hd[i].ri = &hd[i + 1];
		} hd[m].ri = &hd[0];
		for (int i = m; i > 0; --i) {
			hd[i].le = &hd[i - 1];
		} hd[0].le = &hd[m];
		for (int i = 0; i <= m; ++i) {
			hd[i].c = i;
		}
		hd[0].s = 999999;
		idx = -1;
	}

	int n, m;
	std::vector<int> ans;

	struct Node {
		Node() { le = ri = up = dn = this; r = c = s = 0; }
		Node* le, *ri, *up, *dn;
		friend bool operator==(Node &a, Node &b) {
			return a.r == b.r && a.c == b.c;
		}
		friend bool operator!=(Node &a, Node &b) {
			return !(a == b);
		}
		int r, c, s;
	};
	std::vector<Node> hd;
	std::vector<Node> pl;
	std::vector<int> lst;

	int idx;

	void add(int r, int c) {
		++idx;
		if (hd[c].s == 0) {
			auto& u = hd[c], &v = pl[idx];

			u.dn = u.up = &v;
			v.dn = v.up = &u;
			u.s += 1;
			v.r = r, v.c = c;
		} else {
			auto& u = *hd[c].up, &v = pl[idx];

			u.dn = &v, v.up = &u;
			hd[c].up = &v, v.dn = &hd[c];
			hd[c].s += 1;
			v.r = r, v.c = c;
		}

		if (lst[r] != -1) {
			if (*pl[lst[r]].ri == pl[lst[r]]) {
				auto& u = pl[lst[r]], &v = pl[idx];
				u.ri = u.le = &v;
				v.ri = v.le = &u;
			} else {
				auto& x = *pl[lst[r]].ri, &y = pl[lst[r]], &z = pl[idx];
				y.ri = &z, z.le = &y;
				z.ri = &x, x.le = &z;
			}
		}
		lst[r] = idx; // record the last one in this row
	}
	void cover(int c) {
		Node* nd = &hd[c];
		nd->le->ri = nd->ri;
		nd->ri->le = nd->le;
		for (auto i = nd->dn; i != nd; i = i->dn) {
			for (auto j = i->ri; j != i; j = j->ri) {
				hd[j->c].s -= 1;
				j->up->dn = j->dn;
				j->dn->up = j->up;
			}
		}
	}
	void restore(int c) {
		Node* nd = &hd[c];
		for (auto i = nd->up; i != nd; i = i->up) {
			for (auto j = i->le; j != i; j = j->le) {
				hd[j->c].s += 1;
				j->up->dn = j;
				j->dn->up = j;
			}
		}
		nd->le->ri = nd;
		nd->ri->le = nd;
	}
	void print() {
		puts("============hd===============");
		for (int i = 0; i <= m; ++i) {
			std::cout << hd[i].r << ' ' << hd[i].c << ' ' << hd[i].ri->r << ' ' << hd[i].ri->c << ' ' << hd[i].dn->r << ' ' << hd[i].dn->c << ' ' << hd[i].s << '\n';
		}
		puts("============pl===============");
		for (int i = 0; i <= idx; ++i) {
			std::cout << pl[i].r << ' ' << pl[i].c << ' ' << pl[i].ri->r << ' ' << pl[i].ri->c << ' ' << pl[i].dn->r << ' ' << pl[i].dn->c << '\n';
		}
		puts("============end==============");
	}
	bool solv() {
		// print();
		if (*hd[0].ri == hd[0]) {
			return true;
		}
		if (hd[0].ri->s == 0) {
			return false;
		}

		auto t = hd[0].ri;
		for (auto i = hd[0].ri->ri; *i != hd[0]; i = i->ri) {
			if (i->s < t->s) {
				t = i;
			}
		}
		// print();
		cover(t->c);
		// print();
		for (auto i = t->dn; i != t; i = i->dn) {
			ans.push_back(i->r);
			for (auto j = i->ri; j != i; j = j->ri) {
				cover(j->c);
				// std::cout << j->c << '\n';
			}
			// system("pause");
			if (solv()) return true;
			for (auto j = i->le; j != i; j = j->le) {
				restore(j->c);
			}
			ans.pop_back();
		}
		restore(t->c);
		return false;
	}
	std::vector<int> get_ans() {
		return ans;
	}
};

const int T = 3;
const int N = T * T + 1;

int r[N][N], c[N][N], np[N][N];
int mp[N][N];

int get_id(int x, int y) {
	x = (x - 1) / T, y = (y - 1) / T + 1;
	return T * x + y;
}

struct Node {
	Node() { r = c = x = 0; }
	Node(int _r, int _c, int _x) { r = _r, c = _c, x = _x; }
	int r, c, x;
};

signed main() {
	while (true) {
		memset(r, 0, sizeof r), memset(c, 0, sizeof c), memset(np, 0, sizeof np);
		for (int i = 1; i < N; ++i) {
			std::string str;
			std::cin >> str;
			for (int j = 1; j < N; ++j) {
				mp[i][j] = str[j - 1] - '0';
			}
		}
		
		for (int i = 1; i < N; ++i) {
			for (int j = 1; j < N; ++j) {
				if (mp[i][j] != 0) {
					int x = mp[i][j];
					r[i][x] = 1, c[j][x] = 1, np[get_id(i, j)][x] = 1;
				}
			}
		}

		int n = 0, m = 0; // choice and cons
		std::map<std::pair<int, int>, int> rid, cid, nid, bid;
		std::vector<Node> vec;
		for (int i = 1; i < N; ++i) {
			for (int j = 1; j < N; ++j) {
				if (!r[i][j]) ++m, rid[{i, j}] = m;
				if (!c[i][j]) ++m, cid[{i, j}] = m;
				if (!np[i][j]) ++m, nid[{i, j}] = m;
				// 仍需要被满足的限制

				if (mp[i][j] == 0) {
					++m, bid[{i, j}] = m;
					for (int x = 1; x < N; ++x) {
						if (r[i][x] || c[j][x] || np[get_id(i, j)][x]) continue;
						++n; // 一种合法选择
						vec.push_back({i, j, x});
					}
				}
			}
		}

		DLX dlx(n, m); // solv
		n = 0;
		for (auto it : vec) {
			++n;
			int i = it.r, j = it.c, x = it.x;
			std::vector<int> con{rid[{i, x}], cid[{j, x}], nid[{get_id(i, j), x}], bid[{i, j}]};
			// 满足的限制
			std::sort(con.begin(), con.end());
			for (auto it : con) {
				dlx.add(n, it);
			}
		}

		if (!dlx.solv()) std::cout << "No Solution!" << '\n';
		else {
			auto ans = dlx.get_ans();
			for (auto it : ans) {
				auto nd = vec[it - 1];
				int r = nd.r, c = nd.c, x = nd.x;
				mp[r][c] = x;
			}

			std::cout << "Ans:" << '\n';
			for (int i = 1; i < N; ++i) {
				for (int j = 1; j < N; ++j) {
					std::cout << mp[i][j] << " \n"[j == N - 1];
				}
			}
		}
		puts("===================================");
	}
}