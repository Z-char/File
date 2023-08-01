#include <bits/stdc++.h>

#ifdef Z_char
	struct _Timer_check {
		int cnt = 0;
		clock_t val, st;
		void operator()(const char *str = NULL, bool tag = false) {
			clock_t now = clock();
			if (str != NULL) {
				std::cerr << str << ": ";
				if (!tag) std::cerr << (1.0 * now - val) / CLOCKS_PER_SEC << '\n';
				else std::cerr << (1.0 * now - st) / CLOCKS_PER_SEC << '\n';
			}
			val = now;
			if (!cnt) st = now, ++cnt;
		}
	};
	_Timer_check cktime;
#else 
	unsigned int def_cnt = 0;
	#define cktime(...) ++def_cnt
#endif

const int N = 8869;
// const int N = 50;

std::string s[N + 5]; // words
int son[N * 10][800], tr_idx = 0;
int reid[N * 10];
int rt; // root

void scan() {
	std::ifstream fin("scramble.txt");
	for (int i = 1; i <= N; ++i) {
		fin >> s[i];
	}
}
int trans(std::string s) { // w is zero, r is one, o is two.
	int ret = 0, bse = 1;
	for (int i = 0; i < 5; ++i) {
		int now = -1;
		if (s[i] == 'r') now = 1;
		else if (s[i] == 'o') now = 2;
		else if (s[i] == 'w') now = 0;
		ret += now * bse, bse *= 3;
	}
	return ret;
}
int mthre(int si, int sj) {
	std::string str[2];
	str[0] = s[si], str[1] = s[sj]; // ans is str[1], match with str[0]
	std::string mth;
	mth.resize(5, 't');
	for (int i = 0; i < 5; ++i) {
		if (str[0][i] == str[1][i]) {
			mth[i] = 'r';
		}
	}
	std::vector<int> apr(26);
	for (int i = 0; i < 5; ++i) {
		if (mth[i] != 'r') {
			++apr[str[1][i] - 'a'];
		}
	}
	for (int i = 0; i < 5; ++i) {
		if (mth[i] != 'r' && apr[str[0][i] - 'a']) {
			// --apr[str[0][i] - 'a'];
			mth[i] = 'o';
		} else if (mth[i] != 'r') {
			mth[i] = 'w';
		}
	}
	// std::cerr << mth << '\n';
	return trans(mth);
}
int mths[N + 5][N + 5];
void pre() {
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			mths[i][j] = mthre(i, j);
		}
	}
}
int mth(int i, int j) {
	return mths[i][j];
}
int mdep;
const int def = 10;
int build_tree(std::vector<int> now, int dep) {
	// if (dep >= 7) {
	// 	puts("post");
	// 	exit(0);
	// }
	mdep = std::max(mdep, dep);
	if ((int)now.size() == 1) {
		reid[++tr_idx] = now[0];
		// std::cerr << tr_idx << '\n';
		return tr_idx;
	}
	int n = (int)now.size(), mini = 2147483647, id = -1;
	// std::cerr << "siz=" << now.size() << ", dep=" << dep << "\n";

	std::vector<std::vector<int>> sum(N + 1, std::vector<int>(800, 0));
	for (int i = 1; i <= N; ++i) { // let s[i] to be the root
		// if (__builtin_popcount(n - i) == 1) std::cerr << "Remain: " << n - i << '\n';
		// if (n <= 10) std::cerr << i << " as root?\n";
		for (int j = 0; j < n; ++j) {
			if (i != now[j]) {
				int mm = mth(i, now[j]);
				++sum[i][mm];
			}
		}

		int ss = 0;
		for (int j = 0; j < 800; ++j) {
			ss += sum[i][j] * sum[i][j];
		}
		if (ss < mini) {
			mini = ss;
			id = i;
		}
	}

	reid[++tr_idx] = id; // using id to get string
	int now_idx = tr_idx;
	// std::cerr << "dep: " << dep << ", pivot: [" << id << ", " << s[id] << "]" << ", ret: " << now_idx << '\n';
	// std::cerr << "siz: " << (int)now.size() << '\n';
	// std::cerr << "{";
	// for (int i = 0; i < std::min(7, (int)now.size()); ++i) {
	// 	std::cerr << s[now[i]] << " ";
	// }
	// if ((int)now.size() > 7) {
	// 	std::cerr << "... more";
	// }
	// std::cerr << "}\n";

	for (int j = 0; j < 800; ++j) {
		if (!sum[id][j]) {
			continue;
		}
		std::vector<int> nxt;
		for (int i = 0; i < n; ++i) {
			if (now[i] != id && mth(id, now[i]) == j) {
				nxt.push_back(now[i]);
			}
		}

		son[now_idx][j] = build_tree(nxt, dep + 1);
	}
	return now_idx;
}

void test() {
	s[1] = "panic", s[2] = "apple";
	mth(1, 2);

	system("pause");
}

