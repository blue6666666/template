#include<bits/stdc++.h>
using namespace std;
const int maxn =1e5+10;
const int maxm =2*maxn;
const int maxk =3*maxn;
const int maxh =20;
struct edge{
    int u,v,w;
}e[maxk];
int n,m;
int fa[maxk],head[maxk],tot=1;
struct graph{
    int t,n;
}g[maxk];
void add(int u,int v){
    g[++tot].n=head[u];
    g[tot].t=v;
    head[u]=tot;
}
int nodekey[maxk];//kruskal节点权值
int cntu; //重构树上点的数量
int dep[maxk],st[maxk][maxh];
int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
bool cmp(edge x,edge y){
    return x.w<y.w;
}
void kruskalbuild(){
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    sort(e+1,e+m+1,cmp);
    cntu=n;
    for(int i=1,fx,fy;i<=m;i++){
        fx=find(e[i].u);
        fy=find(e[i].v);
        if(fx!=fy){
            fa[fx]=fa[fy]=++cntu;
            fa[cntu]=cntu;
            nodekey[cntu]=e[i].w;
            add(cntu,fx);
            add(cntu,fy);
        }
    }
}
void dfs(int u,int f){
    st[u][0]=f;
    dep[u]=dep[f]+1;
    for(int p=1;p<maxh;p++){
        st[u][p]=st[st[u][p-1]][p-1];
    }
    for(int e=head[u];e;e=g[e].n){
        dfs(g[e].t,u);
    }
}
int lca(int u,int v)
{
	
	if(dep[u]<dep[v])
	{
		swap(u,v);
	}
	for(int p=maxh-1;p>=0;p--){
        if(dep[st[u][p]]>=dep[v]){
            u=st[u][p];
        }
    }
	
	if(u==v)return u;
	for(int p=maxh-1;p>=0;p--)
	{
		if(st[u][p]!=st[v][p]){
            u=st[u][p];
            v=st[v][p];
        }
	}
	return st[u][0];
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>e[i].u>>e[i].v>>e[i].w;
    }
    kruskalbuild();
    for(int i=1;i<=cntu;i++){
        if(fa[i]==i) dfs(i,0);
    }
    int q;
    cin>>q;
    while(q--){
        int u,v;
        cin>>u>>v;
        if(find(u)!=find(v)){
            cout<<"impossible"<<endl;
        }else cout<<nodekey[lca(u,v)]<<endl;
    }
}