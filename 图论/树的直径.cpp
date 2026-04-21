//树上最远的两个点的距离
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=5e5+10;
int head[maxn*2],tot=1,n;
struct tree{
    int t,n,w;
}tr[maxn*2];
void add(int u,int v,int w){
    tr[++tot].t=v;
    tr[tot].n=head[u];
    tr[tot].w=w;
    head[u]=tot;
}
void build(){
    tot=1;
    memset(head,0,sizeof(head));
}
//1 两遍dfs
//不能有负边，能够得到具体两点
// int start,en,dis[maxn],last[maxn];
// void dfs(int u,int f,int w){
//     last[u]=f;
//     dis[u]=dis[f]+w;
//     for(int ei=head[u];ei;ei=tr[ei].n){
//         if(tr[ei].t!=f){
//             dfs(tr[ei].t,u,tr[ei].w);
//         }
//     }
// }
// int main()
// {
//     cin>>n;
//     build();
//     for(int i=1;i<n;i++){
//         int u,v,w;
//         cin>>u>>v>>w;
//         add(u,v,w);
//         add(v,u,w);
//     }
//     dfs(1,0,0);
//     start=1;
//     for(int i=1;i<=n;i++){
//         if(dis[i]>dis[start]){
//             start=i;
//         }
//     }
//     dfs(start,0,0);
//     en=1;
//     for(int i=1;i<=n;i++){
//         if(dis[i]>dis[en]){
//             en=i;
//         }
//     }
//     //cout<<start<<' '<<en<<endl;
//     cout<<dis[en]<<endl;
// }
// 2 树形dp
//不能得到具体的两点
// int dis[maxn],ans[maxn];
// void dp(int u,int f){
//     for(int ei=head[u];ei;ei=tr[ei].n){
//         int v=tr[ei].t,w=tr[ei].w;;
//         if(f!=v){
//             dp(v,u);
//             ans[u]=max(ans[u],dis[u]+dis[v]+w);
//             dis[u]=max(dis[u],dis[v]+w);
//         }

//     }
// }
// int main(){
//     cin>>n;
//     build();
//     for(int i=1;i<n;i++){
//         int u,v,w;
//         cin>>u>>v>>w;
//         add(u,v,w);
//         add(v,u,w);
//     }
//     int Ans=0;
//     dp(1,0);
//     for(int i=1;i<=n;i++){
//         Ans=max(Ans,ans[i]);
//     }
//     cout<<Ans<<endl;
// }

// 3  如和求所有直径的公共部分，使用方法一
ll start,en,dis[maxn],last[maxn];
bool path[maxn];
ll coedge;
void dfs(int u,int f,int w){
    last[u]=f;
    dis[u]=dis[f]+w;
    for(int ei=head[u];ei;ei=tr[ei].n){
        if(tr[ei].t!=f){
            dfs(tr[ei].t,u,tr[ei].w);
        }
    }
}
ll maxdis(int u,int f,ll c){
    ll ans=c;
    for(int ei=head[u];ei;ei=tr[ei].n){
        if(tr[ei].t!=f&&!path[tr[ei].t]){
            ans=max(ans,maxdis(tr[ei].t,u,c+tr[ei].w));
        }
    }
    return ans;
} 
int main()
{
    cin>>n;
    build();
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
        add(v,u,w);
    }
    dfs(1,0,0);
    start=1;
    for(int i=1;i<=n;i++){
        if(dis[i]>dis[start]){
            start=i;
        }
    }
    dfs(start,0,0);
    en=1;
    for(int i=1;i<=n;i++){
        if(dis[i]>dis[en]){
            en=i;
        }
    }
    for(int i=en;i;i=last[i]){
        path[i]=1;
    }
    int l=start,r=en;
    ll maxd;
    for(int i=last[en];i!=start;i=last[i]){
        maxd=maxdis(i,0,0);
        if(maxd==dis[en]-dis[i]){
            r=i;
        }
        if(maxd==dis[i]&&l==start){
            l=i;
        }
    }
    for(int i=r;i!=l;i=last[i]) coedge++;
    cout<<dis[en]<<endl<<coedge;
}