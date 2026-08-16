# ACM模板整合

> The Three Stooges
## 📚 目录
- [不要忘记](#不要忘记)
- [字符串算法](#字符串算法)
- [数据结构](#数据结构)
- [图论算法](#图论算法)
- [数论算法](#数论算法)
- [动态规划](#动态规划)
- [计算几何](#计算几何)
- [其他算法](#其他算法)

---
## 不要忘记 
### 若vscode 没有C++环境
 找到devC++的mingw 的bin文件夹，加入系统路径
 再在vscode中 >edit ui
 将路径输入，标准改为14
 即可

### 记得快读快输
```cpp   

ios::sync_with_stdio(0); 
cin.tie(0), cout.tie(0); 
``` 
### ！！！数据范围
```
    注意爆int

    long long: 8字节，-9,223,372,036,854,775,808到9,223,372,036,854,775,807
    unsigned long long: 8字节，0到18,446,744,073,709,551,615
    如果爆long long 就用__int128,但是注意输入输出

    尽量不要使用double输入，容易超时
```
### __int128的使用
```cpp
#define int __int128
inline void read(int &n){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    n=x*f;
}
inline void print(int n){
    if(n<0){
        putchar('-');
        n*=-1;
    }
    if(n>9) print(n/10);
    putchar(n % 10 + '0');
}
#undef int
```
### 快读模板
```cpp
#define re register
#define il inline
il int read()
{
    re int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*f;
}
```
### 随机数生成器
```cpp
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int Rand(int x, int y) {
	return uniform_int_distribution<int>(x, y)(rng);
}
shuffle(a.begin(), a.end(), rng);
```
### 随机图
```cpp
// n 为节点个数
// m 为边的个数，默认为 -1，表示建树
// root 为根节点编号，默认为 -1，
vector<array<int,2>> Graph(int n, int m=-1, int root=-1)
{
	assert(m==-1 || (n-1<=m && m<=1LL*n*(n-1)/2));
	assert(root==-1 || (1<=root && root<=n));
	vector<array<int,2>> E;
	set<array<int,2>> diff;
	// 先建一棵以 0 为根的树，然后选根偏移
	for (int i = 1; i < n; ++i) {
		E.push_back( { i, Rand(0, i-1) } );
	}
	if (root == -1) { root = Rand(0, n-1); }
	for (auto& [x, y]: E) {
		x = (x+root) % n + 1;
		y = (y+root) % n + 1;
		diff.insert( { x, y } );
		diff.insert( { y, x } );  // 无向图中需要添加这条反向边
	}
	// 从树建图
	if (m != -1) {
		for (int i = n-1; i < m; ++i) {
			while (1) {
				int x = Rand(1, n);
				int y = Rand(1, n);
				if (x == y || diff.count({x,y})) { continue; }
				E.push_back( { x, y } );
				diff.insert( { x, y } );
				diff.insert( { y, x } );  // 无向图中需要添加这条反向边
				break;
			}
		}
	}
	shuffle(E.begin(), E.end(), rng);
	return E;
}
```
### 对拍器
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t=0;
    while(true){
    cout<<"test: "<<t++<<endl;
    system("data.exe>data.in");//data.exe 随机数生成器
    system("std.exe<data.in>data.out");//std.exe 标准程序
    system("solve.exe<data.in>solve.out");//solve.exe 暴力求解算法
    if(system("fc std.out solve.out>diff.log")){
        cout<<"WA"<<endl;
        break;
    } 
}
cout<<"AC\n";
}
/*
// checker.cpp
while (1) {
	system("A_gen > _data.in");  // linux 下换成 ./xxx
	system("A_bf < _data.in > A.ans");
	system("A < _data.in > A.ans");
	if (system("fc A.out A.ans")) {  // linux 下换成 diff
		cout << "WA\n"; return 0;
	} else {
		cout << "AC\n";
	}
}*/
```
## 字符串算法

### AC自动机

```cpp
//dfs版
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

constexpr int N = 2e5 + 6;
constexpr int LEN = 2e6 + 6;
constexpr int SIZE = 2e5 + 6;

int n;

struct Node {
  int son[26];
  int ans;
  int fail;
  int idx;

  void init() {
    memset(son, 0, sizeof(son));
    ans = idx = 0;
  }
} tr[SIZE];

int tot;
int ans[N], pidx;

vector<int> g[SIZE];  // fail 树

void init() {
  tot = pidx = 0;
  tr[0].init();
}

void insert(char s[], int &idx) {
  int u = 0;
  for (int i = 1; s[i]; i++) {
    int &son = tr[u].son[s[i] - 'a'];
    if (!son) son = ++tot, tr[son].init();
    u = son;
  }
  // 由于有可能出现相同的模式串，需要将相同的映射到同一个编号
  if (!tr[u].idx) tr[u].idx = ++pidx;  // 第一次出现，新增编号
  idx = tr[u].idx;  // 这个模式串的编号对应这个结点的编号
}

void build() {
  queue<int> q;
  for (int i = 0; i < 26; i++)
    if (tr[0].son[i]) {
      q.push(tr[0].son[i]);
      g[0].push_back(tr[0].son[i]);  // 不要忘记这里的 fail
    }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < 26; i++) {
      if (tr[u].son[i]) {
        tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];
        g[tr[tr[u].fail].son[i]].push_back(tr[u].son[i]);  // 记录 fail 树
        q.push(tr[u].son[i]);
      } else
        tr[u].son[i] = tr[tr[u].fail].son[i];
    }
  }
}

void query(char t[]) {
  int u = 0;
  for (int i = 1; t[i]; i++) {
    u = tr[u].son[t[i] - 'a'];
    tr[u].ans++;
  }
}

void dfs(int u) {
  for (int v : g[u]) {
    dfs(v);
    tr[u].ans += tr[v].ans;
  }
  ans[tr[u].idx] = tr[u].ans;
}

char s[LEN];
int idx[N];

int main() {
  init();
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%s", s + 1);
    insert(s, idx[i]);
    ans[i] = 0;
  }
  build();
  scanf("%s", s + 1);
  query(s);
  dfs(0);
  for (int i = 1; i <= n; i++) {
    printf("%d\n", ans[idx[i]]);
  }
  return 0;
}
```

### KMP算法

```cpp
#include<bits/stdc++.h>
using namespace std;
void get_nxt(string s, int nxt[]){
    int j = 0;
    nxt[0] = 0;
    for (int i = 1; i < s.length(); i++)
    {
        while(j>0&&s[i]!=s[j]) j=nxt[j-1];
        if(s[i]==s[j])j++;
        nxt[i]=j;
    }
}
void solve(){
    int cnt=0;
    string s, t;
    cin >> s >> t;
    int* nxt = new int[t.length()];
    get_nxt(t, nxt);
    int j=0;
    for (int i = 0; i < s.length(); i++) //这里的s代表主串
    {
        while(j > 0 && s[i] != t[j]) j = nxt[j-1];
        if(s[i]==t[j]) j++;
        if(j==t.length()){
            cout<<i-t.length()+2<<endl;
        }
    }
    for (int i = 0; i < t.length(); i++){
        cout<<nxt[i]<<' ';
    }
}
int main(){
    solve();
}
```

### Trie树

```cpp
#include<bits/stdc++.h>
using namespace std;
int tree[3000005][70],pass[3000005],endp[3000005],cnt=1;
int getidx(char ch){
// 映射函数
if(ch>='a'&&ch<='z') return ch-'a';
if(ch>='A'&&ch<='Z') return ch-'A'+26;
return ch-'0'+52;    
}
void insert(string s){//插入操作
 int cur=1;
 pass[cur]++;
    for(int i=0;i<s.length();i++){
        int idx=getidx(s[i]);
        if(tree[cur][idx]==0) {
            tree[cur][idx]=++cnt;
        }
        cur=tree[cur][idx];
        pass[cur]++;
    }
    endp[cur]++;
}
int search_whole_s(string s){
    //查询整个字符串出现次数
    int cur=1;
    for(int i=0;i<s.length();i++){
        int idx=getidx(s[i]);
        if(tree[cur][idx]==0) return 0;
        cur=tree[cur][idx];
    }
    return endp[cur];
}
int search_prefix_s(string s){
    //查询s作为前缀字符串出现次数
    int cur=1;
    for(int i=0;i<s.length();i++){
        int idx=getidx(s[i]);
        if(tree[cur][idx]==0) return 0;
        cur=tree[cur][idx];
    }
    return pass[cur];
}
void delete1(string s)
{
    if(search_whole_s(s)>0)
    {
    int cur=1;
    for(int i=0;i<s.length();i++)
    {
    int idx=getidx(s[i]);
    if(--pass[tree[cur][idx]]==0)
    {
    tree[cur][idx]==0;
    return;
    }
    cur=tree[cur][idx];
    }
    endp[cur]--;
}
}
void clear()
{
    for(int i=1;i<=cnt;i++)
    {
    for(int j=0;j<=69;j++) tree[i][j]=0;
    pass[i]=0;
    endp[i]=0;
    }
    cnt=1;
}
```
### string常用函数
```cpp
三、基本属性
s.size();      // 长度（常用）
s.length();    // 同 size()
s.empty();     // 是否为空
四、访问与修改
s[i];          // 访问（不检查越界）
s.at(i);       // 访问（会检查越界）

s.front();     // 第一个字符
s.back();      // 最后一个字符
五、拼接与修改
1. 拼接
s += "abc";
s = s + "abc";
2. 插入
s.insert(2, "abc");   // 在下标2插入
3. 删除
s.erase(2, 3);        // 从下标2开始删除3个字符
4. 替换
s.replace(2, 3, "abc");   // 替换区间
六、子串操作
string t = s.substr(pos, len);  // 从pos开始，长度len

示例：

string s = "abcdef";
s.substr(2, 3);   // "cde"
七、查找操作（重点）
1. 查找子串
s.find("abc");     // 返回第一次出现的位置

找不到返回：

string::npos

示例：

if (s.find("abc") != string::npos) {
    // 找到了
}
2. 反向查找
s.rfind("abc");    // 从后往前找
3. 查找字符
s.find('a');
八、比较
if (s == t) {}
if (s < t) {}   // 字典序比较

底层是字典序（lexicographical order）

九、排序
#include <algorithm>

sort(s.begin(), s.end());

示例：

string s = "dcba";
sort(s.begin(), s.end());  // "abcd"
十、反转
reverse(s.begin(), s.end());
十一、大小写转换
#include <cctype>

for (char &c : s) c = toupper(c);
for (char &c : s) c = tolower(c);
十二、统计字符
int cnt = count(s.begin(), s.end(), 'a');
```
---

## 数据结构

### 线段树模板

```cpp
//区间乘法
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000010
#define ll long long
int p;
ll a[maxn], w[maxn*4];
ll lzy_add[maxn*4], lzy_mul[maxn*4];

void pushup(const int u) {
    w[u] = (w[u<<1] + w[u<<1|1]) % p;
}

void build(const int u, int L, int R) {
    lzy_mul[u] = 1;
    lzy_add[u] = 0;
    if (L == R) {
        w[u] = a[L] % p; 
        return;
    }
    int M = (L+R)>>1;
    build(u<<1, L, M);
    build(u<<1|1, M+1, R);
    pushup(u);
}

bool InRange(int L, int R, int l, int r) {
    return (l <= L) && (R <= r);
}

bool OutofRange(int L, int R, int l, int r) {
    return (R < l) || (L > r);
}

void maketag(int u, int L, int R, ll x, int type) {
    if (type == 1) {
        (lzy_mul[u] *= x) %= p;
        (lzy_add[u] *= x) %= p;
        (w[u] *= x) %= p;
    } else {
        (lzy_add[u] += x) %= p; 
        (w[u] += (R-L+1) * x) %= p;
    }
}

void pushdown(int u, int L, int R) {
    int M = (L+R)>>1;
    // 左子节点
    maketag(u<<1, L, M, lzy_mul[u], 1);
    maketag(u<<1, L, M, lzy_add[u], 2);
    // 右子节点
    maketag(u<<1|1, M+1, R, lzy_mul[u], 1);
    maketag(u<<1|1, M+1, R, lzy_add[u], 2);
    lzy_mul[u] = 1;
    lzy_add[u] = 0;
}

ll query(int u, int L, int R, int l, int r) {
    if (InRange(L, R, l, r)) {
        return w[u];
    } else if (!OutofRange(L, R, l, r)) {
        int M = (L+R)>>1;
        pushdown(u, L, R);
        return (query(u<<1, L, M, l, r) + query(u<<1|1, M+1, R, l, r)) % p; 
    } else {
        return 0;
    }
}

void update(int u, int L, int R, int l, int r, ll x, int type) {
    if (InRange(L, R, l, r)) {
        maketag(u, L, R, x, type);
    } else if (!OutofRange(L, R, l, r)) {
        int M = (L+R)>>1;
        pushdown(u, L, R);
        update(u<<1, L, M, l, r, x, type);
        update(u<<1|1, M+1, R, l, r, x, type);
        pushup(u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, m;
    cin >> n >> m >> p;
    for (int i = 1; i <= n; i++) 
        cin >> a[i];
    build(1, 1, n);
    while (m--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1 || op == 2) {
            ll k;
            cin >> k;
            update(1, 1, n, x, y, k, op); 
        } else {
            cout << query(1, 1, n, x, y) << endl; 
        }
    }
    return 0;
}
```

### 主席树（可持久化线段树）
```cpp
//对于单点历史修改与查询
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=(1e6+1);
int top,root[maxn],arr[maxn],n,m,cnt=0;
struct kkk{
    int l,r,val;
} a[maxn*30];
int build(int l,int r){
    int rt=++cnt;
    if(l==r)a[rt].val=arr[l];
    else {
        int mid=(l+r)>>1;
        a[rt].l=build(l,mid);
        a[rt].r=build(mid+1,r);
    }
    return rt;
}
int update(int ji,int jv,int l,int r,int i)//单点修改
{
    int rt=++cnt;
    a[rt].l=a[i].l;
    a[rt].r=a[i].r;
    if(l==r) a[rt].val=jv;
    else {
        int mid=(l+r)>>1;
        if(ji<=mid)a[rt].l=update(ji,jv,l,mid,a[rt].l);
        else a[rt].r=update(ji,jv,mid+1,r,a[rt].r);
    }
    return rt;
}
int query(int ji,int l,int r,int i){
    if(l==r) return a[i].val;
    int mid=(l+r)>>1;
    if(ji<=mid) return query(ji,l,mid,a[i].l);
    else return query(ji,mid+1,r,a[i].r);
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    root[0]=build(1,n);
    for(int i=1,version,op,x,v;i<=m;i++){
        cin>>version>>op>>x;
        if(op==1){
            cin>>v;
            root[i]=update(x,v,1,n,root[version]);
        }else {
            root[i]=root[version];
            cout<<query(x,1,n,root[i])<<endl;
        }
    }
}

```
```cpp
//这个更加重要
 #include <iostream>
  #include <cstdio>
  #include <cstring>
  #include <algorithm>
  using namespace std;
  const int maxn=200001;
  struct Node{
      int ls,rs;
      int cnt;
 }tr[maxn*20];
 int cur,rt[maxn];
 void init(){
     cur=0;
 }
 inline void push_up(int o){
     tr[o].cnt=tr[tr[o].ls].cnt+tr[tr[o].rs].cnt;
 }
 int build(int l,int r){
     int k=cur++;
     if (l==r) {
         tr[k].cnt=0;
         return k;
     }
     int mid=(l+r)>>1;
     tr[k].ls=build(l,mid);
     tr[k].rs=build(mid+1,r);
     push_up(k);
     return k;
 }
 int update(int o,int l,int r,int pos,int val){
     int k=cur++;
     tr[k]=tr[o];
     if (l==pos&&r==pos){
        tr[k].cnt+=val;
         return k;
     }
     int mid=(l+r)>>1;
     if (pos<=mid) tr[k].ls=update(tr[o].ls,l,mid,pos,val);
     else tr[k].rs=update(tr[o].rs,mid+1,r,pos,val);
     push_up(k);
     return k;
 }
 int query(int l,int r,int o,int v,int kth){
     if (l==r) return l;
     int mid=(l+r)>>1;
    int res=tr[tr[v].ls].cnt-tr[tr[o].ls].cnt;
     if (kth<=res) return query(l,mid,tr[o].ls,tr[v].ls,kth);
     else return query(mid+1,r,tr[o].rs,tr[v].rs,kth-res);
 }
 int b[maxn];
 int sortb[maxn];
 int main()
 {
     int n,m;
    // int T;
     //scanf("%d",&T);
     //while (T--){
     while (~scanf("%d%d",&n,&m)){
         init();
         for (int i=1;i<=n;i++){
             scanf("%d",&b[i]);
             sortb[i]=b[i];
         }
         sort(sortb+1,sortb+1+n);
         int cnt=1;
         for (int i=2;i<=n;i++){
             if (sortb[i]!=sortb[cnt]){
                 sortb[++cnt]=sortb[i];
             }
         }
         rt[0]=build(1,cnt);
         for (int i=1;i<=n;i++){
             int p=lower_bound(sortb+1,sortb+cnt+1,b[i])-sortb;
             rt[i]=update(rt[i-1],1,cnt,p,1);
         }
         for (int i=0;i<m;i++){
             int a,b,k;
             scanf("%d%d%d",&a,&b,&k);
             int idx=query(1,cnt,rt[a-1],rt[b],k);
             printf("%d\n",sortb[idx]);
         }
     }
     return 0;
 }
```

### 树状数组
```cpp
//单点修改
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
int b[500010];
int lowbit(int x){
 return x&(-x);
}
int count(int p){//求前p个元素的和
int sum=0;
while(p){
    sum+=b[p];
    p-=lowbit(p);
 }
return sum;
}
void add(int p,int x,int n){//对某一个元素进行修改
    while(p<=n){
    b[p]+=x;
    p+=lowbit(p);
 }
}
void solve() {
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    int tmp;
    cin>>tmp;
    add(i,tmp,n);
 }
 while(m--){
    int choice;
    cin>>choice;
    if(choice==1){
    int x,k;
    cin>>x>>k;
    add(x,k,n);
 }
 else{
    int x,y;
    cin>>x>>y;
    cout<<count(y)-count(x-1)<<endl;
 }
 }
}
signed main() { 
  ios::sync_with_stdio(0); 
  cin.tie(0), cout.tie(0); 
 // int T; 
 // std:: cin >> T; 
 // while(T -- ) 
 solve(); 
 return 0;
}

```
```cpp
//区间修改
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
int b[500010];
int lowbit(int x){
    return x&(-x);
}
int count(int p){
   int sum=0;
   while(p){
   sum+=b[p];
   p-=lowbit(p);
   }
   return sum;
}
void add(int p,int x,int n){
   while(p<=n){
   b[p]+=x;
   p+=lowbit(p);
   }
}
void solve() {
   int n,m,prev=0;
   cin>>n>>m;
   for(int i=1;i<=n;i++){
    int tmp;
   cin>>tmp;
   add(i,tmp-prev,n); // 差分建树
   prev=tmp;
    }
   while(m--){
    int choice;
  cin>>choice;
    if(choice==1){
   int x,y,k;
   cin>>x>>y>>k;
   add(x,k,n);
   add(y+1,-k,n); // 差分
 }
   else{
   int x;
   cin>>x;
   cout<<count(x)<<endl;
   }
 }
}
signed main() { 
 ios::sync_with_stdio(0); 
 cin.tie(0), cout.tie(0); 
 solve(); 
 return 0;
}
```

### 开点线段树

```cpp
//适用于范围很大，但是操作较少
//用于减小空间复杂度
//如果操作过多，则与没有优化相同，因此可能被卡
//在线段树的合并与分裂中不可替代，树链剖分
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=100001;
ll le[maxn],ri[maxn],sum[maxn],add[maxn],cnt;
void up(ll i, ll l, ll r){
    sum[i]=sum[l]+sum[r];
}
void lazy(ll i,ll v, ll n){
    sum[i]+=v*n;
    add[i]+=v;
}
void down(ll i, ll ln, ll rn){
    if(add[i]!=0){
     if(le[i]==0){
        le[i]=++cnt;
     }
    if(ri[i]==0){
        ri[i]=++cnt;
    }
    lazy(le[i],add[i],ln);
    lazy(ri[i],add[i],rn);
    add[i]=0;
    }
}
void Add(ll jl,ll jr,ll v,ll l,ll r,ll i){
     if(jl<=l&&r<=jr){
        lazy(i,v,r-l+1);
       return;
     }
     
    ll mid=(l+r)>>1;
     down(i,mid-l+1,r-mid);
     if(jl<=mid){
        if(le[i]==0){
            le[i]=++cnt;
        }
        Add(jl,jr,v,l,mid,le[i]);
     }
     if(jr>mid){
        if(ri[i]==0){
            ri[i]=++cnt;
        }
        Add(jl,jr,v,mid+1,r,ri[i]);
     }
    
    up(i,le[i],ri[i]);
}
ll query(ll jl,ll jr,ll l, ll r,ll i){
    if(jl<=l&&r<=jr){
        return sum[i];
    }
    ll mid=(l+r)>>1;
    down(i,mid-l+1,r-mid);
    ll ans=0;
    if(jl<=mid){
        if(le[i]!=0){
            ans+=query(jl,jr,l,mid,le[i]);
        }
    }
    if(jr>mid){
        if(ri[i]!=0){
            ans+=query(jl,jr,mid+1,r,ri[i]);
        }
    }
    return ans;
}
int main(){
    int n,m;
    cin>>n>>m;
    cnt=1;
    while(m--){
        int opt;
        cin>>opt;
        if(opt==1){
            int l,r,v;
            cin>>l>>r>>v;
            Add(l,r,v,1,n,1);
        }
    else {
        int l,r;
        cin>>l>>r;
        cout<<query(l,r,1,n,1)<<endl;
    }
}
}
```

### 权值线段树

```cpp
权值线段树模板
#define lson pos<<1
#define rson pos<<1|1
void build(int pos,int l,int r)
{
	int mid=(l+r)>>1;
	if(l==r)
	{
		tree[pos]=a[l];//a[l]表示数l有多少个
		return;
	}
	build(lson,l,mid);
	build(rson,mid+1,r);
	tree[pos]=tree[lson]+tree[rson];
}
void update(int pos,int l,int r,int k,int cnt)//表示数k的个数多cnt个
{
	int mid=(l+r)>>1;
	if(l==r)
	{
		tree[pos]+=cnt;
		return;
	}
	if(k<=mid)
		update(lson,l,mid,k,cnt);
	else	
		update(rson,mid+1,r,k,cnt);
	tree[pos]=tree[lson]+tree[rson];
}
int query(int pos,int l,int r,int k)//查询数k有多少个
{
	int mid=(l+r)>>1;
	if(l==r)
		return tree[pos];
	if(k<=mid)
		return query(lson,l,mid,k);
	else
		return query(rson,mid+1,r,k);
}
int kth(int pos,int l,int r,int k)//查询第k大值是多少
{
	int mid=(l+r)>>1;
	if(l==r)
		return l;
	if(k<mid)
		return kth(rson,mid+1,r,k);
	else
		return kth(lson,l,mid,k-mid);
}
```

### 线段树上最值操作
```cpp
//基本的实现
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000001;
const int minest=-1000001;
long long arr[maxn<<2],sum[maxn<<2],mx[maxn<<2],sem[maxn<<2],cnt[maxn<<2];
void up(int i){
    int l=i<<1;
    int r=i<<1|1;
    sum[i]=sum[l]+sum[r];
    mx[i]=max(mx[l],mx[r]);
    if(mx[l]>mx[r]){
        cnt[i]=cnt[l];
        sem[i]=max(sem[l],mx[r]);
    }else if(mx[r]>mx[l]){
        cnt[i]=cnt[r];
        sem[i]=max(sem[r],mx[l]);
    }else {
        sem[i]=max(sem[l],sem[r]);
        cnt[i]=cnt[l]+cnt[r];
    }
}
void Lazy(int i,int v){
    if(v<mx[i]){
        sum[i]-=(mx[i]-v)*cnt[i];
        mx[i]=v;
    }
}
void down(int i){
    Lazy(i<<1,mx[i]);
    Lazy(i<<1|1,mx[i]);
}
void setmin(int jl,int jr,int v,int l,int r,int i){
    if(v>mx[i]) return;
    if(jl<=l&&r<=jr&&v>sem[i]){
        Lazy(i,v);
        return;
    }else {
        down(i);
        int mid=(l+r)>>1;
        if(jl<=mid) setmin(jl,jr,v,l,mid,i<<1);
        if(jr>mid) setmin(jl,jr,v,mid+1,r,i<<1|1);
    }
    up(i);
}
long long querymax(int jl,int jr,int l,int r,int i){
    if(jl<=l&&r<=jr){
        return mx[i];
    }
    down(i);
    int mid=(l+r)>>1;
    long long lm=minest,rm=minest;
    if(jl<=mid) lm=querymax(jl,jr,l,mid,i<<1);
    if(jr>mid)  rm=querymax(jl,jr,mid+1,r,i<<1|1);
    return max(lm,rm);
}
long long querysum(int jl,int jr,int l,int r,int i){
    if(jl<=l&&r<=jr){
        return sum[i];
    }
    down(i);
    int mid=(l+r)>>1;
    long long ans=0;
    if(jl<=mid) ans+=querysum(jl,jr,l,mid,i<<1);
    if(jr>mid)  ans+=querysum(jl,jr,mid+1,r,i<<1|1);
    return ans;
}
void build(int l,int r,int i){
    if(l==r){
        sum[i]=arr[l];
        mx[i]=arr[l];
        sem[i]=minest;
        cnt[i]=1;
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,i<<1),build(mid+1,r,i<<1|1);
    up(i);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            cin>>arr[i];
        }
        build(1,n,1);
        while(m--){
            int opt;
            cin>>opt;
            if(opt==0){
                int l,r;
                long long mi;
                cin>>l>>r>>mi;
                setmin(l,r,mi,1,n,1);
            }else if(opt==1){
                int l,r;
                cin>>l>>r;
                cout<<querymax(l,r,1,n,1)<<endl;
            }else {
                int l,r;
                cin>>l>>r;
                cout<<querysum(l,r,1,n,1)<<endl;
            }
        }
    }
}
```
``` cpp
//如果在上一题的基础上补充范围增加，则代码如下
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000001;
const int minest=-1000001;
long long arr[maxn<<2],sum[maxn<<2],mx[maxn<<2],sem[maxn<<2],cnt[maxn<<2],maxadd[maxn<<2],otheradd[maxn<<2];
void up(int i){
    int l=i<<1;
    int r=i<<1|1;
    sum[i]=sum[l]+sum[r];
    mx[i]=max(mx[l],mx[r]);
    if(mx[l]>mx[r]){
        cnt[i]=cnt[l];
        sem[i]=max(sem[l],mx[r]);
    }else if(mx[r]>mx[l]){
        cnt[i]=cnt[r];
        sem[i]=max(sem[r],mx[l]);
    }else {
        sem[i]=max(sem[l],sem[r]);
        cnt[i]=cnt[l]+cnt[r];
    }
}
void Lazy(int i,int n,long long maxaddv,long long otheraddv){
    sum[i]+=maxaddv*cnt[i]+otheraddv*(n-cnt[i]);
    mx[i]+=maxaddv;
    sem[i]+=sem[i]==minest?0:otheraddv;
    maxadd[i]+=maxaddv;
    otheradd[i]+=otheraddv;
}
void down(int i,int ln,int rn){
    int l=i<<1;
    int r=i<<1|1;
    int temp=max(mx[l],mx[r]);
    if(mx[l]==temp){
        Lazy(l,ln,maxadd[i],otheradd[i]);
    }else Lazy(l,ln,otheradd[i],otheradd[i]);
    if(mx[r]==temp) Lazy(r,rn,maxadd[i],otheradd[i]);
    else Lazy(r,rn,otheradd[i],otheradd[i]);
    maxadd[i]=0;
    otheradd[i]=0;
}
void setmin(int jl,int jr,int v,int l,int r,int i){
    if(v>mx[i]) return;
    if(jl<=l&&r<=jr&&v>sem[i]){
        Lazy(i,r-l+1,v-mx[i],0);
        return;
    }else {
        
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        if(jl<=mid) setmin(jl,jr,v,l,mid,i<<1);
        if(jr>mid) setmin(jl,jr,v,mid+1,r,i<<1|1);
    }
    up(i);
}
void add(int jl,int jr,int v,int l,int r,int i){
    if(jl<=l&&r<=jr){
        Lazy(i,r-l+1,v,v);
    }else {
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        if(jl<=mid) add(jl,jr,v,l,mid,i<<1);
        if(jr>mid) add(jl,jr,v,mid+1,r,i<<1|1);
        up(i);
    }
}
long long querymax(int jl,int jr,int l,int r,int i){
    if(jl<=l&&r<=jr){
        return mx[i];
    }
    
    int mid=(l+r)>>1;
    down(i,mid-l+1,r-mid);
    long long lm=minest,rm=minest;
    if(jl<=mid) lm=querymax(jl,jr,l,mid,i<<1);
    if(jr>mid)  rm=querymax(jl,jr,mid+1,r,i<<1|1);
    return max(lm,rm);
}
long long querysum(int jl,int jr,int l,int r,int i){
    if(jl<=l&&r<=jr){
        return sum[i];
    }
 
    int mid=(l+r)>>1;
    down(i,mid-l+1,r-mid);
    long long ans=0;
    if(jl<=mid) ans+=querysum(jl,jr,l,mid,i<<1);
    if(jr>mid)  ans+=querysum(jl,jr,mid+1,r,i<<1|1);
    return ans;
}
void build(int l,int r,int i){
    if(l==r){
        sum[i]=arr[l];
        mx[i]=arr[l];
        sem[i]=minest;
        cnt[i]=1;
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,i<<1),build(mid+1,r,i<<1|1);
    up(i);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            cin>>arr[i];
        }
        build(1,n,1);
        while(m--){
            int opt;
            cin>>opt;
            if(opt==0){
                int l,r;
                long long mi;
                cin>>l>>r>>mi;
                setmin(l,r,mi,1,n,1);
            }else if(opt==1){
                int l,r;
                cin>>l>>r;
                cout<<querymax(l,r,1,n,1)<<endl;
            }else {
                int l,r;
                cin>>l>>r;
                cout<<querysum(l,r,1,n,1)<<endl;
            }
        }
    }
}
```
```cpp
//于此基础上如果还要增加一个查询历史最大值的操作
#include<bits/stdc++.h>
using namespace std;
const int maxn=500010;
const long long minest=-1e18;
long long arr[maxn<<2],sum[maxn<<2],mx[maxn<<2],sem[maxn<<2],cnt[maxn<<2],maxadd[maxn<<2],otheradd[maxn<<2];
long long maxhistory[maxn<<2],maxaddtop[maxn<<2],otheraddtop[maxn<<2];
void up(int i){
    int l=i<<1;
    int r=i<<1|1;
    sum[i]=sum[l]+sum[r];
    maxhistory[i]=max(maxhistory[l],maxhistory[r]);
    mx[i]=max(mx[l],mx[r]);
    if(mx[l]>mx[r]){
        cnt[i]=cnt[l];
        sem[i]=max(sem[l],mx[r]);
    }else if(mx[r]>mx[l]){
        cnt[i]=cnt[r];
        sem[i]=max(sem[r],mx[l]);
    }else {
        sem[i]=max(sem[l],sem[r]);
        cnt[i]=cnt[l]+cnt[r];
    }
}
//maxaddvtop:最大值到过的最大提升幅度
//otheraddvtop：其他值到过的最大提升幅度
void Lazy(int i,int n,long long maxaddv,long long otheraddv,long long maxaddvtop,long long otheraddvtop){
    maxhistory[i]=max(maxhistory[i],mx[i]+maxaddvtop);
    maxaddtop[i]=max(maxaddtop[i],maxadd[i]+maxaddvtop);
    otheraddtop[i]=max(otheraddtop[i],otheradd[i]+otheraddvtop);
    sum[i]+=maxaddv*cnt[i]+otheraddv*(n-cnt[i]);
    mx[i]+=maxaddv;
    sem[i]+=sem[i]==minest?0:otheraddv;
    maxadd[i]+=maxaddv;
    otheradd[i]+=otheraddv;
    
}
void down(int i,int ln,int rn){
    int l=i<<1;
    int r=i<<1|1;
    int temp=max(mx[l],mx[r]);
    if(mx[l]==temp){
        Lazy(l,ln,maxadd[i],otheradd[i],maxaddtop[i],otheraddtop[i]);
    }else Lazy(l,ln,otheradd[i],otheradd[i],otheraddtop[i],otheraddtop[i]);
    if(mx[r]==temp) Lazy(r,rn,maxadd[i],otheradd[i],maxaddtop[i],otheraddtop[i]);
    else Lazy(r,rn,otheradd[i],otheradd[i],otheraddtop[i],otheraddtop[i]);
    maxadd[i]=0;
    otheradd[i]=0;
    maxaddtop[i]=0;
    otheraddtop[i]=0;
}
void setmin(int jl,int jr,long long v,int l,int r,int i){
    if(v>mx[i]) return;
    if(jl<=l&&r<=jr&&v>sem[i]){
        Lazy(i,r-l+1,v-mx[i],0,v-mx[i],0);
        return;
    }else {
        
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        if(jl<=mid) setmin(jl,jr,v,l,mid,i<<1);
        if(jr>mid) setmin(jl,jr,v,mid+1,r,i<<1|1);
    }
    up(i);
}
void add(int jl,int jr,long long v,int l,int r,int i){
    if(jl<=l&&r<=jr){
        Lazy(i,r-l+1,v,v,v,v);
    }else {
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        if(jl<=mid) add(jl,jr,v,l,mid,i<<1);
        if(jr>mid) add(jl,jr,v,mid+1,r,i<<1|1);
        up(i);
    }
}
long long querymax(int jl,int jr,int l,int r,int i){
    if(jl<=l&&r<=jr){
        return mx[i];
    }
    
    int mid=(l+r)>>1;
    down(i,mid-l+1,r-mid);
    long long lm=minest,rm=minest;
    if(jl<=mid) lm=querymax(jl,jr,l,mid,i<<1);
    if(jr>mid)  rm=querymax(jl,jr,mid+1,r,i<<1|1);
    return max(lm,rm);
}
long long queryhistorymax(int jl,int jr,int l,int r,int i){
    if(jl<=l&&r<=jr){
        return maxhistory[i];
    }
    
    int mid=(l+r)>>1;
    down(i,mid-l+1,r-mid);
    long long lm=minest,rm=minest;
    if(jl<=mid) lm=queryhistorymax(jl,jr,l,mid,i<<1);
    if(jr>mid)  rm=queryhistorymax(jl,jr,mid+1,r,i<<1|1);
    return max(lm,rm);
}
long long querysum(int jl,int jr,int l,int r,int i){
    if(jl<=l&&r<=jr){
        return sum[i];
    }
 
    int mid=(l+r)>>1;
    down(i,mid-l+1,r-mid);
    long long ans=0;
    if(jl<=mid) ans+=querysum(jl,jr,l,mid,i<<1);
    if(jr>mid)  ans+=querysum(jl,jr,mid+1,r,i<<1|1);
    return ans;
}
void build(int l,int r,int i){
    maxadd[i]=0;
    otheradd[i]=0;
    maxaddtop[i]=0;
    otheraddtop[i]=0;
    if(l==r){
        sum[i]=arr[l];
        mx[i]=arr[l];
        sem[i]=minest;
        cnt[i]=1;
        maxhistory[i]=arr[l];
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,i<<1),build(mid+1,r,i<<1|1);
    up(i);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    //cin>>t;
    //while(t--){
        int n,m;
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            cin>>arr[i];
        }
        build(1,n,1);
        while(m--){
            int opt;
            cin>>opt;
            if(opt==1){
                int l,r;
                long long v;
                cin>>l>>r>>v;
                add(l,r,v,1,n,1);
            }else if(opt==2){
                long long l,r,v;
                cin>>l>>r>>v;
                setmin(l,r,v,1,n,1);
            }else if (opt==3){
                int l,r;
                cin>>l>>r;
                cout<<querysum(l,r,1,n,1)<<endl;
            }else if(opt==4){
                int l,r;
                cin>>l>>r;
                cout<<querymax(l,r,1,n,1)<<endl;
            }else {
                int l,r;
                cin>>l>>r;
                cout<<queryhistorymax(l,r,1,n,1)<<endl;
            }
        }
    //}
}
```
```cpp
//区间最值操作经典题 hdu 5306
#include<bits/stdc++.h>
using namespace std;
const int maxn=500010;
const long long minest=-1e18;
long long arr[maxn<<2],sum[maxn<<2],mx[maxn<<2],sem[maxn<<2],cnt[maxn<<2],maxadd[maxn<<2],otheradd[maxn<<2];
long long maxhistory[maxn<<2],maxaddtop[maxn<<2],otheraddtop[maxn<<2];
void up(int i){
    int l=i<<1;
    int r=i<<1|1;
    sum[i]=sum[l]+sum[r];
    maxhistory[i]=max(maxhistory[l],maxhistory[r]);
    mx[i]=max(mx[l],mx[r]);
    if(mx[l]>mx[r]){
        cnt[i]=cnt[l];
        sem[i]=max(sem[l],mx[r]);
    }else if(mx[r]>mx[l]){
        cnt[i]=cnt[r];
        sem[i]=max(sem[r],mx[l]);
    }else {
        sem[i]=max(sem[l],sem[r]);
        cnt[i]=cnt[l]+cnt[r];
    }
}
//maxaddvtop:最大值到过的最大提升幅度
//otheraddvtop：其他值到过的最大提升幅度
void Lazy(int i,int n,long long maxaddv,long long otheraddv,long long maxaddvtop,long long otheraddvtop){
    maxhistory[i]=max(maxhistory[i],mx[i]+maxaddvtop);
    maxaddtop[i]=max(maxaddtop[i],maxadd[i]+maxaddvtop);
    otheraddtop[i]=max(otheraddtop[i],otheradd[i]+otheraddvtop);
    sum[i]+=maxaddv*cnt[i]+otheraddv*(n-cnt[i]);
    mx[i]+=maxaddv;
    sem[i]+=sem[i]==minest?0:otheraddv;
    maxadd[i]+=maxaddv;
    otheradd[i]+=otheraddv;
    
}
void down(int i,int ln,int rn){
    int l=i<<1;
    int r=i<<1|1;
    int temp=max(mx[l],mx[r]);
    if(mx[l]==temp){
        Lazy(l,ln,maxadd[i],otheradd[i],maxaddtop[i],otheraddtop[i]);
    }else Lazy(l,ln,otheradd[i],otheradd[i],otheraddtop[i],otheraddtop[i]);
    if(mx[r]==temp) Lazy(r,rn,maxadd[i],otheradd[i],maxaddtop[i],otheraddtop[i]);
    else Lazy(r,rn,otheradd[i],otheradd[i],otheraddtop[i],otheraddtop[i]);
    maxadd[i]=0;
    otheradd[i]=0;
    maxaddtop[i]=0;
    otheraddtop[i]=0;
}
void setmin(int jl,int jr,long long v,int l,int r,int i){
    if(v>mx[i]) return;
    if(jl<=l&&r<=jr&&v>sem[i]){
        Lazy(i,r-l+1,v-mx[i],0,v-mx[i],0);
        return;
    }else {
        
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        if(jl<=mid) setmin(jl,jr,v,l,mid,i<<1);
        if(jr>mid) setmin(jl,jr,v,mid+1,r,i<<1|1);
    }
    up(i);
}
void add(int jl,int jr,long long v,int l,int r,int i){
    if(jl<=l&&r<=jr){
        Lazy(i,r-l+1,v,v,v,v);
    }else {
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        if(jl<=mid) add(jl,jr,v,l,mid,i<<1);
        if(jr>mid) add(jl,jr,v,mid+1,r,i<<1|1);
    }
    up(i);
}
long long querymax(int jl,int jr,int l,int r,int i){
    if(jl<=l&&r<=jr){
        return mx[i];
    }
    
    int mid=(l+r)>>1;
    down(i,mid-l+1,r-mid);
    long long lm=minest,rm=minest;
    if(jl<=mid) lm=querymax(jl,jr,l,mid,i<<1);
    if(jr>mid)  rm=querymax(jl,jr,mid+1,r,i<<1|1);
    return max(lm,rm);
}
long long queryhistorymax(int jl,int jr,int l,int r,int i){
    if(jl<=l&&r<=jr){
        return maxhistory[i];
    }
    
    int mid=(l+r)>>1;
    down(i,mid-l+1,r-mid);
    long long lm=minest,rm=minest;
    if(jl<=mid) lm=queryhistorymax(jl,jr,l,mid,i<<1);
    if(jr>mid)  rm=queryhistorymax(jl,jr,mid+1,r,i<<1|1);
    return max(lm,rm);
}
long long querysum(int jl,int jr,int l,int r,int i){
    if(jl<=l&&r<=jr){
        return sum[i];
    }
 
    int mid=(l+r)>>1;
    down(i,mid-l+1,r-mid);
    long long ans=0;
    if(jl<=mid) ans+=querysum(jl,jr,l,mid,i<<1);
    if(jr>mid)  ans+=querysum(jl,jr,mid+1,r,i<<1|1);
    return ans;
}
void build(int l,int r,int i){
    maxadd[i]=0;
    otheradd[i]=0;
    maxaddtop[i]=0;
    otheraddtop[i]=0;
    if(l==r){
        sum[i]=arr[l];
        mx[i]=arr[l];
        sem[i]=minest;
        cnt[i]=1;
        maxhistory[i]=arr[l];
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,i<<1),build(mid+1,r,i<<1|1);
    up(i);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    build(1,n,1);
    while(m--){
        int opt;
        cin>>opt;
        if(opt==1){
            int l,r;
            long long v;
            cin>>l>>r>>v;
            add(l,r,v,1,n,1);
        }else if(opt==2){
            long long l,r,v;
            cin>>l>>r>>v;
            setmin(l,r,v,1,n,1);
        }else if (opt==3){
            int l,r;
            cin>>l>>r;
            cout<<querysum(l,r,1,n,1)<<endl;
        }else if(opt==4){
            int l,r;
            cin>>l>>r;
            cout<<querymax(l,r,1,n,1)<<endl;
        }else {
            int l,r;
            cin>>l>>r;
            cout<<queryhistorymax(l,r,1,n,1)<<endl;
        }
    }
}
```

### 线段树上序列操作

```cpp
//线段树上的序列操作，稍难一点
//求连续1的最长子列，有点难度，容易打错

