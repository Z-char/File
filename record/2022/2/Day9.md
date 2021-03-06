## CF1530F

[cf1530f](https://codeforces.com/problemset/problem/1530/F). 

存在是比较难以处理的，考虑补集转化，现在的问题变成求限制至少有一个 $0$ 的概率。

直接容斥，将对角线看成特殊列，有经典柿子 $f(A) = \sum_{B \subseteq A} (-1)^{|A| - |B|} g(B)$，其中 $g$ 表示至多合法的概率，所求为 $f(ALL)$，由于行列一起容斥复杂度太高，考虑只容斥列，对于行利用 dp 之类的技巧来满足限制。

稍微改写一下柿子的形式会更优雅一点，注意到 $g(B)$ 其实意味着 $A/B$ 必须不满足条件，剩下的随意，而容斥系数也和 $|A| - |B|$ 相关，可以考虑直接枚举补集，那么就是 $f(A) = \sum_{B \subseteq A} (-1)^{|B|}h(B)$，其中 $h(B)$ 表示集合非法(即全 $1$)，剩余随意的概率。

$h(B)$ 并不难求，从上到下一行一行加入即可，要求这一行满足条件，那么这一行就不能全是 $1$，这个概率是容易预处理的，别的列没有限制所以不用管，就是一套预处理的连乘积。

[Submission(0)](https://codeforces.com/contest/1530/submission/145707183). 

## CF1584F

[cf1584f](https://codeforces.com/problemset/problem/1584/F). 

设 $f(c, S)$ 表示当前匹配的是 $c$ 字符，每个串中匹配的是前一个还是后一个。

枚举下一个字符，暴力匹配，总复杂度为 ${\cal O}(2^n \times 52^2 \times n)$。

代码咕掉了。

## AGC16F

[agc16f](https://atcoder.jp/contests/agc016/tasks/agc016_f). 

sg 定理告诉我们，若 $sg(1) \neq sg(2)$，则先手必胜。

考虑补集转化，只需要记录多少种情况满足 $sg(1) = sg(2)$。

注意到边数是比较多的，故考虑从点上下手，考虑比较暴力的想法，暴力枚举 sg 序列，对于 $sg = v$ 的所有点，他们不能连边，对于每个 $k \lt v$，至少连一个 $k$ 点，至于 $k \gt v$ 的点，随便你是否连接了。

考虑枚举一批 $sg = 0$ 的点，他们内部没有边，其他点至少向其中一个连边，他们可以随意向外连边，剩下的点是子问题。

设 $f(S)$ 表示枚举了 $S$ 集合的 sg，使得 $sg(1) = sg(2)$ 的方案数，初始化为 $f(\{1, 2\}) = 1$。

往外刷表即可，加上计算方案数的复杂度，总复杂度为 ${\cal O}(3^n n)$。

[Submission(1)](https://atcoder.jp/contests/agc016/submissions/29179065). 

## CF1519F

[cf1519f](https://codeforces.com/problemset/problem/1519/F). 

设 alice 操作已经确定。

设 $L_x$ 表示 $x$ 宝箱上锁的集合，那么对于任意打开的宝箱集合，都有：$\sum_{i\in S}a_i \le \sum_{j\in (\cup_{i\in S} L_i)} b_j$，如果让每个 $i$ 连向 $L_i$ 集合，那这个东西就像一个带权的 hall 定理。

于是考虑拆点，将宝箱 $i$ 拆成 $a_i$ 个点，锁 $j$ 拆成 $b_j$ 个点，若 $L_i$ 包含锁 $j$，则宝箱 $i$ 拆的所有点向锁 $j$ 拆的所有点连边，代价为 $c_{i, j}$，所以现在的问题变成了最小代价，使得这个二分图存在完美匹配。

设 $f(i, s)$ 表示处理到第 $i$ 个宝箱，右边锁状态为 $s$ 的最小代价，其中 $s$ 压缩了 $m$ 个五进制数，表示每个锁还剩下几个点没有匹配，因为每个锁所有点要连边就是同时连边，所以只需要记录剩下几个点即可，状态总量为 $n \times 5^m$，转移的时候暴力枚举当前宝箱每个点匹配哪个锁，复杂度为 $m^n$，最后 $\min_{k} f(n, k)$ 即为答案(右边无需完全匹配)，总复杂度为 ${\cal O}(n 5^m m^n)$，计算出来之后非常的吓人，考虑优化，类似插头 dp 那样，一行整体转移变为一个格子转移，我们不直接把一个宝箱作为状态的阶段了，我们设 $f(i, s, k)$，其中 $k$ 表示第 $i$ 个宝箱剩余 $k$ 个点没有匹配，转移的时候暴力枚举放到哪个锁头以及放多少，虽然可能对锁头出现重复付款，但这显然不会优，故会被干掉，此时的状态为 $n \times 5^m \times 4$，转移复杂度为 $m \times 4$，总复杂度为 ${\cal O}(16nm 5^m)$。

[Submission(2)](https://codeforces.com/contest/1519/submission/145738790). 

## Luogu6570

[luogu6570](https://www.luogu.com.cn/problem/P6570). 

首先，一个优秀子序列的权值最多不过 $2 \max a_i$ 级别，这是因为最多就是每位都是 $1$ 罢了，事实上，由于 $a_i\; {\rm and}\; a_j = 0$，所以 $a_i + a_j = a_i \; {\rm or} \; a_j$，交集为空，求或，这是经典的子集卷积。

先拿一个桶把 $A$ 搞下来，以集合幂级数为运算对象，子集卷积为运算，做 `exp`，此时的 $f(i)$ 就表示 $\varphi(i + 1)$ 的方案数，当然，注意到序列中存在 $a_i = 0$，和没选一样，可以把他们单独提出来，最后 $f(i) \times 2^{cnt}$ 即可。

[Submission(3)](https://hydro.ac/d/luogu/record/620456346923a982cb191088). 浴谷不太支持看评测记录，就放到 `hydro` 上了，另外，是不是递交评测也计入耗时啊？[luogu Submission](https://www.luogu.com.cn/record/68920194)，怎么耗时差距这么大（指 `1, 8, 9, 10` 四个点

