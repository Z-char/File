$\def\l{\left} \def\r{\right}$ 

## Luogu6693

[luogu6693](https://www.luogu.com.cn/problem/P6693). 

设 $f(i, j)$ 表示 $(i, j)$ 匹配的方案数，$g(i, j)$ 表示 $(i, j)$ 匹配的前缀答案，有转移：
$$
f(i, j) = \sum_{k \lt j} f_{all, k} \\
g(i, j) = \sum_{k \lt j} g_{all, k} + f_{all, k} \l( (i - all - 1)^2 + (j - k - 1)^2 \r)
$$
暴力拆柿子然后随便维护一下二维前缀和即可。

[这是一只加强版](https://www.luogu.com.cn/problem/P6695)。

加强版就不能这么干了，考虑枚举区间的贡献，颓柿子后大力卷积即可。

## Luogu3348

[luogu3348](https://www.luogu.com.cn/problem/P3348). 

对所有一操作建立虚点(一开始也建立一个挂在 $1$ 下面)，对所有 $0$ 操作建立点挂在最近虚点下面。

一操作对应的实际区间可以通过取交得到，一个一操作的影响其实相当于子树改挂，由于我们建立了虚点，所以相当于单点 link cut，LCT 维护即可。

至于怎么求距离，显然只需要可以维护单点 dist 即可，虚点无权即可。

