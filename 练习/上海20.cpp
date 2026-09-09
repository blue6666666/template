// #include<bits/stdc++.h>
// using namespace std;
// #define int long long
// int n;
// int a[1<<17],dp[1<<17];
// int ans=0;
// signed main()
// {
//     cin>>n;

//     for(int i=0;i<(1<<n);i++){
//         cin>>a[i];
//         ans^=a[i];
//     }
    
//     for(int msk=0;msk<(1<<n);msk++){
//         for(int i=0;i<n;i++){
//             if(msk>>i&1){
//                 dp[msk]+=dp[msk^(1<<i)];
//                 dp[msk]+=a[msk]+a[msk^(1<<i)];
//             }
//         }
//         ans^=dp[msk];
//     }
    

//     cout<<ans<<endl;

//     return 0;
// }
// #include<bits/stdc++.h>
// using namespace std;

// #define int long long

// int n;
// int a[1<<17];

// vector<int> dfs(int l,int k)
// {
//     if(k==0)
//     {
//         return {a[l]};
//     }
//     int len=1<<(k-1);
//     vector<int> x=dfs(l,k-1);
//     vector<int> y=dfs(l+len,k-1);

//     vector<int> res;
//     res.resize(x.size()*3);

//     int sz=x.size();

//     for(int i=0;i<sz;i++)
//         res[i]=x[i];
//     for(int i=0;i<sz;i++)
//         res[sz+i]=y[i];
//     for(int i=0;i<sz;i++)
//         res[2*sz+i]=x[i]+y[i];

//     return res;
// }

// signed main()
// {
//     cin>>n;

//     int N=1<<n;

//     for(int i=0;i<N;i++)
//         cin>>a[i];
//     vector<int> x=dfs(0,n-1);
//     vector<int> y=dfs(1<<(n-1),n-1);
//     int ans=0;

//     for(int i=0;i<(int)x.size();i++)
//     {
//         ans^=x[i];
//         ans^=y[i];

//         ans^=(x[i]+y[i]);
//     }

//     cout<<ans<<endl;

//     return 0;
// }
// #include<bits/stdc++.h>
// using namespace std;
// #define int long long
// int t;
// int n;
// void solve(){
//     cin>>n;
//     map<int,int>mp;
//     for(int i=1;i<=2*n;i++){
//         int x;
//         cin>>x;
//         mp[x]++;
//     }
//     int x1=-1,x2=-1,odd=0;
//     for(auto [x,y]:mp){
//         if(y&1){
//             odd++;
//             if(x1==-1) x1=x;
//             else x2=x;
//         }
//     }
//     if(odd>2) {cout<<"Bot"<<endl; return;}
//     if(odd==0){
//         int flag=0;
//         for(auto [x,y]:mp){
//             int yy=y/2;
//             if(yy&1) flag^=x;
//         }
//         if(flag) cout<<"Bot"<<endl;
//         else cout<<"Menji"<<endl;
//         return;
//     }else{
//         int flag=0;
//         for(auto [x,y]:mp){
//             int yy=y/2;
//             if(yy&1) flag^=x;
//         }
//         if(flag!=x1&&flag!=x2) cout<<"Bot"<<endl;
//         else cout<<"Menji"<<endl;
//     }
// }
// signed main(){
//     cin>>t;
//     while(t--){
//         solve();
//     }
// }
// #include<bits/stdc++.h>
// using namespace std;
// #define int  long long
// int t;
// void solve(){
//     int n;
//     cin>>n;
//     vector<int>a(61,0);
//     for(int i=1;i<=n;i++){
//         int x;
//         cin>>x;
//         for(int j=60;j>=0;j--){
//             if((x>>j)&1){
//                 a[j]++;
//             }
//         }
//     }
//     int x=0,flag=0;
//     int ans=0;
//     for(int i=60;i>=0;i--){
//         if(a[i]&&!flag){
//             x=a[i];
//             flag=1;
//             ans+=(1LL<<i);
//             continue;
//         }
//         if(a[i]&&(a[i]-x)%2==0) ans+=(1LL<<i);
       
//     }
//     cout<<ans<<endl;
// }
// signed main(){
//     cin>>t;
//     while(t--){
//         solve();
//     }
// }
// #include <bits/stdc++.h>
// using namespace std;
// using ull = unsigned long long;

