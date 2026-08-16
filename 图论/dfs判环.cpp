bool dfs(int u, int fa) {
    stk[++tp] = u;
    vis[u] = bk[u] = true;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;                // 跳过父节点
        if (bk[v]) {
            if (vis[v]) return true;          // 回边指向当前栈中的祖先 → 有环
        } else {
            if (dfs(v, u)) return true;       // 递归子树，发现环即返回
        }
    }

    tp--;
    vis[u] = false;
    return false;
}
// bool dfs(int u) {
// 	stk[++ tp] = u;
// 	vis[u] = bk[u] = true;
// 	for (int v = 1; v <= n; v++) {//邻接矩阵
// 		if (!c[u][v]) continue;
// 		if (tp >= 2 && v == stk[tp - 1]) continue;
// 		if (bk[v] && vis[v]) return true;
// 	}
// 	for (int v = 1; v <= n; v++) {
// 		if (!c[u][v]) continue;
// 		if (!bk[v] && dfs(v)) return true;
// 	}
// 	tp --;
// 	vis[u] = false;
// 	return false;
// }
