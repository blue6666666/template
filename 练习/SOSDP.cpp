// https://atcoder.jp/contests/arc100/tasks/arc100_c
// #include<bits/stdc++.h>
// using namespace std;
// #define int long long
// #define pi first
// #define pj second 
// int n,k;
// void merge(pair<int,int>&a,pair<int,int>b){
//     if(a.pi<b.pi) swap(a,b);
//     if(a.pj<b.pi) a.pj=b.pi;
// }
// const int inf= 1e15;
// signed main(){
//     cin>>k;
//     n=(1<<k);
//     vector<int>a(n+1);
//     for(int i=0;i<n;i++){
//         cin>>a[i];
//     }
//     vector<pair<int,int>>K(n+1);
//     for(int i=0;i<n;i++){
//         K[i].pi=a[i];
//         K[i].pj=-inf;
//     }
//     for(int l=0;l<k;l++){
//         for(int i=0;i<n;i++){
//             if(i>>l&1) merge(K[i],K[i^(1<<l)]);
//         }
//     }
//     int ans=-inf;
//     for(int i=1;i<n;i++){
//         ans=max(ans,K[i].pi+K[i].pj);
//         cout<<ans<<'\n';
//     }
// }

// https://codeforces.com/contest/1208/problem/F
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
int n;
int a[2000010];
pair<int,int>b[(1<<21)+5];
void add(int x, int id) {
    if (id == -1) return;
    if (id > b[x].fi) {
        b[x].se = b[x].fi;
        b[x].fi = id;
    } else if (id > b[x].se && id != b[x].fi) {
        b[x].se = id;
    }
}
void merge(int x,int y){
    add(x,b[y].fi);
    add(x,b[y].se);
}
int main(){
    cin>>n;
    int N=2e6+10;
    memset(b,-1,sizeof(b));
    for(int i=1;i<=n;i++){
        cin>>a[i];
        add(a[i],i);
    }
    for(int i=0;i<21;i++){
        for(int j=0;j<N;j++){
            if(j>>i&1){
                merge(j^(1<<i),j);
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n-2;i++){
        int lim=(1<<21)-1;
        int cur=lim^a[i];
        int res=0;
        for(int j=20;j>=0;j--){
            if(cur>>j&1){
                if(b[res^(1<<j)].se>i){
                    res^=(1<<j);
                }
            }
        }
        ans=max(ans,res|a[i]);
    }
    cout<<ans;
}