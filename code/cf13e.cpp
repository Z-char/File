#include <bits/stdc++.h>

const int maxn = 2e5;

int n, m;

struct Splay_node {
    int p, s[2], rev;
    int siz;
} tr[maxn + 10];

inline int& fa(int x) { return tr[x].p; }
inline int& ls(int x) { return tr[x].s[0]; }
inline int& rs(int x) { return tr[x].s[1]; }
inline int& siz(int x) { return tr[x].siz; }
inline int& rev(int x) { return tr[x].rev; }
inline int& ch(int x, int k) { return tr[x].s[k]; }
inline int idt(int x) { return rs(fa(x)) == x; }
inline int nrt(int x) { return (ls(fa(x)) == x) || (rs(fa(x)) == x); }
inline void pushup(int x) { siz(x) = siz(ls(x)) + siz(rs(x)) + 1; }
inline void pushrev(int x) { std::swap(ls(x), rs(x)), rev(x) ^= x; }

inline void pushdown(int x) {
    if (rev(x)) {
        pushrev(ls(x)), pushrev(rs(x));
        rev(x) = 0;
    }
}

void relax(int x) {
    if (nrt(x)) relax(fa(x));
    pushdown(x);
}

inline void rotate(int x) {
    int y = fa(x), z = fa(y), k = idt(x);
    if (nrt(y)) ch(z, idt(y)) = x;
    fa(x) = z;
    ch(y, k) = ch(x, k ^ 1), fa(ch(x, k ^ 1)) = y;
    ch(x, k ^ 1) = y, fa(y) = x;
    pushup(y), pushup(x);
}

inline void splay(int x) {
    relax(x);
    for (int y = fa(x); nrt(x); rotate(x), y = fa(x)) 
        if (nrt(y)) rotate((idt(x) ^ idt(y)) ? x : y);
}

inline int access(int x) {
    int p = 0;
    for (; x; p = x, x = fa(x)) 
        splay(x), rs(x) = p, pushup(x);
    return p;
}

inline int findroot(int x) {
    access(x); splay(x);
    while (pushdown(x), ls(x)) x = ls(x);
    return x;
}
inline void makeroot(int x) { access(x); splay(x); pushrev(x); }
inline void split(int x, int y) { makeroot(x); access(y); splay(y); }
inline void link(int x, int y) { makeroot(x); fa(x) = y; }
inline void cut(int x, int y) { split(x, y); ls(y) = fa(x) = 0; pushup(y); }

int k[maxn + 10];

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) 
        std::cin >> k[i], link(i, std::min(i + k[i], n + 1));

    for (int i = 1; i <= m; ++i) {
        int x, y;
        std::cin >> x >> y;
        if (x == 1) {
            split(y, n + 1);
            int k = tr[n + 1].s[0];
            pushdown(k);
            while (tr[k].s[1]) k = tr[k].s[1], pushdown(k);
            std::cout << k << ' ' << siz(n + 1) - 1 << std::endl;
        }
        else {
            int w;
            std::cin >> w;
            cut(y, std::min(y + k[y], n + 1));
            k[y] = w;
            link(y, std::min(y + k[y], n + 1));
        }
    }
}
