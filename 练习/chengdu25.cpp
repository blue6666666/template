// //A.cpp
// #include<bits/stdc++.h>
// using namespace std;
// int t;
// void solve(){
//     int n;
//     cin>>n;
//     vector<int>a(n);

//     int sum=0;
//     int cnt=0;
//     for(int i=0;i<n;i++){
//         cin>>a[i];
//         sum+=a[i];
//         if(a[i]==0) cnt++;
//     }
//     if(cnt==n&&n>=200){
//         if(n==200){cout<<"No"<<endl;
//         return;
//         }
//         cout<<"Yes"<<endl;
//         for(int i=1;i<=n;i++){
//             cout<<1<<' ';
//         }
//         cout<<endl;
//         return;
//     }
//     if(sum==100){
//         cout<<"Yes"<<endl;
//         for(auto x:a){
//             cout<<x<<' ';
//         }
//         cout<<endl;
//     }
//     else if(sum>100){
//         int d=sum-100;
//         if(2*d>n-cnt){
//             cout<<"No"<<endl;
//             return;
//         }
//         cout<<"Yes"<<endl;
//         int k=2*d;
//         for(auto x:a){
//             if(x==0||!k) cout<<x*10<<' ';
//             else {
//                 cout<<x*10-5<<' ';
//                 k--;
//             }
//         }
//         cout<<endl;
//     }else{
//         int d=100-sum;
        
//         if(d*1.0/n>=0.5){
//             cout<<"No"<<endl;
//             return;
//         }
//         cout<<"Yes"<<endl;
//         int t=(d*1.0/n*10000000);
//         for(auto x:a){
//             cout<<x*10000000+t<<' ';
//         }
//         cout<<endl;
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
// const int base1=131313;
// const int base2=599999;
// const int mod=10000000007;
// int b1[7],b2[7];
// int t;
// int n,m,k,r;
// struct node{
//     int v,ap;
// }a[7];
// map<int,int>mp;
// bool flag[7];
// int DP(){
//     vector<set<int>>s(m+1);
//     vector<int>dp(m+1,0);
//     for(int i=1;i<=n;i++){
//         int kk=a[i].ap+(flag[i]?k:0);
//         for(int j=m;j>=kk;j--){
//             if(dp[j]==dp[j-kk]+a[i].v){
//                 if(s[j].size()>s[j-kk].size()+1){
//                     s[j].clear();
//                     s[j].insert(i);
//                     for(auto x:s[j-kk]){
//                         s[j].insert(x);
//                     }
//                 }
//             }else if(dp[j]<dp[j-kk]+a[i].v){
//                     s[j].clear();
//                     s[j].insert(i);
//                     for(auto x:s[j-kk]){
//                         s[j].insert(x);
//                     }
//             }
//         }
//     }
//     set<int>ans;
//     int res=0;
//     for(int i=0;i<=m;i++){
//         if(res<dp[i]||(res==dp[i]&&ans.size()<s[i].size())){
//             res=dp[i];
//             ans.clear();
//             for(auto x:s[i]){
//                 ans.insert(x);
//             }
//         }
//     }
//     int xxx=0;
//     for(auto x:ans){
//         if(flag[x]) xxx+=b1[x];
//         else xxx+=b2[x];
//     }
//     if(mp[xxx]) return -1;
//     memset(flag,0,sizeof(flag));
//     for(auto x:ans){
//         flag[x]=1;
//     }
//     mp[xxx]=res;
//     return res;

// }
// void solve(){
//     cin>>n>>m>>k>>r;
//     for(int i=1;i<=n;i++){
//         cin>>a[i].v>>a[i].ap;
//     }
//     mp.clear();
//     vector<int>aa;
//     while(1){
//         int x=DP();
//         if(x==-1) break;
//         else aa.push_back(x);
//     }
//     int l=r/(int)(aa.size());
//     int ss=r%(int)(aa.size());
//     int sum=0,sy=0;
//     for(int i=0;i<aa.size();i++){
//         sum+=aa[i];
//         if(i<ss) sy+=aa[i];
//     }
//     cout<<l*sum+sy<<endl;
// }
// signed main(){
//     int t;
//     cin>>t;
//     b1[0]=b2[0]=1;
//     for(int i=1;i<=6;i++){
//         b1[i]=b1[i-1]*base1%mod;
//         b2[i]=b2[i-1]*base2%mod;
//     }
//     while(t--){
//         solve();
//     }
// }
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,k;
int main(){
    cin>>n>>m>>k;
    vector<int>a(n+1,0),b(n+1,0);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=m;i++){
        cin>>b[i];
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    ll ans1=0,ans2=0;
    ll l1=n-1,l2=m;
    ll cur=a[n]-k;
    int cnt=0;
    ans1+=k;
    while(l1&&l2){
        if(cnt&1){
            if(cur>a[l1]) ans1+=cur-a[l1],cur=a[l1];
            l1--;
        }else {
            if(cur>b[l2]) {ans1+=cur-b[l2],cur=b[l2];}
            l2--;
        }
        ans1+=k;
        cur-=k;
    }
    while(l1){
        if(cur>a[l1]) ans1+=cur-a[l1],cur=a[l1];
        l1--;
        ans1+=2*k;
        cur-=2*k;
    }
    while(l2){
    if(cur>b[l2]) {ans1+=cur-b[l2],cur=b[l2];}
    l2--;
    ans1+=2*k;
    cur-=2*k;
    }

    l1=n,l2=m-1;
    ans2=k;
    cnt=1;
    cur=b[m]-k;
    while(l1&&l2){
        if(cnt&1){
            if(cur>a[l1]) ans2+=cur-a[l1],cur=a[l1];
            l1--;
        }else {
            if(cur>b[l2]) {ans2+=cur-b[l2],cur=b[l2];}
            l2--;
        }
        ans2+=k;
        cur-=k;
    }
    while(l1){
        if(cur>a[l1]) ans2+=cur-a[l1],cur=a[l1];
        l1--;
        ans2+=2*k;
        cur-=2*k;
    }
    while(l2){
    if(cur>b[l2]) {ans2+=cur-b[l2],cur=b[l2];}
    l2--;
    ans2+=2*k;
    cur-=2*k;
    }
    cout<<min(ans1,ans2)<<endl;
}