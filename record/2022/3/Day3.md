## Luogu3343

[luogu3343](https://www.luogu.com.cn/problem/P3343). 

这种实数的问题，基础的暴力想法就是枚举数字顺序，然后开始做 `kruskal` 的暴力，若最后联通的边是第 $k$ 条，根据提示，期望情况下这条边是 $k/(m + 1)$，于是求出所有情况的和，最后 $/m!$ 即可，或者先求出排名的期望，最后在除以 $(m + 1)$。

唯一的缺点是全排列的复杂度太高了，考虑用状压替代全排列。

那么设 $x$ 表示最后一条树边的排名，答案就是 $E(x)/(m + 1)$，也就是：
$$
(\sum_{i=1}^ m P(i) \times i)/(m + 1)
$$
其中 $P(i)$ 表示排名为 $i$ 的概率。

发现这种恰好问题是比较难以处理的，不过幸运的是，对于这种概率求和，我们有一种转化方法：
$$
\sum_{i=1}^m P(i) \times i = \sum_{i=1}^m P(x\ge i)
$$
那么 $P(x\ge i)$ 表示最小晟晟树的最大边在 $i$ 或以后，或者表述成加入前 $i - 1$ 小的边不能使图联通的概率。

考虑使用状压 dp，设 `dp[i][j][0/1]` 表示 $i$ 点集，连了 $j$ 条边，图是否联通的方案数。

那么 $dp(i, j, 0) = \sum dp(p, s, 1) \times \binom{edge(i - p)}{j - s}$，套路的枚举 $1$ (p)号节点所在联通块大小(指具体集合以及边数)，转移即可，钦定前面是联通的是基本套路了，否则不同的分界线会重复。

显然有 $dp(i, j, 0) + dp(i, j, 1) = \binom{edge(i)}{j}$，所以 $dp(i, j, 1)$ 也好求。

就做完了。

## Luogu3600

[luogu3600](https://www.luogu.com.cn/problem/P3600). 

就是要求：
$$
E(\max q_i)
$$
其中 $q_i$ 表示第 $i$ 次询问结果的随机变量。

先观察一下，发现一个区间包含其他区间一定对 $\max$ 没有贡献，那么可以直接删除这些区间，剩下的区间按照左端点排序后右端点也是单调的。

接下来直接 min-max 容斥就有：
$$
\sum_{t \subseteq s} (-1)^{|t|-1} E(\min_{i \in t} q_i)
$$
又因为 $q_i$ 本身是取 $\min$ 的，所以 $E$ 相当于这么些数取 $\min$ 的期望，这个值显然只和并集大小有关。

设 $f(i)$ 表示 $i$ 个数，在 $1\to x$ 里随机，最小值的期望，自然有：
$$
f(n) = \sum_{i=1}^x i \times ((x-i+1)^{n} - (x-i)^{n}) / x^n
$$
预处理 `pw[i][j]` 表示 $i^j$ 后，可以 $n^2$ 处理出 $f$ 数组。

那么我们已经得到了并集为 $k$ 的期望值，剩下的就是 dp 我们的容斥柿子了。

排除无用区间后，剩下区间按左端点排序，设 $dp(i, k)$ 表示最后一个选择的区间是 $i$，选择的并集大小为 $k$ 的带容斥系数方案数。

那么有转移：
$$
dp(i, k) = \sum_{j, r_j \lt l_i} dp(j, k - len)(-1) + \sum_{j, r_j \ge l_i} dp(j, k + r_j - r_i)(-1)
$$
随便优化一下即可做到 ${\cal O}(n^2)$。

答案就是：
$$
\sum dp(i, k) \times f(k)
$$