#include<bits/stdc++.h>
using namespace std;
const int maxn=100001;
int arr[maxn],sum[maxn<<2],pre0[maxn<<2],len0[maxn<<2],suf0[maxn<<2],pre1[maxn<<2],len1[maxn<<2],suf1[maxn<<2];
int lazy[maxn<<2];
bool update[maxn<<2];
bool rever[maxn<<2];
void up(int i,int ln,int rn){
    int l=i<<1;
    int r=i<<1|1;
    sum[i]=sum[l]+sum[r];
    len0[i]=max(max(len0[l],len0[r]),suf0[l]+pre0[r]);
    pre0[i]=len0[l]<ln?pre0[l]:pre0[l]+pre0[r];
    suf0[i]=len0[r]<rn?suf0[r]:suf0[l]+suf0[r];
    len1[i]=max(max(len1[l],len1[r]),suf1[l]+pre1[r]);
    pre1[i]=len1[l]<ln?pre1[l]:pre1[l]+pre1[r];
    suf1[i]=len1[r]<rn?suf1[r]:suf1[l]+suf1[r];
}
void updateLazy(int i,int v,int n){
    sum[i]=v*n;
    pre0[i]=suf0[i]=len0[i]=v==0?n:0;
    pre1[i]=suf1[i]=len1[i]=v==1?n:0;
    lazy[i]=v;
    update[i]=true;
    rever[i]=false;
}
void reverseLazy(int i,int n){
    sum[i]=n-sum[i];
    swap(pre0[i],pre1[i]);
    swap(len0[i],len1[i]);
    swap(suf0[i],suf1[i]);
    rever[i]=!rever[i];
}
void down(int i,int ln,int rn){
    if(update[i]){
        updateLazy(i<<1,lazy[i],ln);
        updateLazy(i<<1|1,lazy[i],rn);
        update[i]=false;
    }
    if(rever[i]){
        reverseLazy(i<<1,ln);
        reverseLazy(i<<1|1,rn);
        rever[i]=false;
    }
}
void build(int l,int r,int i){
    if(l==r){
        sum[i]=arr[l];
        pre0[i]=arr[l]?0:1;
        suf0[i]=arr[l]?0:1;
        len0[i]=arr[l]?0:1;
        pre1[i]=arr[l]?1:0;
        suf1[i]=arr[l]?1:0;
        len1[i]=arr[l]?1:0;
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,i<<1),build(mid+1,r,i<<1|1);
    up(i,mid-l+1,r-mid);
    rever[i]=0;
    update[i]=0;
}
void Update(int jl,int jr,int v,int l,int r,int i){
    if(jl<=l&&r<=jr){
        updateLazy(i,v,r-l+1);
    }else {
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        if(jl<=mid) Update(jl,jr,v,l,mid,i<<1);
        if(jr>mid) Update(jl,jr,v,mid+1,r,i<<1|1);
        up(i,mid-l+1,r-mid);
    }
}
void Reverse(int jl,int jr,int l,int r,int i){
    if(jl<=l&&r<=jr){
        reverseLazy(i,r-l+1);
    }else {
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        if(jl<=mid) Reverse(jl,jr,l,mid,i<<1);
        if(jr>mid) Reverse(jl,jr,mid+1,r,i<<1|1);
        up(i,mid-l+1,r-mid);
    }
}
tuple<int,int,int> querylength(int jl,int jr,int l,int r,int i){
    if(jl<=l&&r<=jr){
        return make_tuple(len1[i],pre1[i],suf1[i]);
    }
    int mid=(l+r)>>1;
    down(i,mid-l+1,r-mid);
    if(jr<=mid) return querylength(jl,jr,l,mid,i<<1);
    if(jl>mid) return querylength(jl,jr,mid+1,r,i<<1|1);
    tuple<int,int,int> l1=querylength(jl,jr,l,mid,i<<1);
    tuple<int,int,int> r1=querylength(jl,jr,mid+1,r,i<<1|1);
    int llen=get<0>(l1),lpre=get<1>(l1),lsuf=get<2>(l1);
    int rlen=get<0>(r1),rpre=get<1>(r1),rsuf=get<2>(r1);
    int len=max(max(llen,rlen),lsuf+rpre);
    int pre=lpre<mid-max(l,jl)+1?lpre:lpre+rpre;
    int suf=rsuf<min(r,jr)-mid?rsuf:rsuf+lsuf;
    return make_tuple(len,pre,suf);
}
int query(int jl,int jr,int l,int r,int i){
    if(jl<=l&&r<=jr){
        return sum[i];
    }
    int mid=(l+r)>>1;
    down(i,mid-l+1,r-mid);
    int ans=0;
    if(jl<=mid) ans+=query(jl,jr,l,mid,i<<1); 
    if(jr>mid)  ans+=query(jl,jr,mid+1,r,i<<1|1);
    return ans;
}
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>arr[i];
    build(1,n,1);
    while(m--){
        int opt,l,r;
        cin>>opt>>l>>r;
        l+=1;
        r+=1;
        if(opt==0){
            Update(l,r,0,1,n,1);
        }else if(opt==1){
            Update(l,r,1,1,n,1);
        }else if(opt==2){
            Reverse(l,r,1,n,1);
        }else if(opt==3){
            cout<<query(l,r,1,n,1)<<endl;
        }else {
            tuple<int,int,int>a=querylength(l,r,1,n,1);
            cout<<get<0>(a)<<endl;
        }
    }
}
```

### 非经典线段树

```cpp
// 这类题目一般是可以看出来使用线段树，但是不能满足一般的懒更新的条件
//简单的一般需要进行势能分析，再减枝就可以解决
//例如 洛谷 P4145，此题是开根号，换为取模同理
//P1471 求方差
#include<bits/stdc++.h>
using namespace std;

