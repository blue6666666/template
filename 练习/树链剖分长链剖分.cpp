// //根据树的高度来找链
// //长链剖分往上跳O（sqrt（n））
// //对每条长链都建立和子树高度有关的信息整体复杂度为O（n）

// //5903
// #include<bits/stdc++.h>
// using namespace std;
// const int maxn=5e5+10;
// int head[maxn<<1],nex[maxn<<1],to[maxn<<1],tot;
// int dep[maxn],st[maxn][30],top[maxn],down[maxn],up[maxn],len[maxn],son[maxn],dfncnt,dfn[maxn];
// int n,m,high[maxn],root;
// int maxh=30;
// #define ui unsigned int
// ui s;

// inline ui get(ui x) {
// 	x ^= x << 13;
// 	x ^= x >> 17;
// 	x ^= x << 5;
// 	return s = x; 
// }

// void add(int u,int v){
//     nex[++tot]=head[u];
//     to[tot]=v;
//     head[u]=tot;
// }
// void setup(int u,int i,int v){
//     up[dfn[u]+i]=v;
// }
// int getup(int u,int i){
//     return up[dfn[u]+i];
// }
// void setdown(int u,int i,int v){
//     down[dfn[u]+i]=v;
// }
// int getdown(int u,int i){
//     return down[dfn[u]+i];
// }
// void dfs1(int u,int f){
//     st[u][0]=f;
//     dep[u]=dep[f]+1;
//     for(int p=1;p<maxh;p++){
//         st[u][p]=st[st[u][p-1]][p-1];
//     }
//     for(int ei=head[u];ei;ei=nex[ei]){
//         int v=to[ei];
//         if(v==f) continue;
//         dfs1(v,u);
//         if(son[u]==0||len[son[u]]<len[v]){
//             son[u]=v;
//         }
//     }
//     len[u]=len[son[u]]+1;
// }
// void dfs2(int u,int topf){
//     top[u]=topf;
//     dfn[u]=++dfncnt;
//     if(son[u]==0) return;
//     dfs2(son[u],topf);
//     for(int ei=head[u];ei;ei=nex[ei]){
//         int v=to[ei];
//         if(v==st[u][0]||v==son[u]) continue;
//         dfs2(v,v);
//     }
// }
// void prepare(){
//     dfs1(root,0);
//     dfs2(root,root);
//     high[0]=-1;
//     for(int i=1;i<=n;i++){
//         high[i]=high[i/2]+1;
//     }
//     for(int i=1;i<=n;i++){
//         if(top[i]==i){
//             int a=i,b=i;
//             for(int j=0;j<len[i];j++){
//                 setup(i,j,a);
//                 setdown(i,j,b);
//                 a=st[a][0];
//                 b=son[b];
//             }
//         }
//     }
// }
// int query(int x,int k){
//     if(k==0) return x;
//     if(k==1<<high[k]){
//         return st[x][high[k]];
//     }
//     x=st[x][high[k]];
//     k-=1<<high[k];
//     k-=dfn[x]-dfn[top[x]];
//     x=top[x];
//     return (k>=0)?getup(x,k):getdown(x,-k);
// }
// int main(){
//     cin>>n>>m>>s;
//     for(int i=1;i<=n;i++){
//         int f;
//         cin>>f;
//         if(f==0) root=i;
//         else add(f,i);
//     }    
//     prepare();
//     long long ans=0,last=0;
//     for(int i=1,x,k;i<=m;i++){
//         x=(int)((get(s)^last)%n+1);
//         k=(int)((get(s)^last)%dep[x]);
//         last=query(x,k);
//         ans^=1LL*i*last;
        
//     }
//     cout<<ans;
// }


