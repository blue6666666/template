"""One-off, reviewed edits. Every replacement must match the expected source."""
from pathlib import Path
import re

path = Path('模板.md')
text = path.read_text('utf-8')


def replace(old, new, count=1):
    global text
    actual = text.count(old)
    assert actual == count, (old[:90], actual, count)
    text = text.replace(old, new)


start = text.index('# 不要忘记')
text = '''# ACM/ICPC 算法模板

## 使用约定

本手册各代码块独立选用；同名结构体、多个 main 和不同版本不要一起粘贴。片段按题意补齐输入输出与全局数组。

- 默认使用 GNU C++17；`__int128`、`bits/stdc++.h` 和 builtin 属于 GCC 扩展，个别片段另需 C++20/23。
- 常用别名：`using ll = long long; using db = double; using i128 = __int128_t; using pii = pair<int,int>;`。
- 下标和区间以各条目说明为准；多测清空边表、计数器、懒标记与答案，递归深树注意栈空间。
- 先估算时间与内存；乘法在计算前转宽类型，模逆先确认存在，哈希和浮点结果注意碰撞与误差。
- 原有题目解法、样例、重复版本全部保留；标为“片段/骨架”的代码须补齐依赖后使用。

## 如何添加算法

在对应一级章节下添加二级算法标题，可在代码前写“用法 / 注意 / 复杂度”。一个条目支持多个代码块、正文、公式和表格。

````text
## 算法名称

**用法**：调用入口、下标和返回值。**注意**：适用条件。

```cpp
// 你的代码
```
````

运行 `python make.py` 生成 PDF；`python make.py --no-pdf` 仅生成 TeX。需要 XeLaTeX（MiKTeX / TeX Live），Python 无需第三方包。

版式参考：[KACTL](https://github.com/kth-competitive-programming/kactl)、[Stanford ACM Notebook](https://github.com/jaehyunp/stanfordacm)。

---

''' + text[start:]

