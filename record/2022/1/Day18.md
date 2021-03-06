模拟赛

## A. arithmetic

杜教筛板子，线性筛有 95pts，暴力求解有 90pts，牛逼题目。

那个映射 trick 我忘了，直接 `umap` 硬冲了。

## B. series

区间加广义 fib，区间求和。

$n$ 怎么是 $1e9$ 啊，怎么强制在线啊，那就动态开点线段树呗。

怎么空间 64M 啊，太流氓了吧。

考虑这个广义 fib 的特殊性质，他是公比恒定的等比数列。

相当于区间加等比数列，但是公比恒定。

---

拿个平衡树维护一下就好了，但是动态开点也放过去了？非常的震撼，虽然我都没写（

不过不是区间加，而是区间赋值。

## C. tree

第一眼给人的感觉是 01 分数规划。

但是发现分子上是乘法。

考虑设 $f(x, d)$ 表示 $x$ 子树里，$x$ 选择的链长度为 $d + 1$ 的最小连乘积，不难发现容易 ${\cal O}(n^2)$，复杂度瓶颈在于合并答案。

考虑如果能求出所有长度下的最小连乘积，那么最后扫一遍就可以得到答案了。

难求 /qd。

取对数的话，还原仍然需要高精度级别的东西吧，属于是有点恶心了。

---

原来是贪心。

若不存在 $1$，则答案一定是最小点，因为指数增长远大于线性，不难发现即使 $2, 2, 2$ 也逐渐起飞。

若存在 $1$，显然链越长越好，但不一定仅仅是最长链，考虑其中穿插一些数字，不妨设若穿插 $3$，不难发现，总有一边的长度为 $\dfrac{len}{2}$ 下取整，考虑取这一边，而上面的权值除以 $3$，显然更优，所以不会有 $3$，但是 $2$ 就不一定了，不难发现，当且仅当 $2$ 恰好为 $1$ 链中点的时候才更优，所以只需要判断这种情况即可。

## CF123D

[cf123d](https://www.luogu.com.cn/problem/CF123D). 

sam 乱冲罢，随便维护一下 `endpos` 大小，用 `link` 不难得知这个节点对应的串个数，直接计算即可。

## CF132E

[cf132e](https://www.luogu.com.cn/problem/CF132E). 

牛逼网络流。

> 当你不会做网络流的时候就疯狂拆点罢。

先把所有需要打印的数字拿出来离散化，对每个时间拆 $cnt + 1$ 个点，流量代表这个时候为这个值的变量个数，之所以 $+1$ 是因为存在空变量。

于是 $s \to empty$，然后 $empty$ 构成一条 $n$ 长度的链，然后直接连向 $t$，其中，第一条边和最后一条边流量为 $m$，其他边流量为 $m - 1$(其实为 $m$ 大抵也是无所谓的)。

对于每一列，值域点可以选择置空，空点可以选择赋值，值域点的置空流量不限，空点赋值同理，其有边权，就是赋值的边权。

对于除了第一行的行，每个值向下一时刻的同值连边，流量不限，没有代价。

特别的，对于每个时间需要被打印的字符，其向下一时刻的同值连边需要限定下界为 $1$，跑有源汇上下界最小费用最大流即可。

**有牛逼建图如下**：

考虑如果一个变量在 $i$ 使用了，但是没有留到下一次就被抛弃了，那不如直接在 $i$ 抛弃，这是等效的。

如果一个变量我们在 $i$ 使用了，然后在 $j$ 也使用了，发现很难考虑到底有没有留到这里，如果不拆成多权值的话，但是有一个重要的不变量是 **$j$ 必须有一个对应变量**。

考虑类似餐巾计划那么干，我们直接让源点灌输给 $j$ 一个对应变量的流，价格为选择对应变量的价格，我们看成如果 $i$ 流到了 $i - 1$ 并且没有销毁，可以卖出这本书得到对应的收益。

于是将每天拆为两个点，表示入点和出点，源点向所有入点连边当天的费用，流量为 $1$ 的边表示当天买，如果存在上一个位置和这个位置颜色相同，则 $u_{i - 1} \to v_{j}$，表示在 $i - 1$ 卖出这本书，用的是 $j$ 时刻的变量，所以费用为 $-a_i$，流量为 $1$，每个点入点向出点连流量为 $1$ 的边，出点向汇点连边流量 $1$，此时如果一条流直接源汇，说明当天买了直接扔了，如果一条流走过去然后反回来，说明留着到下一次之前卖了，对了，为了往后流，还需要连边一天和下一天，不过大小是 $m - 1$，这是因为我们钦定每天需要买一个。

输出方案就模拟呗。

[cf802c](https://www.luogu.com.cn/problem/CF802C) 没有输出方案。

## Luogu4553

[luogu4553](https://www.luogu.com.cn/problem/P4553). 

更为类似餐巾计划的网络流。

点经过次数自然拆点。

$s \to news$ 流量为 $m$，用来限制人数，$news \to allu$ 流量为 $inf$，表示任选起点，$allu \to T$ 流量为 $v_i$，表示走到这个点就直接灌输给汇点，**满流代表所有点都满足限制了**，接下来直接让 $s \to allv$，流量为 $v_i$，直接灌输这些人，事实上可以看作贡献给汇点后再拿出来，最大流限制满足的同时，使这些人可以继续旅游，原图上的边显然，流量 $inf$ 权值为 $dis$ 即可。

注意，$u \to v$ 没有连边，因为走过去的过程其实被我们看作 $u \to T \to S \to v$ 的循环，贡献了答案同时人可以继续走，当然，也可能 $S \to v$ 不走了。

网络流题真是太 hard 了，目前稍微总结的就是次数要拆点，恰好要用这种餐巾计划的方法，还有给边赋值来限定边的优先级的方法，比较灵活。