// struct LinearBasis {
//     ull basis[64];
//     LinearBasis() { memset(basis,0,sizeof(basis)); }
//     void insert(ull x) {
//         for(int i=63; i>=0; --i) {
//             if(!((x>>i)&1ULL)) continue;
//             if(!basis[i]) { basis[i]=x; return; }
//             x ^= basis[i];
//         }
//     }
//     ull queryMax() const {
//         ull res=0;
//         for(int i=63; i>=0; --i) {
//             if((res ^ basis[i]) > res) res ^= basis[i];
//         }
//         return res;
//     }
// };

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     int T;
//     cin >> T;
//     while(T--) {
//         int n;
//         cin >> n;
//         vector<ull> a(n);
//         ull S=0;
//         for(int i=0; i<n; ++i) {
//             cin >> a[i];
//             S ^= a[i];
//         }
//         LinearBasis lb;
//         ull mask = ~S;
//         for(ull v : a) {
//             lb.insert(v & mask);
//         }
//         ull two = lb.queryMax();
//         ull ans = max(S, two);
//         cout << ans << '\n';
//     }
//     return 0;
// }
// #include<bits/stdc++.h>
// using namespace std;

// const int N=500005;

// int n,m,k,cnt;
// int head[N][9],to[N],nxt[N];

// void add(int u,int v,int w)
// {
//     ++cnt;
//     to[cnt]=v;
//     nxt[cnt]=head[u][w];
//     head[u][w]=cnt;
// }

// struct node
// {
//     vector<int> p;
//     int dep,w;
//     bool vis;
// };

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     cin>>n>>m>>k;

//     vector<int> a[9];

//     for(int i=1;i<=m;i++)
//     {
//         int u,v,w;
//         cin>>u>>v>>w;

//         add(u,v,w);
//         a[w].push_back(v);
//     }

//     vector<node> st;

//     for(int w=8;w>=1;w--)
//     {
//         if(!a[w].empty())
//             st.push_back({a[w],1,1,false});
//     }

//     int ans=0;

//     while(!st.empty()&&ans<k)
//     {
//         node &x=st.back();

//         // 1. 输出当前 Trie 节点
//         if(!x.vis)
//         {
//             x.vis=true;

//             for(int i=0;i<(int)x.p.size()&&ans<k;i++)
//             {
//                 cout<<x.dep<<"\n";
//                 ans++;
//             }
//         }

//         // 2. 当前节点的所有后继都处理完
//         if(x.w>8)
//         {
//             st.pop_back();
//             continue;
//         }

//         // 3. 按边权从小到大扩展
//         int w=x.w++;

//         vector<int> np;

//         for(int u:x.p)
//         {
//             for(int e=head[u][w];e;e=nxt[e])
//             {
//                 np.push_back(to[e]);

//                 // 只需要前 k 条
//                 if((int)np.size()>=k-ans)
//                     break;
//             }

//             if((int)np.size()>=k-ans)
//                 break;
//         }

//         // 4. 新 Trie 节点
//         if(!np.empty())
//             st.push_back({np,x.dep+1,1,false});
//     }

//     while(ans<k)
//     {
//         cout<<-1<<"\n";
//         ans++;
//     }

//     return 0;
// }
// #include<bits/stdc++.h>
// using namespace std;

// const int maxn=5e5+10;

// int n,m,k;
// int head[maxn][9],nx[maxn],to[maxn],tot;

// void add(int u,int v,int w)
// {
//     nx[++tot]=head[u][w];
//     to[tot]=v;
//     head[u][w]=tot;
// }

// struct node
// {
//     vector<int>p;
//     int dep,w;
//     bool vis;
// };

// vector<int>a[9];

// int main()
// {
//     cin>>n>>m>>k;

//     int ans=0;

//     for(int i=1;i<=m;i++)
//     {
//         int u,v,w;
//         cin>>u>>v>>w;

//         add(u,v,w);
//         a[w].push_back(v);
//     }

//     stack<node>st;

//     for(int w=8;w>0;w--)
//     {
//         if(!a[w].empty())
//             st.push({a[w],1,1,0});
//     }

//     while(!st.empty()&&ans<k)
//     {
//         node xx=st.top();
//         st.pop();

//         if(!xx.vis)
//         {
//             xx.vis=1;

//             for(int i=0;i<xx.p.size()&&ans<k;i++)
//             {
//                 cout<<xx.dep<<'\n';
//                 ans++;
//             }
//         }

//         if(xx.w>8)
//             continue;

//         int w=xx.w;
//         xx.w++;
//         vector<int>np;

//         for(auto u:xx.p)
//         {
//             for(int e=head[u][w];e;e=nx[e])
//             {
//                 np.push_back(to[e]);

