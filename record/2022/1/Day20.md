模拟赛

## A. swords

相当于多次询问，每次询问选 $k$ 个数，或是自己的超集的方案数。

正难则反，考虑容斥，可以考虑每个 $1$ 的位置，这些位置必须有值，可以减掉每个位置没有值的，加上两两组合有值的。

不妨设 $g(S)$ 表示 $S$ 这个集合钦定必须有的后面那一坨，显然这可以暴力枚举其子集，`popcount` 贡献答案，但是复杂度是 ${\cal O}(3^n)$，非常遗憾地正好过不去，不过等等，**子集贡献和本集合无关，仅仅是求子集和**，很好，直接做一遍 `fwt_or` 即可。

现在的压力给到了如何计算 $f(S)$ 身上，我们只需要计算有多少个数完全不包含 $S$ 集合集合，换言之，我们只需要计算有多少个数取补是 $S$ 的超集，取补后直接 `fwt_and` 即可，从中选 $k$ 就是要求的了。

复杂度为 ${\cal O}(2^{20} \cdot 20 + Q)$。

## B. trominoes

相当于是填色之后的联通 dag 上拓扑序计数。

## C. islands

看起来比 B 可做。

设 $f(siz, deg)$ 表示 $siz$ 个点的联通块，xy 点的度数为 $deg$ 的方案数，转移应该是比较容易？

这种总和为 $n$ 的东西还是挺 GF 的，事实上，拿出 $sf_k(x)$($f$ 的 $k$ 前缀和)对应的 EGF，做 `exp` 取 $\left[\dfrac{x^n}{n!}\right]$ 就是答案，然而复杂度是起飞的。

dp 的复杂度是 ${\cal O}(nk)$ 的。

如果不想写 GF 相关，可以再做一次 dp 求答案。

设 $g(sum, blo)$ 表示已经放了 $sum$ 个点，划分了 $blo$ 块，枚举这一个块的大小进行转移即可。

想了一想，发现 $f$ 的计算似乎是有重复的，危！

突然想到度数相关也许应该尝试 prufer。

则 $f(s, d)$ 的答案应该是先选出一个 xy 点，即 $s$，然后 $s$ 的度数为 $d$，则其出现 $d - 1$ 次，序列总长度为 $s - 2$，所以答案应该是 $s \times \binom{s - 2}{d - 1} \times (s - 1)^{s - 2 - (d - 1)}$。

---

改题

## B

杨图：

一个图，形如阶梯，更好的说法是，考虑一个 $n \times m$ 的矩阵，如果一个点没有被选择，那么右边和下边也不能被选择，一种合法的选择方案构成一张杨图。

注：oiwiki 上面的上下和这里写的不同。

![杨图](https://gitee.com/Z_char/utools_tc/raw/master/picture/1642659841491-2022-1-20-14:24:01-qix8grivao.png)

例如上图就是一张杨图。

杨表：

在杨图里填入 $1 \to n$ 的排列。

一般我们使用标准杨表，标准杨表填数需要满足同一行从左到右递增，每一列从上到下递增。

> 定理1：
>
> 将 $n$ 个数填入，构成的杨表个数满足如下递推：
> $$
> \begin{array}{c}
> f[1] = 1\\
> f[2] = 2\\
> f[n] = f[n - 1] + (n - 1)f(n - 2)
> \end{array}
> $$
> 证明并不会。

> 定理2：
>
> 定义一个格子的勾长为其下面的元素个数 + 右边的元素个数 + 自己，称为 $\rm hook(v)$。
>
> 杨图的形状给定，填数的方案数为：
> $$
> ans = \dfrac{n!}{\prod \rm hook(x)}
> $$
> 证明也不会。

先观察一点结论，第二个物块明显只有两种放法 —— 否则必然冲突。

接下来考虑暴力怎么做，首先，这玩意看着就很轮廓线，考虑转移时轮廓线的变化，令 $1$ 表示往上走，我们有四种转移，分别是：

1. 1110 -> 0111，这是竖着放一个。
2. 1000 -> 0001，这是横着。
3. 1100 -> 0101，这是开口冲右下。
4. 1010 -> 0011，开口冲左上。

发现这其实等价于将一个 $1$ 向后挪动 $3$ 位。

所以现在的问题变成了，一开始有一个 $n$ 个 $1$，$m$ 个 $0$ 的串，每次可以做如上操作，问有多少种操作序列，使得最后变成 $m$ 个 $0$，然后 $n$ 个 $1$ 的串。

由于挪动三位并不好做，可以按照模三分类。

然后就是套杨表的公式即可。

## C

事实上在看到和为 $n$ 的时候，意识到即使搞出来柿子用了多项式也是 ${\cal O}( n\log n)$ 的时候就应该考虑换做法了。

考虑先枚举港口，这可以用一个组合数来算，由于 $m, k$ 都很小，所以可以枚举度数和 $D$，然后将剩余 $n - m$ 个点划分为 $D$ 个 **有根树**，然后将这些有根树挂到港口下面就行了，这等价于 $D$ 个有标号的小球放到 $m$ 个有标号的盒子里，每个盒子不能放超过 $k$ 个。

先考虑有根树计数，这种限制根个数的经典做法是拟一个虚点，钦定其度数为 $D$，由于一共 $n - m + 1$ 个点，所以序列长度 $n - m - 1$，其中 $D - 1$ 个位置被预留了，只需要确定是谁，即 $\binom{n - m - 1}{D - 1}$，剩余部分可以任选 $n - m$ 个点，即 $(n - m)^{n - m - 1 - (D - 1)} = (n - m)^{n - m - D}$。

考虑挂树，由于个数很少，可以尝试暴力 dp，设 $f(i, j)$ 表示 $i$ 个盒子放 $j$ 个小球的方案数，考虑第 $j$ 个小球放在哪里，就有 $f(i, j - 1) \times i$ 的转移，考虑 $k$ 的限制，假定 $f(i, j - 1)$ 里面的方案都是合法的，那么此时非法的盒子只可能有一个，而且恰好是 $k + 1$ 个球，暴力枚举是哪个盒子，是哪些球即可，剩下的方案数即为 $f(i - 1, j - (k + 1))$，暴力枚举不难写成组合数就是 $i \times \binom{j - 1}{k}$。

dp 的复杂度很小，盒子只有 $m$ 个，小球只有 $mk$ 个，可以暴力预处理组合数，总复杂度为 ${\cal O}(m^2k)$。

此时答案显然：
$$
\binom{n}{m} \sum_{D=0}^{mk} \binom{n - m - 1}{D - 1} (n-m)^{n-m-d} f(m, D)
$$
还有最后一个问题，$f$ 的组合数很小可以暴力预处理，$n$ 级别的组合数如何处理？并不保证模数为质数。

一个数在 $\bmod md$ 下没有逆元，说明 $\gcd(x, md) \neq 1$，那么考虑将 $x$ 划分为两部分，具体的，每次我们分解 $md$，然后将 $x$ 拆成 $v$ 和 $md$ 的约数，对于每个 $md$ 的约数只需要记录 `cnt` 即可，然后预处理出 $n - m - 1$ 的 $mk$ 次下降幂的结果以及 $mk$ 的阶乘(在拆分数下)，此时容易处理相除，对于 $md$ 的约数做差即可，否则其余部分存在逆元，求逆即可，得到真实值也是容易的，复杂度仅为 $\omega(md)$，只有 $9$ 级别，于是问题就解决了。

## CF200A

[cf200a](https://www.luogu.com.cn/problem/CF200A). 