# Minimal, demonstrable corrections. Keep the algorithm families and variants.
replace('-std=c++23 -o2', '-std=c++23 -O2')
replace('system("A < _data.in > A.ans");', 'system("A < _data.in > A.out");', 2)
replace('system("std.exe<data.in>data.out")', 'system("std.exe<data.in>std.out")')
replace('cout<<"AC\\n";\n}', 'cout<<"对拍结束（已发现不一致）\\n";\n}')
replace('int mx = *min_element(vec.begin(), vec.end(), cmp);', 'int mx = *max_element(vec.begin(), vec.end(), cmp);')
replace('// 填充 1~n，令 a[i]=i', '// 填充 0~n-1，令 a[i]=i')
replace('__lg(i);  // i 最多 32 位', '__lg(i);  // i > 0；按实参类型支持 int / long long')
replace('区间长度应该用 key 的差值，比如 *next(it) - *prev(it)。', '元素个数与 key 差值不同；要 O(log n) 查排名，请使用树状数组/平衡树。')
replace('assert(m==-1 || (n-1<=m', 'assert(n >= 1);\n\tassert(m==-1 || (n-1<=m')
replace('if (root == -1) { root = Rand(0, n-1); }', 'if (root == -1) { root = Rand(0, n-1); }\n\telse { --root; }  // 指定根为 1-based，转为偏移量')
replace('    int sz;\n    multiset', '    int sz = 0;\n    multiset')
replace('    ll minS, maxS;', '    ll minS = 0, maxS = 0;')
replace('for(int i=bi[l];i<bi[r];i++)', 'for(int i=bi[l]+1;i<bi[r];i++)')
replace('        f[x] = y;\n        pre[x] += siz[y];', '        if (x == y) { return; }\n        f[x] = y;\n        pre[x] += siz[y];')
replace('        return abs(pre[x]-pre[y])-1;', '        if (!same(x, y)) { return -1; }  // 同时完成路径压缩\n        return x == y ? 0 : abs(pre[x]-pre[y])-1;')
replace('for (int j = 0; j+(1<<(i-1)) < n; ++j)', 'for (int j = 0; j+(1<<i) <= n; ++j)')
old = '''\tint find(int l, int x) {  // 倍增写法
\t    assert(l < n);
\t    if (st[0][l] < x) { return l; }
\t    if (query(l, n-1) >= x) { return n; }
\t    int ans = l, g = st[0][l];
\t    for (int i = I; i >= 0; --i) {
\t        if (ans+(1<<i) < n && gcd(g, st[i][ans]) >= x) {
\t            g = max(g, st[i][ans]);
\t            ans += 1 << i;
\t        }
\t    }
\t    return ans;
\t}'''
new = '''\tint find_binary_lifting(int l, T x) {  // 同一查询的倍增写法
\t    if (l >= n) { return -1; }
\t    int ans = l;
\t    for (int i = I; i >= 0; --i) {
\t        if (ans+(1<<i) <= n && st[i][ans] < x) {
\t            ans += 1 << i;
\t        }
\t    }
\t    return ans == n ? -1 : ans;
\t}'''
replace(old, new)
replace('findLast(lson, m, r, x, y, pred)', 'findLast(rson, m, r, x, y, pred)')
replace('findLast(rson, l, m, x, y, pred)', 'findLast(lson, l, m, x, y, pred)')
replace('a(4 << __lg(n))', 'a(4 * max(1, n))')
replace('        build(1, 0, n);', '        if (n) { build(1, 0, n); }')
replace('cerr << format("a[{}] = [ {}, {}, {} ]\\n", p, l, r, a[p].mx);', 'cerr << "a[" << p << "] = [ " << l << ", " << r << ", " << a[p].mx << " ]\\n";')
replace('    Info(int mx = 0): mx(mx) { }', '    Info(int mx = numeric_limits<int>::lowest()): mx(mx) { }')
replace('        root = 0;\n        cnt = 0;\n        vc = 0;', '        root = 0;\n        sz[0] = 0;\n        cnt = 0;\n        vc = 0;', 2)
replace('        sz[0] = 0;\n        cnt = 0;', '        sz[0] = 0;\n        cnt = 0;', 2)  # sentinel setup, dif separately below
replace('    int sz[MAXN], dif[MAXN];', '    int sz[MAXN]{}, dif[MAXN]{};')
replace('    if (l == r) { return 0; }', '    if (l >= r) { return 0; }')
replace('    return tmp[0];', '    return tmp.empty() ? 0 : tmp[0];')
# The omitted closing edge must not participate in path search on a unicyclic graph.
replace('''\t    G[u].push_back(v);
\t    G[v].push_back(u);
\t    if (d.same(u, v)) { s=u; t=v; }
\t    d.merge(u, v);''', '''\t    if (d.same(u, v)) { s=u; t=v; }
\t    else {
\t        G[u].push_back(v);
\t        G[v].push_back(u);
\t        d.merge(u, v);
\t    }''')
replace('    return tmp.empty() ? 0 : tmp[0];', '    return tmp.empty() ? 0 : tmp[0];')
replace('for(int i=0;i<tmp.size()-1;i++)', 'for(int i=0;i+1<(int)tmp.size();i++)')
replace('''\tint s = 1;
\twhile (s <= 2*n''', '''\tif (n == 0) { cout << "YES\\n"; return 0; }
\tint s = 1;
\twhile (s <= 2*n''')
replace('cout << "NO\\n"; return;', 'cout << "NO\\n"; return 0;')
replace('''\t} else {
\t    cout << "YES\\n";
\t    for (auto x: ans)''', '''\t} else {
\t    reverse(ans.begin(), ans.end());  // 回溯顺序转为行走顺序
\t    cout << "YES\\n";
\t    for (auto x: ans)''')
replace('void add_edge(int u, int v, ll w) {\n        G[u].push_back', 'void add_edge(int u, int v, ll w) {\n        if (u == v) { return; }  // 自环不贡献 s-t 最大流\n        G[u].push_back')
replace('    ll dicnic(int st, int ed) {\n        for', '    ll dicnic(int st, int ed) {\n        if (st == ed) { return 0; }\n        for')
replace('    matrix C(n, vector<ll>(m));', '    matrix C(n, vector<ll>(k));')
replace('printf ("%d\\n", x);', 'printf ("%lld\\n", x);')
replace('''ll C(ll n, ll k) { return n==0? 1: fac[n] * Inv[k] % MOD * Inv[n-k] % MOD; }
ll P(ll n, ll k) { return n==0? 1: fac[n] * Inv[n-k] % MOD; }
// 预处理阶乘和阶乘的逆元
for (int i = 1; i <= N; ++i) {
\tfac[i] = fac[i-1] * i % MOD;
\tInv[i] = qpow(fac[i]); 
}''', '''ll C(ll n, ll k) {
    if (n < 0 || k < 0 || k > n) { return 0; }
    return fac[n] * Inv[k] % MOD * Inv[n-k] % MOD;
}
ll P(ll n, ll k) {
    if (n < 0 || k < 0 || k > n) { return 0; }
    return fac[n] * Inv[n-k] % MOD;
}
// 预处理阶乘和逆阶乘；依赖质数 MOD 与 qpow，limit < MOD
void init_comb(int limit = N) {
    assert(0 <= limit && limit <= N && limit < MOD);
    fac[0] = Inv[0] = 1;
    for (int i = 1; i <= limit; ++i) {
        fac[i] = fac[i-1] * i % MOD;
        Inv[i] = qpow(fac[i]);
    }
}''')
replace('if (a < p && b < p) { return C(a, b); }', 'if (a < MOD && b < MOD) { return C(a, b); }')
replace('        if (k&1) res = res * t % p;\n        t = t * t % p;', '        if (k&1) res = 1LL * res * t % p;\n        t = 1LL * t * t % p;')
replace('    int res = 1 % p, t = m;', '    int res = 1 % p, t = (m % p + 1LL * p) % p;')
replace('void insert(int *num)', 'void insert(long long *num)')
replace('    long long place[N];', '    long long place[64]{};')
replace('if(i * p > n) break;', 'if(1LL * i * p > n) break;')
replace('if (i*p > n) { break; }', 'if (1LL*i*p > n) { break; }')
replace('for(int p=2;p*p<=x;p++)', 'for(int p=2;1LL*p*p<=x;p++)')
replace('int norm(int n) { return 1 << (__lg(n-1) + 1); }', 'int norm(int n) { return n <= 1 ? 1 : 1 << (__lg(n-1) + 1); }')
replace('a[i] = int(c[i].y * 0.5 + 0.5);', 'a[i] = int(llround(c[i].y * 0.5));')
replace('''\tfor (int i = 1; i <= k; ++i) {
\t\tupdate(i, a[i]);
\t}''', '''\tfor (int i = 1; i < k; ++i) {
\t\tupdate(i, a[i]);
\t}''')
replace('''\t\tans[v] = w - ans[u]; // 递推求解
''', '''\t\tans[v] = w - ans[u]; // 递推求解
            q.push(v);
''')
replace('''            cout<<i-t.length()+2<<endl;
        }''', '''            cout<<i-t.length()+2<<endl;
            j = nxt[j-1];  // 回退后继续匹配，允许重叠
        }''')
replace('''        cout<<nxt[i]<<' ';
    }
}''', '''        cout<<nxt[i]<<' ';
    }
    delete[] nxt;
}''')
# The second shifted Vandermonde formula had the wrong sign.
replace('''\\binom b{k-r}
=\\binom{a+b}{a+r}''', '''\\binom b{k-r}
=\\binom{a+b}{a-r}''')

