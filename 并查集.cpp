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