## Luogu3781

[luogu3781](https://www.luogu.com.cn/problem/P3781). 

由于 $m$ 特别小可以考虑设 $f(i, v)$ 表示方案数，不难发现转移为异或卷积，直接维护 poly 用 fwt 优化，为了求答案，还需要维护一个 $s(i, v)$ 表示子树和。

带修不难想到 ddp，矩阵乘法显然，考虑维护 $lf, ls$，其中 $lf$ 的维护涉及乘除 $0$，可以维护 $a \times 0^b$ 形数字来解决这个问题。

调不出来，建议重构，摸了。

**调出来了，万岁**！

没啥注意事项可以写，总之就是一车锅。