const int maxn=100001;
double a[maxn],sum[maxn<<2],pf[maxn<<2],lazy[maxn<<2];
void up(int i){
    sum[i]=sum[i<<1]+sum[i<<1|1];
    pf[i]=pf[i<<1]+pf[i<<1|1];
}

void Lazy(int i,double v,int n){
    lazy[i]+=v;
    pf[i]+=2*v*sum[i]+v*v*n;
    sum[i]+=v*n;
}
void down(int i,int ln,int rn){
    if(lazy[i]!=0){
        Lazy(i<<1,lazy[i],ln);
        Lazy(i<<1|1,lazy[i],rn);
        lazy[i]=0;
    }
}
void add(int jl,int jr,double v,int l,int r,int i){
    if(jl<=l&&jr>=r){
        Lazy(i,v,r-l+1);
        return;
    }
    int mid=(l+r)>>1;
    down(i,mid-l+1,r-mid);
    if(jl<=mid){
        add(jl,jr,v,l,mid,i<<1);
    }
    if(jr>mid) add(jl,jr,v,mid+1,r,i<<1|1);
    up(i);
}
double query(int jl,int jr,int jt,int l,int r,int i){
    if(jl<=l&&jr>=r){
        if(jt){
            return pf[i];
        }else return sum[i];
    }
    int mid=(l+r)>>1;
    down(i,mid-l+1,r-mid);
    double ans=0;
    if(jl<=mid) ans+=query(jl,jr,jt,l,mid,i<<1);
    if(jr>mid) ans+=query(jl,jr,jt,mid+1,r,i<<1|1);
    return ans;
}
void build(int l,int r,int i){
    if(l==r){
        sum[i]=a[l];
        pf[i]=a[l]*a[l];
        
    }
    else {
    int mid=(l+r)>>1;
    build(l,mid,i<<1);
    build(mid+1,r,i<<1|1);
    up(i);
    }
    lazy[i]=0;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1,n,1);
    while(m--){
        int opt;
        cin>>opt;
        if(opt==1){
            int l,r;
            double v;
            cin>>l>>r>>v;
            add(l,r,v,1,n,1);
        }else if(opt==2){
            int l,r;
            cin>>l>>r;
            printf("%.4lf\n",query(l,r,0,1,n,1)/(r-l+1));
        }else {
            int l,r;
            cin>>l>>r;
            printf("%.4lf\n",query(l,r,1,1,n,1)/(r-l+1)-query(l,r,0,1,n,1)/(r-l+1)*query(l,r,0,1,n,1)/(r-l+1));
        }
    }
}
```

### 左偏树

```cpp
//可并堆结构，两个堆的合并时间复杂度为log（n）
//查询操作需要并查集的优化
//P3377,模板,删除一个堆中最小值
#include<bits/stdc++.h>
using namespace std;
const int maxn=100001;
int n,m;
int num[maxn],lef[maxn],righ[maxn],dis[maxn];
int father[maxn];
//father并不是代表该节点的父亲节点，而是代表并查集所对应的路径信息
//需要保证，并查集最上方代表节点=左偏树的头，也就是堆顶
void prepare(){
    dis[0]=-1;
    for(int i=1;i<=n;i++){
        lef[i]=0;
        righ[i]=0;
        dis[i]=0;
        father[i]=i;
    }
}
int find(int i){
    father[i]=father[i]==i?i:find(father[i]);
    return father[i];
}
int merge(int i,int j){
    if(i==0||j==0) return i+j;
    //维护小根堆，如果值一样，编号小的节点做头,大根堆同理
    if(num[i]>num[j]||(num[i]==num[j]&&i>j)){
        swap(i,j);
    }
    righ[i]=merge(righ[i],j);
    if(dis[lef[i]]<dis[righ[i]]){
        swap(lef[i],righ[i]);
    }
    dis[i]=dis[righ[i]]+1;
    father[lef[i]]=father[righ[i]]=i;
    return i;
}
//节点i一定是左偏树的头，在左偏树上删除节点i，返回新树的头结点编号
int pop(int i){
    father[lef[i]]=lef[i];
    father[righ[i]]=righ[i];
    father[i]=merge(lef[i],righ[i]);//保证删除节点后，能够正确再次查询
    lef[i]=righ[i]=dis[i]=0;
    return father[i];
}
int main(){
    cin>>n>>m;
    prepare();
    for(int i=1;i<=n;i++) cin>>num[i];
    for(int i=1;i<=m;i++){
        int op;
        cin>>op;
        if(op==1){
            int l,r;
            cin>>l>>r;
            if(num[l]!=-1&&num[r]!=-1){
                l=find(l),r=find(r);
                if(l!=r) merge(l,r);
            }
        }else {
            int x;
            cin>>x;
            if(num[x]==-1) cout<<-1<<endl;
            else {
            int ans=find(x);
            cout<<num[ans]<<endl;
            pop(ans);
            num[ans]=-1;
        }
    }
    }
}

```
 ```cpp
 //进一步，删除任意一个节点
#include<bits/stdc++.h>
using namespace std;
#define  int  long long
const int maxn=2000100;
int n,m;
int num[maxn],father[maxn],lef[maxn],righ[maxn],dis[maxn],up[maxn];
// up数组存储的就是节点真正的父节点
void prepare(){
    dis[0]=-1;
    for(int i=1;i<=n;i++){
        dis[i]=lef[i]=righ[i]=up[i]=0;
        father[i]=i;
    }
}
int find(int i){
    father[i]=father[i]==i?i:find(father[i]);
    return father[i];
}
int merge(int i,int j){
    if(i==0||j==0){
        return i+j;
    }
    //这段代码是维护的大根堆
    if(num[i]<num[j]||(num[i]==num[j]&&i>j)){
        swap(i,j);
    }
    righ[i]=merge(righ[i],j);
    up[righ[i]]=i;//多了一句
    if(dis[lef[i]]<dis[righ[i]]){
        swap(lef[i],righ[i]);
    }
    dis[i]=dis[righ[i]]+1;
    father[lef[i]]=father[righ[i]]=i;
    return i;
}
//删除任意节点，返回整棵树的头节点
//这是主要的改动
int remove(int i){
    int h=find(i);
    father[lef[i]]=lef[i];
    father[righ[i]]=righ[i];
    int s=merge(lef[i],righ[i]);
    int f=up[i];
    father[i]=s;
    up[s]=f;
    if(h!=i){
        father[s]=h;
        if(lef[f]==i) lef[f]=s;
        else righ[f]=s;
        for(int d=dis[s];dis[f]>d+1;f=up[f],d++){// log(n)
            if(dis[lef[f]]<dis[righ[f]]){
                swap(lef[f],righ[f]);
            }
            dis[f]=d+1;
        }
    }
    up[i]=lef[i]=righ[i]=dis[i]=0;
    return father[s];
}
void reduce(int i,int v){//把i对应的减小v
    int h=remove(i);
    num[i]=max((long long)0,num[i]-v);
    father[h]=father[i]=merge(h,i);
}
void solve(){
    int n,m;
    cin>>n>>m;
    prepare();
    for(int i=1;i<=n;i++){
        cin>>num[i];
    }
    for(int i=1;i<=m;i++){
        int op;
        cin>>op;
        if(op==2){
            int x;
            cin>>x;
            reduce(x,num[x]);
        }else if(op==3){
            int x,y;
            cin>>x>>y;
            reduce(find(x),y);
        }else {
            int x,y;
            cin>>x>>y;
            x=find(x),y=find(y);
            if(x!=y) merge(x,y);
        }
    }
}
 ```
---

## 图论算法

### 最小生成树
有两种算法，一般使用kruskal
```cpp
//prim算法求最小生成树的大小
#include<bits/stdc++.h>
using namespace std;
#define re register
#define il inline
il int read()
{
    re int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*f;
}//快读，不理解的用cin代替即可
#define inf 123456789
#define maxn 5005
#define maxm 200005
struct edge
{
	int v,w,next;
}e[maxm<<1];
//注意是无向图，开两倍数组
int head[maxn],dis[maxn],cnt,n,m,tot,now=1,ans;
//已经加入最小生成树的的点到没有加入的点的最短距离，比如说1和2号节点已经加入了最小生成树，那么dis[3]就等于min(1->3,2->3)
bool vis[maxn];
//链式前向星加边
il void add(int u,int v,int w)
{
	e[++cnt].v=v;
	e[cnt].w=w;
	e[cnt].next=head[u];
	head[u]=cnt;
}
//读入数据
il void init()
{
    n=read(),m=read();
    for(re int i=1,u,v,w;i<=m;++i)
    {
        u=read(),v=read(),w=read();
        add(u,v,w),add(v,u,w);
    }
}
il int prim()
{
	//先把dis数组附为极大值
	for(re int i=2;i<=n;++i)
	{
		dis[i]=inf;
	}
    //这里要注意重边，所以要用到min
	for(re int i=head[1];i;i=e[i].next)
	{
		dis[e[i].v]=min(dis[e[i].v],e[i].w);
	}
    while(++tot<n)//最小生成树边数等于点数-1
    {
        re int minn=inf;//把minn置为极大值
        vis[now]=1;//标记点已经走过
        //枚举每一个没有使用的点
        //找出最小值作为新边
        //注意这里不是枚举now点的所有连边，而是1~n
        for(re int i=1;i<=n;++i)
        {
            if(!vis[i]&&minn>dis[i])
            {
                minn=dis[i];
				now=i;
            }
        }
        ans+=minn;
        //枚举now的所有连边，更新dis数组
        for(re int i=head[now];i;i=e[i].next)
        {
        	re int v=e[i].v;
        	if(dis[v]>e[i].w&&!vis[v])
        	{
        		dis[v]=e[i].w;
        	}
		}
    }
    return ans;
}
int main()
{
    init();
    printf("%d",prim());
    return 0;
}

