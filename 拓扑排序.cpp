#include<bits/stdc++.h>
using namespace std;
const int maxn=100001;
int cnt,n,m,head[maxn],indegree[maxn],per[maxn];

struct graph{
    int next,to;
}g[maxn];

void add(int u,int v){
    g[cnt].next=head[u];
    g[cnt].to=v;
    head[u]=cnt++;
}

bool tpsort(){
    //queue<int> q;  // 如果把队列改成小根堆的话，就可以使队列结果为字典序最小排列
    priority_queue<int,vector<int>,greater<int>>q;
    for(int i=1;i<=n;i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    int fill=0;
    while(!q.empty()){
        int cur=q.top();
        q.pop();
        per[++fill]=cur;
        for(int ei=head[cur];ei!=0;ei=g[ei].next){
            if(--indegree[g[ei].to]==0){
                q.push(g[ei].to);
            }
        }
    }
    return fill==n;
}
int main(){
    cin>>n>>m;
    cnt=1;
    memset(head,0,sizeof(head));  // 初始化head数组
    memset(indegree,0,sizeof(indegree));  // 初始化入度数组
    
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        indegree[v]++;
    }
    
    if(!tpsort()){
        cout<<-1<<endl;
    }else {
        for(int i=1;i<=n;i++){
            cout<<per[i]<<' ';
        }
        cout<<endl;
    }
    return 0;
}