std::string mthp(std::string sa, std::string sb) {
	std::string str[2];
	str[0] = sa, str[1] = sb; // ans is str[1], match with str[0]
	std::string mth;
	mth.resize(5, 't');
	for (int i = 0; i < 5; ++i) {
		if (str[0][i] == str[1][i]) {
			mth[i] = 'r';
		}
	}
	std::vector<int> apr(26);
	for (int i = 0; i < 5; ++i) {
		if (mth[i] != 'r') {
			++apr[str[1][i] - 'a'];
		}
	}
	for (int i = 0; i < 5; ++i) {
		if (mth[i] != 'r' && apr[str[0][i] - 'a']) {
			--apr[str[0][i] - 'a'];
			mth[i] = 'o';
		} else if (mth[i] != 'r') {
			mth[i] = 'w';
		}
	}
	return mth;
}

char sure[6];
bool noway[6][27]; // i cannot be j
int higherthan[27];

bool Check(std::string s) {
	for (int i = 0; i < 5; ++i) {
		if (sure[i] && s[i] != sure[i]) {
			return false;
		}
		for (int t = 0; t < 26; ++t) {
			if (noway[i][t] && s[i] - 'a' == t) {
				return false;
			}
		}
	}
	std::vector<int> cnt(26);
	for (int i = 0; i < 5; ++i) {
		if (!sure[i]) {
			++cnt[s[i] - 'a'];
		}
	}
	for (int i = 0; i < 26; ++i) {
		if (cnt[i] < higherthan[i]) {
			return false;
		}
	}
	return true;
}

signed main() {
	// std::ios::sync_with_stdio(false);
	// std::cin.tie(nullptr);

	// std::cerr << mthp("aayyy","xaxxx") << "\n";
	// system("pause");

	// test();

	cktime("start");
	puts("if you have any exculuded letters(input 0 to exit):");
	while (true) {
		char x;
		std::cin >> x;
		if (x == '0') {
			break;
		} else if ('a' <= x && x <= 'z') {
			int t = x - 'a';
			for (int i = 0; i < 5; ++i) {
				noway[i][t] = 1;
			}
		} else if ('A' <= x && x <= 'Z') {
			int t = x - 'A';
			for (int i = 0; i < 5; ++i) {
				noway[i][t] = 1;
			}
		}
	}
	puts("if you have any sure letters(input 0 0 to exit, letter position):");
	while (true) {
		char x; int p;
		std::cin >> x >> p;
		--p;
		if (x == '0') {
			break;
		} else if ('a' <= x && x <= 'z') {
			sure[p] = x;
		} else if ('A' <= x && x <= 'Z') {
			sure[p] = x - 'A' + 'a';
		}
	}
	puts("if you have any maybe letters(input 0 0 to exit, letter count):");
	while (true) {
		char x; int c;
		std::cin >> x >> c;
		if (x == '0') {
			break;
		} else {
			int tr = 0;
			if ('a' <= x && x <= 'z') {
				tr = x - 'a';
				higherthan[x - 'a'] = c;
			} else if ('A' <= x && x <= 'Z') {
				tr = x - 'A';
				higherthan[x - 'A'] = c;
			}
			puts("this letter cannot be in how many position?");
			std::cin >> c;
			puts("please input these positions:");
			for (int i = 1; i <= c; ++i) {
				int p;
				std::cin >> p; --p;
				noway[p][tr] = 1;
			}
		}
	}
	scan();
	pre();
	cktime("pre match");

	std::vector<int> now;
	for (int i = 1; i <= N; ++i) {
		if (Check(s[i])) now.push_back(i);
	}

	rt = build_tree(now, 1);
	cktime("finish the stratagy tree");
	std::cerr << "max dep: " << mdep << '\n';

	while (1) {
		puts("now start guess. input no to let me know my ans is incorrect, or input yes. If you input no, then input the status like wwrow.(w means wrong, r means right, o means other place)");
		int now = rt;
		bool flg = false;
		while (now) {
			// std::cerr << reid[now] << ' ' << now << '\n';
			std::cout << "The Answer word that I guess is: " << s[reid[now]] << ", " << "yes or no?" << '\n';
			bck:;
			std::cin >> s[0];
			if (s[0][0] == 'y') {
				flg = true;
				break;
			} else if (s[0][0] == 'n') {
				puts("please input your word's status(w means wrong(grey), r means right(green), o means other place(gold)): ");
				std::cin >> s[0];
				now = son[now][trans(s[0])];
			} else {
				puts("you seem to input something wrong? try it again.");
				goto bck;
			}
		}
		if (flg) {
			puts("so ez! press again to play again, exit to exit");
			bck1:;
			std::cin >> s[0];
			if (s[0][0] == 'a') {
				;
			} else if (s[0][0] == 'e') {
				return 0;
			} else {
				puts("you seem to input something wrong? try it again.");
				goto bck1;
			}
		} else {
			puts("I'm sorry, I can't guess it. press a to play again, e to exit");
			bck2:;
			std::cin >> s[0];
			if (s[0][0] == 'a') {
				;
			} else if (s[0][0] == 'e') {
				return 0;
			} else {
				puts("you seem to input something wrong? try it again.");
				goto bck2;
			}
		}
	}
}