//                 if(np.size()>=k-ans)
//                     break;
//             }

//             if(np.size()>=k-ans)
//                 break;
//         }
//         if(xx.w<=8)
//             st.push(xx);
//         if(!np.empty())
//             st.push({np,xx.dep+1,1,0});
//     }

//     while(ans<k)
//     {
//         cout<<-1<<'\n';
//         ans++;
//     }

//     return 0;
// }
#include<bits/stdc++.h>
using namespace std;

struct twtree {
    int dep;
    int mxdep;
    int lc, rc;
} a[30010];

int st[30010][20];
int tin[30010], tout[30010], timer;
int cnt_sub[30010];
vector<int> d;

void dfs(int u, int f) {
    tin[u] = ++timer;
    a[u].dep = a[f].dep + 1;
    st[u][0] = f;
    a[u].mxdep = a[u].dep;

    for (int p = 1; p < 20; p++) {
        st[u][p] = st[st[u][p - 1]][p - 1];
    }

    if (a[u].lc) dfs(a[u].lc, u);
    if (a[u].rc) dfs(a[u].rc, u);

    a[u].mxdep = max(a[u].mxdep,
                     max(a[a[u].lc].mxdep, a[a[u].rc].mxdep));
    tout[u] = timer;
}

int findlca(int x, int y) {
    if (a[x].dep < a[y].dep) swap(x, y);

    for (int p = 19; p >= 0; p--) {
        if (a[st[x][p]].dep >= a[y].dep) {
            x = st[x][p];
        }
    }

    if (x == y) return x;

    for (int p = 19; p >= 0; p--) {
        if (st[x][p] != st[y][p]) {
            x = st[x][p];
            y = st[y][p];
        }
    }

    return st[x][0];
}

bool isAnc(int anc, int u) {
    return tin[anc] <= tin[u] && tout[u] <= tout[anc];
}

void collect(int u, int target_dist, vector<int>& vec) {
    if (a[u].dep - 1 > target_dist) return;
    if (a[u].mxdep - 1 < target_dist) return;
    if (a[u].dep - 1 == target_dist) {
        vec.push_back(u);
        return;
    }
    if (a[u].lc) collect(a[u].lc, target_dist, vec);
    if (a[u].rc) collect(a[u].rc, target_dist, vec);
}
void solve() {
    memset(a, 0, sizeof(a));
    memset(st, 0, sizeof(st));
    memset(tin, 0, sizeof(tin));
    memset(tout, 0, sizeof(tout));
    timer = 0;
    int n;
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int x;
        cin >> x;
        if (!a[x].lc) a[x].lc = i;
        else a[x].rc = i;
    }
    dfs(1, 0);
    int maxdist = a[1].mxdep - 1;
    int l = 0, r = maxdist;

    while (l < r) {
        int mid = (l + r) >> 1;
        cout << "? 1 " << mid << '\n';
        cout.flush();

        int resp;
        cin >> resp;

        if (resp) r = mid;
        else l = mid + 1;
    }

    int D = l; 
    vector<int> S;
    collect(1, D, S);
    while ((int)S.size() > 1) {
        int m = (int)S.size();

        memset(cnt_sub, 0, sizeof(cnt_sub));
        for (int u : S) cnt_sub[u] = 1;
        for (int u = n; u >= 1; u--) {
            if (a[u].lc) cnt_sub[u] += cnt_sub[a[u].lc];
            if (a[u].rc) cnt_sub[u] += cnt_sub[a[u].rc];
        }

        int cur = 1;
        while (true) {
            int left = a[cur].lc;
            int right = a[cur].rc;

            int cntL = left ? cnt_sub[left] : 0;
            int cntR = right ? cnt_sub[right] : 0;

            if (left && cntL > 9 * m / 10) {
                cur = left;
                continue;
            }

            if (right && cntR > 9 * m / 10) {
                cur = right;
                continue;
            }

            int q = (cntL >= cntR ? left : right);
            int radius = D - (a[q].dep - 1);

            cout << "? " << q << " " << radius << '\n';
            cout.flush();
            int resp;
            cin >> resp;
            vector<int> nS;
            if (resp) {
                for (int u : S) {
                    if (isAnc(q, u)) nS.push_back(u);
                }
            } else {
                for (int u : S) {
                    if (!isAnc(q, u)) nS.push_back(u);
                }
            }

            S.swap(nS);
            break;
        }
    }

    cout << "! " << S[0] << '\n';
    cout.flush();
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}