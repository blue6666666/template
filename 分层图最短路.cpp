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