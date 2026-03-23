// #include<bits/stdc++.h>
// using namespace std;
// const int maxn=1e5+10;
// int n,m;
// int dfn[maxn],low[maxn],dfncnt,cutedge[maxn<<1],tot=1,head[maxn<<1],ans1;
// struct graph{
//     int t,nex;
// }e[maxn<<1];
// void add(int u,int v){
//     e[++tot].t=v;
//     e[tot].nex=head[u];
//     head[u]=tot;
// }
// void tarjan(int u,int pre) {
//   low[u] = dfn[u] = ++dfncnt;
//   for (int ei = head[u]; ei; ei = e[ei].nex) {
//     if((ei^1)==pre) continue;
//     const int &v = e[ei].t;
//     if (!dfn[v]) {
//       tarjan(v,ei);
      
//       low[u] = min(low[u], low[v]);
//       if(low[v]>dfn[u]){
//         cutedge[ei>>1]=1;//无向图割边
//         ans1++;
//       }
//     } else  {
//       low[u] = min(low[u], dfn[v]);
//     }
//   }
// }
// int main(){
//     cin>>n>>m;
//     for(int i=1;i<=m;i++){
//         int u,v;
//         cin>>u>>v;
//         add(u,v);
//         add(v,u);
//     }
//     for(int i=1;i<=n;i++){
//         if(!dfn[i]) tarjan(i,0);
//     }
//     cout<<ans1<<endl;
//     for(int i=1;i<=m;i++){
//         if(cutedge[i]) cout<<i<<' ';
//     }
// }
