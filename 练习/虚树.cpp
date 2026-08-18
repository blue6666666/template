// //二次排序+lca连边
// #include<bits/stdc++.h>
// using namespace std;
// const int maxn=1e5+10;
// int h[maxn<<1],ne[maxn<<1],to[maxn<<1],tot1;//初始树
// int n,q,k;
// int hn[maxn<<1],nn[maxn<<1],tn[maxn<<1],tot2;//新树
// int dep[maxn],st[maxn][20],dfn[maxn],dfncnt;
// vector<int>arr,tmp;//关键点
// bool iskey[maxn];
// int cost[maxn],siz[maxn];
// bool cmp(int x,int y){
//     return dfn[x]<dfn[y];
// }
// void add1(int u,int v){
//     ne[++tot1]=h[u];
//     to[tot1]=v;
//     h[u]=tot1;
// }
// void add2(int u,int v){
//     nn[++tot2]=hn[u];
//     tn[tot2]=v;
//     hn[u]=tot2;
// }
// void dfs(int u,int f){
//     dep[u]=dep[f]+1;
//     dfn[u]=++dfncnt;
//     st[u][0]=f;
//     for(int i=1;i<20;i++){
//         st[u][i]=st[st[u][i-1]][i-1];
//     }
//     for(int e=h[u];e;e=ne[e]){
//         int v=to[e];
//         if(v==f) continue;
//         dfs(v,u);
//     }
// }
// int getlca(int u,int v){
//     if(dep[u]!=dep[v]){
//         if(dep[u]<dep[v]) swap(u,v);
//         for(int p=19;p>=0;p--){
//             if(dep[st[u][p]]>=dep[v]){
//                 u=st[u][p];
//             }
//         }
//     }
//     if(u==v) return u;
//     for(int p=19;p>=0;p--){
//         if(st[u][p]!=st[v][p]){
//             u=st[u][p];
//             v=st[v][p];
//         }
//     }
//     return st[u][0];
// }
// int buildvtree(){
//     sort(arr.begin(),arr.end(),cmp);
//     tmp=arr;
//     for(int i=0;i<(int)arr.size()-1;i++){
//         tmp.push_back(getlca(arr[i],arr[i+1]));
//     }
//     sort(tmp.begin(),tmp.end(),cmp);
//     tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());
//     tot2=0;
//     for(int i=0;i<(int)tmp.size();i++){
//         hn[tmp[i]]=0;
//     }
//     for(int i=0;i<tmp.size()-1;i++){
//         add2(getlca(tmp[i],tmp[i+1]),tmp[i+1]);
//     }
//     return tmp[0];
// }
// void dp(int u){
//     cost[u]=siz[u]=0;
//     for(int e=hn[u];e;e=nn[e]){
//         int v=tn[e];
//         dp(v);
//         cost[u]+=cost[v];
//         siz[u]+=siz[v];
//     }
//     if(iskey[u]){
//         cost[u]+=siz[u];
//         siz[u]=1;
//     }else if(siz[u]>1){
//         cost[u]++;
//         siz[u]=0;
//     }

// }
// int compute(){
//     for(int i=0;i<k;i++){
//         iskey[arr[i]]=1;
//     }
//     bool flag=0;
//     for(int i=0;i<k;i++){
//         if(iskey[st[arr[i]][0]]){
//             flag=1;
//             break;
//         }
//     }
//     int ans=-1;
//     if(!flag){
//         int root=buildvtree();
//         dp(root);
//         ans=cost[root];
//     }
//     for(int i=0;i<k;i++){
//         iskey[arr[i]]=0;
//     }
//     return ans;
// }
// int main(){
//     cin>>n;
//     for(int i=1;i<n;i++){
//         int u,v;
//         cin>>u>>v;
//         add1(u,v);
//         add1(v,u);
//     }
//     dfs(1,0);
//     cin>>q;
//     while(q--){
//         cin>>k;
//         arr.clear();
//         arr.resize(k);
//         for(int i=0;i<k;i++){
//             cin>>arr[i];
//         }
//         cout<<compute()<<endl;
//     }
// }

