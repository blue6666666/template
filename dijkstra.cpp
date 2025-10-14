//小根堆实现较为简单，这里采用以点为复杂度的反向索引堆的优化,一般不会用
//不能有负边
#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
const int inf=1e8;
struct graph{
    int next,to,w;
}g[maxn*2];
int head[maxn],cnt,n,m;
int heap[maxn];//反向索引堆
int where[maxn];//表示点在堆上位置，初始化为-1
int heapSize;
int dis[maxn];
void build(int n){
    cnt=1;
    heapSize=0;
    for(int i=1;i<=n;i++){
        heap[i]=0;
        where[i]=-1;
        head[i]=0;
        dis[i]=inf;
    }
}
void add(int u,int v,int w){
    g[cnt].next=head[u];
    g[cnt].to=v;
    g[cnt].w=w;
    head[u]=cnt++;
}
void Swap(int i,int j){
    swap(heap[i],heap[j]);
    where[heap[i]]=i;
    where[heap[j]]=j;
}
void heapInsert(int i){
    while(dis[heap[i]]<dis[heap[(i-1)/2]]){
        Swap(i,(i-1)/2);
        i=(i-1)/2;
    }
}
void addorupdateoringnore(int v,int c){
    if(where[v]==-1){
        heap[heapSize]=v;
        where[v]=heapSize++;
        dis[v]=c;
        heapInsert(where[v]);
    }else if(where[v]>=0){
        dis[v]=min(dis[v],c);
        heapInsert(where[v]);
    }
}
void heapify(int i){
    int l=1;
    while(l<heapSize){
        int best=l+1<heapSize&&dis[heap[l+1]]<dis[heap[l]]?l+1:l;
        best=dis[heap[best]]<dis[heap[i]]?best:i;
        if(best==i) break;
        Swap(best,i);
        i=best;
        l=i*2+1;
    }
}
bool isEmpty(){
    return heapSize==0;
}
int pop(){
    int ans=heap[0];
    swap(heap[0],heap[--heapSize]);
    heapify(0);
    where[ans]=-2;
    return ans;
}
int main(){
    cin>>n>>m;
    int s;
    cin>>s;
    build(n);
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
    }
    addorupdateoringnore(s,0);
    while(!isEmpty()){
        int u=pop();
        for(int ei=head[u];ei>0;ei=g[ei].next){
            addorupdateoringnore(g[ei].to,dis[u]+g[ei].w);
        }
    }
    int ans=-inf;
    for(int i=1;i<=n;i++){
        /*if(dis[i]==inf){
            cout<<-1<<endl;
        }
        ans=max(ans,dis[i]);*/
        cout<<dis[i]<<' ';
    }
    //cout<<ans<<endl;
}
// 扩充 A*算法
//本质上是dijkstra的一种变形  
//只是小根堆添加排序的数不一样，多了一个估值函数
//难点就是找到预估函数
//f(x)<=x到终点真实距离
//在二维网格比较简单
// f(x)可以考虑曼哈顿距离，切比雪夫距离，以及线段距离