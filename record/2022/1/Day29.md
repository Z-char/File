$\def\l{\left} \def\r{\right} \def\lr#1#2#3{\l#1 #3 \r#2}$ 
## A. shampagne

手玩一下特殊情况就得出结论了。

## B. whiskey

显然要枚举一个的，枚举 $a$，画出图像后容易用线段树维护。

## C. vodka

等效于求 $\l[\dfrac{x^n}{n!}\r] \l( \sum i^F \dfrac{x^i}{i!} \r)^L e^{x(K - L)}$。

那么：

$$
\begin{aligned}
\sum_{i} i^F \dfrac{x^i}{i!} &= \sum_{i}\sum_{k}k! \binom{i}{k} {f \brace k} \dfrac{x^i}{i!} \\
&= \sum_{i}\sum_{k}k! {F \brace k} \dfrac{x^i}{k! (i - k)!} \\
&= \sum_{k} {F \brace k} x^k e^x \\

\end{aligned}
$$

那么所求：
$$
\l[\dfrac{x^n}{n!}\r] e^{xK} \lr(){\sum_{k} {F\brace k} x^k}^L
$$
考虑 $e^{xK}$ 的展开形式：
$$
\sum_{i} \dfrac{K^i x^i}{i!}
$$
注意到右边的系数是个整数，前面的 $n!$ 意味着，如果右柿贡献了 $x^{mod}$ 及更高的项，则会出现一个 $n^{\underline{mod}}$ 的常数，显然包含 $mod$ 的倍数，故右柿最多只有 $mod$ 项，暴力快速幂可以做到 ${\cal O}(mod^2 \log L)$ 的复杂度。

如果使用短多项式快速幂科技，可以做到 ${\cal O}(mod^2)$(其实是 ${\cal O}(mod \times l)$)，常数很小。