//10641
// #include<bits/stdc++.h>
// using namespace std;
// #define int long long
// const int maxn=2e5+10;
// int head[maxn],nex[maxn],to[maxn],tot;
// int a[maxn];
// int top[maxn],fa[maxn],son[maxn];
// int n,k;
// void add(int u,int v){
//     nex[++tot]=head[u];
//     head[u]=tot;
//     to[tot]=v;
// }
// void dfs1(int u,int f){
//     for(int ei=head[u];ei;ei=nex[ei]){
//         int v=to[ei];
//         if(v==f) continue;
//         dfs1(v,u);
//         if(!son[u]||a[son[u]]<a[v]){
//             son[u]=v;
//         }
//     }
//     a[u]+=a[son[u]];
// }
// void dfs2(int u,int topf){
//     top[u]=topf;
//     if(!son[u]) return;
//     dfs2(son[u],topf);
//     for(int ei=head[u];ei;ei=nex[ei]){
//         int v=to[ei];
//         if(v==fa[u]||v==son[u]) continue;
//         dfs2(v,v);
//     }   
// }
// bool cmp(int a,int b){
//     return a>b;
// }
// signed main(){
//     cin>>n>>k;
//     for(int i=1;i<=n;i++){
//         cin>>a[i];
//     }
//     for(int i=1;i<n;i++){
//         int u,v;
//         cin>>u>>v;
//         add(u,v);
//         fa[v]=u;
//     }
//     int r;
//     for(int i=1;i<=n;i++){
//         if(!fa[i]) {r=i; break;}
//     }
//     dfs1(r,0);
//     dfs2(r,r);
//     vector<int>ans;
//     for(int i=1;i<=n;i++){
//         if(top[i]==i){
//             ans.push_back(a[i]);
//         }
//     }
//     sort(ans.begin(),ans.end(),cmp);
//     int aa=0;
//     for(int i=0;i<min((int)ans.size(),k);i++){
//         aa+=ans[i];
//     }
//     cout<<aa<<endl;
// }

//CF1009F
// #include<bits/stdc++.h>
// using namespace std;
// const int maxn=1e6+10;
// int head[maxn<<1],nex[maxn<<1],to[maxn<<1],tot;
// int len[maxn],dfn[maxn],son[maxn],dfncnt,top[maxn],fa[maxn],dep[maxn];
// int n,dp[maxn],ans[maxn];
// void add(int u,int v){
//     nex[++tot]=head[u];
//     to[tot]=v;
//     head[u]=tot;
// }
// void setdp(int u,int i,int v){
//     dp[dfn[u]+i]=v;
// }
// int  getdp(int u,int i){
//     return dp[dfn[u]+i];
// }
// void dfs1(int u,int f){
//     dep[u]=dep[f]+1;
//     fa[u]=f;
//     for(int ei=head[u];ei;ei=nex[ei]){
//         int v=to[ei];
//         if(v==f) continue;
//         dfs1(v,u);
//         if(son[u]==0||len[son[u]]<len[v]){
//             son[u]=v;
//         }
//     }
//     len[u]=len[son[u]]+1;
// }
// void dfs2(int u,int topf){
//     top[u]=topf;
//     dfn[u]=++dfncnt;
//     setdp(u,0,1);
//     ans[u]=0;
//     if(son[u]==0) return;
//     dfs2(son[u],topf);
//     for(int ei=head[u];ei;ei=nex[ei]){
//         int v=to[ei];
//         if(v==fa[u]||v==son[u]) continue;
//         dfs2(v,v);
//     }
//     ans[u]=ans[son[u]]+1;
//     for(int ei=head[u];ei;ei=nex[ei]){
//         int v=to[ei];
//         if(v==fa[u]||v==son[u]) continue;
//         for(int i=1;i<=len[v];i++){
//             setdp(u,i,getdp(u,i)+getdp(v,i-1));
//             if(getdp(u,i)>getdp(u,ans[u])||(getdp(u,i)==getdp(u,ans[u])&&i<ans[u])){
//                 ans[u]=i;
//             }
//         }
//     }
//     if(getdp(u,ans[u])==1){
//         ans[u]=0;
//     }   
// }
// int main(){
//     cin>>n;
//     for(int i=1,u,v;i<n;i++){
//         cin>>u>>v;
//         add(u,v);
//         add(v,u);
//     }
//     dfs1(1,0);
//     dfs2(1,1);
//     for(int i=1;i<=n;i++){
//         cout<<ans[i]<<endl;
//     }
// }

