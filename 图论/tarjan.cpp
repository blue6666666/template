// //强连通分量求解
// 模板
// int dfn[N], low[N], dfncnt, s[N], in_stack[N], tp;
// int scc[N], sc;  // 结点 i 所在 SCC 的编号
// int sz[N];       // 强连通 i 的大小

// void tarjan(int u) {
//   low[u] = dfn[u] = ++dfncnt, s[++tp] = u, in_stack[u] = 1;
//   for (int i = h[u]; i; i = e[i].nex) {
//     const int &v = e[i].t;
//     if (!dfn[v]) {
//       tarjan(v);
//       low[u] = min(low[u], low[v]);
//     } else if (in_stack[v]) {
//       low[u] = min(low[u], dfn[v]);
//     }
//   }
//   if (dfn[u] == low[u]) {
//     ++sc;
//     do {
//       scc[s[tp]] = sc;
//       sz[sc]++;
//       in_stack[s[tp]] = 0;
//     } while (s[tp--] != u);
//   }
// }
//受欢迎的牛 https://loj.ac/p/10091
// #include <bits/stdc++.h>
// #define N 100010  // 定义数组最大长度，适配题目中N≤1e4的范围（留有余量）
// using namespace std;
// struct graph{
//     int t,nex;
// }e[N*2];
// //强连通分量求解
// int dfn[N], low[N], dfncnt, s[N], in_stack[N], tp,cnt=1,h[N*2];
// int scc[N], sc;  // 结点 i 所在 SCC 的编号
// int sz[N];       // 强连通 i 的大小
// int out[N];
// void add(int u,int v){
//     e[cnt].nex=h[u];
//     e[cnt].t=v;
//     h[u]=cnt++;
// }
// void tarjan(int u) {
//   low[u] = dfn[u] = ++dfncnt, s[++tp] = u, in_stack[u] = 1;
//   for (int i = h[u]; i; i = e[i].nex) {
//     const int &v = e[i].t;
//     if (!dfn[v]) {
//       tarjan(v);
//       low[u] = min(low[u], low[v]);
//     } else if (in_stack[v]) {
//       low[u] = min(low[u], dfn[v]);
//     }
//   }
//   if (dfn[u] == low[u]) {
//     ++sc;
//     do {
//       scc[s[tp]] = sc;
//       sz[sc]++;
//       in_stack[s[tp]] = 0;
//     } while (s[tp--] != u);
//   }
// }
// int main() {
//     // 输入：奶牛数量n，爱慕关系数量m
//     int n,m,a,b;
//     cin >> n >> m;

//     // 读入m条爱慕关系：A喜欢B → 建边A→B
//     while (m--) {
//         cin >> a >> b;
//         add(a,b);
//     }

//     // 对所有未遍历的节点执行Tarjan算法，找出所有强连通分量
//     for (int i = 1; i <= n; i++) {
//         if (dfn[i] == 0) { // dfn[i]=0表示i未被访问
//             tarjan(i);
//         }
//     }

//     // 步骤1：统计每个强连通分量的大小（h[分量编号] = 该分量的奶牛数）
//     // 步骤2：计算缩点后每个分量的出度（out[分量编号]）
//     for (int i = 1; i <= n; i++) {
//         // 遍历i的所有邻接节点v
//         for (int j = h[i]; j; j=e[j].nex) {
//             int v = e[j].t;
//             // 如果i和v属于不同的强连通分量 → 说明缩点后i的分量有一条出边到v的分量
//             if (scc[i]!=scc[v]) {
//                 out[scc[i]]++;  // i所属分量的出度+1
//             }
//         }
// }

//     // 步骤3：寻找缩点后出度为0的强连通分量
//     int t = 0, ans = 0;  // t：出度为0的分量数量；ans：答案（明星奶牛数）

//     for (int i = 1; i <= sc; i++) {
//         if (out[i] == 0) { // 找到出度为0的分量
//             t++;           // 计数+1
//             ans = sz[i];    // 记录该分量的大小（候选答案）
//         }
//     }

//     // 关键结论：
//     // - 如果出度为0的分量数量≠1 → 没有明星奶牛（输出0）
//     // - 如果出度为0的分量数量=1 → 该分量的所有奶牛都是明星（输出分量大小）
//     if (t != 1) {
//         cout << 0 << endl;
//         return 0;
//     }

//     cout << ans << endl;

//     return 0;
// }
//P2812
#include<bits/stdc++.h>
using namespace std;
struct graph{
    int t,nex;
}e[50010];
int n;
int head[10010],cnt=1;
int dfn[10010],low[10010],dfncnt,s[10010],sc,tp,scc[10010],sz[10010],instack[10010];
int cd[10010],rd[10010],ans1,ans2;
void add(int u,int v){
    e[cnt].t=v;
    e[cnt].nex=head[u];
    head[u]=cnt++;
}
void tarjan(int u){
    low[u]=dfn[u]=++dfncnt;
    s[++tp]=u;
    instack[u]=1;
    for(int i=head[u];i;i=e[i].nex){
        int v=e[i].t;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }else if(instack[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(dfn[u]==low[u]){
        sc++;
        do{
            sz[sc]++;
            scc[s[tp]]=sc;
            instack[s[tp]]=0;   
        }while(s[tp--]!=u);
    }
}

int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        while(x!=0){
            add(i,x);
            cin>>x;
        }
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=head[i];j;j=e[j].nex){
            int v=e[j].t;
            if(scc[i]!=scc[v]){
                cd[scc[i]]++;
                rd[scc[v]]++;
            }
        }
    }
    for(int i=1;i<=sc;i++){
        if(cd[i]==0) ans1++;
        if(rd[i]==0) ans2++;
    }
    if(sc==1) cout<<1<<endl<<0;
    else cout<<ans2<<endl<<max(ans1,ans2);
}