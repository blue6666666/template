#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
struct node{
	int next,to;
}e[N<<1];
int tot,head[N];
int dep[N],siz[N],hson[N],fa[N];
int top[N];
int n,m,s;
void add(int x,int y){
	e[++tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
}
void dfs1(int x,int f){
	siz[x]=1;
	fa[x]=f;
	dep[x]=dep[f]+1;
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].to;
		if(y!=f){
			dfs1(y,x);
			siz[x]+=siz[y];
			if(siz[hson[x]]<siz[y] || !hson[x]){
				hson[x]=y;
			}
		}
	}
}
void dfs2(int x,int t){
	top[x]=t;
	if(!hson[x])return ;
	dfs2(hson[x],t);
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].to;
		if(y!=fa[x] && y!=hson[x]){
			dfs2(y,y);
		}
	}
}
int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]){
			swap(x,y);
		}
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n>>m>>s;
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		add(x,y);
		add(y,x);
	}
	dfs1(s,0);
	dfs2(s,s);
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		cout<<LCA(a,b)<<'\n';
	}
	return 0;
}
/*
#include<bits/stdc++.h>
using namespace std;

const int MN=5e5+10;
int fa[MN],vis[MN],ans[MN],n,m,s;
vector<int> v[MN];
vector<pair<int,int>> ask[MN];

int find(int x){
    if(fa[x]!=x) fa[x]=find(fa[x]);
    return fa[x];
}

void merge(int x,int y){
    x=find(x);
    y=find(y);
    fa[x]=y;
}

void tarjan(int x){
    vis[x]=true;

    for(int i=0;i<v[x].size();i++){
        int y=v[x][i];

        if(vis[y]) continue;//无向图 防止遍历自己爹

        tarjan(y);
        merge(y,x);
    }

    for(int i=0;i<ask[x].size();i++){
        int y=ask[x][i].first;
        int id=ask[x][i].second;
        if(vis[y]) ans[id]=find(y);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    for(int i=1;i<MN;i++) fa[i]=i;//初始化并查集
    
    cin>>n>>m>>s;

    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }

    for(int i=1;i<=m;i++){
        int a,b;
        cin>>a>>b;

        if(a==b) ans[i]=a;
        else{
            ask[a].push_back({b,i});
            ask[b].push_back({a,i});
        } 
    }

    tarjan(s);

    for(int i=1;i<=m;i++){
        cout<<ans[i]<<"\n";
    }
    return 0;
}

*/
/*
倍增LCA

inline int lca(int u,int v)
{
	int deepu=deep[u],deepv=deep[v];
	if(deepu!=deepv)//先跳到同一深度
	{
		if(deep[u]<deep[v])
		{
			swap(u,v);
			swap(deepu,deepv);
		}
		int d=deepu-deepv;
		for(int i=0;i<=log2n;i++)
			if((1<<i)&d)u=fa[u][i];
	}
	if(u==v)return u;
	for(int i=log2n;i>=0;i--)
	{
		if(deep[fa[u][i]]<=0)continue;
		if(fa[u][i]==fa[v][i])continue;
		else u=fa[u][i],v=fa[v][i];//因为我们要跳到它们LCA的下面一层，所以它们肯定不相等，如果不相等就跳过去。
	}
	return fa[u][0];
}
*/