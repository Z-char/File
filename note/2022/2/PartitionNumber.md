###### 五边形数

考虑分拆数的 GF 分母部分：
$$
\prod_{i=1}^{\infin} (1 - x^i)
$$
注意到互异分拆数：
$$
\prod_{i=1}^{\infin} (1+x^i)
$$
设 $pde_n$ 表示 $n$ 个数划分为不同的偶数个数的方案数(`partition different even`)，$pdo_n$ 同理。

不难有：
$$
\sum_{u=0}^{\infin} (pde_i - pdo_i) x^i = \prod_{i=1}^{\infin} (1-x^i)
$$
然后通过一些牛逼(我完全没懂，详见 [参考资料1][1])的操作，证明了分拆数的递推式满足：
$$
p_n = p_{n - 1} + p_{n - 2} - p_{n - 5} - p_{n - 7} + \ldots
$$
连续两个正，连续两个负，其中 $n - a_2, n - a_3 , \ldots$ 中的 $a_i$ 两两满足通项(所以两两同号？)$i(3i - 1) / 2, i(3i + 1)/2$。

由于这个是平方级别的，所以复杂度为 $n  \sqrt n$。

以上就是五边形数快速球拆分数的方法了。

###### EI 科技

> how EI's mind works?

如果你已经看过了参考资料1，那么应当对 `Ferrers` 图并不陌生。

考虑从左上角拿走一个极大的正方形，不妨设边长为 $h$，那么剩余两部分的方案数均为个数不超过 $h$ 的整数划分方案数(当然，也是最大值不超过 $h$ 的方案数)。

因此有：
$$
\prod _{k \ge 1} \dfrac{1}{1-x^k} = \sum_{h \ge 1} x^{h^2} \left( \prod_{k=1}^h \dfrac{1}{1-x^k} \right)^2
$$
那么直接枚举 $h$，后面的部分相当于每个物品做两次完全背包，由于 $h$ 的数量级是 $\sqrt n$ 的，总复杂度为 $\Theta (n \sqrt n)$。

###### 参考资料：

[1]:https://oi-wiki.org/math/combinatorics/partition/	"oi-wiki 拆分数"
[2]:https://blog.csdn.net/EI_Captain/article/details/104729572	"how EI's mind works"

