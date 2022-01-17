$\def\l#1{\left#1} \def\r#1{\right#1}$ 
## CF87E

[cf87e](https://www.luogu.com.cn/problem/CF87E). 

重心性质？

$\vec{OA} + \vec{OB} + \vec{OC} = 3\vec{OP}$，因为重心是三点算术平均嘛。

直接把 ABC 求 `minkowski` 和，现在的凸包就是前面的凸包了，只需要验证 $3p$ 这个点是否落在内部即可。

## AGC028B

[agc028b](https://www.luogu.com.cn/problem/AT4436). 

考虑点对 $(i, j)$ 对答案的贡献，即删除 $i$ 时，有多少种方案可以贡献 $a_j$，不难发现求和就是答案。

考虑 $f(i, j)$，设 $len = |i - j| + 1$，那么 $i$ 应该是这个区间最后删除的，不难发现方案数就是 $n! / len$。

那么答案就是：
$$
\begin{align}
& \quad\quad \sum_{i = 1} ^ n \sum_{j = 1} ^ n \dfrac{n!}{|i - j| + 1} a_j \\
&= n! \sum_{j = 1} ^ n a_j \cdot \left( \sum_{i=1}^j \dfrac{1}{i} + \sum_{i=2}^{n - j + 1} \dfrac{1}{i} \right)
\end{align}
$$
预处理逆元前缀和即可做到线性复杂度。

## Luogu4072

[Luogu4072](https://www.luogu.com.cn/problem/P4072). 

先尝试使用方差的柿子，即 $\dfrac{\sum s_i^2}{m} - \left( \dfrac{\sum s_i}{m} \right)^2$，$s_i$ 表示划分第 $i$ 段的和。

显然后面那个是个定值，直接捶死。

前面的由于 $m$ 是定值，所以问题等效于最小化平方和，这题给 $3000$ 直接斜率优化即可，wqs 二分可以做到更好的复杂度，不过单调队列维护的斜率优化显然也满足决策单调性，又因为分层，直接分治也可。

总之就是爱怎么做怎么做，不过斜率优化和 wqs 都需要脑子，有一些细节，不如直接决策单调性分治。

## CF1278F

[cf1278f](https://www.luogu.com.cn/problem/CF1278F). 

暴力枚举 $x$ 可以得到柿子：
$$
\begin{align}
& \quad \quad \sum_{i=0}^n \binom{n}{i} \l( \dfrac{1}{m} \r) ^i \l( \dfrac{m - 1}{m} \r) ^ {n - i} i^k \\
&= \dfrac{1}{m^n} \sum_{i=0}^n \binom{n}{i} (m-1)^{n - i} i^k \\
&= \dfrac{1}{m^n} \sum_{i=0}^n \binom{n}{i}(m-1)^{n-i} \sum_{j=1}^{\min(i, k)} \binom{i}{j} {k \brace j} j! \\
&= \dfrac{1}{m^n} \sum_{j=1}^k j! {k \brace j} \sum_{i=0}^n \binom{n}{i} \binom{i}{j} (m-1)^{n - i} \\
&= \dfrac{1}{m^n} \sum_{j=1}^k j!{k \brace j}\binom{n}{j} m^{n - j}
\end{align}
$$
预处理 stirling 数即可做到 ${\cal O}(k^2)$。

## CF25E

[cf25e](https://www.luogu.com.cn/problem/CF25E). 

开业看了，秒了。

