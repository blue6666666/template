#include<bits/stdc++.h>
//#define int long long
#define in(a) a = read_int()
using namespace std;
const int N = 2e5 + 5;
const int inf = INT_MAX;
inline int read_int() {
	int x = 0;
	char ch = getchar();
	bool f = 0;
	while('9' < ch || ch < '0') f |= ch == '-' , ch = getchar();
	while('0' <= ch && ch <= '9') x = (x << 3) + (x << 1) + ch - '0' , ch = getchar();
	return f ? -x : x;
}
struct Edge {
	int n , v , w;
} edge[N << 1];
int head[N] , eid;
void eadd(int u , int v , int w) {
	edge[++ eid].n = head[u] , edge[eid].v = v , edge[head[u] = eid].w = w;
}
int n;
int l[N] , r[N] , ans[N];
void dfs(int u , int fa) { // 树形 DP 部分 
	l[u] = 1; // 初始化左边界 
	for(int i = head[u] ; i ; i = edge[i].n) {
		int v = edge[i].v , w = edge[i].w;
		if(v != fa) {
			r[v] = w - 1; // 初始化右边界 
			dfs(v , u);
			r[u] = min(r[u] , w - l[v]); // 转移过程 
			l[u] = max(l[u] , w - r[v]);
		}
	}
}
queue<int>q;
signed main() {
	in(n);
	for(int i = 1 ; i < n ; i ++) {
		int u , v , w;
		in(u) , in(v) , in(w);
		eadd(u , v , w) , eadd(v , u , w);
	}
	r[1] = 1e9; // 初始化根节点的右边界 
	dfs(1 , 0); // 求每个点权的取值范围 
	for(int i = 1 ; i <= eid ; i += 2) { // 判无解部分 
		int u = edge[i].v , v = edge[i + 1].v , w = edge[i].w;
		if(r[u] + r[v] < w || l[u] > r[u] || l[v] > r[v]) { 
            cout<<"NO";
			return 0;
		}
	}
	ans[1] = l[1]; // 若有解，根节点点权取左边界 
	q.push(1);
	while(!q.empty()) { // 广搜部分 
		int u = q.front();
		q.pop();
		for(int i = head[u] ; i ; i = edge[i].n) {
			int v = edge[i].v , w = edge[i].w;
			if(ans[v]) continue;
			ans[v] = w - ans[u]; // 递推求解 
			q.push(v);
		}
	}
	cout<<"YES\n"; // 打印答案 
	for(int i = 1 ; i <= n ; i ++) cout<<ans[i]<<' ';
	return 0;
}