```
```cpp
//kruskal
#include<bits/stdc++.h>
using namespace std;
#define re register
#define il inline
il int read()
{
    re int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c>='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*f;
}
struct Edge
{
	int u,v,w;
}edge[200005];
int fa[5005],n,m,ans,eu,ev,cnt;
il bool cmp(Edge a,Edge b)
{
    return a.w<b.w;
}
//快排的依据（按边权排序）
il int find(int x)
{
    while(x!=fa[x]) x=fa[x]=fa[fa[x]];
    return x;
}
//并查集循环实现模板，及路径压缩，不懂并查集的同学可以戳一戳代码上方的"并查集详解"
il void kruskal()
{
    sort(edge,edge+m,cmp);
    //将边的权值排序
    for(re int i=0;i<m;i++)
    {
        eu=find(edge[i].u), ev=find(edge[i].v);
        if(eu==ev)
        {
            continue;
        }
        //若出现两个点已经联通了，则说明这一条边不需要了
        ans+=edge[i].w;
        //将此边权计入答案
        fa[ev]=eu;
        //将eu、ev合并
        if(++cnt==n-1)
        {
            break;
        }
        //循环结束条件，及边数为点数减一时
    }
}
int main()
{
    n=read(),m=read();
    for(re int i=1;i<=n;i++)
    {
        fa[i]=i;
    }
    //初始化并查集
    for(re int i=0;i<m;i++)
    {
        edge[i].u=read(),edge[i].v=read(),edge[i].w=read();
    }
    kruskal();
    if(cnt!=n-1) cout<<"orz"<<endl;
    else printf("%d",ans);
    return 0;
}
```

### 最近公共祖先（LCA）

```cpp
//利用树链剖分的方法
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
struct node{
	int next,to;
}e[N<<1];
int tot,head[N];
int dep[N],siz[N],hson[N],fa[N];
int top[N];
int n,m,s;
void add(int x,int y){
	e[++tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
}
void dfs1(int x,int f){
	siz[x]=1;
	fa[x]=f;
	dep[x]=dep[f]+1;
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].to;
		if(y!=f){
			dfs1(y,x);
			siz[x]+=siz[y];
			if(siz[hson[x]]<siz[y] || !hson[x]){
				hson[x]=y;
			}
		}
	}
}
void dfs2(int x,int t){
	top[x]=t;
	if(!hson[x])return ;
	dfs2(hson[x],t);
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].to;
		if(y!=fa[x] && y!=hson[x]){
			dfs2(y,y);
		}
	}
}
int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]){
			swap(x,y);
		}
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n>>m>>s;
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		add(x,y);
		add(y,x);
	}
	dfs1(s,0);
	dfs2(s,s);
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		cout<<LCA(a,b)<<'\n';
	}
	return 0;
}
```
```cpp
//使用链式前向星与tarjan算法的结合
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+5;
int cnt=1,head[maxn<<1],n,m,s;
struct graph{
	int next,to;
}g[maxn<<1];
void add(int u,int v){
	g[cnt].next=head[u];
	g[cnt].to=v;
	head[u]=cnt++;
}
//问题列表也可以用链式前向星存储
int qcnt=1,qhead[maxn<<1],qindex[maxn<<1];
struct quenstion{
	int next,to;
}q[maxn<<1];
void addq(int u,int v,int i){
	q[qcnt].next=qhead[u];
	q[qcnt].to=v;
	qindex[qcnt]=i;
	qhead[u]=qcnt++;
	
}
bool vis[maxn];
int father[maxn];
int ans[maxn];//答案与问题编号
void build(){
	qcnt=cnt=1;
	for(int i=1;i<=n;i++){
		head[i]=qhead[i]=0;
		vis[i]=false;
		father[i]=i;
	}
}
int find(int x){
	father[x]=father[x]==x?x:find(father[x]);
	return father[x];
}
void tarjan(int u,int f){
	vis[u]=true;
	for(int ei=head[u];ei;ei=g[ei].next){
		int v=g[ei].to;
		if(v!=f){
			tarjan(v,u);
			father[v]=u;
		}
	}
	for(int ei=qhead[u];ei;ei=q[ei].next){
		int v=q[ei].to;
		if(vis[v]) ans[qindex[ei]]=find(v);
	}
}
int main(){
	cin>>n>>m>>s;
	build();
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		addq(u,v,i);
		addq(v,u,i);
	}
	tarjan(s,0);
	for(int i=1;i<=m;i++){
		cout<<ans[i]<<endl;
	}
}
```
### 树链剖分

```cpp
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#define Rint register int
#define mem(a,b) memset(a,(b),sizeof(a))
#define Temp template<typename T>
using namespace std;
typedef long long LL;
Temp inline void read(T &x){
    x=0;T w=1,ch=getchar();
    while(!isdigit(ch)&&ch!='-')ch=getchar();
    if(ch=='-')w=-1,ch=getchar();
    while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^'0'),ch=getchar();
    x=x*w;
}

#define mid ((l+r)>>1)
#define lson rt<<1,l,mid
#define rson rt<<1|1,mid+1,r
#define len (r-l+1)

const int maxn=200000+10;
int n,m,r,mod;
//见题意 
int e,beg[maxn],nex[maxn],to[maxn],w[maxn],wt[maxn];
//链式前向星数组，w[]、wt[]初始点权数组 
int a[maxn<<2],laz[maxn<<2];
//线段树数组、lazy操作 
int son[maxn],id[maxn],fa[maxn],cnt,dep[maxn],siz[maxn],top[maxn]; 
//son[]重儿子编号,id[]新编号,fa[]父亲节点,cnt dfs_clock/dfs序,dep[]深度,siz[]子树大小,top[]当前链顶端节点 
int res=0;
//查询答案 

inline void add(int x,int y){//链式前向星加边 
    to[++e]=y;
    nex[e]=beg[x];
    beg[x]=e;
}
//-------------------------------------- 以下为线段树 
inline void pushdown(int rt,int lenn){
	laz[rt<<1]+=laz[rt];
	laz[rt<<1|1]+=laz[rt];
    a[rt<<1]+=laz[rt]*(lenn-(lenn>>1));
    a[rt<<1|1]+=laz[rt]*(lenn>>1);
    a[rt<<1]%=mod;
    a[rt<<1|1]%=mod;
    laz[rt]=0;
}

inline void build(int rt,int l,int r){
    if(l==r){
        a[rt]=wt[l];
        if(a[rt]>mod)a[rt]%=mod;
        return;
    }
    build(lson);
    build(rson);
    a[rt]=(a[rt<<1]+a[rt<<1|1])%mod;
}

inline void query(int rt,int l,int r,int L,int R){
	if(L<=l&&r<=R){res+=a[rt];res%=mod;return;}
	else{
		if(laz[rt])pushdown(rt,len);
		if(L<=mid)query(lson,L,R);
		if(R>mid)query(rson,L,R);
	}
}

inline void update(int rt,int l,int r,int L,int R,int k){
    if(L<=l&&r<=R){
		laz[rt]+=k;
		a[rt]+=k*len;
	}
	else{
		if(laz[rt])pushdown(rt,len);
		if(L<=mid)update(lson,L,R,k);
		if(R>mid)update(rson,L,R,k);
		a[rt]=(a[rt<<1]+a[rt<<1|1])%mod;
	}
}
//---------------------------------以上为线段树 
inline int qRange(int x,int y){
	int ans=0;
	while(top[x]!=top[y]){//当两个点不在同一条链上 
		if(dep[top[x]]<dep[top[y]])swap(x,y);//把x点改为所在链顶端的深度更深的那个点
		res=0;
		query(1,1,n,id[top[x]],id[x]);//ans加上x点到x所在链顶端 这一段区间的点权和
		ans+=res;
		ans%=mod;//按题意取模 
		x=fa[top[x]];//把x跳到x所在链顶端的那个点的上面一个点
	}
	//直到两个点处于一条链上
	if(dep[x]>dep[y])swap(x,y);//把x点深度更深的那个点
	res=0;
	query(1,1,n,id[x],id[y]);//这时再加上此时两个点的区间和即可
	ans+=res;
	return ans%mod;
}

inline void updRange(int x,int y,int k){//同上 
	k%=mod;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		update(1,1,n,id[top[x]],id[x],k);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	update(1,1,n,id[x],id[y],k);
}

inline int qSon(int x){
	res=0;
	query(1,1,n,id[x],id[x]+siz[x]-1);//子树区间右端点为id[x]+siz[x]-1 
	return res;
}

inline void updSon(int x,int k){//同上 
	update(1,1,n,id[x],id[x]+siz[x]-1,k);
}

inline void dfs1(int x,int f,int deep){//x当前节点，f父亲，deep深度 
	dep[x]=deep;//标记每个点的深度 
	fa[x]=f;//标记每个点的父亲 
	siz[x]=1;//标记每个非叶子节点的子树大小 
	int maxson=-1;//记录重儿子的儿子数 
	for(Rint i=beg[x];i;i=nex[i]){
		int y=to[i];
		if(y==f)continue;//若为父亲则continue 
		dfs1(y,x,deep+1);//dfs其儿子 
		siz[x]+=siz[y];//把它的儿子数加到它身上 
		if(siz[y]>maxson)son[x]=y,maxson=siz[y];//标记每个非叶子节点的重儿子编号 
	}
}

inline void dfs2(int x,int topf){//x当前节点，topf当前链的最顶端的节点 
	id[x]=++cnt;//标记每个点的新编号 
	wt[cnt]=w[x];//把每个点的初始值赋到新编号上来 
	top[x]=topf;//这个点所在链的顶端 
	if(!son[x])return;//如果没有儿子则返回 
	dfs2(son[x],topf);//按先处理重儿子，再处理轻儿子的顺序递归处理 
	for(Rint i=beg[x];i;i=nex[i]){
		int y=to[i];
		if(y==fa[x]||y==son[x])continue;
		dfs2(y,y);//对于每一个轻儿子都有一条从它自己开始的链 
	}
}

int main(){
    read(n);read(m);read(r);read(mod);
    for(Rint i=1;i<=n;i++)read(w[i]);
    for(Rint i=1;i<n;i++){
        int a,b;
        read(a);read(b);
        add(a,b);add(b,a);
    }
    dfs1(r,0,1);
    dfs2(r,r);
    build(1,1,n);
	while(m--){
        int k,x,y,z;
        read(k);
        if(k==1){
            read(x);read(y);read(z);
            updRange(x,y,z);
        }
        else if(k==2){
            read(x);read(y);
            printf("%d\n",qRange(x,y));
        }
        else if(k==3){
            read(x);read(y);
            updSon(x,y);
        }
        else{
            read(x);
            printf("%d\n",qSon(x));
    	}
    }
}
```

### 最大路匹配

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=510;
vector<int>g[N];
bool vis[N];
int match[N];
bool dfs(int u){
    for(int v:g[u]){
        if(!vis[v]){
            vis[v]=1;
            if(match[v]==0||dfs(match[v])){
                match[v]=u;
                return true;
            }
        }
    }
    return false;
}
int main(){
    int n,m,ans=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        for(int j=1;j<=x;j++){
            int y;
            cin>>y;
            g[i].push_back(y);
        }
    }
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        if(dfs(i)) ans++;
    }
    cout<<ans;
}
```

### Dijkstra算法

```cpp
//小根堆实现较为简单，这里采用以点为复杂度的反向索引堆的优化,一般不会用
#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
const int inf=1e8;
struct graph{
    int next,to,w;
}g[maxn*2];
int head[maxn],cnt,n,m;
int heap[maxn];//反向索引堆
int where[maxn];//表示点在堆上位置，初始化为-1
int heapSize;
int dis[maxn];
void build(int n){
    cnt=1;
    heapSize=0;
    for(int i=1;i<=n;i++){
        heap[i]=0;
        where[i]=-1;
        head[i]=0;
        dis[i]=inf;
    }
}
void add(int u,int v,int w){
    g[cnt].next=head[u];
    g[cnt].to=v;
    g[cnt].w=w;
    head[u]=cnt++;
}
void Swap(int i,int j){
    swap(heap[i],heap[j]);
    where[heap[i]]=i;
    where[heap[j]]=j;
}
void heapInsert(int i){
    while(dis[heap[i]]<dis[heap[(i-1)/2]]){
        Swap(i,(i-1)/2);
        i=(i-1)/2;
    }
}
void addorupdateoringnore(int v,int c){
    if(where[v]==-1){
        heap[heapSize]=v;
        where[v]=heapSize++;
        dis[v]=c;
        heapInsert(where[v]);
    }else if(where[v]>=0){
        dis[v]=min(dis[v],c);
        heapInsert(where[v]);
    }
}
void heapify(int i){
    int l=1;
    while(l<heapSize){
        int best=l+1<heapSize&&dis[heap[l+1]]<dis[heap[l]]?l+1:l;
        best=dis[heap[best]]<dis[heap[i]]?best:i;
        if(best==i) break;
        Swap(best,i);
        i=best;
        l=i*2+1;
    }
}
bool isEmpty(){
    return heapSize==0;
}
int pop(){
    int ans=heap[0];
    swap(heap[0],heap[--heapSize]);
    heapify(0);
    where[ans]=-2;
    return ans;
}
int main(){
    cin>>n>>m;
    int s;
    cin>>s;
    build(n);
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
    }
    addorupdateoringnore(s,0);
    while(!isEmpty()){
        int u=pop();
        for(int ei=head[u];ei>0;ei=g[ei].next){
            addorupdateoringnore(g[ei].to,dis[u]+g[ei].w);
        }
    }
    int ans=-inf;
    for(int i=1;i<=n;i++){
        /*if(dis[i]==inf){
            cout<<-1<<endl;
        }
        ans=max(ans,dis[i]);*/
        cout<<dis[i]<<' ';
    }
    //cout<<ans<<endl;
}
```

### 分层图最短路

```cpp
//无论是在bfs上分层还是dijkstra上，本质其实就是把原图上的点与其的不同状态整合出更多的点
//难点在于如何将点上的状态给储存下来，以及如何转移
#include<bits/stdc++.h>
using namespace std;
const int maxn=50010;
const int inf=1e8;
struct dot{
    int x,cost,k;
};
struct graph{
    int next,to,w;
}g[maxn<<1];
struct compare{
   bool operator()(dot x,dot y){
        return x.cost>y.cost;
        // 小根堆
    }
};
int head[maxn<<1],cnt=1,n,m,k,dis[maxn][20];
bool vis[maxn][20];
priority_queue<dot,vector<dot>,compare>q;
void add(int u,int v,int w){
    g[cnt].next=head[u];
    g[cnt].to=v;
    g[cnt].w=w;
    head[u]=cnt++;
}
int main(){
    cin>>n>>m>>k;
    int s,t;
    cin>>s>>t;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
        add(v,u,w);
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=k;j++){
            dis[i][j]=inf;
        }
    }
    dis[s][0]=0;
    q.push({s,0,0});
    while(!q.empty()){
        int xn=q.top().x;
        int cost=q.top().cost;
        int kn=q.top().k;
        q.pop();
        if(vis[xn][kn]) continue;
        vis[xn][kn]=1;
        if(xn==t){
            cout<<cost<<endl;
            return 0;
        }
        for(int i=head[xn];i>0;i=g[i].next){
            int v=g[i].to;
            if(kn<k&&cost<dis[v][kn+1]){
                dis[v][kn+1]=cost;
                q.push({v,cost,kn+1});
            }
            if(cost+g[i].w<dis[v][kn]){
                dis[v][kn]=cost+g[i].w;
                q.push({v,cost+g[i].w,kn});
            }
        }
    }   
}
/*
struct Compare {
    bool operator()(const State& a, const State& b) {
        return a.cost > b.cost; // 小根堆
    }
};
    priority_queue<State, vector<State>, Compare> q;
    这样子定义也可以
*/
```

