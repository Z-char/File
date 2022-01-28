## A. roche

首先 ${\cal O}(n^2m^2q)$ 的 $20\rm pts$ 是显然的。

可以发现，最优决策下每一步要么 $x + 1$ 要么 $y + 1$，于是决策点减少到了线性，复杂度变成 ${\cal O}(n^3 q)$，可以发现的是，其合法决策点应该是连续的一段区间，每次暴力枚举属实不智，应当考虑更好的做法。

先考虑维护一行的最左点，一个矩形的影响相当于 $[c_1 + 1, c_2]$ 这些行，其中 $[r_1 + 1, r_2]$ 这些位置的 `left` 对 $r_1$ 取 `min`，最下点同理。
