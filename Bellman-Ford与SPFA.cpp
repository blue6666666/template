//没有优化的Bellman-Ford
//每一轮操作都把所有边带入进去，看距离是否变化，若不变化，就停止
//最多n-1轮，因此时间复杂度为O（n*m）
//适用于单源点，找最短路问题
//可以判断从某个点出发会不会遇到负环，若轮数超过n-1，就经过负环
//单独的Bellman-Ford不会单独使用
//一般要和SPFA优化
//SPFA只做到了常数级优化，仍然为O（n*m）
//因此没有负边时，仍然使用dijkstra

//判断是否存在负环，P3385
#include<bits/stdc++.h>
using namespace std; 
const int maxn=2010,maxm=3010,inf=1e8;
int head[maxm<<1],n,m,cnt,upfill[maxn],dis[maxn],t;
queue<int>q;
bool enter[maxn];
struct graph{
    int next,to,w;
}g[maxm<<1];
void add(int u,int v,int w){
    g[cnt].next=head[u];
    g[cnt].to=v;
    g[cnt].w=w;
    head[u]=cnt++;
}
void build(int n){
    cnt=1;
    while(!q.empty()) q.pop();
    for(int i=1;i<=n;i++){
        head[i]=0;
        upfill[i]=0;
        dis[i]=inf;
        enter[i]=0;
    }
}
bool spfa(){
    dis[1]=0;
    upfill[1]++;
    q.push(1);
    enter[1]=true;
    while(!q.empty()){
        int x=q.front();
        q.pop();
        enter[x]=false;
        for(int ei=head[x];ei;ei=g[ei].next){
            int v=g[ei].to;
            int w=g[ei].w;
            if(dis[x]+w<dis[v]){
                dis[v]=dis[x]+w;
                if(!enter[v]){
                    if(upfill[v]++==n){
                        return true;
                    }
                }
                enter[v]=true;
                q.push(v);
            }
        }
    }
    return false;
}
void solve(){
    cin>>n>>m;
    build(n);
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        if(w>=0){
            add(u,v,w);
            add(v,u,w);
        } 
        else add(u,v,w);
    }
    if(spfa()) cout<<"YES"<<endl;
    else cout<<"NO"<<endl; 
}
int main(){
    cin>>t;
    while(t--){
        solve();
    }
}

