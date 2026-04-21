//给定任意节点i，可以快速查询，从i节点往上走的路径中位于第s层的编号
//生成复杂度 nlog（n）,查询复杂度log（n）
// #include<bits/stdc++.h>
// using namespace std;
// const int maxn=5e5+10;
// int limit=32;
// int power;
// int log2(int x){
//     int ans=0;
//     while((1<<ans)<=(n>>1)){
//         ans++;
//     }
//     return ans;;
// }
// struct tree{
//     int n,t;
// }tr[maxn];
// int head[maxn],deep[maxn],st[maxn][limit],tot=1;
// void add(int u,int v){
//     tr[++tot].t=v;
//     tr[tot].n=head[u];
//     head[u]=tot;
// }
// void dfs(int i,int f){
//     if(i==0){// 0节点为头节点
//         deep[i]=1;
//     }else deep[i]=deep[f]+1;
// 		st[i][0]=f;
//     for(int p=1;(1<<p)<=deep[i];p++){
//         st[i][p]=st[st[i][p-1]][p-1];
//     }
//     for(int ei=head[i];ei;ei=tr[ei].n){
//         dfs(tr[ei].t,i);
//     }
// }
// int getkthAncestor(int i,int k){
//     if(deep[i]<=k) return -1;
//     int s=deep[i]-k;
//     for(int p=power;p>=0;p--){
//         if(deep[st[i][p]]>=s){
//             i=st[i][p];
//         }
//     }
//     return i;
// }



// 更快的查询方法,迭代版，防止爆栈
// P5903
// int find(int u,int k){
// 	int cnt = 0;
// 	while(k){
// 		if(k & 1) u = fa[u][cnt];
// 		k >>= 1;
// 		cnt++;
// 	}
// 	return u;
// }

// // 利用树上倍增来求LCA
// #include<bits/stdc++.h>
// using namespace std;
// const int maxn = 5e5 + 10;
// int n, q, root;
// int power;                     // log2(n)

// // 邻接表（无向树边数 = 2*(n-1)，所以数组要开 2*maxn）
// struct edge {
//     int to, nxt;
// } tr[maxn * 2];
// int head[maxn], tot = 1;
// int deep[maxn];
// int st[maxn][20];              // 20 > log2(5e5) ≈ 19，足够
// // 预处理log2(n)
// int getLog2(int x) {
//     int res = 0;
//     while ((1 << (res + 1)) <= x) res++;
//     return res;
// }

// void add(int u, int v) {
//     tr[++tot].to = v;
//     tr[tot].nxt = head[u];
//     head[u] = tot;
// }

// void dfs(int u, int fa) {
//     deep[u] = deep[fa] + 1;
//     st[u][0] = fa;                         // 设置父节点
//     for (int p = 1; (1 << p) <= deep[u]; p++) {
//         st[u][p] = st[st[u][p-1]][p-1];
//     }
//     for (int i = head[u]; i; i = tr[i].nxt) {
//         int v = tr[i].to;
//         if (v == fa) continue;             // 跳过父节点，避免无限递归
//         dfs(v, u);
//     }
// }

// int findLCA(int a, int b) {
//     if (deep[a] < deep[b]) swap(a, b);
//     // 将a上移到与b同深度
//     for (int p = power; p >= 0; p--) {
//         if (deep[st[a][p]] >= deep[b]) {
//             a = st[a][p];
//         }
//     }
//     if (a == b) return a;
//     // 一起向上跳
//     for (int p = power; p >= 0; p--) {
//         if (st[a][p] != st[b][p]) {
//             a = st[a][p];
//             b = st[b][p];
//         }
//     }
//     return st[a][0];
// }

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(0);
//     cin >> n >> q >> root;
//     power = getLog2(n);
//     for (int i = 1; i < n; i++) {
//         int u, v;
//         cin >> u >> v;
//         add(u, v);
//         add(v, u);
//     }
//     // 根节点的父节点设为0，deep[0]=0
//     dfs(root, 0);
//     while (q--) {
//         int x, y;
//         cin >> x >> y;
//         cout << findLCA(x, y) << '\n';
//     }
//     return 0;
// }



