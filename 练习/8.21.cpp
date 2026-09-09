// #include<bits/stdc++.h>
// using namespace std;
// #define int long long
// unordered_map<int,bool>mp,mp2;
// vector<int> sieve(int n)
// {
// 	vector<bool> vis(n+1);
//     vector<int> mP(n+1,1);
// 	vector<int> prime;
// 	vis[1] = 1;
// 	for (int i = 2; i <= n; ++i) {
// 		if (!vis[i]) {
//             prime.push_back(i); 
//             mP[i] = i;
//         }
// 		for (auto p: prime) {
// 			if (i*p > n) { break; }
// 			vis[i*p] = 1;
//             mP[i*p] = p;
// 			if (i%p == 0) { break; }  // 线性筛关键优化
// 		}
// 	}
// 	return prime;
// }
// signed main(){
//     vector<int>prime=sieve(100010);
//         for(int i=0;i<prime.size();i++){
//         mp2[prime[i]]=1;
//     }
//     long long n;
//     cin>>n;
//     int ans=0;
//     for(int i=0;i<prime.size();i++){
//         if(prime[i]>n) break;
//         for(int j=i+1;j<prime.size();j++){
//             long long k=(long long)(prime[j]*prime[j])*(long long)(prime[j]*prime[i]);
//             if(k > n) break;
//             if(!mp[k]){ans++;mp[k]=1;}

//         }
//     }
//     cout<<ans<<endl;
// }
// #include<bits/stdc++.h>
// using namespace std;
// int n,a,b;
// int main(){
//     cin>>n>>a>>b;
//     bool f=1;
//     for(int i=1;i<=n;i++){

//     for(int k=1;k<=a;k++){
//         if(i&1) f=1;
//         else f=0;
//         for(int j=1;j<=n;j++){
//                 for(int m=1;m<=b;m++){
//                     if(f) cout<<'.';
//                     else cout<<"#";
//                 }
//             f=!f;
//         }
//         cout<<endl;
//     }
//     }
// }
// #include <bits/stdc++.h>
// using namespace std;
// vector<long long> sieve(int n) {
//     vector<bool> vis(n + 1, false);
//     vector<long long> primes;
//     for (int i = 2; i <= n; ++i) {
//         if (!vis[i]) primes.push_back(i);
//         for (long long p : primes) {
//             if (i * p > n) break;
//             vis[i * p] = true;
//             if (i % p == 0) break;
//         }
//     }
//     return primes;
// }
// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     long long n;
//     cin >> n;
//     int limit = (int)min<long long>(n, 1000000);
//     vector<long long> primes = sieve(limit);
//     long long ans = 0;
//     for (int i = 0; i < (int)primes.size(); ++i) {
//         long long p = primes[i];
//         if (p > n) break;
//         for (int j = i + 1; j < (int)primes.size(); ++j) {
//             long long q = primes[j];
//             long long q3 = q * q * q; 
//             if (q3 > n / p) break;
//             ans++;
//         }
//     }

//     cout << ans << '\n';
//     return 0;
// }
// #include<bits/stdc++.h>
// using namespace std;
// int t;
// void solve(){
//     string s;
//     cin>>s;
//     int cnt1=0,cnt2=0,ans=0;
//     for(int i=0;i<s.length();i++){
//         if(s[i]=='(') cnt1++;
//         else if(s[i]==')'&&cnt1){
//             ans++;
//             cnt1--;
//         }else if(s[i]=='[') cnt2++;
//         else if(s[i]==']'&&cnt2){
//             ans++;
//             cnt2--;
//         }
//     }
//     cout<<ans<<endl;
// }
// int main(){
//     cin>>t;
//     while(t--){
//     solve();
//     }
// }
// #include<bits/stdc++.h>
// using namespace std;
// int t;
// void solve(){
//     int x,y;
//     cin>>x>>y;
//     if(x==y){
//         cout<<x+y<<endl;
//         return;
//     }
//     if(x>y){
//         int ans=2*y;
//         int k=x-y-1;
//         ans+=k*2+1;
//         cout<<ans<<endl;
//         return;
//     }
//     int ans=2*x;
//     int k=y-x-1;
    
