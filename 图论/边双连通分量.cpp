// void tarjan(int u, int in) {
//   low[u] = dfn[u] = ++dfncnt;
//   st.push(u), vis[u] = true;
//   for (int i = hd[u]; i; i = e[i].nt) {
//     int v = e[i].to;
//     if (i == (in ^ 1)) continue;
//     if (!dfn[v])
//       tarjan(v, i), low[u] = min(low[u], low[v]);
//     else if (vis[v])
//       low[u] = min(low[u], dfn[v]);
//   }
//   if (dfn[u] == low[u]) {
//     bcc_cnt++;
//     bcc[u]=bcc_cnt;
//     while (st.top() != u)
//        bcc[st.top()]=bcc_cnt,vis[st.top()] = false, st.pop();
//     st.pop(), ans.push_back(t);
//   }
// }
// #include <algorithm>
// #include <iostream>
// #include <stack>
// #include <vector>

// using namespace std;
// constexpr int N = 5e5 + 5, M = 2e6 + 5;
// int n, m;

// struct edge {
//   int to, nt;
// } e[M << 2];

// int hd[N << 1], tot = 1;

// void add(int u, int v) { e[++tot] = edge{v, hd[u]}, hd[u] = tot; }

// void uadd(int u, int v) { add(u, v), add(v, u); }

// int bcc_cnt, sum;
// int dfn[N], low[N];
// bool vis[N];
// vector<vector<int>> ans;
// stack<int> st;

// void tarjan(int u, int in) {
//   low[u] = dfn[u] = ++bcc_cnt;
//   st.push(u), vis[u] = true;
//   for (int i = hd[u]; i; i = e[i].nt) {
//     int v = e[i].to;
//     if (i == (in ^ 1)) continue;
//     if (!dfn[v])
//       tarjan(v, i), low[u] = min(low[u], low[v]);
//     else if (vis[v])
//       low[u] = min(low[u], dfn[v]);
//   }
//   if (dfn[u] == low[u]) {
//     vector<int> t;
//     t.push_back(u);
//     while (st.top() != u)
//       t.push_back(st.top()), vis[st.top()] = false, st.pop();
//     st.pop(), ans.push_back(t);
//   }
// }

// int main() {
//   cin.tie(nullptr)->sync_with_stdio(false);
//   cin >> n >> m;
//   int u, v;
//   for (int i = 1; i <= m; i++) {
//     cin >> u >> v;
//     if (u != v) uadd(u, v);
//   }
//   for (int i = 1; i <= n; i++)
//     if (!dfn[i]) tarjan(i, 0);
//   cout << ans.size() << '\n';
//   for (int i = 0; i < ans.size(); i++) {
//     cout << ans[i].size() << ' ';
//     for (int j = 0; j < ans[i].size(); j++) cout << ans[i][j] << ' ';
//     cout << '\n';
//   }
//   return 0;
// }
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;
constexpr int N = 5e5 + 5, M = 2e6 + 5;
int n, m;

struct edge {
  int to, nt;
} e[M << 2];

int hd[N << 1], tot = 1;

void add(int u, int v) { e[++tot] = edge{v, hd[u]}, hd[u] = tot; }

void uadd(int u, int v) { add(u, v), add(v, u); }

int bcc_cnt,dfncnt;
int dfn[N], low[N],bcc[N],degree[N],a[N],b[N];
bool vis[N];
stack<int> st;
void tarjan(int u, int in) {
  low[u] = dfn[u] = ++dfncnt;
  st.push(u), vis[u] = true;
  for (int i = hd[u]; i; i = e[i].nt) {
    int v = e[i].to;
    if (i == (in ^ 1)) continue;
    if (!dfn[v])
      tarjan(v, i), low[u] = min(low[u], low[v]);
    else if (vis[v])
      low[u] = min(low[u], dfn[v]);
  }
  if (dfn[u] == low[u]) {
    bcc_cnt++;
    bcc[u]=bcc_cnt;
    while (st.top() != u)
       bcc[st.top()]=bcc_cnt,vis[st.top()] = false, st.pop();
    st.pop();
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> a[i] >> b[i];
    if (a[i] != b[i]) uadd(a[i], b[i]);
  }
  for (int i = 1; i <= n; i++)
    if (!dfn[i]) tarjan(i, 0);
  for(int i=1;i<=m;i++){
    int ebcc1=bcc[a[i]];
    int ebcc2=bcc[b[i]];
    if(ebcc1!=ebcc2){
        degree[ebcc1]++;
        degree[ebcc2]++;
    }
  }
  int ans=0;
  for(int i=1;i<=bcc_cnt;i++){
    if(degree[i]==1){
        ans++;
    }
  }
  cout<<(ans+1)/2;
  return 0;
}