### 双向广搜

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m;
ll an[45];
ll l[1<<20+1],r[1<<20+1];
ll f(int i,int e,ll s,ll w,ll a[],ll j){
    if(s>w) return j;
    if(i==e) a[j++]=s;
    else {
        j=f(i+1,e,s,w,a,j);
        j=f(i+1,e,s+an[i],w,a,j);
    }
    return j;
}
ll compute(){
    ll lsize=f(0,n>>1,0,m,l,0);
    ll rsize=f(n>>1,n,0,m,r,0);
    sort(l,l+lsize);
    sort(r,r+rsize);
    ll ans=0;
    for(int i=lsize-1,j=0;i>=0;i--){
        while(j<rsize&&l[i]+r[j]<=m){
            j++;
        }
        ans+=j;
    }
    return ans;
}
int main(){
    cin>>n>>m;
  for(int i=0;i<n;i++) cin>>an[i];
  sort(an,an+n);
  cout<<compute();
}
```

### 拓扑排序

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100001;
int cnt,n,m,head[maxn],indegree[maxn],per[maxn];

struct graph{
    int next,to;
}g[maxn];

void add(int u,int v){
    g[cnt].next=head[u];
    g[cnt].to=v;
    head[u]=cnt++;
}

bool tpsort(){
    //queue<int> q;  // 如果把队列改成小根堆的话，就可以使队列结果为字典序最小排列
    priority_queue<int,vector<int>,greater<int>>q;
    for(int i=1;i<=n;i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    int fill=0;
    while(!q.empty()){
        int cur=q.top();
        q.pop();
        per[++fill]=cur;
        for(int ei=head[cur];ei!=0;ei=g[ei].next){
            if(--indegree[g[ei].to]==0){
                q.push(g[ei].to);
            }
        }
    }
    return fill==n;
}
int main(){
    cin>>n>>m;
    cnt=1;
    memset(head,0,sizeof(head));  // 初始化head数组
    memset(indegree,0,sizeof(indegree));  // 初始化入度数组
    
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        indegree[v]++;
    }
    
    if(!tpsort()){
        cout<<-1<<endl;
    }else {
        for(int i=1;i<=n;i++){
            cout<<per[i]<<' ';
        }
        cout<<endl;
    }
    return 0;
}
```
### tarjan(强连通分量)
```cpp
//强连通分量求解
int dfn[N], low[N], dfncnt, s[N], in_stack[N], tp;
int scc[N], sc;  // 结点 i 所在 SCC 的编号
int sz[N];       // 强连通 i 的大小

void tarjan(int u) {
  low[u] = dfn[u] = ++dfncnt, s[++tp] = u, in_stack[u] = 1;
  for (int i = h[u]; i; i = e[i].nex) {
    const int &v = e[i].t;
    if (!dfn[v]) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
    } else if (in_stack[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if (dfn[u] == low[u]) {
    ++sc;
    do {
      scc[s[tp]] = sc;
      sz[sc]++;
      in_stack[s[tp]] = 0;
    } while (s[tp--] != u);
  }
}
```
```cpp
#include <bits/stdc++.h>
#define N 100010  // 定义数组最大长度，适配题目中N≤1e4的范围（留有余量）
using namespace std;
struct graph{
    int t,nex;
}e[N*2];
//强连通分量求解
int dfn[N], low[N], dfncnt, s[N], in_stack[N], tp,cnt=1,h[N*2];
int scc[N], sc;  // 结点 i 所在 SCC 的编号
int sz[N];       // 强连通 i 的大小
int out[N];
void add(int u,int v){
    e[cnt].nex=h[u];
    e[cnt].t=v;
    h[u]=cnt++;
}
//求每个分量出度
for (int i = 1; i <= n; i++) {
        // 遍历i的所有邻接节点v
        for (int j = h[i]; j ; j=e[i].nex) {
            int v = e[i].t
            // 如果i和v属于不同的强连通分量 → 说明缩点后i的分量有一条出边到v的分量
            if (scc[i]!=scc[v]) {
                out[scc[i]]++;  // i所属分量的出度+1
            }
        }
}
```
### 边双连通分量
```cpp
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;
constexpr int N = 5e5 + 5, M = 2e6 + 5;
int n, m;

struct edge {
  int to, nt;
} e[M << 2];

int hd[N << 1], tot = 1;

void add(int u, int v) { e[++tot] = edge{v, hd[u]}, hd[u] = tot; }

void uadd(int u, int v) { add(u, v), add(v, u); }

int bfncnt, sum;
int dfn[N], low[N],bcc[N],bcc_cnt;
bool vis[N];
vector<vector<int>> ans;
stack<int> st;
void tarjan(int u, int in) {
  low[u] = dfn[u] = ++dfncnt;
  st.push(u), vis[u] = true;
  for (int i = hd[u]; i; i = e[i].nt) {
    int v = e[i].to;
    if (i == (in ^ 1)) continue;
    if (!dfn[v])
      tarjan(v, i), low[u] = min(low[u], low[v]);
    else if (vis[v])
      low[u] = min(low[u], dfn[v]);
  }
  if (dfn[u] == low[u]) {
    bcc_cnt++;
    bcc[u]=bcc_cnt;
    vector<int> t;
    t.push_back(u);
    while (st.top() != u)
      t.push_back(st.top()), bcc[st.top()]=bcc_cnt,vis[st.top()] = false, st.pop();
    st.pop(), ans.push_back(t);
  }
}
```
### 割边
```cpp

void tarjan(int u,int pre) {
  low[u] = dfn[u] = ++dfncnt;
  for (int ei = head[u]; ei; ei = e[ei].nex) {
    if((ei^1)==pre) continue;
    const int &v = e[ei].t;
    if (!dfn[v]) {
      tarjan(v,ei);
      
      low[u] = min(low[u], low[v]);
      if(low[v]>dfn[u]){
        cutedge[ei>>1]=1;//无向图割边
        ans1++;
      }
    } else  {
      low[u] = min(low[u], dfn[v]);
    }
  }
}
```
### 点双连通分量
```cpp

void tarjan(int u) {
  dfn[u] = low[u] = ++bcc_cnt, sta[++top] = u;
  if (u == root && hd[u] == 0) { //root=i;
    dcc[++cnt].push_back(u);
    return;
  }
  int f = 0;
  for (int i = hd[u]; i; i = e[i].nt) {
    int v = e[i].to;
    if (!dfn[v]) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
      if (low[v] >= dfn[u]) {
        if (++f > 1 || u != root) cut[u] = true;
        cnt++;
        do dcc[cnt].push_back(sta[top--]);
        while (sta[top + 1] != v);
        dcc[cnt].push_back(u);
      }
    } else
      low[u] = min(low[u], dfn[v]);
  }
}
```
---

## 数论算法

### 快速幂

```cpp
int qmi(int m, int k, int p)
{
    int res = 1 % p, t = m;
    while (k)
    {
        if (k&1) res = res * t % p;
        t = t * t % p;
        k >>= 1;
    }
    return res;
}
```

### 乘法逆元

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll fpm(ll x, ll power, ll mod) {
    x %= mod;
    ll ans = 1;
    for (; power; power >>= 1, (x *= x) %= mod)
    	if(power & 1) (ans *= x) %= mod;
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,p;
    cin>>n>>p;
    for(int a=1;a<=n;a++){
	cout<< fpm(a, p - 2, p)<<endl;
    }//x为a在mod p意义下的逆元
}
```

### 组合数求法

```cpp
#include <iostream>

using namespace std;

typedef long long LL;

LL qmi(LL a,int k, int p)
{
    LL res = 1;
    while(k)
    {
        if (k & 1) res = res * a % p;
        k >>= 1;
        a = a * a % p;
    }
    return res;
}

int C(int a,int b,int p)
{
    if(a < b) return 0;

    LL res = 1;
    for(int i = 1, j = a; i <= b; i ++ , j -- )
    {
        res = res * j % p;
        res = res * qmi(i, p - 2, p) % p;
    }
    return res;
}

LL lucas(LL a, LL b, int p)
{
    if(a < p && b < p) return C(a, b, p);
    return C(a % p, b % p, p) * lucas(a / p, b / p, p) % p;
}

int main()
{
    int n;
    cin >> n;
    while(n --)
    {
        LL a,b;
        int p;
        cin >> a >> b >> p;
        cout << lucas(a, b, p) << endl;
    }
    return 0;
}
```

### 线性基

```cpp
//普通消元法
void insert(long long x)
{
    for(int i=63;~i;i--) if((x>>i)&1ll)
    {
        if(!place[i]) {place[i]=x;return;}
        else x^=place[i];
    }
}
void insert(int *num)
{
    for(int j=63;~j;j--)
    {
        int p=0;
        for(int i=1;(!p)&&i<=n;i++)
            if((!v[i])&&((num[i]>>j)&1ll)) p=i;
        if(!p) {place[j]=0;continue;}
        v[p]=true,place[j]=num[p];
        for(int i=1;i<=n;i++) if(i!=p&&((num[i]>>j)&1ll))
            num[i]^=num[p];
    }
}
bool check(long long x)
{
    for(int i=63;~i;i--)
        if((x>>i)&1ll) x^=place[i];
    return x==0;
}
struct Base
{
    long long place[N];
    void insert(long long x)
    {
        for(int i=63;~i;i--) if((x>>i)&1ll)
        {
            if(!place[i]) {place[i]=x;return;}
            else x^=place[i];
        }
    }
};
void merge(Base A,Base &B)
{
    for(int i=63;~i;i--) if(A.place[i])
        B.insert(A.place[i]);
}
long long mx()
{
    long long ans=0;
    for(int i=63;~i;i--)
        if((ans^place[i])>ans)
            ans^=place[i];
    return ans;
}
long long mn()
{
    for(int i=0;i<=63;i++)
        if(place[i]) return place[i];
    return -1;
}
```
```cpp
//K大异或和
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
ll b[55];
int flg;
void insert(ll x) {
    int i;
    for(i=50;i>=0;i--) {
        if(x&(1ll<<i)) {
            if(b[i]) x^=b[i];
            else {b[i]=x; return ;}
        }
    }
    if(!x) flg=1;
}
void Guass() {
    int i,j;
    for(i=50;i>=0;i--) {
        if(b[i]) {
            for(j=50;j>=0;j--) {
                if(i!=j&&(b[j]&(1ll<<i))) {
                    b[j]^=b[i];
                }
            }
        }
    }
}
int main() {
    int n,m;
    scanf("%d",&n);
    int i;
    ll x;
    for(i=1;i<=n;i++) scanf("%lld",&x),insert(x);
    Guass();
    int cnt=0;
    for(i=0;i<=50;i++) {
        if(b[i]) b[cnt++]=b[i];
    }
    scanf("%d",&m);
    while(m--) {
        scanf("%lld",&x);
        if(x>(1ll<<cnt)) {
            puts("-1"); continue;
        }
        x-=flg;
        ll ans=0;
        for(i=cnt;i>=0;i--) {
            if(x&(1ll<<i)) ans^=b[i];
        }
        printf("%lld\n",ans);
    }
}
```

### 矩阵快速幂及高斯消元

```cpp
// 1.矩阵快速幂
#include <bits/stdc++.h>
using namespace std; 
#define int long long
using ll = long long;
const int MOD = 1e9 + 7;
// 矩阵结构体
struct Matrix {
    int n, m; // n: 行数, m: 列数
    vector<vector<ll>> a;
    Matrix(int _n, int _m) : n(_n), m(_m), a(_n + 1, vector<ll>(_m + 1, 0)) {}

    static Matrix identity(int n) {
        Matrix I(n, n);
        for (int i = 1; i <= n; ++i) {
            I.a[i][i] = 1;
        }
        return I;
    }
};
// 矩阵乘法: C = A * B
// 时间复杂度: O(n^3) 或 O(A.n * A.m * B.m)
Matrix operator*(const Matrix& A, const Matrix& B) {
    Matrix C(A.n, B.m);
    for (int i = 1; i <= A.n; ++i) {
        for (int j = 1; j <= B.m; ++j) {
            for (int k = 1; k <= A.m; ++k) {
                C.a[i][j] = (C.a[i][j] + A.a[i][k] * B.a[k][j]) % MOD;
            }
        }
    }
    return C;
}

// 矩阵快速幂: A^p, 时间复杂度: O(n^3 * log p) , A必须是方阵
Matrix power(Matrix A, ll p) {
    Matrix res = Matrix::identity(A.n);
    while (p) {
        if (p & 1) res= res * A;
        A = A * A;
        p >>= 1;
    }
    return res;
}
signed main(){
    ios::sync_with_stdio(false); 
    cin.tie(0), cout.tie(0); 
    int n, k; cin >> n >> k; 
    Matrix A(n, n);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n;j++){
            cin >> A.a[i][j]; 
        }
    }
    Matrix res = power(A, k); 
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cout << res.a[i][j] << " ";  
        }
        cout << endl; 
    }
}
```

---

## 动态规划

### 数位DP

```cpp
// 一般做法
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll num[25],n=0,dp[25][2];
ll dfs(int len,bool if6,bool shangxian){
    if(len==0) return 1;
    if(!shangxian&&dp[len][if6]) return dp[len][if6];
    ll cnt=0,maxx=(shangxian?num[len]:9);
    for(int i=0;i<=maxx;i++){
        if((if6&&i==2)||i==4){
          continue;
        }
        cnt+=dfs(len-1,i==6,shangxian&&i==maxx);
    }
    return shangxian? cnt:dp[len][if6]=cnt;
}
ll solve(ll x){
    n=0;
    memset(num, 0, sizeof(num));
    while(x){
        num[++n]=x%10;
        x/=10;
    }
     return dfs(n,false,true);

}
int main(){
    
    ll a,b;
    while(cin>>a>>b){
        if(a==0&&b==0) break;
        
       cout<<solve(b)-solve(a-1);
        cout<<endl;
    }
}
```

### 树形DP

```cpp
#include<bits/stdc++.h>
//#define int long long
#define in(a) a = read_int()
using namespace std;
const int N = 2e5 + 5;
const int inf = INT_MAX;
inline int read_int() {
	int x = 0;
	char ch = getchar();
	bool f = 0;
	while('9' < ch || ch < '0') f |= ch == '-' , ch = getchar();
	while('0' <= ch && ch <= '9') x = (x << 3) + (x << 1) + ch - '0' , ch = getchar();
	return f ? -x : x;
}
struct Edge {
	int n , v , w;
} edge[N << 1];
int head[N] , eid;
void eadd(int u , int v , int w) {
	edge[++ eid].n = head[u] , edge[eid].v = v , edge[head[u] = eid].w = w;
}
int n;
int l[N] , r[N] , ans[N];
void dfs(int u , int fa) { // 树形 DP 部分 
	l[u] = 1; // 初始化左边界 
	for(int i = head[u] ; i ; i = edge[i].n) {
		int v = edge[i].v , w = edge[i].w;
		if(v != fa) {
			r[v] = w - 1; // 初始化右边界 
			dfs(v , u);
			r[u] = min(r[u] , w - l[v]); // 转移过程 
			l[u] = max(l[u] , w - r[v]);
		}
	}
}
queue<int>q;
signed main() {
	in(n);
	for(int i = 1 ; i < n ; i ++) {
		int u , v , w;
		in(u) , in(v) , in(w);
		eadd(u , v , w) , eadd(v , u , w);
	}
	r[1] = 1e9; // 初始化根节点的右边界 
	dfs(1 , 0); // 求每个点权的取值范围 
	for(int i = 1 ; i <= eid ; i += 2) { // 判无解部分 
		int u = edge[i].v , v = edge[i + 1].v , w = edge[i].w;
		if(r[u] + r[v] < w || l[u] > r[u] || l[v] > r[v]) { 
            cout<<"NO";
			return 0;
		}
	}
	ans[1] = l[1]; // 若有解，根节点点权取左边界 
	q.push(1);
	while(!q.empty()) { // 广搜部分 
		int u = q.front();
		q.pop();
		for(int i = head[u] ; i ; i = edge[i].n) {
			int v = edge[i].v , w = edge[i].w;
			if(ans[v]) continue;
			ans[v] = w - ans[u]; // 递推求解
		}
	}
	cout<<"YES\n"; // 打印答案 
	for(int i = 1 ; i <= n ; i ++) cout<<ans[i]<<' ';
	return 0;
    
}
/*
#include<bits/stdc++.h>
using namespace std;
const int maxn=10000;
int cnt=1,n,head[maxn],yes[maxn],no[maxn],num[maxn],b[maxn];
struct graph{
    int next,to;
}g[maxn];
void add(int u,int v){
    g[cnt].next=head[u];
    g[cnt].to=v;
    head[u]=cnt++;
}
void dfs(int i){
    no[i]=0;
    yes[i]=num[i];
    for(int ei=head[i],v;ei;ei=g[ei].next){
        v=g[ei].to;
        dfs(v);
        no[i]+=max(yes[v],no[v]);
        yes[i]+=no[v];
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>num[i];
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        b[u]=1;
        add(v,u);
        
    }
    for(int i=1;i<=n;i++){
        if(!b[i]){
            dfs(i);
            cout<<max(yes[i],no[i])<<endl;
            break;
        }
    }
}
*/
```

### 最长不下降子序列

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5+9;
int n,k,m,a[N],b[N],dp[N],t[N<<2];

void updata(int i,int l,int r,int n,int val){
    t[i]=max(val,t[i]);
    if(l==r) return;
  int mid=(l+r)>>1;
  if(n<=mid) updata(i<<1,l,mid,n,val);
  else updata(i<<1|1,mid+1,r,n,val);
  return;
}
int getmax(int i,int l,int r,int nl,int nr){
  if(l==nl&&r==nr){
    return t[i];
  }
  int mid=(l+r)>>1;
  if(mid>=nr) return getmax(i<<1,l,mid,nl,nr);
  else if(mid<nl) return getmax(i<<1|1,mid+1,r,nl,nr);
  else return max(getmax(i<<1,l,mid,nl,mid),getmax(i<<1|1,mid+1,r,mid+1,nr));
}
void solve(){
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i],b[i]=a[i];
    // 离散化
    sort(b+1,b+n+1);
    m=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+m+1,a[i])-b;
    for(int i=1;i<=n;i++){
        dp[i]=getmax(1,1,m,1,a[i])+1;
        updata(1,1,m,a[i],dp[i]);
    }
    //到这里dp 中存储的是以a[i]结尾的最长不下降子序列
    int ans=0;
    memset(t,0,sizeof t);
    for(int i=n;i>k;i--){
        ans=max(ans,dp[i-k]+k-1+getmax(1,1,m,a[i-k],m)+1); //通过再次利用线段树找到往后最长（题目要求）
        int tem=getmax(1,1,m,a[i],m)+1;
        updata(1,1,m,a[i],tem);
    }
    ans=max(ans,k+getmax(1,1,m,a[k+1],m));
    cout<<ans<<'\n';
}

// 1 2 3 ... i-k i-k+1 i-k+2 i-k+3 ... i ...

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    int q=1;
    //cin>>q;
    while(q--){
        solve();
    }
    return 0;
}

```
---

## 计算几何

### 计算几何模板

