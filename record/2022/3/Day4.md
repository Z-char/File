## Luogu3706

[luogu3706](https://www.luogu.com.cn/problem/P3706). 

首先，我们有一个显然的暴力，就是拿一个 trie 图，设 $f(i, j)$ 表示从 $i$ 出发 $j$ 胜利的概率，转移高斯消元，复杂度为 ${\cal O}((nm)^3)$，无法通过。

考虑类似 [歌唱王国](https://www.luogu.com.cn/problem/P4548) 那么做。

设 $f(i, j)$ 表示在 $i$ 位置，恰好 $j$ 胜利的概率，若 $j = 0$，则表示无人胜利。

套用歌唱王国的技巧就有：
$$
f(i, 0) (1/2)^m = f(i + m, j) + \sum_{k}\sum_{t=1}^{m - [i = j]} f(i + t, k) (1/2)^{m - t} [s_{k, t} \neq p_{j, t}]
$$
其中 $p_{i, j}$ 表示 $s_i$ 的前 $j$ 个字符，$s$ 表示后缀。

显然所求的 $p_i = \sum f(k, i)$，于是不妨对 $i$ 无穷求和得到：
$$
p_0 (1/2)^m = p_j + \sum_{k}\sum_{t=1}^{m - [i = j]} p_k(1/2)^{m-t}[s_{k,t}\neq p_{j, t}]
$$
那么枚举 $j$，我们可以得到 $n$ 个方程。

另外，注意到总会有人胜利，所以 $\sum_{i\gt 0} p_i = 1$。

于是我们得到 $n + 1$ 个方程，$n + 1$ 个未知数，直接高斯消元即可。

至于枚举 $j, k, t$ 后如何快速判断是否相同，直接 hash 即可。

## TC13444

[tc13444](https://vjudge.net/problem/TopCoder-13444). 

设 $f(i, j)$ 表示 $i$ 行 $j$ 列，其中行互不相同，列没有限制的方案数。

显然：
$$
f(i, j) = (c^j)^{i\downarrow}
$$
设 $g(i, j)$ 表示 $i \times j$ 的答案。

那么：
$$
f(n, m) = \sum_{i=1}^{m} g(n, i) {m \brace i}
$$
由斯特林反演：
$$
g(n, m) = \sum_{i=1}^m (-1)^{m-i}{m \brack i} f(n, i)
$$
那么随便做即可。

[Submission(0)](https://vjudge.net/solution/35212184). 

