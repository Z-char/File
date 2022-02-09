## AGC24F

[agc24f](https://atcoder.jp/contests/agc024/tasks/agc024_f). 

这题的状态定义及处理过程感觉还是比较奇妙的。

设 $f(a, b)$ 表示贪心的匹配串 $a$ 后，剩余部分为 $b$ 的串个数，总状态是 $n2^n$ 级别的，考虑对串编号，然后如果 $\sum_{t} f(a, t) \ge k$ 则说明 $a$ 是合法的子序列，更新答案并考虑添加字符即可。

似乎是因为常数巨大多所以 TLE 了，本地测试极限数据跑了 5s。

[TLE(0)](https://atcoder.jp/contests/agc024/submissions/29162275). 

但是不用编号的一个问题就是 $0$ 和 $00$ 无法区分，不过没关系，可以在所有串前面钦定加一个 $1$，就可以解决前导零的问题了，省略了 `umap` 和 `vector<string>` 的部分，此时的常数可以通过。

[Submission(1)](https://atcoder.jp/contests/agc024/submissions/29166137). [无调试纯享版](https://atcoder.jp/contests/agc024/submissions/29166276). 