```cpp
#include <bits/stdc++.h>
using namespace std;

using point_t=long double;  //全局数据类型，可修改为 long long 等

constexpr point_t eps=1e-8;
constexpr long double PI=3.1415926535897932384l;

// 点与向量
template<typename T> struct point
{
    T x,y;

    bool operator==(const point &a) const {return (abs(x-a.x)<=eps && abs(y-a.y)<=eps);}
    bool operator<(const point &a) const {if (abs(x-a.x)<=eps) return y<a.y-eps; return x<a.x-eps;}
    bool operator>(const point &a) const {return !(*this<a || *this==a);}
    point operator+(const point &a) const {return {x+a.x,y+a.y};}
    point operator-(const point &a) const {return {x-a.x,y-a.y};}
    point operator-() const {return {-x,-y};}
    point operator*(const T k) const {return {k*x,k*y};}
    point operator/(const T k) const {return {x/k,y/k};}
    T operator*(const point &a) const {return x*a.x+y*a.y;}  // 点积
    T operator^(const point &a) const {return x*a.y-y*a.x;}  // 叉积，注意优先级
    int toleft(const point &a) const {const auto t=(*this)^a; return (t>eps)-(t<-eps);}  // to-left 测试
    T len2() const {return (*this)*(*this);}  // 向量长度的平方
    T dis2(const point &a) const {return (a-(*this)).len2();}  // 两点距离的平方

    // 涉及浮点数
    long double len() const {return sqrtl(len2());}  // 向量长度
    long double dis(const point &a) const {return sqrtl(dis2(a));}  // 两点距离
    long double ang(const point &a) const {return acosl(max(-1.0l,min(1.0l,((*this)*a)/(len()*a.len()))));}  // 向量夹角
    point rot(const long double rad) const {return {x*cos(rad)-y*sin(rad),x*sin(rad)+y*cos(rad)};}  // 逆时针旋转（给定角度）
    point rot(const long double cosr,const long double sinr) const {return {x*cosr-y*sinr,x*sinr+y*cosr};}  // 逆时针旋转（给定角度的正弦与余弦）
};

using Point=point<point_t>;

// 极角排序
struct argcmp
{
    bool operator()(const Point &a,const Point &b) const
    {
        const auto quad=[](const Point &a)
        {
            if (a.y<-eps) return 1;
            if (a.y>eps) return 4;
            if (a.x<-eps) return 5;
            if (a.x>eps) return 3;
            return 2;
        };
        const int qa=quad(a),qb=quad(b);
        if (qa!=qb) return qa<qb;
        const auto t=a^b;
        return t>eps;
    }
};

// 直线
template<typename T> struct line
{
    point<T> p,v;  // p 为直线上一点，v 为方向向量

    bool operator==(const line &a) const {return v.toleft(a.v)==0 && v.toleft(p-a.p)==0;}
    int toleft(const point<T> &a) const {return v.toleft(a-p);}  // to-left 测试
    bool operator<(const line &a) const  // 半平面交算法定义的排序
    {
        if (abs(v^a.v)<=eps && v*a.v>=-eps) return toleft(a.p)==-1;
        return argcmp()(v,a.v);
    }

    // 涉及浮点数
    point<T> inter(const line &a) const {return p+v*((a.v^(p-a.p))/(v^a.v));}  // 直线交点
    long double dis(const point<T> &a) const {return abs(v^(a-p))/v.len();}  // 点到直线距离
    point<T> proj(const point<T> &a) const {return p+v*((v*(a-p))/(v*v));}  // 点在直线上的投影
};

using Line=line<point_t>;

//线段
template<typename T> struct segment
{
    point<T> a,b;

    bool operator<(const segment &s) const {return make_pair(a,b)<make_pair(s.a,s.b);}

    // 判定性函数建议在整数域使用

    // 判断点是否在线段上
    // -1 点在线段端点 | 0 点不在线段上 | 1 点严格在线段上
    int is_on(const point<T> &p) const  
    {
        if (p==a || p==b) return -1;
        return (p-a).toleft(p-b)==0 && (p-a)*(p-b)<-eps;
    }

    // 判断线段直线是否相交
    // -1 直线经过线段端点 | 0 线段和直线不相交 | 1 线段和直线严格相交
    int is_inter(const line<T> &l) const
    {
        if (l.toleft(a)==0 || l.toleft(b)==0) return -1;
        return l.toleft(a)!=l.toleft(b);
    }
    
    // 判断两线段是否相交
    // -1 在某一线段端点处相交 | 0 两线段不相交 | 1 两线段严格相交
    int is_inter(const segment<T> &s) const
    {
        if (is_on(s.a) || is_on(s.b) || s.is_on(a) || s.is_on(b)) return -1;
        const line<T> l{a,b-a},ls{s.a,s.b-s.a};
        return l.toleft(s.a)*l.toleft(s.b)==-1 && ls.toleft(a)*ls.toleft(b)==-1;
    }

    // 点到线段距离
    long double dis(const point<T> &p) const
    {
        if ((p-a)*(b-a)<-eps || (p-b)*(a-b)<-eps) return min(p.dis(a),p.dis(b));
        const line<T> l{a,b-a};
        return l.dis(p);
    }

    // 两线段间距离
    long double dis(const segment<T> &s) const
    {
        if (is_inter(s)) return 0;
        return min({dis(s.a),dis(s.b),s.dis(a),s.dis(b)});
    }
};

using Segment=segment<point_t>;

// 多边形
template<typename T> struct polygon
{
    vector<point<T>> p;  // 以逆时针顺序存储

    size_t nxt(const size_t i) const {return i==p.size()-1?0:i+1;}
    size_t pre(const size_t i) const {return i==0?p.size()-1:i-1;}
    
    // 回转数
    // 返回值第一项表示点是否在多边形边上
    // 对于狭义多边形，回转数为 0 表示点在多边形外，否则点在多边形内
    pair<bool,int> winding(const point<T> &a) const
    {
        int cnt=0;
        for (size_t i=0;i<p.size();i++)
        {
            const point<T> u=p[i],v=p[nxt(i)];
            if (abs((a-u)^(a-v))<=eps && (a-u)*(a-v)<=eps) return {true,0};
            if (abs(u.y-v.y)<=eps) continue;
            const Line uv={u,v-u};
            if (u.y<v.y-eps && uv.toleft(a)<=0) continue;
            if (u.y>v.y+eps && uv.toleft(a)>=0) continue;
            if (u.y<a.y-eps && v.y>=a.y-eps) cnt++;
            if (u.y>=a.y-eps && v.y<a.y-eps) cnt--;
        }
        return {false,cnt};
    }

    // 多边形面积的两倍
    // 可用于判断点的存储顺序是顺时针或逆时针
    T area() const
    {
        T sum=0;
        for (size_t i=0;i<p.size();i++) sum+=p[i]^p[nxt(i)];
        return sum;
    }

    // 多边形的周长
    long double circ() const
    {
        long double sum=0;
        for (size_t i=0;i<p.size();i++) sum+=p[i].dis(p[nxt(i)]);
        return sum;
    }
};

using Polygon=polygon<point_t>;

//凸多边形
template<typename T> struct convex: polygon<T>
{
    // 闵可夫斯基和
    convex operator+(const convex &c) const  
    {
        const auto &p=this->p;
        vector<Segment> e1(p.size()),e2(c.p.size()),edge(p.size()+c.p.size());
        vector<point<T>> res; res.reserve(p.size()+c.p.size());
        const auto cmp=[](const Segment &u,const Segment &v) {return argcmp()(u.b-u.a,v.b-v.a);};
        for (size_t i=0;i<p.size();i++) e1[i]={p[i],p[this->nxt(i)]};
        for (size_t i=0;i<c.p.size();i++) e2[i]={c.p[i],c.p[c.nxt(i)]};
        rotate(e1.begin(),min_element(e1.begin(),e1.end(),cmp),e1.end());
        rotate(e2.begin(),min_element(e2.begin(),e2.end(),cmp),e2.end());
        merge(e1.begin(),e1.end(),e2.begin(),e2.end(),edge.begin(),cmp);
        const auto check=[](const vector<point<T>> &res,const point<T> &u)
        {
            const auto back1=res.back(),back2=*prev(res.end(),2);
            return (back1-back2).toleft(u-back1)==0 && (back1-back2)*(u-back1)>=-eps;
        };
        auto u=e1[0].a+e2[0].a;
        for (const auto &v:edge)
        {
            while (res.size()>1 && check(res,u)) res.pop_back();
            res.push_back(u);
            u=u+v.b-v.a;
        }
        if (res.size()>1 && check(res,res[0])) res.pop_back();
        return {res};
    }

    // 旋转卡壳
    // func 为更新答案的函数，可以根据题目调整位置
    template<typename F> void rotcaliper(const F &func) const
    {
        const auto &p=this->p;
        const auto area=[](const point<T> &u,const point<T> &v,const point<T> &w){return (w-u)^(w-v);};
        for (size_t i=0,j=1;i<p.size();i++)
        {
            const auto nxti=this->nxt(i);
            func(p[i],p[nxti],p[j]);
            while (area(p[this->nxt(j)],p[i],p[nxti])>=area(p[j],p[i],p[nxti]))
            {
                j=this->nxt(j);
                func(p[i],p[nxti],p[j]);
            }
        }
    }

    // 凸多边形的直径的平方
    T diameter2() const
    {
        const auto &p=this->p;
        if (p.size()==1) return 0;
        if (p.size()==2) return p[0].dis2(p[1]);
        T ans=0;
        auto func=[&](const point<T> &u,const point<T> &v,const point<T> &w){ans=max({ans,w.dis2(u),w.dis2(v)});};
        rotcaliper(func);
        return ans;
    }
    
    // 判断点是否在凸多边形内
    // 复杂度 O(logn)
    // -1 点在多边形边上 | 0 点在多边形外 | 1 点在多边形内
    int is_in(const point<T> &a) const
    {
        const auto &p=this->p;
        if (p.size()==1) return a==p[0]?-1:0;
        if (p.size()==2) return segment<T>{p[0],p[1]}.is_on(a)?-1:0; 
        if (a==p[0]) return -1;
        if ((p[1]-p[0]).toleft(a-p[0])==-1 || (p.back()-p[0]).toleft(a-p[0])==1) return 0;
        const auto cmp=[&](const Point &u,const Point &v){return (u-p[0]).toleft(v-p[0])==1;};
        const size_t i=lower_bound(p.begin()+1,p.end(),a,cmp)-p.begin();
        if (i==1) return segment<T>{p[0],p[i]}.is_on(a)?-1:0;
        if (i==p.size()-1 && segment<T>{p[0],p[i]}.is_on(a)) return -1;
        if (segment<T>{p[i-1],p[i]}.is_on(a)) return -1;
        return (p[i]-p[i-1]).toleft(a-p[i-1])>0;
    }

    // 凸多边形关于某一方向的极点
    // 复杂度 O(logn)
    // 参考资料：https://codeforces.com/blog/entry/48868
    template<typename F> size_t extreme(const F &dir) const
    {
        const auto &p=this->p;
        const auto check=[&](const size_t i){return dir(p[i]).toleft(p[this->nxt(i)]-p[i])>=0;};
        const auto dir0=dir(p[0]); const auto check0=check(0);
        if (!check0 && check(p.size()-1)) return 0;
        const auto cmp=[&](const Point &v)
        {
            const size_t vi=&v-p.data();
            if (vi==0) return 1;
            const auto checkv=check(vi);
            const auto t=dir0.toleft(v-p[0]);
            if (vi==1 && checkv==check0 && t==0) return 1;
            return checkv^(checkv==check0 && t<=0);
        };
        return partition_point(p.begin(),p.end(),cmp)-p.begin();
    }

    // 过凸多边形外一点求凸多边形的切线，返回切点下标
    // 复杂度 O(logn)
    // 必须保证点在多边形外
    pair<size_t,size_t> tangent(const point<T> &a) const
    {
        const size_t i=extreme([&](const point<T> &u){return u-a;});
        const size_t j=extreme([&](const point<T> &u){return a-u;});
        return {i,j};
    }

    // 求平行于给定直线的凸多边形的切线，返回切点下标
    // 复杂度 O(logn)
    pair<size_t,size_t> tangent(const line<T> &a) const
    {
        const size_t i=extreme([&](...){return a.v;});
        const size_t j=extreme([&](...){return -a.v;});
        return {i,j};
    }
};

using Convex=convex<point_t>;

// 圆
struct Circle
{
    Point c;
    long double r;

    bool operator==(const Circle &a) const {return c==a.c && abs(r-a.r)<=eps;}
    long double circ() const {return 2*PI*r;}  // 周长
    long double area() const {return PI*r*r;}  // 面积

    // 点与圆的关系
    // -1 圆上 | 0 圆外 | 1 圆内
    int is_in(const Point &p) const {const long double d=p.dis(c); return abs(d-r)<=eps?-1:d<r-eps;}

    // 直线与圆关系
    // 0 相离 | 1 相切 | 2 相交
    int relation(const Line &l) const
    {
        const long double d=l.dis(c);
        if (d>r+eps) return 0;
        if (abs(d-r)<=eps) return 1;
        return 2;
    }

    // 圆与圆关系
    // -1 相同 | 0 相离 | 1 外切 | 2 相交 | 3 内切 | 4 内含
    int relation(const Circle &a) const
    {
        if (*this==a) return -1;
        const long double d=c.dis(a.c);
        if (d>r+a.r+eps) return 0;
        if (abs(d-r-a.r)<=eps) return 1;
        if (abs(d-abs(r-a.r))<=eps) return 3;
        if (d<abs(r-a.r)-eps) return 4;
        return 2;
    }

    // 直线与圆的交点
    vector<Point> inter(const Line &l) const
    {
        const long double d=l.dis(c);
        const Point p=l.proj(c);
        const int t=relation(l);
        if (t==0) return vector<Point>();
        if (t==1) return vector<Point>{p};
        const long double k=sqrt(r*r-d*d);
        return vector<Point>{p-(l.v/l.v.len())*k,p+(l.v/l.v.len())*k};
    }

    // 圆与圆交点
    vector<Point> inter(const Circle &a) const
    {
        const long double d=c.dis(a.c);
        const int t=relation(a);
        if (t==-1 || t==0 || t==4) return vector<Point>();
        Point e=a.c-c; e=e/e.len()*r;
        if (t==1 || t==3) 
        {
            if (r*r+d*d-a.r*a.r>=-eps) return vector<Point>{c+e};
            return vector<Point>{c-e};
        }
        const long double costh=(r*r+d*d-a.r*a.r)/(2*r*d),sinth=sqrt(1-costh*costh);
        return vector<Point>{c+e.rot(costh,-sinth),c+e.rot(costh,sinth)};
    }

    // 圆与圆交面积
    long double inter_area(const Circle &a) const
    {
        const long double d=c.dis(a.c);
        const int t=relation(a);
        if (t==-1) return area();
        if (t<2) return 0;
        if (t>2) return min(area(),a.area());
        const long double costh1=(r*r+d*d-a.r*a.r)/(2*r*d),costh2=(a.r*a.r+d*d-r*r)/(2*a.r*d);
        const long double sinth1=sqrt(1-costh1*costh1),sinth2=sqrt(1-costh2*costh2);
        const long double th1=acos(costh1),th2=acos(costh2);
        return r*r*(th1-costh1*sinth1)+a.r*a.r*(th2-costh2*sinth2);
    }

    // 过圆外一点圆的切线
    vector<Line> tangent(const Point &a) const
    {
        const int t=is_in(a);
        if (t==1) return vector<Line>();
        if (t==-1)
        {
            const Point v={-(a-c).y,(a-c).x};
            return vector<Line>{{a,v}};
        }
        Point e=a-c; e=e/e.len()*r;
        const long double costh=r/c.dis(a),sinth=sqrt(1-costh*costh);
        const Point t1=c+e.rot(costh,-sinth),t2=c+e.rot(costh,sinth);
        return vector<Line>{{a,t1-a},{a,t2-a}};
    }

    // 两圆的公切线
    vector<Line> tangent(const Circle &a) const
    {
        const int t=relation(a);
        vector<Line> lines;
        if (t==-1 || t==4) return lines;
        if (t==1 || t==3)
        {
            const Point p=inter(a)[0],v={-(a.c-c).y,(a.c-c).x};
            lines.push_back({p,v});
        }
        const long double d=c.dis(a.c);
        const Point e=(a.c-c)/(a.c-c).len();
        if (t<=2)
        {
            const long double costh=(r-a.r)/d,sinth=sqrt(1-costh*costh);
            const Point d1=e.rot(costh,-sinth),d2=e.rot(costh,sinth);
            const Point u1=c+d1*r,u2=c+d2*r,v1=a.c+d1*a.r,v2=a.c+d2*a.r;
            lines.push_back({u1,v1-u1}); lines.push_back({u2,v2-u2});
        }
        if (t==0)
        {
            const long double costh=(r+a.r)/d,sinth=sqrt(1-costh*costh);
            const Point d1=e.rot(costh,-sinth),d2=e.rot(costh,sinth);
            const Point u1=c+d1*r,u2=c+d2*r,v1=a.c-d1*a.r,v2=a.c-d2*a.r;
            lines.push_back({u1,v1-u1}); lines.push_back({u2,v2-u2});
        }
        return lines;
    }

    // 圆的反演
    tuple<int,Circle,Line> inverse(const Line &l) const
    {
        const Circle null_c={{0.0,0.0},0.0};
        const Line null_l={{0.0,0.0},{0.0,0.0}};
        if (l.toleft(c)==0) return {2,null_c,l};
        const Point v=l.toleft(c)==1?Point{l.v.y,-l.v.x}:Point{-l.v.y,l.v.x};
        const long double d=r*r/l.dis(c);
        const Point p=c+v/v.len()*d;
        return {1,{(c+p)/2,d/2},null_l};
    }
    
    tuple<int,Circle,Line> inverse(const Circle &a) const
    {
        const Circle null_c={{0.0,0.0},0.0};
        const Line null_l={{0.0,0.0},{0.0,0.0}};
        const Point v=a.c-c;
        if (a.is_in(c)==-1)
        {
            const long double d=r*r/(a.r+a.r);
            const Point p=c+v/v.len()*d;
            return {2,null_c,{p,{-v.y,v.x}}};
        }
        if (c==a.c) return {1,{c,r*r/a.r},null_l};
        const long double d1=r*r/(c.dis(a.c)-a.r),d2=r*r/(c.dis(a.c)+a.r);
        const Point p=c+v/v.len()*d1,q=c+v/v.len()*d2;
        return {1,{(p+q)/2,p.dis(q)/2},null_l};
    }
};

// 圆与多边形面积交
long double area_inter(const Circle &circ,const Polygon &poly)
{
    const auto cal=[](const Circle &circ,const Point &a,const Point &b)
    {
        if ((a-circ.c).toleft(b-circ.c)==0) return 0.0l;
        const auto ina=circ.is_in(a),inb=circ.is_in(b);
        const Line ab={a,b-a};
        if (ina && inb) return ((a-circ.c)^(b-circ.c))/2;
        if (ina && !inb)
        {
            const auto t=circ.inter(ab);
            const Point p=t.size()==1?t[0]:t[1];
            const long double ans=((a-circ.c)^(p-circ.c))/2;
            const long double th=(p-circ.c).ang(b-circ.c);
            const long double d=circ.r*circ.r*th/2;
            if ((a-circ.c).toleft(b-circ.c)==1) return ans+d;
            return ans-d;
        }
        if (!ina && inb)
        {
            const Point p=circ.inter(ab)[0];
            const long double ans=((p-circ.c)^(b-circ.c))/2;
            const long double th=(a-circ.c).ang(p-circ.c);
            const long double d=circ.r*circ.r*th/2;
            if ((a-circ.c).toleft(b-circ.c)==1) return ans+d;
            return ans-d;
        }
        const auto p=circ.inter(ab);
        if (p.size()==2 && Segment{a,b}.dis(circ.c)<=circ.r+eps)
        {
            const long double ans=((p[0]-circ.c)^(p[1]-circ.c))/2;
            const long double th1=(a-circ.c).ang(p[0]-circ.c),th2=(b-circ.c).ang(p[1]-circ.c);
            const long double d1=circ.r*circ.r*th1/2,d2=circ.r*circ.r*th2/2;
            if ((a-circ.c).toleft(b-circ.c)==1) return ans+d1+d2;
            return ans-d1-d2;
        }
        const long double th=(a-circ.c).ang(b-circ.c);
        if ((a-circ.c).toleft(b-circ.c)==1) return circ.r*circ.r*th/2;
        return -circ.r*circ.r*th/2;
    };

    long double ans=0;
    for (size_t i=0;i<poly.p.size();i++)
    {
        const Point a=poly.p[i],b=poly.p[poly.nxt(i)];
        ans+=cal(circ,a,b);
    }
    return ans;
}

// 点集的凸包
// Andrew 算法，复杂度 O(nlogn)
Convex convexhull(vector<Point> p)
{
    vector<Point> st;
    if (p.empty()) return Convex{st};
    sort(p.begin(),p.end());
    const auto check=[](const vector<Point> &st,const Point &u)
    {
        const auto back1=st.back(),back2=*prev(st.end(),2);
        return (back1-back2).toleft(u-back1)<=0;
    };
    for (const Point &u:p)
    {
        while (st.size()>1 && check(st,u)) st.pop_back();
        st.push_back(u);
    }
    size_t k=st.size();
    p.pop_back(); reverse(p.begin(),p.end());
    for (const Point &u:p)
    {
        while (st.size()>k && check(st,u)) st.pop_back();
        st.push_back(u);
    }
    st.pop_back();
    return Convex{st};
}

// 半平面交
// 排序增量法，复杂度 O(nlogn)
// 输入与返回值都是用直线表示的半平面集合
vector<Line> halfinter(vector<Line> l, const point_t lim=1e9)
{
    const auto check=[](const Line &a,const Line &b,const Line &c){return a.toleft(b.inter(c))<0;};
    l.push_back({{-lim,0},{0,-1}}); l.push_back({{0,-lim},{1,0}});
    l.push_back({{lim,0},{0,1}}); l.push_back({{0,lim},{-1,0}});
    sort(l.begin(),l.end());
    deque<Line> q;
    for (size_t i=0;i<l.size();i++)
    {
        if (i>0 && l[i-1].v.toleft(l[i].v)==0 && l[i-1].v*l[i].v>eps) continue;
        while (q.size()>1 && check(l[i],q.back(),q[q.size()-2])) q.pop_back();
        while (q.size()>1 && check(l[i],q[0],q[1])) q.pop_front();
        if (!q.empty() && q.back().v.toleft(l[i].v)<=0) return vector<Line>();
        q.push_back(l[i]);
    }
    while (q.size()>1 && check(q[0],q.back(),q[q.size()-2])) q.pop_back();
    while (q.size()>1 && check(q.back(),q[0],q[1])) q.pop_front();
    return vector<Line>(q.begin(),q.end());
}

// 点集形成的最小最大三角形
// 极角序扫描线，复杂度 O(n^2logn)
// 最大三角形问题可以使用凸包与旋转卡壳做到 O(n^2)
pair<point_t,point_t> minmax_triangle(const vector<Point> &vec)
{
    if (vec.size()<=2) return {0,0};
    vector<pair<int,int>> evt;
    evt.reserve(vec.size()*vec.size());
    point_t maxans=0,minans=numeric_limits<point_t>::max();
    for (size_t i=0;i<vec.size();i++)
    {
        for (size_t j=0;j<vec.size();j++)
        {
            if (i==j) continue;
            if (vec[i]==vec[j]) minans=0;
            else evt.push_back({i,j});
        }
    }
    sort(evt.begin(),evt.end(),[&](const pair<int,int> &u,const pair<int,int> &v)
    {
        const Point du=vec[u.second]-vec[u.first],dv=vec[v.second]-vec[v.first];
        return argcmp()({du.y,-du.x},{dv.y,-dv.x});
    });
    vector<size_t> vx(vec.size()),pos(vec.size());
    for (size_t i=0;i<vec.size();i++) vx[i]=i;
    sort(vx.begin(),vx.end(),[&](int x,int y){return vec[x]<vec[y];});
    for (size_t i=0;i<vx.size();i++) pos[vx[i]]=i;
    for (auto [u,v]:evt)
    {
        const size_t i=pos[u],j=pos[v];
        const size_t l=min(i,j),r=max(i,j);
        const Point vecu=vec[u],vecv=vec[v];
        if (l>0) minans=min(minans,abs((vec[vx[l-1]]-vecu)^(vec[vx[l-1]]-vecv)));
        if (r<vx.size()-1) minans=min(minans,abs((vec[vx[r+1]]-vecu)^(vec[vx[r+1]]-vecv)));
        maxans=max({maxans,abs((vec[vx[0]]-vecu)^(vec[vx[0]]-vecv)),abs((vec[vx.back()]-vecu)^(vec[vx.back()]-vecv))});
        if (i<j) swap(vx[i],vx[j]),pos[u]=j,pos[v]=i;
    }
    return {minans,maxans};
}

// 判断多条线段是否有交点
// 扫描线，复杂度 O(nlogn)
bool segs_inter(const vector<Segment> &segs)
{
    if (segs.empty()) return false;
    using seq_t=tuple<point_t,int,Segment>;
    const auto seqcmp=[](const seq_t &u, const seq_t &v)
    {
        const auto [u0,u1,u2]=u;
        const auto [v0,v1,v2]=v;
        if (abs(u0-v0)<=eps) return make_pair(u1,u2)<make_pair(v1,v2);
        return u0<v0-eps;
    };
    vector<seq_t> seq;
    for (auto seg:segs)
    {
        if (seg.a.x>seg.b.x+eps) swap(seg.a,seg.b);
        seq.push_back({seg.a.x,0,seg});
        seq.push_back({seg.b.x,1,seg});
    }
    sort(seq.begin(),seq.end(),seqcmp);
    point_t x_now;
    auto cmp=[&](const Segment &u, const Segment &v)
    {
        if (abs(u.a.x-u.b.x)<=eps || abs(v.a.x-v.b.x)<=eps) return u.a.y<v.a.y-eps;
        return ((x_now-u.a.x)*(u.b.y-u.a.y)+u.a.y*(u.b.x-u.a.x))*(v.b.x-v.a.x)<((x_now-v.a.x)*(v.b.y-v.a.y)+v.a.y*(v.b.x-v.a.x))*(u.b.x-u.a.x)-eps;
    };
    multiset<Segment,decltype(cmp)> s{cmp};
    for (const auto [x,o,seg]:seq)
    {
        x_now=x;
        const auto it=s.lower_bound(seg);
        if (o==0)
        {
            if (it!=s.end() && seg.is_inter(*it)) return true;
            if (it!=s.begin() && seg.is_inter(*prev(it))) return true;
            s.insert(seg);
        }
        else
        {
            if (next(it)!=s.end() && it!=s.begin() && (*prev(it)).is_inter(*next(it))) return true;
            s.erase(it);
        }
    }
    return false;
}

// 多边形面积并
// 轮廓积分，复杂度 O(n^2logn)，n为边数
// ans[i] 表示被至少覆盖了 i+1 次的区域的面积
vector<long double> area_union(const vector<Polygon> &polys)
{
    const size_t siz=polys.size();
    vector<vector<pair<Point,Point>>> segs(siz);
    const auto check=[](const Point &u,const Segment &e){return !((u<e.a && u<e.b) || (u>e.a && u>e.b));};

    auto cut_edge=[&](const Segment &e,const size_t i)
    {
        const Line le{e.a,e.b-e.a};
        vector<pair<Point,int>> evt;
        evt.push_back({e.a,0}); evt.push_back({e.b,0});
        for (size_t j=0;j<polys.size();j++)
        {
            if (i==j) continue;
            const auto &pj=polys[j];
            for (size_t k=0;k<pj.p.size();k++)
            {
                const Segment s={pj.p[k],pj.p[pj.nxt(k)]};
                if (le.toleft(s.a)==0 && le.toleft(s.b)==0)
                {
                    evt.push_back({s.a,0});
                    evt.push_back({s.b,0});
                }
                else if (s.is_inter(le))
                {
                    const Line ls{s.a,s.b-s.a};
                    const Point u=le.inter(ls);
                    if (le.toleft(s.a)<0 && le.toleft(s.b)>=0) evt.push_back({u,-1});
                    else if (le.toleft(s.a)>=0 && le.toleft(s.b)<0) evt.push_back({u,1});
                }
            }
        }
        sort(evt.begin(),evt.end());
        if (e.a>e.b) reverse(evt.begin(),evt.end());
        int sum=0;
        for (size_t i=0;i<evt.size();i++)
        {
            sum+=evt[i].second;
            const Point u=evt[i].first,v=evt[i+1].first;
            if (!(u==v) && check(u,e) && check(v,e)) segs[sum].push_back({u,v});
            if (v==e.b) break;
        }
    };
    
    for (size_t i=0;i<polys.size();i++)
    {
        const auto &pi=polys[i];
        for (size_t k=0;k<pi.p.size();k++)
        {
            const Segment ei={pi.p[k],pi.p[pi.nxt(k)]};
            cut_edge(ei,i);
        }
    }
    vector<long double> ans(siz);
    for (size_t i=0;i<siz;i++)
    {
        long double sum=0;
        sort(segs[i].begin(),segs[i].end());
        int cnt=0;
        for (size_t j=0;j<segs[i].size();j++)
        {
            if (j>0 && segs[i][j]==segs[i][j-1]) segs[i+(++cnt)].push_back(segs[i][j]);
            else cnt=0,sum+=segs[i][j].first^segs[i][j].second;
        }
        ans[i]=sum/2;
    }
    return ans;
}

// 圆面积并
// 轮廓积分，复杂度 O(n^2logn)
// ans[i] 表示被至少覆盖了 i+1 次的区域的面积
vector<long double> area_union(const vector<Circle> &circs)
{
    const size_t siz=circs.size();
    using arc_t=tuple<Point,long double,long double,long double>;
    vector<vector<arc_t>> arcs(siz);
    const auto eq=[](const arc_t &u,const arc_t &v)
    {
        const auto [u1,u2,u3,u4]=u;
        const auto [v1,v2,v3,v4]=v;
        return u1==v1 && abs(u2-v2)<=eps && abs(u3-v3)<=eps && abs(u4-v4)<=eps;
    };

    auto cut_circ=[&](const Circle &ci,const size_t i)
    {
        vector<pair<long double,int>> evt;
        evt.push_back({-PI,0}); evt.push_back({PI,0});
        int init=0;
        for (size_t j=0;j<circs.size();j++)
        {
            if (i==j) continue;
            const Circle &cj=circs[j];
            if (ci.r<cj.r-eps && ci.relation(cj)>=3) init++;
            const auto inters=ci.inter(cj);
            if (inters.size()==1) evt.push_back({atan2l((inters[0]-ci.c).y,(inters[0]-ci.c).x),0});
            if (inters.size()==2)
            {
                const Point dl=inters[0]-ci.c,dr=inters[1]-ci.c;
                long double argl=atan2l(dl.y,dl.x),argr=atan2l(dr.y,dr.x);
                if (abs(argl+PI)<=eps) argl=PI;
                if (abs(argr+PI)<=eps) argr=PI;
                if (argl>argr+eps)
                {
                    evt.push_back({argl,1}); evt.push_back({PI,-1});
                    evt.push_back({-PI,1}); evt.push_back({argr,-1});
                }
                else
                {
                    evt.push_back({argl,1});
                    evt.push_back({argr,-1});
                }
            }
        }
        sort(evt.begin(),evt.end());
        int sum=init;
        for (size_t i=0;i<evt.size();i++)
        {
            sum+=evt[i].second;
            if (abs(evt[i].first-evt[i+1].first)>eps) arcs[sum].push_back({ci.c,ci.r,evt[i].first,evt[i+1].first});
            if (abs(evt[i+1].first-PI)<=eps) break;
        }
    };

    const auto oint=[](const arc_t &arc)
    {
        const auto [cc,cr,l,r]=arc;
        if (abs(r-l-PI-PI)<=eps) return 2.0l*PI*cr*cr;
        return cr*cr*(r-l)+cc.x*cr*(sin(r)-sin(l))-cc.y*cr*(cos(r)-cos(l));
    };

    for (size_t i=0;i<circs.size();i++)
    {
        const auto &ci=circs[i];
        cut_circ(ci,i);
    }
    vector<long double> ans(siz);
    for (size_t i=0;i<siz;i++)
    {
        long double sum=0;
        sort(arcs[i].begin(),arcs[i].end());
        int cnt=0;
        for (size_t j=0;j<arcs[i].size();j++)
        {
            if (j>0 && eq(arcs[i][j],arcs[i][j-1])) arcs[i+(++cnt)].push_back(arcs[i][j]);
            else cnt=0,sum+=oint(arcs[i][j]);
        }
        ans[i]=sum/2;
    }
    return ans;
}
```

