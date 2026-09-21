/*替罪羊树 是一种依靠重构操作维持平衡的重量平衡树．替罪羊树会在插入、删除操作后，检测树是否发生失衡；如果失衡，将有针对性地进行重构以恢复平衡．
一般地，替罪羊树不支持区间操作，且无法完全持久化；但它具有实现简单、常数较小的优点．
*/
//单次查询，单次调整的代价均摊为log（n），平衡因子一般为0.7--0.8
#include<bits/stdc++.h>
using namespace std;

struct ScapegoatTree {
    static const int MAXN = 200005;
    static constexpr double ALPHA = 0.7;
    static const int INF = 1e9 + 10;
    int root, cnt;
    int key[MAXN], num[MAXN];
    int l[MAXN], r[MAXN];
    int sz[MAXN], dif[MAXN];
    int v[MAXN];
    int vc;
    int top, fa, side;

    ScapegoatTree() {
        clear();
    }

    int init(int x) {
        ++cnt;
        key[cnt] = x;
        num[cnt] = 1;
        l[cnt] = r[cnt] = 0;
        sz[cnt] = dif[cnt] = 1;
        return cnt;
    }

    void pushup(int p) {
        sz[p] = sz[l[p]] + sz[r[p]] + num[p];
        dif[p] = dif[l[p]] + dif[r[p]] + (num[p] > 0);
    }

    bool balance(int p) {
        return ALPHA * dif[p] >= max(dif[l[p]], dif[r[p]]);
    }

    void inorder(int p) {
        if (!p) return;

        inorder(l[p]);

        if (num[p] > 0)
            v[++vc] = p;

        inorder(r[p]);
    }

    int build(int L, int R) {
        if (L > R) return 0;

        int mid = (L + R) >> 1;
        int p = v[mid];

        l[p] = build(L, mid - 1);
        r[p] = build(mid + 1, R);

        pushup(p);

        return p;
    }

    void rebuild() {
        if (!top) return;

        vc = 0;
        inorder(top);

        if (!vc) {
            if (!fa) root = 0;
            else if (side == 1) l[fa] = 0;
            else r[fa] = 0;
            return;
        }

        int p = build(1, vc);

        if (!fa)
            root = p;
        else if (side == 1)
            l[fa] = p;
        else
            r[fa] = p;
    }

    void insert(int p, int f, int s, int x) {
        if (!p) {
            if (!f)
                root = init(x);
            else if (s == 1)
                l[f] = init(x);
            else
                r[f] = init(x);

            return;
        }

        if (key[p] == x)
            ++num[p];
        else if (key[p] > x)
            insert(l[p], p, 1, x);
        else
            insert(r[p], p, 2, x);

        pushup(p);

        if (!balance(p)) {
            top = p;
            fa = f;
            side = s;
        }
    }

    void insert(int x) {
        top = fa = side = 0;
        insert(root, 0, 0, x);
        rebuild();
    }

    int countLess(int p, int x) {
        if (!p) return 0;

        if (key[p] >= x)
            return countLess(l[p], x);

        return sz[l[p]] + num[p] + countLess(r[p], x);
    }

    // x 的排名：第一个 >= x 的位置
    int rank(int x) {
        return countLess(root, x) + 1;
    }

    int kth(int p, int k) {
        if (sz[l[p]] >= k)
            return kth(l[p], k);

        if (sz[l[p]] + num[p] < k)
            return kth(r[p], k - sz[l[p]] - num[p]);

        return key[p];
    }

    // 第 k 小
    int kth(int k) {
        if (k <= 0 || k > sz[root])
            return INF;

        return kth(root, k);
    }

    bool exist(int p, int x) {
        if (!p) return false;

        if (key[p] == x)
            return num[p] > 0;

        if (key[p] > x)
            return exist(l[p], x);

        return exist(r[p], x);
    }

    void erase(int p, int f, int s, int x) {
        if (!p) return;

        if (key[p] == x)
            --num[p];
        else if (key[p] > x)
            erase(l[p], p, 1, x);
        else
            erase(r[p], p, 2, x);

        pushup(p);

        if (!balance(p)) {
            top = p;
            fa = f;
            side = s;
        }
    }

    void erase(int x) {
        if (!exist(root, x)) return;

        top = fa = side = 0;
        erase(root, 0, 0, x);
        rebuild();
    }

    // < x 的最大值
    int pre(int x) {
        int k = rank(x);

        if (k == 1)
            return -INF;

        return kth(k - 1);
    }

    // > x 的最小值
    int nxt(int x) {
        int k = rank(x + 1);

        if (k == sz[root] + 1)
            return INF;

        return kth(k);
    }

    // 当前元素总数
    int size() {
        return sz[root];
    }

    // 是否为空
    bool empty() {
        return sz[root] == 0;
    }

    // 清空
    void clear() {
        root = 0;
        cnt = 0;
        vc = 0;
        top = fa = side = 0;
    }
};
ScapegoatTree T;
int main(){
    int n;
    cin>>n;
    while(n--){
        int op,x;
        cin>>op>>x;
        if(op==1){
        
            T.insert(x);
        }else if(op==2){

            T.erase(x);
        }else if(op==3){
            cout<<T.rank(x)<<endl;
        }else if(op==4){
            cout<<T.kth(x)<<endl;
        }else if(op==5){
            cout<<T.pre(x)<<endl;
        }else cout<<T.nxt(x)<<endl;
    }
}