//      ans+=2*k+1;
//     cout<<ans<<endl;
// }
// int main(){
//     cin>>t;
//     while(t--){
//         solve();
//     }
// }
// #include<bits/stdc++.h>
// using namespace std;
// map<int,int>mp;
// int main(){
//     int n,q;
//     cin>>n>>q;
//     vector<int>a(n);
//     for(int i=0;i<n;i++) {mp[i]=i;a[i]=i;}
//     // for(int i=0;i<n;i++) cout<<a[i]+1<<' ';
//     // cout<<endl;
//     while(q--){
//         int x;
//         cin>>x;
//         x--;
//         int l=mp[x];
//         if(l!=n-1){
//         mp[x]=(l+1)%n;
//         int k=a[(l+1)%n];
//         mp[k]=l;
//         swap(a[l],a[(l+1)%n]);
//         }else{
//             mp[x]=l-1;
//             int k=a[l-1];
//             mp[k]=l;
//             swap(a[l],a[l-1]);
//         }
//         // for(int i=0;i<n;i++) cout<<a[i]+1<<' ';
//         // cout<<endl;
//     }
//     for(int i=0;i<n;i++) cout<<a[i]+1<<' ';
// }
// #include<bits/stdc++.h>
// using namespace std;
// #define int long long
// const int maxn=1e5+10;
// int t;
// int sum;
// int a[maxn];
// void solve(){
//     int n;
//     cin>>n;
//     sum=0;
//     int ans=0;
//     priority_queue<int>q1;
//     priority_queue<int,vector<int>,greater<int>>q2;
//     for(int i=1;i<=n;i++){
//         cin>>a[i];
//         q1.push(a[i]);
//         q2.push(a[i]);
//         sum+=a[i];
//     }
//     while(1){
//         int mn=q2.top(),mx=q1.top();
//         if(mx*(n-1)==sum) break;
//         if(mx*(n-1)>sum){
//             int k=mx*(n-1)-sum;
//             ans+=k;
//             sum+=k;
//             q2.pop();
//             q2.push(mn+k);
//             q1.push(mn+k);
//         }else {

//             int kk=mx*(n-1)+mn-sum;
//             int k=(mn-kk);
//             if(k%(n-1)==0) break;
//             int kkk=(k/(n-1)+1)*(n-1)-k;
//             ans+=kkk;
//             sum+=kkk;
//             q2.pop();
//             q2.push(mn+kkk);
//             q1.push(mn+kkk);
//         }
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
// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     int t;
//     cin >> t;
//     while (t--) {
//         long long n;
//         cin >> n;
//         vector<long long> a(n);
//         long long sum = 0;
//         long long mx = LLONG_MIN;

//         for (long long i = 0; i < n; ++i) {
//             cin >> a[i];
//             sum += a[i];
//             mx = max(mx, a[i]);
//         }
//         long long k = max(mx, (sum + n - 2) / (n - 1));
//         cout << k * (n - 1) - sum << '\n';
//     }
//     return 0;
// }
// #include<bits/stdc++.h>
// using namespace std;
// int n,q;
// int a[200010],b[200010],fa[200010],fb[200010],tt[400010];
// map<int,int>mp1,mp2;
// int main(){
//     cin>>n;
//     int tot=0;
//     for(int i=1;i<=n;i++){
//         cin>>a[i];
//         if(!mp1[a[i]])mp1[a[i]]=i;
//     }
//     for(int i=1;i<=n;i++){
//         cin>>b[i];
//         if(!mp2[b[i]]) mp2[b[i]]=i;
//     }
//     for(int i=1;i<=n;i++){
//         fa[i]=mp2[a[i]];
//         fb[i]=mp1[b[i]];
//         if(!fa[i]) fa[i]=n+1;
//         if(!fb[i]) fb[i]=n+1;
//     }
//     for(int i=1;i<=n;i++){
//         fa[i]=max(fa[i],fa[i-1]);
//         fb[i]=max(fb[i],fb[i-1]);
//     }
//     cin>>q;
//     while(q--){
//         int x,y;
//         cin>>x>>y;
//         if(fa[x]<=y&&fb[y]<=x){
//             cout<<"Yes"<<endl;
//         }else cout<<"No"<<endl;
//     }

// }
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    priority_queue<long long,vector<long long>,greater<long long>> pq;
    long long ans=0;
    for (int i = 0; i<N;i++) {
        long long p;
        cin>>p;
        pq.push(p);
        if (pq.top()<p) {
            ans += p - pq.top();
            pq.pop();
            pq.push(p);  
        }
    }
    cout << ans<<'\n';
    return 0;
}