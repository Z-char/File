## Luogu7897

[luogu7897](https://www.luogu.com.cn/problem/P7897). 

也就是说，如果我们能维护这个森林以及其上的 $f$ 值，就可以快速查询答案了。

考虑一个点什么时候向父亲连边，即 $siz(x) \times v + sum(x) \ge 0$，那么 $v = \lceil -sum(x)/siz(x)\rceil$，考虑一开始 `v = -inf`，我们维护一堆散点，并维护他们的 $sum, siz$，算出他们对应的 $v$，插入一个 `set` 里，然后从前往后扫，当一个点改变后，连接他的父亲，此时父亲往上的整条森林里的链的 $siz, sum$ 都要修改，这其实可以树上差分，用 `bit` 即可维护，然后用并查集维护根，直接跳到根，若他的 $f$ 直接合法了，那就继续向上连接，否则更新 $v$，重新插入 `set` 即可。

每条边只会连接一次，连接一次更新一次 `set`，进行一个 `bit` 的修改，故均摊复杂度为 ${\cal O}(n \log n)$，离线询问，双指针考虑 `set` 的结果即可，总复杂度为 ${\cal O}(n \log n + m)$。

`set` 离场了，实在是太慢了，换 `priority_queue` 就过了。

[Submission(3)](https://www.luogu.com.cn/record/69220925). 

因为洛谷提交记录可能看不了，所以放在 `Code` 目录下了一份。

## AGC20F

[agc20f](https://atcoder.jp/contests/agc020/tasks/agc020_f). 

[record](https://www.one-tab.com/page/q7arn0zWQGOvunN9AptFig). 

