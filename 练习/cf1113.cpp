#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
const int maxn=1e10;
void solve(){
    int n,m;
    cin>>n>>m;
    vector<int>a(n),b(m);
    int mn1=maxn,mn2=maxn,mx1=0,mx2=0;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=m;i++){
        cin>>b[i-1];
    }
    if(n<2*m){
        cout<<"No"<<endl;
        return;
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    int l1=lower_bound(a.begin(),a.end(),b[0])-a.begin();
    int l2=lower_bound(a.begin(),a.end(),b[m-1])-a.begin();
    if(n-l1>=2&&l2>=2)cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
}
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        solve();
    }
}