//4103
//二次排序+lca连边
// #include<bits/stdc++.h>
// using namespace std;
// const int maxn=1e6+10;
// const long long inf=100000000000;
// int h[maxn<<1],ne[maxn<<1],to[maxn<<1],tot1;//初始树
// int n,q,k;
// int hn[maxn<<1],nn[maxn<<1],tn[maxn<<1],tot2;//新树
// int dep[maxn],st[maxn][20],dfn[maxn],dfncnt;
// vector<int>arr,tmp;//关键点
// bool iskey[maxn];
// long long sum[maxn],siz[maxn],near[maxn],far[maxn],mx,mn,cost;
// bool cmp(int x,int y){
//     return dfn[x]<dfn[y];
// }
// void add1(int u,int v){
//     ne[++tot1]=h[u];
//     to[tot1]=v;
//     h[u]=tot1;
// }
// void add2(int u,int v){
//     nn[++tot2]=hn[u];
//     tn[tot2]=v;
//     hn[u]=tot2;
// }
// void dfs(int u,int f){
//     dep[u]=dep[f]+1;
//     dfn[u]=++dfncnt;
//     st[u][0]=f;
//     for(int i=1;i<20;i++){
//         st[u][i]=st[st[u][i-1]][i-1];
//     }
//     for(int e=h[u];e;e=ne[e]){
//         int v=to[e];
//         if(v==f) continue;
//         dfs(v,u);
//     }
// }
// int getlca(int u,int v){
//     if(dep[u]!=dep[v]){
//         if(dep[u]<dep[v]) swap(u,v);
//         for(int p=19;p>=0;p--){
//             if(dep[st[u][p]]>=dep[v]){
//                 u=st[u][p];
//             }
//         }
//     }
//     if(u==v) return u;
//     for(int p=19;p>=0;p--){
//         if(st[u][p]!=st[v][p]){
//             u=st[u][p];
//             v=st[v][p];
//         }
//     }
//     return st[u][0];
// }
// int buildvtree(){
//     sort(arr.begin(),arr.end(),cmp);
//     tmp=arr;
//     for(int i=0;i<(int)arr.size()-1;i++){
//         tmp.push_back(getlca(arr[i],arr[i+1]));
//     }
//     sort(tmp.begin(),tmp.end(),cmp);
//     tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());
//     tot2=0;
//     for(int i=0;i<(int)tmp.size();i++){
//         hn[tmp[i]]=0;
//     }
//     for(int i=0;i<(int)tmp.size()-1;i++){
//         add2(getlca(tmp[i],tmp[i+1]),tmp[i+1]);
//     }
//     return tmp[0];
// }
// void dp(int u){
//     siz[u]=iskey[u]?1:0;
//     sum[u]=0;
//     if(iskey[u]){
//         far[u]=near[u]=0;
//     }else {
//         far[u]=-inf,near[u]=inf;
//     }
//     for(int e=hn[u];e;e=nn[e]){
//         int v=tn[e];
//         dp(v);
//         long long len=dep[v]-dep[u];
//         cost+=sum[u]*siz[v]+len*siz[v]*siz[u]+sum[v]*siz[u];
//         sum[u]+=sum[v]+len*siz[v];
//         siz[u]+=siz[v];
//         mn=min(mn,near[u]+near[v]+len);
//         mx=max(mx,far[u]+far[v]+len);
//         near[u]=min(near[u],near[v]+len);
//         far[u]=max(far[u],far[v]+len);
//     }
// }
// void compute(){
//     for(int i=0;i<(int)arr.size();i++) {
//         iskey[arr[i]]=1;
//     }
//     cost=0;
//     mx=-inf;
//     mn=inf;
//     if(k==1){
//         cout<<0<<' '<<0<<' '<<0<<endl;
//         return;
//     }
//     int root=buildvtree();
//     dp(root);
//     cout<<cost<<' '<<mn<<' '<<mx<<endl;
//     for(int i=0;i<(int)arr.size();i++) {
//         iskey[arr[i]]=0;
//     }
// }
// int main(){
//     cin>>n;
//     for(int i=1;i<n;i++){
//         int u,v;
//         cin>>u>>v;
//         add1(u,v);
//         add1(v,u);
//     }
//     dfs(1,0);
//     cin>>q;
//     while(q--){
//         cin>>k;
//         arr.clear();
//         arr.resize(k);
//         for(int i=0;i<k;i++){
//             cin>>arr[i];
            
