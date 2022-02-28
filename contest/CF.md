#### Codeforces Round #773 (Div. 1)

[link](https://codeforces.com/contest/1641). 

##### *C. Anonymity Is Important

${\cal O}(n \log ^2 n)$ 遗憾 TLE。

先拿一个 `set` 维护所有不确定的位置，那么 $0$ 修改直接暴力即可，均摊为 ${\cal O}(n \log n)$，对于一修改，直接在 $[l, r]$ 内第一个不确定的位置打标记 $r$，若下一个不确定就超过了，那可以直接确定，否则在 $0$ 操作的时候，删掉一个不确定的，标记向后平移一次，然后考虑区间前第一个和区间后第一个是否已经确定即可，至于如果打多次标记，只需要取最小值即可。

