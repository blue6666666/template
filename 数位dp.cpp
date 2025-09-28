
/*#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
static ll dp[25][25][2005];
ll n, num[25];
void precompute() {
    //对于多次询问部分可以提前初始化
    for (int len = 0; len <= 20; len++) {
        for (int mid = 1; mid <= 20; mid++) {
            for (int liju = 0; liju <= 2000; liju++) {
                if (len == 0) {
                    dp[len][mid][liju] = (liju == 0);
                    continue;
                }
                ll cnt = 0;
                for (int i = 0; i <= 9; i++) {
                    ll temp = liju + (len - mid) * i;
                    if (temp < 0) continue;
                    cnt += dp[len-1][mid][temp];
                }
                dp[len][mid][liju] = cnt;
            }
        }
    }
}

ll dfs(ll len, ll mid, ll liju, bool sx) {
    if (len == 0) return liju == 0;
    if (liju < 0) return 0;
    if (!sx) return dp[len][mid][liju];
    ll cnt = 0, maxx = sx ? num[len] : 9;
    for (int i = 0; i <= maxx; i++) {
        ll temp = liju + (len - mid) * i;
        cnt += dfs(len - 1, mid, temp, sx && (i == maxx));
    }
    return cnt;
}

ll solve(ll x) {
    if (x < 0) return 0;
    if (x == 0) return 1; 
    n = 0;
    while (x) {
        num[++n] = x % 10;
        x /= 10;
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += dfs(n, i, 0, true);
    }
    
    return ans - n + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    precompute(); 
    ll t;
    cin >> t;
    while (t--) {
        ll a, b;
        cin >> a >> b;
        cout << solve(b) - solve(a - 1) << endl;
    }
    return 0;
}*/
// 一般做法
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll num[25],n=0,dp[25][2];
ll dfs(int len,bool if6,bool shangxian){
    if(len==0) return 1;
    if(!shangxian&&dp[len][if6]) return dp[len][if6];
    ll cnt=0,maxx=(shangxian?num[len]:9);
    for(int i=0;i<=maxx;i++){
        if((if6&&i==2)||i==4){
          continue;
        }
        cnt+=dfs(len-1,i==6,shangxian&&i==maxx);
    }
    return shangxian? cnt:dp[len][if6]=cnt;
}
ll solve(ll x){
    n=0;
    memset(num, 0, sizeof(num));
    while(x){
        num[++n]=x%10;
        x/=10;
    }
     return dfs(n,false,true);

}
int main(){
    
    ll a,b;
    while(cin>>a>>b){
        if(a==0&&b==0) break;
        
       cout<<solve(b)-solve(a-1);
        cout<<endl;
    }
}
