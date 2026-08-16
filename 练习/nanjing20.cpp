// #include<bits/stdc++.h>
// using namespace std;
// int t;
// void solve(){
//     int x1,y1,x2,y2;
//     cin>>x1>>y1>>x2>>y2;
//     if(x1==1||x1==9||y1==1||y1==10){
//               if(x1==1&&y1==1){
//             if((x2==2&&y2==1)||(x2==2&&y2==2)||(x2==1&&y2==2)||(x2==3&&y2==3)){
//                 cout<<"YES"<<endl;
//                 return;
//             }
        
//         }
//         if(x1==9&&y1==1){
//             if((x2==8&&y2==1)||(x2==9&&y2==2)||(x2==8&&y2==2)||(x2==7&&y2==3)){
//                 cout<<"YES"<<endl;
//                 return;
//             }
            
//         }
//         if(x1==1&&y1==10){
//             if((x2==1&&y2==9)||(x2==2&&y2==10)||(x2==2&&y2==9)||(x2==3&&y2==8)){
//                 cout<<"YES"<<endl;
//                 return;
//             }
            
//         }
//         if(x1==9&&y1==10){
//             if((x2==9&&y2==9)||(x2==8&&y2==10)||(x2==8&&y2==9)||(x2==7&&y2==8)){
//                 cout<<"YES"<<endl;
//                 return;
//             }
            
//         }
//         if((x1==1&&y1==2)||(x1==2&&y1==1)||(x1==2&&y1==2)||(x1==8&&y1==1)||(x1==8&&y1==2)||(x1==9&&y1==2)||(x1==8&&y1==9)||(x1==9&&y1==9)||(x1==8&&y1==10)||(x1==1&&y1==9)||(x1==2&&y1==9)||(x1==2&&y1==10)){
//             if(abs(x2-x1)==2&&abs(y2-y1)==2){
//                 cout<<"YES"<<endl;
//             return;
//             }
            
//         }
//         if(x1==1&&y1==y2&&x2==2) {
//             cout<<"YES"<<endl;
//             return;
//         }
//         if(x1==9&&y1==y2&&x2==8) {
//             cout<<"YES"<<endl;
//             return;
//         }
//         if(y1==1&&x1==x2&&y2==2) {
//             cout<<"YES"<<endl;
//             return;
//         }
//         if(y1==10&&x1==x2&&y2==9) {
//             cout<<"YES"<<endl;
//             return;
//         }
//         cout<<"NO"<<endl;
//         return;
//     }else {
//         cout<<"NO"<<endl;
//     }
// }
// int main(){
//     cin>>t;
//     while(t--){
//         solve();
//     }
// }
// #include<bits/stdc++.h>
// using namespace std;
// #define int long long
// int t;
// int n,sum1,sum2;
// struct node{
//     int v,s,i;
// }a[200010],b[200010];
// map<pair<int,int>,int>mp;
// bool cmp(node x,node y){
//     if(x.v!=y.v) return x.v<y.v;
//     return x.s>y.s;
// }
// bool cmp1(node x,node y){
//     if(x.s!=y.s) return x.s>y.s;
//     return x.v<y.v;
// }
// bool check(int x,int& ans,int tt,int q){
//     int sub1=0,sub2=0;
//     int l1=1,l2=1;
//     while(x){
//         if(mp[{a[l1].i,q}]) l1++;
//         if(mp[{b[l2].i,q}]) l2++;
//         if(tt*a[l2].s>=a[l1].v) return false;
//         mp[{a[l1].i,q}]=1;
//         mp[{a[l2].i,q}]=1;
//         sub1+=a[l1].v;
//         sub2+=a[l2].s;
//         l1++;
//         l2++;
//         x--;
//     }
//     ans=sum1-sub1-(sum2-sub2)*tt;
//     return true;
// }
// void solve(){
//     mp.clear();
//     sum1=0,sum2=0;
//     cin>>n;
//     for(int i=1;i<=n;i++){
//         cin>>a[i].v;
//         a[i].i=i;
//         sum1+=a[i].v;
//     }
//     for(int i=1;i<=n;i++){
//         cin>>a[i].s;
//         b[i]=a[i];
//         sum2+=a[i].s;
//     }
//     sort(a+1,a+n+1,cmp);
//     sort(b+1,b+n+1,cmp1);
//     int q;
//     cin>>q;
//     while(q--){
//         int tt;
//         cin>>tt;
//         int l=0,r=n;
//         int mid;
//         int ans=0;
//         while(r-l>1){
//             mid=(r+l)>>1;
//             if(check(mid,ans,tt,q)) r=mid-1;
//             else l=mid+1;
//         }
//         cout<<max(ans,1LL*0)<<' ';
//     }
//     cout<<endl;
// } 
// signed main(){
//     cin>>t;
//     while(t--){
//         solve();
//     }
// }
#include<bits/stdc++.h>
using namespace std;
void solve() {
    int n;
    cin >> n;

    map<long double, int> mp;
    int cur = 0;
    for (int i = 0; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 0 && b == 0) {
            continue;
        }
        long double s = atan2l(a, -b); // 必须long double
        long double t = atan2l(-a, b);
        mp[s]++;
        mp[t]--;    
        if (s > t) {
            cur++;
        }
    }

    int ans = cur;
    for (auto [_, delta] : mp) {
        cur += delta;
        ans = max(ans, cur);
    }
    cout << ans << '\n';
}
int main(){
    int t;
    cin>>t;
    while(t--){
        solve();
    }
}
/*
2
4
1 1 1 -1 3 4
0 -2 7 -5 0 10
1
0 0 1
*/
// #include<bits/stdc++.h>
// using namespace std;
// #define int long long
// int t;
// struct DisjointSets {
//     vector<int> f;
//     int tot;
//     DisjointSets(int n) : f(n, -1), tot(n) {}
//     int find(int x) {
//         return f[x] < 0 ? x : f[x] = find(f[x]);
//     }
//     int size(int x) {
//         return -f[find(x)];
//     }
//     bool same(int x, int y) {
//         return find(x) == find(y);
//     }
//     bool uno(int x, int y) {
//         x = find(x), y = find(y);
//         if (x == y) return false;
//         return f[x] += f[y], f[y] = x, tot--;
//     }
// };
// void add(int x,int y,int m,vector<DisjointSets>&dsu){
//     if(dsu[m].uno(x,y)){
//         for(int i=0;i<12;i++){
//             if(m>>i&1){
//                 add(x,y,m^(1<<i),dsu);
//             }
//         }
//     }
// }
// void solve(){
//     int n,q;
//     cin>>n>>q;
//     vector<DisjointSets>dsu(1<<12,DisjointSets(n));
//     int ans=0;
//     while(q--){
//         char op;
//         int x,y;
//         cin>>op>>x>>y;
//         x--,y--;
//         if(op=='+'){
//             int m;
//             cin>>m;
//             add(x,y,m,dsu);
//         }else {
//             int res=0;
//             for(int i=11;i>=0;i--){
//                 if(dsu[res|(1<<i)].same(x,y)){
//                     res|=1<<i;
//                 }
//             }
//             if(!dsu[0].same(x,y)) res=-1;
//             ans+=res;
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