//         }
//         compute();
//     }
// }

//2495

#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+10;
const long long inf=100000000000;
int h[maxn<<1],ne[maxn<<1],to[maxn<<1],ww[maxn<<1],tot1;//初始树
int n,q,k;
int hn[maxn<<1],nn[maxn<<1],tn[maxn<<1],wn[maxn<<1],tot2;//新树
int dep[maxn],st[maxn][20],dfn[maxn],dfncnt;
vector<int>arr,tmp;//关键点
bool iskey[maxn];
long long cost[maxn],stw[maxn][20];
bool cmp(int x,int y){
    return dfn[x]<dfn[y];
}
void add1(int u,int v,int w){
    ne[++tot1]=h[u];
    to[tot1]=v;
    ww[tot1]=w;
    h[u]=tot1;
}
void add2(int u,int v,int w){
    nn[++tot2]=hn[u];
    tn[tot2]=v;
    wn[tot2]=w;
    hn[u]=tot2;
}
void dfs(int u,int f,long long w){
    dep[u]=dep[f]+1;
    dfn[u]=++dfncnt;
    st[u][0]=f;
    stw[u][0]=w;
    for(int i=1;i<20;i++){
        st[u][i]=st[st[u][i-1]][i-1];
        stw[u][i]=min(stw[u][i-1],stw[st[u][i-1]][i-1]);
    }
    for(int e=h[u];e;e=ne[e]){
        int v=to[e];
        long long w=ww[e];
        if(v==f) continue;
        dfs(v,u,w);
    }
}
int getlca(int u,int v){
    if(dep[u]!=dep[v]){
        if(dep[u]<dep[v]) swap(u,v);
        for(int p=19;p>=0;p--){
            if(dep[st[u][p]]>=dep[v]){
                u=st[u][p];
            }
        }
    }
    if(u==v) return u;
    for(int p=19;p>=0;p--){
        if(st[u][p]!=st[v][p]){
            u=st[u][p];
            v=st[v][p];
        }
    }
    return st[u][0];
}
long long getminedge(int u,int v){
    long long dis=inf;
    for(int p=19;p>=0;p--){
        if(dep[st[u][p]]>=dep[v]){
            dis=min(dis,stw[u][p]);
            u=st[u][p];
        }
    }
    return dis;
}
int buildvtree(){
    sort(arr.begin(),arr.end(),cmp);
    tmp=arr;
    tmp.push_back(1);
    for(int i=0;i<(int)arr.size()-1;i++){
        tmp.push_back(getlca(arr[i],arr[i+1]));
    }

    sort(tmp.begin(),tmp.end(),cmp);
    tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());
    tot2=0;
    for(int i=0;i<(int)tmp.size();i++){
        hn[tmp[i]]=0;
    }
    for(int i=0;i<(int)tmp.size()-1;i++){
        int lca=getlca(tmp[i],tmp[i+1]);
        add2(lca,tmp[i+1],getminedge(tmp[i+1],lca));
    }
    return tmp[0];
}
void dp(int u){
    if(iskey[u]){
        cost[u]=0;
        return;
    }
    cost[u]=0;
    for(int e=hn[u];e;e=nn[e]){
        int v=tn[e];
        long long w=wn[e];
        dp(v);
        if(iskey[v]){
            cost[u]+=w;
        }else {
            cost[u]+=min(w,1LL*cost[v]);
        }
    }
}
void compute(){
    for(int i=0;i<(int)arr.size();i++) {
        iskey[arr[i]]=1;
    }
    int root=buildvtree();
    dp(root);
    cout<<cost[root]<<endl;
    for(int i=0;i<(int)arr.size();i++) {
        iskey[arr[i]]=0;
    }
}
int main(){
    for (int j = 0; j < 20; ++j) stw[0][j] = inf;
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        add1(u,v,w);
        add1(v,u,w);
    }
    dfs(1,0,inf);
    cin>>q;
    while(q--){
        cin>>k;
        arr.clear();
        arr.resize(k);
        for(int i=0;i<k;i++){
            cin>>arr[i];
        }
        compute();
    }
}