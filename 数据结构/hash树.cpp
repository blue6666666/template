//树同构

#include <bits/stdc++.h>
 
 typedef long long LL;
 const int N = 60, MO = 998244353;
 
 struct Edge {
     int nex, v;
 }edge[N << 1]; int tp;
 
 int e[N], n, m, turn, fr[N], p[1000010], top, siz[N], h[N], g[N];
 std::vector<int> v[N];
 bool vis[1000010];
 
 inline void add(int x, int y) {
     tp++;
     edge[tp].v = y;
     edge[tp].nex = e[x];
     e[x] = tp;
     return;
 }
 
 inline bool equal(int a, int b) {
     int len = v[a].size();
     if(len != v[b].size()) return false;
     for(int i = 0; i < len; i++) {
         if(v[a][i] != v[b][i]) return false;
     }
     return true;
 }
 
 inline void getp(int n) {
     for(int i = 2; i <= n; i++) {
         if(!vis[i]) {
             p[++top] = i;
         }
         for(int j = 1; j <= top && i * p[j] <= n; j++) {
             vis[i * p[j]] = 1;
             if(i % p[j] == 0) {
                 break;
             }
         }
     }
     return;
 }
 
 void DFS_1(int x, int f) {
     siz[x] = 1;
     h[x] = 1;
     for(int i = e[x]; i; i = edge[i].nex) {
         int y = edge[i].v;
         if(y == f) continue;
         DFS_1(y, x);
         h[x] = (h[x] + 1ll * h[y] * p[siz[y]] % MO) % MO;
         siz[x] += siz[y];
     }
     return;
 }
 
 void DFS_2(int x, int f, int V) {
     g[x] = (h[x] + 1ll * V * p[n - siz[x]] % MO) % MO;
     v[turn].push_back(g[x]);
     V = (1ll * V * p[n - siz[x]] % MO + 1) % MO;
     for(int i = e[x]; i; i = edge[i].nex) {
         int y = edge[i].v;
         if(y == f) {
             continue;
         }
         DFS_2(y, x, ((LL)V + h[x] - 1 - 1ll * h[y] * p[siz[y]] % MO + MO) % MO);
     }
     return;
 }
 
 int main() {
     getp(1000009);
     scanf("%d", &m);
     for(turn = 1; turn <= m; turn++) {
         scanf("%d", &n);
         tp = 0;
         memset(e + 1, 0, n * sizeof(int));
         for(int i = 1, x; i <= n; i++) {
             scanf("%d", &x);
             if(x) {
                 add(x, i);
                 add(i, x);
             }
         }
         DFS_1(1, 0);
         DFS_2(1, 0, 0);
         std::sort(v[turn].begin(), v[turn].end());
         /*for(int i = 0; i < n; i++) {
             printf("%d ", v[turn][i]);
         }
         puts("\n");*/
     }
 
     for(int i = 1; i <= m; i++) {
         fr[i] = i;
     }
     for(int i = 2; i <= m; i++) {
         for(int j = 1; j < i; j++) {
             if(equal(i, j)) {
                 fr[i] = fr[j];
                 break;
             }
         }
     }
     for(int i = 1; i <= m; i++) {
         printf("%d\n", fr[i]);
     }
     return 0;
 }