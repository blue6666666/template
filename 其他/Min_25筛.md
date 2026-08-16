
求积性函数 $f(n)$ 前缀和 $\sum_{i=1}^n f(i)$

> 以下 $p$ 表示质数

### 限制
$f(p)$ 是一个最高次数低，关于 $p$ 的多项式，即 $f(p)=\sum_{j=0}^{\infty}coe_j p^j$  
$f(p^k)$ 可以快速计算

## 第1部分
自己设一个完全积性函数 $f'$，要求 $f'(p)=f(p)$

> 以下 $p_j$ 表示第 $j$ 个质数，$p_1=2$，特别地，$p_0=1$  
> 以下 $minp(i)$ 表示 $i$ 的最小质因子，特别地，$minp(1)=0$

定义函数：
$$g(n,j)=\sum_{i=1}^n [i \in prime \text{ 或 } p_j < minp(i)] f'(i)$$

考虑DP求解，从 $g(n,j-1) \to g(n,j)$ 的转移中，减少的贡献为：
$$\sum_{i=p_j^2}^n [p_j=minp(i)] f'(i)$$

当 $p_j^2>n$ 时上式=0，即 $g(n,j)=g(n,j-1)$

当 $p_j \le \lfloor \sqrt n \rfloor$ 时：
$$\begin{aligned}
&\sum_{k=p_j}^{\lfloor n/p_j \rfloor} [p_j \le minp(k)] f'(p_j k) \\
=& f'(p_j) \sum_{k=p_j}^{\lfloor n/p_j \rfloor} [p_j \le minp(k)] f'(k) \\
=& f'(p_j) \left( g(\frac{n}{p_j},j-1) - \sum_{i=1}^{j-1} f'(p_i) \right)
\end{aligned}$$

整理得：
$$g(n,j)=\begin{cases} 
g(n,j-1) & p_j^2>n \\
g(n,j-1) - f'(p_j) \left( g(\frac{n}{p_j},j-1) - \sum_{i=1}^{j-1} f'(p_i) \right) & \text{otherwise}
\end{cases}$$

### 子问题复杂度证明
$\lfloor n/x \rfloor$ 最多 $2\sqrt{n}$ 个：  
- $x \le \sqrt{n}$ 时：$x$ 最多 $\sqrt{n}$ 个  
- $x > \sqrt{n}$ 时：$\lfloor n/x \rfloor \le \sqrt{n}$  

## 第2部分
定义函数：
$$S(n,j)=\sum_{i=1}^n [p_j < minp(i)] f(i)$$

分解贡献：
1. **质数部分**：  
   $\sum_{p \le n} f(p) - \sum_{i=1}^j f(p_i) = g(n,\infty) - \sum_{i=1}^j f(p_i)$
   
2. **合数部分**：  
   $$\begin{aligned}
   &\sum_{p}^{\lfloor \sqrt n \rfloor} \sum_{k=1}^{\lfloor \log_p n \rfloor} \left( [k>1]f(p^k) + f(p^k) \sum_{i=p+1}^{\lfloor n/p^k \rfloor} [minp(i)>p] f(i) \right) \\
   =& \sum_{j=1}^{\infty} \sum_{k=1}^{\lfloor \log_{p_j} n \rfloor} f(p_j^k) \left( S(\frac{n}{p_j^k},j) + [k>1] \right)
   \end{aligned}$$

最终表达式：
$$S(n,j)=g(n,\infty) - \sum_{i=1}^j f(p_i) + \sum_{k>j}^{\infty} \sum_{i=1}^{\lfloor \log_{p_k} n \rfloor} f(p_k^i) \left( S(\frac{n}{p_k^i},k) + [i>1] \right)$$

总前缀和：
$$\sum_{i=1}^n f(i) = S(n,0) + 1$$
