#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5+9;
int n,k,m,a[N],b[N],dp[N],t[N<<2];

void updata(int i,int l,int r,int n,int val){
    t[i]=max(val,t[i]);
    if(l==r) return;
  int mid=(l+r)>>1;
  if(n<=mid) updata(i<<1,l,mid,n,val);
  else updata(i<<1|1,mid+1,r,n,val);
  return;
}
int getmax(int i,int l,int r,int nl,int nr){
  if(l==nl&&r==nr){
    return t[i];
  }
  int mid=(l+r)>>1;
  if(mid>=nr) return getmax(i<<1,l,mid,nl,nr);
  else if(mid<nl) return getmax(i<<1|1,mid+1,r,nl,nr);
  else return max(getmax(i<<1,l,mid,nl,mid),getmax(i<<1|1,mid+1,r,mid+1,nr));
}
void solve(){
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i],b[i]=a[i];
    // 离散化
    sort(b+1,b+n+1);
    m=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+m+1,a[i])-b;
    for(int i=1;i<=n;i++){
        dp[i]=getmax(1,1,m,1,a[i])+1;
        updata(1,1,m,a[i],dp[i]);
    }
    //到这里dp 中存储的是以a[i]结尾的最长不下降子序列
    int ans=0;
    memset(t,0,sizeof t);
    for(int i=n;i>k;i--){
        ans=max(ans,dp[i-k]+k-1+getmax(1,1,m,a[i-k],m)+1); //通过再次利用线段树找到往后最长（题目要求）
        int tem=getmax(1,1,m,a[i],m)+1;
        updata(1,1,m,a[i],tem);
    }
    ans=max(ans,k+getmax(1,1,m,a[k+1],m));
    cout<<ans<<'\n';
}

// 1 2 3 ... i-k i-k+1 i-k+2 i-k+3 ... i ...

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    int q=1;
    //cin>>q;
    while(q--){
        solve();
    }
    return 0;
}