---

## 其他算法
### 矩阵加速
```cpp
//1939
// #include <iostream>
// #include <cstdio>
// #include <cstring>

// using namespace std;

// typedef long long LL;
// const int Mod = 1e9+7;
// int T, n;
// struct mat{
// 	LL m[5][5];
// }Ans, base;
// inline void init() {
// 	memset(Ans.m, 0, sizeof(Ans.m));
// 	for(int i=1; i<=3; i++) Ans.m[i][i] = 1;
// 	memset(base.m, 0, sizeof(base.m));
// 	base.m[1][1] = base.m[1][3] = base.m[2][1] = base.m[3][2] = 1;
// }
// inline mat mul(mat a, mat b) {
// 	mat res;
// 	memset(res.m, 0, sizeof(res.m));
// 	for(int i=1; i<=3; i++) {
// 		for(int j=1; j<=3; j++) {
// 			for(int k=1; k<=3; k++) {
// 				res.m[i][j] += (a.m[i][k] % Mod) * (b.m[k][j] % Mod);
// 				res.m[i][j] %= Mod;
// 			}
// 		}
// 	}
// 	return res;
// }
// inline void Qmat_pow(int p) {
// 	while (p) {
// 		if(p & 1) Ans = mul(Ans, base);
// 		base = mul(base, base);
// 		p >>= 1;
// 	}
// }

// int main() {
// 	scanf("%d", &T);
// 	while (T--) {
// 		scanf("%d", &n);
// 		if(n <= 3) {
// 			printf("1\n");
// 			continue;
// 		}
// 		init();
// 		Qmat_pow(n);
// 		printf("%lld\n", Ans.m[2][1]);
// 	}
// }
/*
f[i-1]       f[i]
f[i-2] ----> f[i-1]
f[i-3]       f[i-2]
f[i] = f[i-1] * 1 + f[i-2] * 0 + f[i-3] * 1
f[i-1] = f[i-1] * 1 + f[i-2] * 0 + f[i-3] * 0
f[i-2] = f[i-1] * 0 + f[i-2] * 1 + f[i-3] * 0
so
1 0 1
1 0 0
0 1 0
*/
//P6569
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct matrix{//用结构体存矩阵敲好使哒~
	long long qwq[105][105];
    int x,y;//x,y就是矩阵的行数和列数
	matrix(){x=0,y=0;memset(qwq,0,sizeof(qwq));};//构造函数，刚听说这玩意，用着玩玩
}; 
matrix operator * (const matrix &a,const matrix &b){//重载“异或版矩阵乘法”的运算符
	matrix c;
	c.x=a.x,c.y=b.y;
	for(int i=1;i<=a.x;i++){  
		for(int j=1;j<=b.y;j++){
			for(int k=1;k<=a.y;k++)
			c.qwq[i][j]^=a.qwq[i][k]*b.qwq[k][j];//和矩阵乘法别无二致，只不过就是改成异或
		}
	}
	return c;                   
}
matrix wyx[40];//存储e矩阵的2^i次方，取这个变量名是因为想借助神仙的力量AC本题
long long f[105];//每个城市的初始魔法值（提醒：十年OI一场空……）
int main(){
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++)
	scanf("%lld",&f[i]);
	wyx[0].x=n,wyx[0].y=n;//初始化一开始的邻接矩阵（也就是2的0次方）的大小
	for(int i=1;i<=m;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		wyx[0].qwq[a][b]=wyx[0].qwq[b][a]=1;//给邻接矩阵连上边
	}
	for(int i=1;i<32;i++)wyx[i]=wyx[i-1]*wyx[i-1];//利用快速幂的思想，处理出邻接矩阵2的i次方
	while(q--){
		long long x;
		scanf("%lld",&x);
        matrix ans;
		for(int i=1;i<=n;i++)ans.qwq[1][i]=f[i];//一开始就是初始f值
		ans.x=1,ans.y=n;
		for(int i=0;i<32;i++){//开始进行二进制拆分
			if((x>>i)&1)//如果这一位是1
			ans=ans*wyx[i];//就乘上对应的2的i次方
		}
		printf("%lld\n",ans.qwq[1][1]);
	}
	return 0;
}

```

### 并查集
```cpp

//推导部分和
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1e5+10;
struct tree{
  ll n,w,to;
}e[N<<1];
ll head[N<<1],tot,fa[N],vis[N],sum[N];
void add(int u,int v,ll w){
  e[tot].to=v;
  e[tot].n=head[u];
  e[tot].w=w;
  head[u]=tot++;
}
int find(int i){
  if(fa[i]!=i) return fa[i]=find(fa[i]);
  return i;
}
void unite(int x,int y){
  x=find(x);
  y=find(y);
  if(x!=y) fa[x]=y;
}
void bfs(int x){
  vis[x]=1;
  queue<int>q; q.push(x);
  sum[x]=0;
  while(!q.empty()){
    int u=q.front();
    q.pop();
    for(int i=head[u];i!=-1;i=e[i].n){
      int v=e[i].to;
      if(vis[v]) continue;
      vis[v]=1;
      sum[v]=sum[u]+e[i].w;
      q.push(v);
    }
  }
}
int main()
{
  memset(head,-1,sizeof(head));
  int n,m,q;
  cin>>n>>m>>q;
  for(int i=1;i<=n;i++) fa[i]=i;
  for(int i=1;i<=m;i++){
    ll l,r,w;
    cin>>l>>r>>w;
    add(l-1,r,w);
    add(r,l-1,-w);
    unite(l-1,r);
  }
  for(int i=0;i<=n;i++){
    if(!vis[i]) bfs(i);
  }
  for(int i=1;i<=m;i++){
    int l,r;
    cin>>l>>r;
    if(find(l-1)!=find(r)) cout<<"UNKNOWN"<<endl;
    else cout<<sum[r]-sum[l-1]<<endl;
  }
  return 0;
}
```

### FFT（快速傅里叶变换）

```cpp
// 当vector用就可以了
#include <bits/stdc++.h>
#define fp(i, a, b) for (int i = (a), i##_ = (b) + 1; i < i##_; ++i)
#define fd(i, a, b) for (int i = (a), i##_ = (b) - 1; i > i##_; --i)
using namespace std;
using ll = int64_t;
using db = double;
/*---------------------------------------------------------------------------*/
struct cp {
    db x, y;
    cp(db real = 0, db imag = 0) : x(real), y(imag) {};
    cp operator+(cp b) const { return {x + b.x, y + b.y}; }
    cp operator-(cp b) const { return {x - b.x, y - b.y}; }
    cp operator*(cp b) const { return {x * b.x - y * b.y, x * b.y + y * b.x}; }
};
using vcp = vector<cp>;
using Poly = vector<int>;
namespace FFT {
const db pi = acos(-1);
vcp Omega(int L) {
    vcp w(L);
    w[1] = 1;
    for (int i = 2; i < L; i <<= 1) {
        auto w0 = w.begin() + i / 2, w1 = w.begin() + i;
        cp wn(cos(pi / i), sin(pi / i));
        for (int j = 0; j < i; j += 2)
            w1[j] = w0[j >> 1], w1[j + 1] = w1[j] * wn;
    }
    return w;
}
auto W = Omega(1 << 21);  // NOLINT
void DIF(cp *a, int n) {
    cp x, y;
    for (int k = n >> 1; k; k >>= 1)
        for (int i = 0; i < n; i += k << 1)
            for (int j = 0; j < k; ++j)
                x = a[i + j], y = a[i + j + k],
                a[i + j + k] = (a[i + j] - y) * W[k + j], a[i + j] = x + y;
}
void IDIT(cp *a, int n) {
    cp x, y;
    for (int k = 1; k < n; k <<= 1)
        for (int i = 0; i < n; i += k << 1)
            for (int j = 0; j < k; ++j)
                x = a[i + j], y = a[i + j + k] * W[k + j], a[i + j + k] = x - y,
                a[i + j] = x + y;
    const db Inv = 1. / n;
    fp(i, 0, n - 1) a[i].x *= Inv, a[i].y *= Inv;
    reverse(a + 1, a + n);
}
}  // namespace FFT

namespace Polynomial {
// basic operator
void DFT(vcp &a) { FFT::DIF(a.data(), a.size()); }
void IDFT(vcp &a) { FFT::IDIT(a.data(), a.size()); }
int norm(int n) { return 1 << (__lg(n - 1) + 1); }

// Poly mul
vcp &dot(vcp &a, vcp &b) {
    fp(i, 0, a.size() - 1) a[i] = a[i] * b[i];
    return a;
}
Poly operator+(Poly a, Poly b) {
    int maxlen = max(a.size(), b.size());
    Poly ans(maxlen + 1);
    a.resize(maxlen + 1), b.resize(maxlen + 1);
    for (int i = 0; i < maxlen; i++) ans[i] = a[i] + b[i];
    return ans;
}
Poly operator*(ll k, Poly a) {
    Poly ans;
    for (auto i : a) ans.push_back(k * i);
    return ans;
}
Poly operator*(Poly a, Poly b) {
    int n = a.size() + b.size() - 1;
    vcp c(norm(n));
    fp(i, 0, a.size() - 1) c[i].x = a[i];
    fp(i, 0, b.size() - 1) c[i].y = b[i];
    DFT(c), dot(c, c), IDIT(c), a.resize(n);
    fp(i, 0, n - 1) a[i] = int(c[i].y * .5 + .5);
    return a;
}
}  // namespace Polynomial
/*---------------------------------------------------------------------------*/
using namespace Polynomial;
```

