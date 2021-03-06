模拟赛

改题

## A. mie

写了各种状压和暴力。

实际上正解十分简洁。

考虑用给出的数组拼成整个矩形，也就是选取一些点，使得他们的覆盖区间不重复，且恰好覆盖整个矩形，这就是答案。

## B. yds

题面实在是很奇怪。

合着就是菱形求和，单点查询呗。

考虑把所有点曼哈顿转切比雪夫，求和变成了正方形，随便做做即可。

## C. leaves

考虑基础的平衡，首先若相邻两两叶片间距离相等，这是一组平衡的，或者说，任意两个相邻叶片的编号差模 $n$ 相同，并且不难发现，差值之和(模意义下)恰为 $n$，也就是说差值必须为 $n$ 的约数，并且若一组差值为 $d$ 的平衡，满足 $d$ 存在一个不是 $n$ 的倍数，为 $n$ 的约数，那么可以将其拆为 $k$ 个差值为 $kd$ 的平衡，故若 $n / d$ 是一个质数，那么我们称差值为 $d$ 的平衡，是基础平衡，他们不能在拆分，而且可以拼出一切平衡。

而更一般的平衡，一定可以拆成若干基础平衡。

注意到题目中特别的限定，$n$ 最多只有两个质因数，不妨设为 $p, q$，那么基础平衡只有两种，$n / p$ 和 $n / q$。

现在的问题转化为，选出若干不交的基础平衡，满足覆盖所有的坏点，并且大小最小。

考虑将一个点和对应的 $p$ 平衡的所有点拿出来，所有点后面挂一条链，为他们 $q$ 平衡对应的链。

考虑将 $q$ 平衡的拿出来，然后将每个点后面挂 $p$ 平衡的链，不难发现这两组覆盖的数字相同，事实上，把两个叠加起来看会构成一张表格，其中左上角为 $x$，那么 $(i, j)$ 对应的值应该是 $x + i\cdot(n/p) + j\cdot(n/q)$，选基础平衡就等价于选一行或者选一列，由于不交，所以一张表格里要么全是选行，要么全是选列。

注意到表格之间独立，可以直接一个表格一个表格的处理，先按行考虑，若这一行有坏点，那么选上，否则不选，再按列考虑，取较小值即可。

## A. white

昨日考试题补题。

注意到后半部分是一个分治fft/多项式求逆，那么再上一个 `ntt` 就可以从 $m^2n$ 优化至 $n m \log m$，那么后半部分已经不超时了，考虑优化前半部分暴力求 $f$ 的过程。

不妨令 $Qs(X)$ 表示邻接矩阵 $X$ 贡献的答案，令初始给定的邻接矩阵为 $A$，那么所求的其实就是 $Qs(A), Qs(A^2), \ldots, Qs(A^m)$。注意到 $Qs$ 是具有线性性的，这不难证明。

定义一个矩阵的特征多项式为 $f(x) = {\rm det}(Ix - A)$，其中 $I$ 为单位矩阵。

根据 `Cayley-Hamilton` 定理，$A$ 的特征多项式满足 $f(A) = 0$，其中 $0$ 指全零矩阵(所以用矩阵求出多项式然后再带入矩阵得到矩阵)。

设 $f(x)= \sum_{i=0}^n f_ix^i$($n$ 阶方阵是 $n$ 次多项式捏)，则有：
$$
\begin{aligned}
\sum_{i=0}^n f_iA^i = 0\\
\sum_{i=0}^n f_i A^{i + w} = 0 \\
Qs(\sum_{i=0}^n f_iA^{i + w}) = 0\\
\sum_{i=0}^n f_iQs(A^{i + w}) = 0
\end{aligned}
$$
于是我们得到一个 $n$ 次递推式，故暴力求出 $Qs(A), \ldots, Qs(A^n)$ 即可快速递推 $Qs(A^{n + 1}) \ldots$ 

$Qs$ 项数为 $n$，一次递推需要前面 $n$ 个贡献，需要求出 $m$ 项，复杂度为 $n^2 m$。

至于特征多项式怎么求，方法很多，可以直接 lagrange 插值，复杂度为 $n^4 + n^2$。

总复杂度为 ${\cal O}(n^4 + n^2 + n^2m + n m \log m)$。

