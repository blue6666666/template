// //1
// #include<bits/stdc++.h>
// using namespace std;
// #define int long long
// int n,q;
// vector<int>a;
// bool minp[100000010];
// void xxs(){
//     for(int i=2;i<=n;i++){
//         if(minp[i]==0){
//             minp[i]=1;
//             a.push_back(i);
//         }
//         for(auto x:a){
//             if(x*i>n) break;
//             minp[i*x]=1;
//         }
//     }
// }
// signed main(){
//     ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
//     cin>>n>>q;
//     xxs();
//     while(q--){
//         int x;
//         cin>>x;
//         cout<<a[x-1]<<'\n';
//     }
// }
//2
// #include<bits/stdc++.h>
// using namespace std;
// const int maxn=10000001;
// int minp[10000001],d[10000001],num[maxn];
// vector<int>a;
// void ssx(){
//     d[1]=1;
//     for(int i=2;i<maxn;i++){
//         if(minp[i]==0){
//             minp[i]=i;
//             a.push_back(i);
//             d[i]=2;
//             num[i]=1;
//         }
//         for(auto x:a){
//             if((long long)i*x>=maxn) break;
//             minp[x*i]=x;
//             if(minp[i]==x){
//                 num[i*x]=num[i]+1;
//                 d[i*x]=d[i]/(num[i]+1)*(num[i*x]+1);
//                 break;
//             }
//             d[i*x]=d[i]*d[x];
//             num[i*x]=1;
//         }
        
//     }
// }
// int main(){
//     ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
//     int t;
//     cin>>t;
//     ssx();
//     while(t--){
//         int x;
//         cin>>x;
//         cout<<d[x]<<'\n';
//     }
// }
// #include <bits/stdc++.h>
// using namespace std;
// const int maxn = 13000001;
// const int mod = 1e9 + 7;
// int qmi(int m, int k, int p) {
//     int res = 1 % p, t = m;
//     while (k) {
//         if (k & 1) res = 1LL * res * t % p;
//         t = 1LL * t * t % p;
//         k >>= 1;
//     }
//     return res;
// }

// int n;
// int d[maxn];           
// vector<int> primes;    
// void ssx() {
//     d[1] = 1;
//     for (int i = 2; i <= n; ++i) {
//         if (d[i] == 0) {                
//             primes.push_back(i);
//             d[i] = qmi(i, n, mod);
//         }
//         for (int x : primes) {
//             if (1LL * i * x > n) break;
//             d[i * x] = 1LL * d[i] * d[x] % mod;
//             if (i % x == 0) break;     
//         }
//     }
// }
// int main() {
//     ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
//     cin >> n;
//     ssx();
//     long long ans = 0;
//     for (int i = 1; i <= n; ++i)
//         ans ^= d[i];
//     cout << ans << endl;
//     return 0;
// }
// #include<bits/stdc++.h>
// using namespace std;
// const int maxn = 10000001;
// int minp[maxn], d[maxn], g[maxn];  
// vector<int> a;
// int mp[maxn];
// void ssx() {
//     d[1] = 1; g[1] = 1;
//     for (int i = 2; i < maxn; ++i) {
//         if (minp[i] == 0) {
//             minp[i] = i;
//             a.push_back(i);
//             d[i] = 1 + i;
//             g[i] = 1 + i;
//         }
//         for (int x : a) {
//             long long nxt = 1LL * i * x;
//             if (nxt >= maxn) break;
//             minp[nxt] = x;
//             if (minp[i] == x) {
//                 g[nxt] = g[i] * x + 1;
//                 d[nxt] = d[i] / g[i] * g[nxt];
//                 break;
//             } else {
//                 d[nxt] = d[i] * d[x];
//                 g[nxt] = 1 + x;
//             }
//         }
//     }
//     for (int i = 1; i < maxn; ++i) {       
//         if (d[i] >= maxn) continue;        
//         if (!mp[d[i]]) mp[d[i]] = i;
//         else if (i < mp[d[i]]) mp[d[i]] = i;
//     }
// }

// int main() {
//     ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
//     ssx();
//     int q;
//     cin >> q;
//     while (q--) {
//         int x;
//         cin >> x;
//         if (!mp[x]) cout << -1 << endl;
//         else cout << mp[x] << endl;
//     }
// }
#include<bits/stdc++.h>
using namespace std;
const int maxn=32768;
int minp[maxn+1],d[maxn+1],num[maxn];
vector<int>a;
void ssx(){
    d[1]=0;
    for(int i=2;i<maxn;i++){
        if(minp[i]==0){
            minp[i]=i;
            a.push_back(i);
            d[i]=i-1;
        }
        for(auto x:a){
            if((long long)i*x>=maxn) break;
            minp[x*i]=x;
            if(minp[i]==x){
                d[i*x]=d[i]*x;
                break;
            }
            d[i*x]=d[i]*d[x];
        }
        
    }
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    ssx();
    while(t--){
        int x;
        cin>>x;
        cout<<d[x]<<'\n';
    }
}