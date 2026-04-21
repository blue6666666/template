//求解二分图最大权，但是时间复杂度O(n^3)
#include <bits/stdc++.h>
using namespace std;
const int N = 510; // 最大顶点数
const long long INF = 1e18; // 定义无穷大

long long w[N][N]; // 邻接矩阵存储边权
long long la[N], lb[N]; // 左右部顶标
bool va[N], vb[N]; // 访问标记，用于交错树
int match[N]; // 记录右部点匹配的左部点
int n; // 每部顶点数
long long slack[N]; // 松弛量

bool dfs(int x) {
    va[x] = true;
    for (int y = 1; y <= n; y++) {
        if (!vb[y]) {
            if (la[x] + lb[y] == w[x][y]) { // 相等子图中的边
                vb[y] = true;
                if (match[y] == -1 || dfs(match[y])) {
                    match[y] = x;
                    return true;
                }
            } else { // 非相等子图边，更新松弛量
                slack[y] = min(slack[y], la[x] + lb[y] - w[x][y]);
            }
        }
    }
    return false;
}

long long KM() {
    // 1. 初始化顶标
    fill(lb, lb + N, 0);
    for (int i = 1; i <= n; i++) {
        la[i] = -INF;
        for (int j = 1; j <= n; j++) {
            la[i] = max(la[i], w[i][j]);
        }
    }

    fill(match, match + N, -1);
    for (int i = 1; i <= n; i++) {
        while (true) {
            fill(va, va + N, false);
            fill(vb, vb + N, false);
            fill(slack, slack + N, INF);

            if (dfs(i)) break; // 找到增广路，匹配成功

            // 3. 调整顶标
            long long d = INF;
            for (int j = 1; j <= n; j++) {
                if (!vb[j]) d = min(d, slack[j]);
            }
            for (int j = 1; j <= n; j++) {
                if (va[j]) la[j] -= d;
                if (vb[j]) lb[j] += d;
            }
        }
    }

    // 计算最大权匹配和
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += w[match[i]][i];
    }
    return ans;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> w[i][j];
        }
    }
    
    // 求最小总效益（边权取反）
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            w[i][j] = -w[i][j];
        }
    }
    cout << -KM() << endl;
    
    // 恢复并求最大总效益
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            w[i][j] = -w[i][j];
        }
    }
    cout << KM() << endl;
    
    return 0;
}