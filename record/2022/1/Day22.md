模拟赛

## A. study

原题。

## B. cow

感觉那个 $40\rm pts$ 想提醒我是 cdq/线段树 分治啊。

想一想，三操作其实是问是否存在一个矩形和我相交，感觉问题更加困难了？（虽然更加形式化了

大概也许可以跑 $4$ 次五维偏序来做，然后还不能加入时间。

好像横竖可以拆开来做？答案取或即可。

然后问题好像转化为了支持动态加入删除的二维数点？

现在可以跑 $2$ 次五维偏序来做了，可以包括时间，不过感觉会 T。

好像可以直接树套树。

假了 /kel，并不能拆开做。

直接树套树区间加？似乎相等不代表同块。

## C. max

不大会。

## D. sun

暴力倍增复杂度就是对的。

---

改题

## B. cow

emmm，其实可以看作高维 $01$ 向量，表示是否被某个矩形框住，如果向量不同则被区分，这个东西自然是不能显式维护的，考虑经典套路，随机权值异或和，相同表示同一个向量，冲突概率较小。

不需要使用树套树，简单的二维 bit 维护即可，因为只有单点查询。

## C. max

拆成前缀和相减的形式，不难发现没有 $m$ 答案就是极差。

有 $m$ 可以发现一个值相当于变成了用 $-m$ 去切他，对应的截距，于是维护上下凸壳，分别二分求极值即可。

## D. sun

笑死，考场上没调出来，大样例一个没过过了 $40 \rm pts$。

在 qq 老师的指导下，发现是 $0$ 不能到达的联通块没有被清空导致遗憾离场，因为数据比较弱，块数很少，直接暴力清空所有点居然过了。

正确的做法应该是倒序 `pop` 出来并清空。

---

## CF1408H

[cf1408h](https://www.luogu.com.cn/problem/CF1408H). 

考虑序列中 $0$ 的个数 $cntz$，答案有上界 $\left\lfloor \dfrac{cntz}{2} \right\rfloor$。

考察两个集合 $L,R$，其中 $L$ 集合中的每个数满足右面有至少上界个 $0$，$R$ 满足左边有上界。

那么 $L$ 只需要考察左边的匹配，因为右边总能匹配上，$R$ 同理。

如果 $L$ 中有多个重复权值，如果这个权值被取走了，且是在 $L$ 中被取走的，我们可以调整，使得其取得是 $L$ 中的最后一个，故一定存在一种方案，使得一个元素如果选在 $L$，一定是 $L$ 中最后的这个元素，$R$ 同理。

不妨设 $l_x$ 表示 $x$ 权值在 $L$ 中的最后一个出现位置，$r_x$ 同理(换成第一个出现位置)。

此时有一个网络流做法，可以发现 $L, R$ 恰好分布满整个区间(如果把 $0$ 也计算在集合内)，让 $L$ 每个节点向左连正无穷流量，$R$ 同理，$s$ 向 $x$ 权值连 $1$ 流量，$x$ 向 $l_x, r_x$ 连 $1$ 流量，每个 $0$ 向汇点连 $1$ 流量。

跑最大流，最大流与上界取 $\min$ 即得到答案。

然而 $2e5$ 的数据范围不允许我们跑网络流。

考虑最大流 = 最小割定理。

一定存在一组最小割，满足割边是一些前缀 $0$，一些后缀 $0$，一些颜色。

这种情况下经常考虑枚举前缀 $0$ 被割的个数，用 ds 维护其余部分。

我们可以先钦定割了所有颜色，在 $col$ 的基础上维护最小割。

使用线段树维护，叶子节点 $(x, l, l)$ 维护割 $l$ 个 $0$ 的最小代价，初始化为 $l$。

如果一个颜色只在 $R$ 中出现，那么如果后缀割超过他的 $0$，这个颜色就不需要割了，这是一个区间减操作，从其对应的后缀个数到总个数的区间减，也就是如果选了这些位置，那么 $col$ 中就有一个需要被干掉了。

枚举前缀割的过程中，会增加一些只在 $R$ 中出现的数，同理操作即可，如果在 $R$ 中也不存在，那就全局减少即可。

就做完了。

## Luogu3348

[luogu3348](https://www.luogu.com.cn/problem/P3348). 

直接动态维护不太好维护，但是 $0, 1$ 操作不会影响 $2$ 的答案，那么可以考虑离线，从前往后扫描每棵树。