### NTT（数论变换）

```cpp
#include <bits/stdc++.h>
#define fp(i, a, b) for (int i = (a), i##_ = (b) + 1; i < i##_; ++i)
#define fd(i, a, b) for (int i = (a), i##_ = (b) - 1; i > i##_; --i)
using namespace std;
const int maxn = 2e5 + 5, P = 998244353;
using ll = int64_t;
#define ADD(a, b) (((a) += (b)) >= P ? (a) -= P : 0)
#define SUB(a, b) (((a) -= (b)) < 0 ? (a) += P : 0)
#define MUL(a, b) (ll(a) * (b) % P)
int POW(ll a, int b = P - 2, ll x = 1) {
    for (; b; b >>= 1, a = a * a % P)
        if (b & 1) x = x * a % P;
    return x;
}

namespace NTT {
const int g = 3;
vector<int> Omega(int L) {
    int wn = POW(g, P / L);
    vector<int> w(L);
    w[L >> 1] = 1;
    fp(i, L / 2 + 1, L - 1) w[i] = MUL(w[i - 1], wn);
    fd(i, L / 2 - 1, 1) w[i] = w[i << 1];
    return w;
}
auto W = Omega(1 << 21);
void DIF(int *a, int n) {
    for (int k = n >> 1; k; k >>= 1) {
        for (int i = 0, y; i < n; i += k << 1)
            fp(j, 0, k - 1) y = a[i + j + k],
                            a[i + j + k] = MUL(a[i + j] - y + P, W[k + j]),
                            ADD(a[i + j], y);
    }
}
void IDIT(int *a, int n) {
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0, x, y; i < n; i += k << 1)
            fp(j, 0, k - 1) x = a[i + j], y = MUL(a[i + j + k], W[k + j]),
                            a[i + j + k] = x - y < 0 ? x - y + P : x - y,
                            ADD(a[i + j], y);
    }
    int Inv = P - (P - 1) / n;
    fp(i, 0, n - 1) a[i] = MUL(a[i], Inv);
    reverse(a + 1, a + n);
}
}  // namespace NTT
namespace Polynomial {
using Poly = std::vector<int>;
Poly &operator*=(Poly &a, int b) {
    for (auto &x : a) x = MUL(x, b);
    return a;
}
Poly operator*(Poly a, int b) { return a *= b; }
Poly operator*(int a, Poly b) { return b * a; }
void DFT(Poly &a) { NTT::DIF(a.data(), a.size()); }
void IDFT(Poly &a) { NTT::IDIT(a.data(), a.size()); }
int norm(int n) { return 1 << (32 - __builtin_clz(n - 1)); }
void norm(Poly &a) {
    if (!a.empty()) a.resize(norm(a.size()), 0);
}
Poly &dot(Poly &a, Poly &b) {
    fp(i, 0, a.size() - 1) a[i] = MUL(a[i], b[i]);
    return a;
}
Poly operator*(Poly a, Poly b) {
    int n = a.size() + b.size() - 1, L = norm(n);
    if (a.size() <= 8 || b.size() <= 8) {
        Poly c(n);
        fp(i, 0, a.size() - 1) fp(j, 0, b.size() - 1) c[i + j] =
            (c[i + j] + (ll)a[i] * b[j]) % P;
        return c;
    }
    a.resize(L), b.resize(L);
    DFT(a), DFT(b), dot(a, b), IDFT(a);
    return a.resize(n), a;
}
}  // namespace Polynomial
using namespace Polynomial;
```

### 扫描线算法

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll arr[15010],n,height[15010];

struct node{
    ll l,r,h;
}a[15010];

struct compare{
    bool operator()(pair<ll,ll> a,pair<ll,ll> b){
        if(a.first!=b.first) return a.first<b.first;
        return a.second>b.second;
        //大根堆
    }
};
bool cmp(node x,node y){
    return x.l<y.l;
}
int main(){
    ll l,r,h,m=0;
    while(scanf("%lld %lld %lld",&l,&h,&r)!=EOF){
        a[++m].l=l;
        a[m].r=r-1;
        a[m].h=h;
        arr[++n]=l;
        arr[++n]=r;
        arr[++n]=r-1;
    }
    sort(arr+1,arr+n+1);
    ll len=unique(arr+1,arr+n+1)-arr-1;
    for(int j=1;j<=m;j++){
        a[j].l=lower_bound(arr+1,arr+len+1,a[j].l)-arr;
        a[j].r=lower_bound(arr+1,arr+len+1,a[j].r)-arr;
    }
    sort(a+1,a+m+1,cmp);
   priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, compare> heap;
   for(int i=1,j=0;i<=len;i++){
    for(;j<=m&&a[j].l<=i;j++){
        heap.push(make_pair(a[j].h,a[j].r));
    }
    while(!heap.empty()&&heap.top().second<i)
    {
        heap.pop();
    }
   
   if(!heap.empty()){
    height[i]=heap.top().first;
   }
}
    ll ansn=0;
    pair<ll,ll>ans[15010];
    for(ll i=1,pre=0;i<=len;i++){
        if(pre!=height[i]){
            ans[++ansn]=make_pair(arr[i],height[i]);
        }
        pre=height[i];
    }
    for(int i=1;i<=ansn;i++){
        cout<<ans[i].first<<' '<<ans[i].second<<' ';
    }
}
```

### 最长上升子序列

```cpp
#include<cstdio>
#include<algorithm>
const int MAXN=200001;
int a[MAXN];
int d[MAXN];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    d[1]=a[1];
    int len=1;
    for(int i=2;i<=n;i++)
    {
        if(a[i]>d[len])
            d[++len]=a[i];
        else
        {
            int j=std::lower_bound(d+1,d+len+1,a[i])-d;
            d[j]=a[i]; 
        }
    }
    printf("%d\n",len);    
    return 0;
}
```

### 全排列输出

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> arr = {1, 2, 3};  // 示例数组
    
    // 先排序（必须步骤，确保生成所有排列）
    std::sort(arr.begin(), arr.end());
    
    // 输出所有排列组合
    do {
        for (int num : arr) {
            std::cout << num << " ";
        }
        std::cout << "\n";
    } while (std::next_permutation(arr.begin(), arr.end()));
    
    return 0;
}
```

### 位运算用法

```cpp
/*为了更好的理解状压dp，首先介绍位运算相关的知识。

'&'符号，x&y，会将两个十进制数在二进制下进行与运算(都1为1，其余为0） 然后返回其十进制下的值。例如3(11)&2(10)=2(10)。
'|'符号，x|y，会将两个十进制数在二进制下进行或运算（都0为0，其余为1） 然后返回其十进制下的值。例如3(11)|2(10)=3(11)。
'^'符号，x^y，会将两个十进制数在二进制下进行异或运算（不同为1，其余 为0）然后返回其十进制下的值。例如3(11)^2(10)=1(01)。
'~'符号，~x，按位取反。例如~101=010。
'<<'符号，左移操作，x<<2，将x在二进制下的每一位向左移动两位，最右边用0填充，x<<2相当于让x乘以4。 '>>'符号，是右移操作，x>>1相当于给x/2，去掉x二进制下的最右一位
1.判断一个数字x二进制下第i位是不是等于1。（最低第1位）

方法：if(((1<<(i−1))&x)>0) 将1左移i-1位，相当于制造了一个只有第i位 上是1，其他位上都是0的二进制数。然后与x做与运算，如果结果>0， 说明x第i位上是1，反之则是0。

2.将一个数字x二进制下第i位更改成1。

方法：x=x|(1<<(i−1)) 证明方法与1类似。

3.将一个数字x二进制下第i位更改成0。

方法：x=x&~(1<<(i−1))

4.把一个数字二进制下最靠右的第一个1去掉。

方法：x=x&(x−1)
__builtin_popcount() 二进制数中一的个数
*/
#include<iostream>
using namespace std;
struct state {
    int st[1 << 12+1];  
    int num;          
} a[15];
int m, n;
int f[15][1 << 12+1];   
const int MOD = 100000000;
void getstate(int i, int t) {
    a[i].num = 0;
    for (int j = 0; j < (1 << n); j++) {
        if ((j & (j << 1)) || (j & t)) 
            continue;
        a[i].st[++a[i].num] = j;
    }
}
void dp() {
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= a[i].num; j++)
            f[i][j] = 0;
    for (int j = 1; j <= a[1].num; j++)
        f[1][j] = 1;
    for (int i = 2; i <= m; i++) {
        for (int j = 1; j <= a[i].num; j++) {
            int s1 = a[i].st[j];
            for (int k = 1; k <= a[i-1].num; k++) {
                int s2 = a[i-1].st[k];
                if (s1 & s2) continue; 
                f[i][j] = (f[i][j] + f[i-1][k]) % MOD;
            }
        }
    }
    int ans = 0;
    for (int j = 1; j <= a[m].num; j++)
        ans = (ans + f[m][j]) % MOD;
    cout << ans << endl;
}
int main() {
    cin >> m >> n;  
    for (int i = 1; i <= m; i++) {
        int t = 0;
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            t = (t << 1) + (1 - x); 
        }
        getstate(i, t); 
    }
    dp();
    return 0;
}
```

### Map的使用

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	//什么是map？map是干什么用的
	map<int,int>mp; //定义了一个名叫mp的map容器
	mp[10001]=82;mp[100002]=82;
	//输出10001信息
	cout<<mp[10001]<<endl;//可能会溢出
	//安全的方法
	if(mp.find(10005)!=mp.end()){
		cout<<mp[10005]<<endl;
	}

    else cout<<"没有此人信息"<<endl;
	//储存学生姓名对应成绩
	map<string,int>stu;
	stu["xiaoming"]=85;
	stu["xiaohong"]=77;
	cout<<stu["xiaohong"]<<endl;
	//map的遍历
    //1.
	for(auto it:stu){//将容器从头到尾遍历了一遍
		//map自动按照首位字典序从小到大排序
		cout<<it.first<<' '<<it.second<<endl;
	}
	//2.迭代器类型
	map<string,int>::iterator it;//定义map<string,int>类型的迭代器it
	for(it=stu.begin();it!=stu.end();it++){
		cout<<(*it).first<<' '<<(*it).second<<endl;
	}
}
```
### 优先队列（堆）

```cpp
//自定义类的优先队列
struct Student {
    std::string name;
    int score;
    int age;
    
    // 重载 < 运算符，用于大根堆（按score从大到小）
    bool operator<(const Student& other) const {
        // 注意：priority_queue默认用 < 比较，但实际表现是最大堆
        // 所以这里返回 true 表示优先级更低
        return score < other.score;  // 大根堆
    }
};
priority_queue<Student>q1;//大根堆
priority_queue<int>q2;//默认大根堆
priority_queue<int,vector<int>,greater<int>>q3;//小根堆
```

### 扫描线+线段树（矩形面积并）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll arr[15010],n,height[15010];

struct node{
    ll l,r,h;
}a[15010];

struct compare{
    bool operator()(pair<ll,ll> a,pair<ll,ll> b){
        if(a.first!=b.first) return a.first<b.first;
        return a.second>b.second;
        //大根堆
    }
};
bool cmp(node x,node y){
    return x.l<y.l;
}
int main(){
    ll l,r,h,m=0;
    while(scanf("%lld %lld %lld",&l,&h,&r)!=EOF){
        a[++m].l=l;
        a[m].r=r-1;
        a[m].h=h;
        arr[++n]=l;
        arr[++n]=r;
        arr[++n]=r-1;
    }
    sort(arr+1,arr+n+1);
    ll len=unique(arr+1,arr+n+1)-arr-1;
    for(int j=1;j<=m;j++){
        a[j].l=lower_bound(arr+1,arr+len+1,a[j].l)-arr;
        a[j].r=lower_bound(arr+1,arr+len+1,a[j].r)-arr;
    }
    sort(a+1,a+m+1,cmp);
   priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, compare> heap;
   for(int i=1,j=0;i<=len;i++){
    for(;j<=m&&a[j].l<=i;j++){
        heap.push(make_pair(a[j].h,a[j].r));
    }
    while(!heap.empty()&&heap.top().second<i)
    {
        heap.pop();
    }
   
   if(!heap.empty()){
    height[i]=heap.top().first;
   }
}
    ll ansn=0;
    pair<ll,ll>ans[15010];
    for(ll i=1,pre=0;i<=len;i++){
        if(pre!=height[i]){
            ans[++ansn]=make_pair(arr[i],height[i]);
        }
        pre=height[i];
    }
    for(int i=1;i<=ansn;i++){
        cout<<ans[i].first<<' '<<ans[i].second<<' ';
    }
}
```

### 建树参考

```cpp
#include<bits/stdc++.h>
//#define int long long
#define in(a) a = read_int()
using namespace std;
const int N = 2e5 + 5;
const int inf = INT_MAX;
inline int read_int() {
	int x = 0;
	char ch = getchar();
	bool f = 0;
	while('9' < ch || ch < '0') f |= ch == '-' , ch = getchar();
	while('0' <= ch && ch <= '9') x = (x << 3) + (x << 1) + ch - '0' , ch = getchar();
	return f ? -x : x;
}
struct Edge {
	int n , v , w;
} edge[N << 1];
int head[N] , eid;
void eadd(int u , int v , int w) {
	edge[++ eid].n = head[u] , edge[eid].v = v , edge[head[u] = eid].w = w;
}
int n;
int l[N] , r[N] , ans[N];
void dfs(int u , int fa) { // 树形 DP 部分 
	l[u] = 1; // 初始化左边界 
	for(int i = head[u] ; i ; i = edge[i].n) {
		int v = edge[i].v , w = edge[i].w;
		if(v != fa) {
			r[v] = w - 1; // 初始化右边界 
			dfs(v , u);
			r[u] = min(r[u] , w - l[v]); // 转移过程 
			l[u] = max(l[u] , w - r[v]);
		}
	}
}
queue<int>q;
signed main() {
	in(n);
	for(int i = 1 ; i < n ; i ++) {
		int u , v , w;
		in(u) , in(v) , in(w);
		eadd(u , v , w) , eadd(v , u , w);
	}
	r[1] = 1e9; // 初始化根节点的右边界 
	dfs(1 , 0); // 求每个点权的取值范围 
	for(int i = 1 ; i <= eid ; i += 2) { // 判无解部分 
		int u = edge[i].v , v = edge[i + 1].v , w = edge[i].w;
		if(r[u] + r[v] < w || l[u] > r[u] || l[v] > r[v]) { 
            cout<<"NO";
			return 0;
		}
	}
	ans[1] = l[1]; // 若有解，根节点点权取左边界 
	q.push(1);
	while(!q.empty()) { // 广搜部分 
		int u = q.front();
		q.pop();
		for(int i = head[u] ; i ; i = edge[i].n) {
			int v = edge[i].v , w = edge[i].w;
			if(ans[v]) continue;
			ans[v] = w - ans[u]; // 递推求解 
			q.push(v);
		}
	}
	cout<<"YES\n"; // 打印答案 
	for(int i = 1 ; i <= n ; i ++) cout<<ans[i]<<' ';
	return 0;
}
```

### Hash树

```cpp
//树同构

#include <bits/stdc++.h>
 
 typedef long long LL;
 const int N = 60, MO = 998244353;
 
 struct Edge {
     int nex, v;
 }edge[N << 1]; int tp;
 
 int e[N], n, m, turn, fr[N], p[1000010], top, siz[N], h[N], g[N];
 std::vector<int> v[N];
 bool vis[1000010];
 
 inline void add(int x, int y) {
     tp++;
     edge[tp].v = y;
     edge[tp].nex = e[x];
     e[x] = tp;
     return;
 }
 
 inline bool equal(int a, int b) {
     int len = v[a].size();
     if(len != v[b].size()) return false;
     for(int i = 0; i < len; i++) {
         if(v[a][i] != v[b][i]) return false;
     }
     return true;
 }
 
 inline void getp(int n) {
     for(int i = 2; i <= n; i++) {
         if(!vis[i]) {
             p[++top] = i;
         }
         for(int j = 1; j <= top && i * p[j] <= n; j++) {
             vis[i * p[j]] = 1;
             if(i % p[j] == 0) {
                 break;
             }
         }
     }
     return;
 }
 
 void DFS_1(int x, int f) {
     siz[x] = 1;
     h[x] = 1;
     for(int i = e[x]; i; i = edge[i].nex) {
         int y = edge[i].v;
         if(y == f) continue;
         DFS_1(y, x);
         h[x] = (h[x] + 1ll * h[y] * p[siz[y]] % MO) % MO;
         siz[x] += siz[y];
     }
     return;
 }
 
 void DFS_2(int x, int f, int V) {
     g[x] = (h[x] + 1ll * V * p[n - siz[x]] % MO) % MO;
     v[turn].push_back(g[x]);
     V = (1ll * V * p[n - siz[x]] % MO + 1) % MO;
     for(int i = e[x]; i; i = edge[i].nex) {
         int y = edge[i].v;
         if(y == f) {
             continue;
         }
         DFS_2(y, x, ((LL)V + h[x] - 1 - 1ll * h[y] * p[siz[y]] % MO + MO) % MO);
     }
     return;
 }
 
 int main() {
     getp(1000009);
     scanf("%d", &m);
     for(turn = 1; turn <= m; turn++) {
         scanf("%d", &n);
         tp = 0;
         memset(e + 1, 0, n * sizeof(int));
         for(int i = 1, x; i <= n; i++) {
             scanf("%d", &x);
             if(x) {
                 add(x, i);
                 add(i, x);
             }
         }
         DFS_1(1, 0);
         DFS_2(1, 0, 0);
         std::sort(v[turn].begin(), v[turn].end());
     }
 
     for(int i = 1; i <= m; i++) {
         fr[i] = i;
     }
     for(int i = 2; i <= m; i++) {
         for(int j = 1; j < i; j++) {
             if(equal(i, j)) {
                 fr[i] = fr[j];
                 break;
             }
         }
     }
     for(int i = 1; i <= m; i++) {
         printf("%d\n", fr[i]);
     }
     return 0;
}
```