## Luogu6261

[luogu6261](https://www.luogu.com.cn/problem/P6261). 

考虑差分，假设可以求出 $f(i)$ 表示连续通过 $i$ 个灯的概率(至少)，可以使用简单的 $f(i) - f(i + 1)$ 来得到单点答案。

一个红绿灯的周期显然是 $r_i + g_i$，那么通过 $i$ 的条件就是 $X + x_i \ge r_i \pmod{g_i + r_i}$。

考虑一个特殊的情形，所有的 $g_i + r_i$ 互质，考虑暴力枚举 $\bmod {\rm lcm(r_1 + g_1, \ldots)}$ 下的 $X$，可以发现所有的 $X$ 构成的解恰好会填满所有同余方程的所有值，故合法的概率就是每个红绿灯的合法概率乘积，即 $\prod \dfrac{g_i}{r_i + g_i}$ —— 这其实相当于每个位置的概率独立，和顺序无关。

考虑另一种特殊的情形，现在任意两个 $g_i + r_i$ 要么互质，要么有倍数关系，那么可以把同余方程分类，考虑第一类间合法的 $X$ 有 $c_1$ 个，其最大周期为 $l_1$，第二类间合法的 $X$ 有 $c_2$ 个，周期同理 —— 这和 excrt 很像，此时合并第一类为一个同余方程，合并第二类为一个同余方程，此时合并两个同余方程，由于模数互质，容易套用第一个公式，概率为 $\prod \dfrac{c_i}{l_i}$。

现在还有一个小问题，$c_i$ 如何计算，其实也不难，考虑从前往后扫描，每次把自己的周期放大为类内最大的周期，然后枚举步数，如果这个步数在自己这里非法，并且不曾被周期标记过，那么 $c_i - 1\to c_i$，由于步数只有周期级别，所以复杂度为 ${\cal O}(n (r_i + g_i))$。

那么一般情形呢？

考虑划归为特殊情形，如何改变周期？改变步长即可，考虑固定一个步长，然后对于所有 $X$ 按照对步长的模数分类，对于步长 $kM$，原本的周期会变成 $\dfrac{len}{\gcd(len, kM)}$，这是经典结论，那么可以发现取 $kM = 2^3 \times 3^2 \times 5 \times 7$ 就可以满足任意新周期满足特殊情形了，于是枚举模数，然后从前往后处理，然后枚举这个周期内部的步数，总复杂度为 ${\cal O}(kM \times n \times \max(r_i + g_i))$，可以通过。

这是看题解后整理而得的思路，一般的思路应该为先转化为同余方程求解个数，考虑从前往后合并，注意到合并时模数互质则解个数是简单相乘，于是考虑按照同余类划分，若存在 $\gcd$ 且不是倍数关系难以合并，可以考虑特殊情形，发现特殊情形是好做的，只需要对每个同余类维护同余方程解个数即可，联想到环上步长周期的结论，可以考虑更改步长，将所有 $X$ 按照步长余数分类，在此步长下，情形特殊，由于周期不过 $100$，所以超过 $10$ 的质因子顶多一个，而且如果有，那么 $2, 3, 5,7 $ 最多有 $3, 2, 1, 1$ 个，故取 $3, 2, 1, 1$ 即可使这样的周期会和别人互质，否则如果只有 $10$ 以下质因子，去掉这个东西后，最多只是单个质数的次幂，故这个东西就是一个合法的步长，于是就做完了。

