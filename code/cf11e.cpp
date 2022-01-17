#include <bits/stdc++.h>
 
using i64 = long long;
 
signed main() {
    std::string prestr;
    std::cin >> prestr;
    std::string str;
    int N = int(prestr.size()), up = 0, dn = N;
    if (prestr[0] == 'R' && prestr[0] == prestr[N - 1]) ++dn, str += 'X';
    for (int i = 0; i < N; ++i) {
        if (i && prestr[i] == prestr[i - 1] && prestr[i] != 'X') str += 'X', ++dn;
        str += prestr[i];
        if (prestr[i] != 'X') ++up;
    }
    if (prestr[0] == 'L' && prestr[0] == prestr[N - 1]) ++dn, str += 'X';
    N = int(str.size());
    int dlt = 0, len = 0;
    std::vector<int> add;
    for (int i = 0, j; i < N; i = j + 1) {
        j = i;
        if (str[i] == 'X') continue;
        while (j + 1 < N && str[j + 1] != 'X') ++j;
        if (str[i] == 'L' && ((i + dlt) & 1)) ++dlt, ++dn, add.push_back(len + 1);
        if (str[i] == 'R' && (!((i + dlt) & 1))) ++dlt, ++dn, add.push_back(len + 1);
        len += j - i + 1;
    }
    if (dn & 1) ++dn, add.push_back(len + 1);
    if (up + up > dn) {
        int M = int(add.size());
        for (int i = 0; i < M - 1; ++i)
            if (add[i] + 1 == add[i + 1]) dn -= 2, up -= 1, ++i;
    }
    i64 ret = 100000000ll * up / dn;
    printf("%.6f\n", ret / 1000000.0);
}
