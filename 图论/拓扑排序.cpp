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
//反拓扑排序
// #include <bits/stdc++.h>
// using namespace std;

// const int maxn = 105;
// const int maxm = 10005;

// struct Edge {
//     int u, v, w, id; 
// } edges[maxm];

// int head[maxn], nxt[maxm], to[maxm], weight[maxm], idx; 
// int rhead[maxn], rnxt[maxm], rto[maxm], rweight[maxm]; 
// int indeg[maxn];
// int ve[maxn], vl[maxn];

// void add_edge(int u, int v, int w, int id) {
//     to[++idx] = v; weight[idx] = w; nxt[idx] = head[u]; head[u] = idx;
//     rto[idx] = u; rweight[idx] = w; rnxt[idx] = rhead[v]; rhead[v] = idx;
// }

// int main() {
//     int n, m;
//     cin >> n >> m;
//     idx = 0;
//     memset(head, 0, sizeof(head));
//     memset(rhead, 0, sizeof(rhead));
//     memset(indeg, 0, sizeof(indeg));
//     memset(ve, 0, sizeof(ve));
//     for (int i = 1; i <= m; i++) {
//         int u, v, w;
//         cin >> u >> v >> w;
//         edges[i] = {u, v, w, i};   
//         add_edge(u, v, w, i);
//         indeg[v]++;
//     }

//     queue<int> q;
//     for (int i = 0; i < n; i++) {
//         if (indeg[i] == 0) {
//             q.push(i);
//         }
//     }

//     vector<int> topo;
//     while (!q.empty()) {
//         int u = q.front(); q.pop();
//         topo.push_back(u);
//         for (int e = head[u]; e; e = nxt[e]) {
//             int v = to[e], w = weight[e];
//             ve[v] = max(ve[v], ve[u] + w);
//             if (--indeg[v] == 0) {
//                 q.push(v);
//             }
//         }
//     }

//     if ((int)topo.size() != n) {
//         cout << "关键路径分析结果为 0" << endl;
//         return 0;
//     }
//     int max_ve = 0;
//     for (int i = 0; i < n; i++) {
//         max_ve = max(max_ve, ve[i]);
//     }
//     fill(vl, vl + n, max_ve);
//     for (int i = n - 1; i >= 0; i--) {
//         int u = topo[i];
//         for (int e = rhead[u]; e; e = rnxt[e]) {
//             int pre = rto[e], w = rweight[e];
//             vl[pre] = min(vl[pre], vl[u] - w);
//         }
//     }
//     vector<Edge> key_acts;
//     for (int i = 1; i <= m; i++) {
//         int u = edges[i].u, v = edges[i].v, w = edges[i].w, id = edges[i].id;
//         if (ve[u] == vl[v] - w) {
//             key_acts.push_back(edges[i]);
//         }
//     }
//     sort(key_acts.begin(), key_acts.end(), [](const Edge &a, const Edge &b) {
//         if (a.u != b.u) return a.u < b.u;
//         return a.id > b.id;
//     });

//     for (auto &act : key_acts) {
//         cout << "<" << act.u << ", " << act.v << ">" << endl;
//     }
//     cout << "关键路径分析结果为 1" << endl;
//     return 0;
// }