notes = {
'土制cph(仅linux)': '用法：保存为 Python 脚本，传入题号和源文件名；读取 samples-题号中的 .in/.ans。注意：依赖 Linux timeout 与 g++；文件名不要含空格，先确认编译成功。',
'土制cph(全平台)': '用法：同上，Python 分支传带 .py 的文件名，C++ 分支传不含扩展名的文件名。注意：需可用的 Python/g++，非零退出码按 RE 处理；浮点比较须同时检查 token 数量。',
'随机数': '用法：Rand(x,y) 返回闭区间 [x,y] 的均匀随机整数，要求 x<=y；shuffle 打乱序列。注意：对拍复现时固定种子。',
'对拍': '用法：依次运行生成器、暴力程序和待测程序，比较 A.out 与 A.ans。注意：先确认三个命令都成功；Windows 用 fc，Linux 用 diff，保留首个失败输入。',
'解除python大数限制': '用法：Python 3.11+ 在转换超长十进制整数前设置；此处仍限制为 100005 位。注意：set_int_max_str_digits(0) 才是完全解除；旧版本需判断该函数是否存在。',
'常用函数': '用法：read 读取 int，qpow(a,b) 求模幂，qpow(a) 求逆元。注意：快读假定输入完整；模运算传入 [0,MOD) 的数，逆元要求 MOD 为质数且 a 非零；乘积超 ll 时用 i128。',
'高精度': '用法：先定义 __int128 的流运算符，再以 cin/cout 读写；fixed/setprecision 只控制浮点显示。注意：__int128 是固定 128 位整数，不是任意精度；本版不处理最小负数取反。',
'多进程评测': '用法：此处仅为接收进程编号并读写数据的示例。注意：它不会自动启动多个进程；并发调度与每个进程的独立输入输出需另写。',
'迭代器辅助函数': '注意：不要递增 end()、递减 begin() 或解引用 end()；set 的迭代器不支持减法，distance 是线性时间。',
'set相关': '用法：优先用 s.lower_bound/upper_bound 进行对数查找。注意：比较器须严格弱序，不能用 <=；multiset.erase(x) 会删掉全部 x，只删一个时用 find 后 erase(it)。',
'vector相关': '注意：min/max_element 要求非空；unique 只去相邻重复，须先排序；reserve 不改变 size，resize 会；扩容后旧迭代器、引用可能失效。',
'整数域三分': '用法：给定非空整数闭区间 [l,r]，用于严格单峰最大值；末尾比较剩余端点。注意：任意平台区不保证正确；值类型按范围调整，二次函数优先直接检查顶点附近整数。',
'运行时间': '用法：start 放在待测代码之前，stop 放在之后，duration 单位为毫秒。注意：计时截断属于启发式，不保证答案最优；稳定计时建议用 steady_clock。',
'记得快读快输': '注意：放在任何 cin/cout 操作之前；关闭同步后避免混用 scanf/printf/getchar；交互题在输出后显式 flush。',
'！！！数据范围': '注意：1LL*a*b 先提升类型，(ll)(a*b) 仍可能先溢出；不要把 memset(a,1) 当成逐元素赋 1；double 有精度限制，是否超时取决于输入量与实现。',
'__int128的使用': '用法：本块的 int 宏只在 read/print 定义期间生效，之后已 undef。注意：输入须完整；最小负数的绝对值不可用有符号 __int128 表示，必要时改用无符号中间量。',
'快读模板': '用法：read() 读取有符号 int。注意：仅在输入完整、数值不超 int 时使用；EOF 循环与更宽整数需另行处理，register 在现代 C++ 中可省略。',
'数组离散化': '用法：先把全部候选值放入 vals，排序去重；编号可用 lower_bound(vals.begin(),vals.end(),x)-vals.begin()+1。注意：只保留大小关系，不保留数值间距。',
'随机数生成器': '用法：Rand(x,y) 生成闭区间整数；若同时粘贴“随机数”条目，只保留一份 rng/Rand 定义。注意：记录种子方便复现。',
'随机图': '用法：Graph(n) 生成树；Graph(n,m,root) 生成 1-based 连通无向简单图，指定根属于 [1,n]。注意：结果不保证均匀分布，稠密图拒绝采样较慢；依赖 rng/Rand。',
'对拍器': '用法：先编译 data/std/solve，比较 std.out 与 solve.out，失败输入为 data.in。注意：示例命令按 Windows 写；应检查命令返回值，浮点题改为误差比较。',
'对顶multiset': '用法：add(x)/del(x) 插入或删除一个已有元素，med() 取中位数，dis_to_med() 求绝对偏差和；可用 clear() 重置。注意：偶数时取较大中位数，空集不能查询；每次增删 O(log n)，查询 O(1)。',
'分块': '用法：读入 1-based arr 后 build；update(i,v) 单点赋值，query(l,r,v) 统计闭区间内 >=v 的个数。复杂度：修改 O(B log B)，查询 O(B+(n/B) log B)，B 约为 sqrt(n)。',
'带权并查集': '用法：DSU d(n)，merge(x,y) 把 x 所在整列接到 y 列后；query(x,y) 返回两点间元素数，不同列返回 -1。注意：这是队列距离版，不是通用差分约束版；同列不再合并。',
'Trie': '用法：insert(s) 插入，query(s) 统计以 s 为前缀的字符串数，init() 清空；根为 0。注意：字符限 62 种字母数字，空前缀计数未维护；ch 约占 710 MiB，按总字符数缩小 S，勿在栈上定义。',
'ST表': '用法：ST<int> st(a)，query(l,r) 查询 0-based 闭区间最大值；find/find_binary_lifting 返回从 l 开始第一个使最大值 >=x 的右端点，无解为 -1。复杂度：预处理 O(n log n)，查询 O(1)，查找 O(log n)；静态数组，不支持修改。',
'树状数组': '用法：BIT t(n)，modify(i,d) 单点加，query(r)-query(l-1) 求 1-based 闭区间和，select(k) 找最小前缀和 >=k 的位置。注意：modify 不能传 0；select 要求各点非负、n>0，越过总和返回 n+1；累计值超 int 时改 ll。',
'线段树': '用法：segmentTree<Info> t(vector<Info>{...})，modify(pos,x) 单点赋值，query(l,r) 查询 0-based 闭区间最大值。注意：底层 dfs/findFirst/findLast 用半开区间 [x,y)；pred 必须允许整段剪枝（如 mx>=x）；无懒标记，不支持任意区间更新。',
'替罪羊树': '用法：两个 ScapegoatTree 版本二选一；insert/erase、rank（1-based）、kth、pre/nxt。注意：大数组对象放全局/静态；删除不会回收 cnt，容量按历史插入量估计；后继的 x+1 不可溢出，kth 先检查范围。',
'逆序对': '用法：msort(a,0,n-1) 返回严格逆序对数，并将原数组排序。复杂度：O(n log n) 时间、O(n) 辅助空间；计数用 ll，相等元素不计逆序。',
'笛卡尔树': '用法：下标 1..n，预清空 L/R，单调栈建立小根笛卡尔树，根为 stk[0]。注意：n>0；相等值按原下标稳定保留；遍历最坏可能达到 n 层。构建 O(n)。',
'可持久化': '用法：此块为版本数组的输入输出样例，对应下一份历史单点修改模板。注意：不是实现代码；版本 0 为初始数组，每次操作产生新版本。',
'线段树模板': '用法：build(1,1,n)，update(1,1,n,l,r,x,type)，type=1 乘、type=2 加；query 求闭区间和模 p。注意：乘标记初值为 1，先乘后加，p>0；x 先取模，乘积按范围提升类型。',
'主席树（可持久化线段树）': '用法：root[0]=build(1,n)，update 返回新版本根，query(root[v],1,n,i) 查历史单点。注意：本版是可持久化数组，不是区间第 k 小；查询操作也须保留对应根。空间 O(n+m log n)。',
'开点线段树': '用法：用于大值域上的稀疏区间修改/求和，按需创建左右子节点。注意：建点计数不能超过池容量，懒标记下推前保证子节点存在；多测重置根与节点池，不能假定一定省内存。',
'权值线段树': '用法：在离散化值域上 build；update(k,cnt) 调整数值频次，query 查频次，kth 沿左右子树计数找排名。注意：本实现 kth 优先左子树，返回第 k 小；频次非负，1<=k<=总数。',
'线段树上最值操作': '用法：setmin 将闭区间每个值改为 min(原值,v)，维护 sum、最大值、次大值和最大值个数。注意：仅当次大值 <v<最大值时可整段打标；sentinel 应小于所有真实值，复杂度需势能分析。',
'线段树上序列操作': '用法：在 0/1 序列上维护前缀、后缀与最长连续 1；Update 赋值，Reverse 翻转，query 查最长连续段。注意：先核对原题的下标转换，覆盖和翻转标记须正确合成。',
'非经典线段树': '用法：当前实际代码维护区间加、和、平方和，用 E[x²]-E[x]² 求方差。注意：不是区间开方模板；更新平方和要使用更新前的和，输出精度和微小负误差按题意处理。',
'Kruskal重构树': '用法：按权排序合并，原点为叶子，新点存合并边权，树上 LCA 权值为最小生成树路径最大边。注意：最多 2n-1 个点，边数组按 m 分配；不连通时建森林并先判连通。',
'左偏树': '用法：merge 合并小根堆，pop/remove 删除根，find 定位所属堆；后半部分为题目变体，二选一。注意：被删节点不能再参与操作；dis[0] 的约定、并查集代表同步更新。',
'虚树的构建': '用法：先对原树 dfs 预处理 dfn/LCA，再把关键点放入 arr，buildvtree 返回虚树根；空集返回 0。注意：每轮清空 arr、iskey 和相关 DP，只清本轮 tmp 节点边表；边表示原树路径而非一条原边。',
'最短路': '用法：此 bitset 片段实际求传递闭包（可达性），先令 b[u][v]=1，再执行中转点外层循环。注意：不计算带权最短距离；需要长度 0 路径可达时设置 b[i][i]。',
'判奇环（无向图）': '用法：hasOddCycle(n,adj)，顶点为 0..n-1，true 表示存在奇环。注意：无向边加入两次，包含不连通图；示例提示文字提交前移除，递归深链注意爆栈。O(n+m)。',
'最小生成树': '用法：kruskal 读入边并排序，用普通并查集 dsu 合并，G 存生成树。注意：cnt 必须等于 n-1 才连通，否则为生成森林；总权用 ll，dsu 不要误用队列距离版。O(m log m)。',
'拓扑排序': '用法：预先统计有向边入度 deg，运行后 topo.size()==n 表示 DAG。注意：过程会修改 deg，多次调用先保存副本；输出顺序不唯一，字典序最小用小根堆。O(n+m)。',
'LCA': '用法：填满 mn 为 INF、根深度从 1 起，dfs(root,0) 后调用 LCA(u,v)。注意：该函数返回路径最小边权，不返回祖先编号；u==v 返回 INF。预处理 O(n log n)，查询 O(log n)。',
'树的直径与中心': '用法：清空 d/mxd，dfs(root,0)，mxd 为无权树直径边数。注意：本段没有恢复直径路径或中心；中心为直径路径中间的一点或两点。O(n)。',
'点分治与树的重心': '用法：先求重心并以重心重新计算 siz，再 work；在 work 中补充各子树距离的统计与去重贡献。注意：当前是分治骨架，尚无具体答案；vis 为已移除的重心，距离累加可需 ll。',
'基环树': '用法：无向连通图恰有 n 条边时，并查集找出闭环边 s-t，其余边组成树，dfs 找出环上的点。注意：输出将点排序，失去环顺序；不用于一般多环图，s/t/n 与普通 dsu 需补齐。',
'Hierholzer求欧拉路': '用法：本版 n 为边数，点号至多 2n；无向边两端共用唯一边 id，deg 按边计算。注意：非零度点须连通，奇度点为 0 或 2，结果为边 id；回溯后逆序才是行走顺序。O(n)。',
'DSU on tree': '用法：dfs_init(root,0)，再 dfs_solve(root,0,true)；轻子树清空，重子树保留。注意：补齐 cnt、ccnt、ans 并初始化，颜色离散化；此例统计子树颜色出现次数是否相同。O(n log n)。',
'tarjan': '用法：SCC s(n)，add_edge(u,v) 添加有向边，work() 返回 1-based 分量编号 col。注意：同编号等价于互相可达，缩点后为 DAG；编号是出栈顺序，别当原图拓扑序直接用。O(n+m)。',
'树哈希': '用法：getHash(root,0) 求有根树无序子树哈希，has 相等用于快速比较。注意：概率算法可能碰撞；无根树先取重心（一或两个），比较同一随机种子下的结果。O(n)。',
'Bellman-Ford / SPFA（判负环）': '用法：build(n)、add(u,v,w) 后 spfa()，true 表示从点 1 可达的负环。注意：判全图负环须把所有点距离置 0 并入队；最坏 O(nm)，dis/松弛和按范围改 ll。',
'Floyd 全源最短路': '用法：对角线置 0，其余置 INF，重边取最小，再 floyd。注意：中转点最外层；负环可由 dis[i][i]<0 检测；INF 要大于实际距离且加法不溢出。O(n³) 时间、O(n²) 空间。',
'树上倍增': '用法：先设根深度为 1、0 号虚父深度为 0，预处理 st，power 取足够大的最高位；getkthAncestor(i,k) 返回祖先或 -1。注意：此 dfs 按有向父子边写，无向树须跳过父亲。',
'树的直径': '用法：无权树两次 dfs，第二次从第一次最远点出发；每次遍历前重置 maxd。注意：边数为距离；带非负权可累加边权，负权树不适用两次最远点法。O(n)。',
'树的重心': '用法：清空 sz，dfs(root,0,centroid)，centroid 得到一个重心。注意：n 必须是当前连通子树大小；可能有两个重心，此版仅保存其中一个。O(n)。',
'最大流': '用法：Flow f，add_edge(u,v,cap) 建有向容量边，dicnic(s,t) 求最大流。注意：s!=t、容量非负，流量用 ll；调用会修改残量网络，多测清空边表；数组较大时全局定义。一般复杂度 O(V²E)。',
'最近公共祖先（LCA）': '用法：无向树建边，dfs1(s,0)、dfs2(s,s)，LCA(x,y) 返回祖先编号。注意：链深递归可能爆栈，多测清空 hson/top；预处理 O(n)，查询 O(log n)。',
'树链剖分': '用法：dfs1/dfs2 预处理，在线段树上对新编号操作，路径拆为多段，子树对应连续区间。注意：本版点权、模运算；边权版需排除 LCA 点，多测清空全局状态，乘长度先用 ll。路径 O(log² n)。',
'最大路匹配': '用法：当前为二分图增广路匹配，match 记录对侧匹配，逐个左部点尝试增广。注意：每次增广重新清访问标记；仅适用于二分图，不是一般图最大匹配。',
'Dijkstra算法': '用法：建带权邻接表，源点 dis=0，堆中取最小距离进行松弛；同块版本择一。注意：边权必须非负，跳过已确定或过期状态；距离/INF 用足够宽类型。堆版 O((n+m) log n)。',
'分层图最短路': '用法：把状态写成（已使用次数,原顶点），普通边留在本层，特殊操作连下一层；在所有合法终点层取最优。注意：各层的点边容量、总内存和边权条件均要核对。',
'双向广搜': '用法：从起点和终点分别 BFS，扩展较小前沿。注意：反向搜索需使用反图；普通 BFS 要求单位边权，交会判定须保证最短层次；本块按原题状态定义使用。',
'tarjan(强连通分量)': '用法：对所有未访问点运行 tarjan，收集有向图 SCC。注意：回边仅指向仍在栈中的点时更新 low；与无向图割点/双连通算法区分。O(n+m)。',
'边双连通分量': '用法：无向边成对添加，DFS 时按边 id 排除反向父边，收集去掉桥后的连通块。注意：不能只排除父顶点（会误判重边）；对全部连通分量启动 DFS。O(n+m)。',
'割边': '用法：成对 add，tot 从 1 开始，反向边为 ei^1；tarjan 后 cutedge[原边号] 标记桥。注意：桥条件 low[v]>dfn[u]，重边按 id 跳过反向父边。O(n+m)。',
'点双连通分量': '用法：uadd 添加无向边，对每个未访问点设 root 并 tarjan；dcc 存点双分量。注意：割点可以属于多个点双；根割点与孤立点特殊处理，low[v]>=dfn[u] 为分界。',
'割点': '用法：对每个连通分量 Tarjan(i,i)，flag 为割点标记。注意：非根条件 low[v]>=dfn[u]，根需至少两个 DFS 子树；与桥的严格不等号不同。O(n+m)。',
'2-SAT': '用法：TwoSAT s(n)，变量 0-based，文字用 pos/neg；addOr、imply、setTrue 等建约束，solve() 后读取 ans。注意：^1 只对原始文字有效，辅助节点不能取反；蕴含必须有逆否边。O(V+E)。',
'线段树优化建图': '用法：Graph G(n)，原点映射 a，SegGraph sg(G,a)，再 pointToRange/rangeToPoint/rangeToRange。注意：区间为 0-based 闭区间；本版无权辅助边只表达可达性，最短路版需补权值且辅助边权为 0。',
'线性筛': '用法：sieve(n) 返回不超过 n 的质数，mP 为最小质因子表；分解 x 时重复除以 mP[x]。注意：n>=1、1<=x<=n，多测重新筛；筛表若放函数内部，分解片段需在同作用域执行。O(n)。',
'因数': '用法：getFactors(x) 返回所有正因数（未排序），x>=1；x=1 返回 {1}。复杂度：试除 O(sqrt(x)) 加生成因数；大量查询可改为预筛最小质因子。',
'拉格朗日插值': '用法：lagrange_interpolation(x,y) 返回按低次到高次存储的系数；Horner 法求 f(k)。注意：x/y 等长，模 MOD 的 x 两两不同；x/y/k 先规范化到 [0,MOD)，总时间 O(n²+n log MOD)。',
'快速幂与乘法逆元': '用法：qpow(a,b) 求模幂，qpow(a) 用费马小定理求逆元；Exgcd 求 ax+py=gcd(a,p)。注意：费马逆元要求质数模且 a 非零，一般逆元要求 gcd=1；线性逆元公式需质数模、i<p。',
'中国剩余定理': '用法：CRT(k,a,r)，数组下标 1..k，解 x≡a[i] (mod r[i])。注意：本版要求模数两两互质且 >0；依赖 exgcd，模数乘积及中间乘法可能溢出，非互质需 EXCRT。',
'扩展欧几里得': '用法：本块保留的仍是 CRT 代码；exgcd 的实现见“快速幂与乘法逆元”的 Exgcd，使用时统一函数名/别名。注意：ax+by=gcd(a,b)，只有 gcd=1 才能取模逆。',
'排列组合数': '用法：先 init_comb(limit)，再 C(n,k)/P(n,k)，要求 n<=limit；非法 k 返回 0。注意：依赖质数 MOD 与 qpow，limit<MOD；预处理 O(limit log MOD)，每次查询 O(1)。',
'Lucas': '用法：lucas(a,b) 求大 n 的组合数模 MOD。注意：MOD 必须为质数；依赖同模数 qpow，单个小组合数为 O(b)，MOD 较大或大量查询需预处理。',
'卡特兰数': '用法：Cat(n)=C(2n,n)/(n+1)，用于括号序列、栈序列等。注意：组合数预处理至少到 2n，n+1 模 MOD 非零才可除；不可逆时用 C(2n,n)-C(2n,n+1)。',
'数论分块': '用法：l 从 1 开始，r=n/(n/l)，在 [l,r] 内 floor(n/i) 相同，再 l=r+1。注意：多个整除式并用时取各自 r 的最小值，最后区间长度为 r-l+1。O(sqrt(n)) 块。',
'高斯消元': '用法：Guess(a)，a 为 n 行 n+1 列增广矩阵；返回 0 唯一解、1 无穷多解、2 无解，唯一解存最后一列。注意：会修改矩阵，需 db 与基于 eps 的 sgn；整数/模数消元不能直接套用。O(n³)。',
'矩阵快速幂': '用法：qpow(A,b)，b>=0，A 为非空方阵；矩阵乘法支持相容矩形矩阵，依赖模加 add 与模乘 mul。注意：状态向量采用行/列形式须与转移矩阵一致。O(d³ log b)。',
'自适应辛普森法': '用法：定义被积函数 f，calc(l,r,eps) 估计定积分。注意：step 是最小细分深度，不是递归上限；尖点/奇点先分段，eps 必须为正，极端情况应另设递归上限。',
'多项式': '用法：Poly 按低次到高次存系数，operator* 做实数 FFT 卷积；依赖 db、ll、cp。注意：非空多项式，变换长度为 2 的幂且<=2^21，结果须在 int 范围内，浮点误差大时用 NTT。',
'快速幂': '用法：qmi(m,k,p) 求 m^k mod p，k>=0、p>0；此版模数/指数均为 int。复杂度 O(log k)；更大模数用 ll/i128 乘法。',
'乘法逆元': '用法：fpm(a,p-2,p) 求逆元。注意：p 为质数且 a%p!=0；打印 1..n 的逆元需 n<p，0 不存在逆元；复合模改用 exgcd。',
'组合数求法': '用法：lucas(a,b,p)，拆分 p 进制位并用 C 计算小组合数。注意：p 必须为质数；此实现每项单独求逆，大 p/多查询可能超时，优先预处理阶乘。',
'线性基': '用法：insert(x) 插入，check(x) 判能否异或表示，mx/mn 求最大/最小非零异或；merge(A,B) 合入 B。注意：place 预清零，离线 insert 会改 num；有符号版最大值仅用于非负 63 位整数，全 64 位请改 ull。',
'矩阵快速幂及高斯消元': '用法：当前块实际仅有矩阵快速幂，power(A,p) 返回 A^p，Matrix 为 1-based。注意：矩阵维度须匹配，p>=0；高斯消元请使用前面的独立条目。',
'线性筛求质因子个数（Omega函数）': '用法：sieve_omega(n)，omega[x] 为计重质因子个数，如 omega[12]=3。注意：不是不同质因子个数，多次调用先清 primes/is_comp/omega；数组内存按 n 估算。O(n)。',
'线性筛(O(n))': '用法：运行片段得到 prime 与最小质因子 minp。注意：1 不是质数，分解时仅对 x>1 访问 minp；片段应放函数体内，i*p 判断先用 ll。',
'位运算的部分性质': '注意：此块是代数速查，不是可直接编译的 C++；表达式比较时给位运算加括号，^ 表示异或而非乘方，>>> 不是 C++ 运算符。补码/位宽恒等式须区分数学整数与无符号模 2^w 运算。',
'builtin': '注意：clz/ctz 的参数不能为 0；32/64 位选对应后缀；GCC 扩展，C++20 可用 bit 头文件里的 popcount/countl_zero/countr_zero。',
'前缀函数与KMP': '用法：prefixFunction(s) 返回 1-based fail，fail[i] 是前 i 个字符的最长真 border；kmp 输出 1-based 匹配起点。注意：连接用分隔符 # 必须不在原串中，模式串非空。O(n+m)。',
'Manacher': '用法：按示例插入分隔符并加两种不同哨兵，manacher(t) 返回包含中心的半径，最大 d-1 为原串最长回文长度。注意：哨兵不能出现在输入中；直接传未处理原串会越界。O(n)。',
'字符串哈希': '用法：Hash h(s)，预处理正反前缀及幂，再用成员函数查询子串/回文，按代码的 0-based 下标传参。注意：不同字符串使用同一组底数/模数；双模仍可能碰撞。预处理 O(n)，查询 O(1)。',
'AC自动机': '用法：add 插入所有模式并保存终点，work 建 fail，再从根 1 扫描主串并沿 fail 树汇总 cnt。注意：字符仅 a-z，work 仅调用一次；多测清 G/cnt，统计可包含重叠匹配。',
'后缀自动机SAM': '用法：sam.clear() 后逐字符 extend(c-\'a\'+1)，get_endpos 汇总出现次数；solve 求“重复子串长度×次数”最大值。注意：最多约 2|s| 个状态，大对象全局定义；get_endpos 不能重复累加。',
'KMP算法': '用法：主串 s、模式 t，get_nxt 生成 0-based 前缀函数，输出所有 1-based 匹配起点，再输出 nxt。注意：模式非空，完整匹配后回退 nxt[j-1] 保留重叠；O(n+m)。',
'Trie树': '用法：getidx 映射字母数字，insert 插入，查询时区分 pass 前缀数与 endp 完整串数。注意：根为 1，总节点数按字符总数估计；二维转移数组很大，多测需清已用节点。',
'string常用函数': '注意：find 未找到返回 string::npos（size_t），不要强转 int 再判；substr(pos,len) 第二参是长度；tolower/toupper 先转 unsigned char，修改字符串可能使迭代器失效。',
'数位DP': '用法：f 初始化为 -1，query(b)-query(a-1) 统计相邻数字差至少 2 的数。注意：当前把 0 计为合法；只缓存非 limit、非前导零状态；改变限制条件须调整状态，范围按 ll。',
'单调队列优化（滑动窗口）': '用法：定义 1-based a 与窗口长度 k，work(less<int>{}) 输出最小值，work(greater<int>{}) 输出最大值。注意：1<=k<=n，以编号移除过期元素；O(n) 时间、O(k) 空间。',
'无向图上回路计数': '用法：简单无向图，f[mask][i] 记录固定最小点为起点的路径数，再去边、除以 2 去方向重复。注意：只适合小 n（如 n<=19），不能含重边/自环；f/ans 用 ll。',
'SOSDP': '用法：第一段累计子集和，第二段累计超集和；g 先复制原数组，状态 0..2^B-1。注意：两段二选一，不可无意连续作用同一 g；循环上界必须覆盖完整 B 位集合。O(B·2^B)。',
'树形DP': '用法：当前主程序解“正整数点权且每条边两端和为 w”，先 dfs 收缩可行区间，再 BFS 恢复；注释块为无上司舞会。注意：两个解法按题意选择，权值/边界范围按数据调整。O(n)。',
'最长不下降子序列': '用法：前半段离散化+线段树得到以 i 结尾的 LNDS 长度 dp[i]；后半段带 k 的合并为特定题解。注意：不下降查询 <=a[i]，严格上升查询 <a[i]；不能把整段当通用 LNDS。',
'define': '用法：整数几何选择 T=ll、精确 sgn；浮点几何选择 T=db 并启用 eps 版本 sgn。注意：后续截取使用时统一类型，不要重复定义 sgn。',
'向量': '用法：Point/Vector 的 * 为点积，^ 为叉积，len/ang 求长度/方向。注意：旋转、投影、缩放须用浮点 T，否则截断；trunc 不可传零向量，坐标乘积超 ll 时用 i128。',
'点线操作': '用法：Line(a,b) 表示两端点确定的直线，onSegment/hasIntersection 判闭线段，proj/getIntersection 求投影与交点。注意：a!=b；投影/交点用浮点 T；本 isParallel 排除重合直线，重合需单独判。',
'多边形与凸包': '用法：先排序并去重再构造凸包，面积用相邻点叉积和/2。注意：是否保留边界共线点由弹栈条件决定；处理 0/1/2 点，整型叉积与浮点精度须分开。O(n log n)。',
'计算几何模板': '用法：按需选择点线、圆、多边形相关函数，统一 eps 与 Point 类型。注意：输入退化情况（零长度、共线、相切）分别判；三角函数入参夹到 [-1,1]，避免 NaN。',
'二维差分与前缀和': '用法：矩形 [x1,x2]×[y1,y2] 四角差分，再做二维前缀和恢复。注意：下标从 1 开始，数组多开一行一列；边界差分避免四个角重复，面积/累计值可能需 ll。',
'CDQ分治': '用法：prepare 按三维排序并处理重复点，cdq(1,n) 统计三维偏序，BIT 在第三维计数。注意：坐标第三维>=1，修改后必须撤销；<= 和重复点计数要保持一致。本版每层排序约 O(n log² n)。',
'矩阵加速': '用法：当前主程序为 0/1 转移上的异或传播，预处理 wyx[i]，按步数二进制乘状态行向量。注意：这不是普通模加线性递推，支持的步数仅低 32 位；注释块才是普通递推例子。',
'cdq斜率优化': '用法：前缀 s[i]=sum(c[j]+1)，DP 为 f[i]=min(f[j]+(s[i]-s[j]-L)²)，f[0]=0 后 CDQ(0,n)。注意：这是原题递推，L 偏移按题意核对；交叉乘积用 i128，同斜率保留最小截距。',
'并查集': '用法：本块为“推导部分和”题解，利用并查集判断连通并在边图 BFS 计算势差。注意：不是普通 DSU 独立模板；边方向与权值符号、head 的 -1 哨兵按代码初始化。',
'FFT（快速傅里叶变换）': '用法：按低次到高次填系数，补零到至少 n+m-1 的 2 次幂长度，变换、点乘、逆变换。注意：逆变换除长度、取整有误差；大系数/精确模运算优先 NTT。O(L log L)。',
'NTT（数论变换）': '用法：系数先取模，长度补到卷积需要的 2 次幂，正变换点乘后逆变换。注意：长度必须整除 MOD-1，并配套原根；998244353 最长支持 2^23，数组池同时检查。O(L log L)。',
'扫描线算法': '用法：按事件坐标排序，坐标离散化后在线段树维护覆盖长度。注意：树节点代表相邻坐标的区间，不是坐标点；同坐标事件批量处理/令距离为 0，面积用 ll。',
'最长上升子序列': '用法：严格 LIS 的耐心排序用 lower_bound 替换第一个 >=x 的尾值；非下降改 upper_bound。注意：本条具体代码的附加判定按原题保留；只求长度时无需恢复完整序列。O(n log n)。',
'全排列输出': '用法：先 sort，再 do/while(next_permutation) 输出每个排列。注意：空序列有一个空排列；重复值仅输出不同排列，n! 增长很快，按题意过滤。',
'位运算用法': '注意：64 位掩码使用 1ULL<<k 且 k<64；子集枚举通常不含 0，需另处理；按位判断加括号；此块夹有文字示例，不是完整程序。',
'Map的使用': '用法：map 支持按 key 有序查询，find/contains 查存在性，lower_bound 找首个不小于 key。注意：operator[] 会插入缺失键，查询不想插入时用 find；每次操作 O(log n)。',
'优先队列（堆）': '用法：默认大根堆，greater<T> 为小根堆；top 后用 pop 删除。注意：空堆不能 top/pop，不支持任意删改；Dijkstra 用过期状态过滤。每次插入/弹出 O(log n)。',
'扫描线+线段树（矩形面积并）': '用法：矩形生成上下边事件，线段树维护 x 方向被覆盖的实际长度，相邻事件高度差乘覆盖长度。注意：叶子数为离散坐标数-1，重叠用计数而非 bool；零面积矩形可忽略。',
'建树参考': '用法：本块为特定建树题解，按原有条件构造边。注意：先验证可构造性与节点容量，不能当通用随机树生成器。',
'Hash树': '用法：用于树结构的随机哈希比较，按原题选择根与聚合方式。注意：概率碰撞仍存在；无根树先取重心，跨对象比较必须同一随机参数。',
'1. 范德蒙德卷积': '用法：组合数乘积求和先改成互补下标 n-k；平移 k+r 与 k-r 的右侧符号相反。注意：a/b 非负整数，越界下标的项按 0 处理。',
'2. 按位置拆分': '注意：带 2^(n-r-s) 的形式要求 0<=r,s 且 r+s<=n；不满足时原和为 0，不要在程序中计算负指数。',
'3. Hockey-stick': '用法：固定下标、上标连续增长时套用；有限求和范围必须与公式一致。注意：本块“带权形式”原内容仍为同一无权恒等式，不要误认为包含 k 权重。',
'5. 普通幂与组合数': '注意：这些等式按整数/有理数成立；小 n 使 2 的指数为负时单独计算或用逆元（模数须为奇数），别传负指数给快速幂。',
'7. 偶数项 / 奇数项': '注意：等分公式要求 n>0，n=0 时偶数项和为 1、奇数项和为 0；带符号三角公式是精确恒等式，不宜直接用浮点取模。',
'13. 负上标组合数': '注意：此处采用广义组合数，负上标不能按开头的普通越界约定置 0；n 为正整数、k>=0，先转换为非负上标再计算。',
'15. 竞赛速查': '注意：表中省略的求和范围沿用各正文公式；偶数项和要求 n>0，hockey-stick 固定 r 且 k 从 r 到 n。',
}

# Insert prose only outside fences; headings/code order is kept intact.
lines = text.splitlines()
out = []
fence = None
used = []
for line in lines:
    match = re.match(r'^\s*(`{3,}|~{3,})', line)
    if match:
        if fence is None:
            fence = match[1]
        elif match[1][0] == fence[0] and len(match[1]) >= len(fence):
            fence = None
    out.append(line)
    if fence is None and line.startswith('## '):
        title = line[3:]
        if title in notes:
            note = notes[title]
            # Consistent concise labels, not extra TOC entries.
            note = re.sub(r'^(用法|注意)：', r'**\1**：', note)
            note = note.replace('注意：', '**注意**：').replace('复杂度：', '**复杂度**：')
            note = note.replace('****注意****', '**注意**')
            out.extend(['', note])
            used.append(title)
assert set(notes) == set(used), set(notes)-set(used)
path.write_text('\n'.join(out)+'\n', 'utf-8')
print('Added notes to', len(used), 'entries')
