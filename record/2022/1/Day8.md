## CF506E

[cf506e](https://www.luogu.com.cn/problem/CF506E).

[放在这里了](https://www.cnblogs.com/-Railgun/p/15777440.html)。

## Luogu4557

[luogu4557](https://www.luogu.com.cn/problem/P4557). 

判断是否 $\exists b \in B, s.t. \; (b + w) \in A$。

也就是 $\exists b \in B, a \in A, s.t. \; b + w = a$。

那么 $\exists b \in B, a \in A, s.t. \; w = a - b$。

这等价于 $w$ 处于 $a$ 和 $-b$ 做闵和的凸包中，直接求闵和，二分判断是否在凸包中即可。

