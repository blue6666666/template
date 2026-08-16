//二次排序+lca连边
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int h[maxn<<1],ne[maxn<<1],to[maxn<<1],tot1;//初始树
int n,q,k;
int hn[maxn],nn[maxn],tn[maxn],tot2;//新树
int dep[maxn],st[maxn][20],dfn[maxn],dfncnt;
vector<int>arr,tmp;//关键点
bool cmp(int x,int y){
    return dfn[x]<dfn[y];
}
void add1(int u,int v){
    ne[++tot1]=h[u];
    to[tot1]=v;
    h[u]=tot1;
}
void add2(int u,int v){
    nn[++tot2]=hn[u];
    tn[tot2]=v;
    hn[u]=tot2;
}

void buildvtree(){
    sort(arr.begin(),arr.end(),cmp);
    tmp=arr;
    for(int i=0;i<(int)arr.size()-1;i++){
        tmp.push_back(getlca(arr[i],arr[i+1]));
    }
    sort(tmp.begin(),tmp.end(),cmp);
    tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());
    tot2=0;
    for(int i=0;i<(int)tmp.size();i++){
        hn[tmp[i]]=0;
    }
    for(int i=0;i<tmp.size()-1;i++){
        add2(getlca(tmp[i],tmp[i+1]),tmp[i+1]);
    }
}