//利用树上倍增和最小生成树的实际应用
//P1967
// #include<bits/stdc++.h>
// using namespace std;
// #define re register
// #define il inline

// const int maxn = 5e5 + 10;
// int n, m, q;
// int power,st[maxn][21],stmin[maxn][21],inf=1e8+10,tot=1,head[maxn],fa[maxn],vis[maxn],deep[maxn];  
// struct edge {
//     int to, nxt,w;
// } tr[maxn * 2];
// struct Edge
// {
// 	int u,v,w;
// }edge[maxn];
// int getLog2(int x) {
//     int res = 0;
//     while ((1 << (res + 1)) <= x) res++;
//     return res;
// }
// void add(int u, int v,int w) {
//     tr[++tot].to = v;
//     tr[tot].nxt = head[u];
//     tr[tot].w=w;
//     head[u] = tot;
// }

// il bool cmp(Edge a,Edge b)
// {
//     return a.w>b.w;
// }
// //快排的依据（按边权排序）
// il int find(int x)
// {
//     while(x!=fa[x]) x=fa[x]=fa[fa[x]];
//     return x;
// }
// //并查集循环实现模板，及路径压缩，不懂并查集的同学可以戳一戳代码上方的“并查集详解”
// il void kruskal()
// {
//     int eu,ev;
//     sort(edge,edge+m,cmp);
//     //将边的权值排序
//     for(re int i=0;i<m;i++)
//     {
//         eu=find(edge[i].u), ev=find(edge[i].v);
//         if(eu==ev)
//         {
//             continue;
//         }
//         fa[eu]=ev;
//         add(edge[i].u,edge[i].v,edge[i].w);
//         add(edge[i].v,edge[i].u,edge[i].w);
//     }
// }
// void dfs(int x,int w,int f){
//     vis[x]=1;
//     if(f==0){
//         deep[x]=1;
//         st[x][0]=x;
//         stmin[x][0]=inf;
//     }else {
//         deep[x]=deep[f]+1;
//         st[x][0]=f;
//         stmin[x][0]=w;
//     }
//     for(int p=1;(1<<p)<=deep[x];p++){
//         st[x][p]=st[st[x][p-1]][p-1];;
//         stmin[x][p]=min(stmin[x][p-1],stmin[st[x][p-1]][p-1]);
//     }
//     for(int i=head[x];i;i=tr[i].nxt){
//         if(tr[i].to==f) continue;
//         if(!vis[tr[i].to]){
//             dfs(tr[i].to,tr[i].w,x);
//         }
//     }
// }
// int findlca(int a,int b){
//     int ans=inf;
//     if(find(a)!=find(b)) return -1;
//     if(deep[a]<deep[b]) swap(a,b);
//     for(int p=power;p>=0;p--){
//         if(deep[st[a][p]]>=deep[b]){
            
//             ans=min(stmin[a][p],ans);
//             a=st[a][p];
//         }
//     }
//     if(a==b) return ans;
//     for(int p=power;p>=0;p--){
//         if(st[a][p]!=st[b][p]){
//             ans=min({ans,stmin[a][p],stmin[b][p]});
//             a=st[a][p];
//             b=st[b][p];
//         }
//     } 
// ans = min(ans, stmin[a][0]);
// ans = min(ans, stmin[b][0]);
//     return ans;
// }
// int main()
// {
//     cin>>n>>m;
//     power=getLog2(n);
//     for(re int i=1;i<=n;i++)
//     {
//         fa[i]=i;
//     }
//     //初始化并查集
//     for(re int i=0;i<m;i++)
//     {
//         cin>>edge[i].u>>edge[i].v>>edge[i].w;
//     }
//     kruskal();
//     for(int i=1;i<=n;i++){
//         if(!vis[i]) dfs(i,0,0);
//     }
//     int q;
//     cin>>q;
//     while(q--){
//         int x,y;
//         cin>>x>>y;
//         cout<<findlca(x,y)<<endl;
//     }
//     return 0;
// }
