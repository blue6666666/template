#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m;
ll an[45];
ll l[1<<20+1],r[1<<20+1];
ll f(int i,int e,ll s,ll w,ll a[],ll j){
    if(s>w) return j;
    if(i==e) a[j++]=s;
    else {
        j=f(i+1,e,s,w,a,j);
        j=f(i+1,e,s+an[i],w,a,j);
    }
    return j;
}
ll compute(){
    ll lsize=f(0,n>>1,0,m,l,0);
    ll rsize=f(n>>1,n,0,m,r,0);
    sort(l,l+lsize);
    sort(r,r+rsize);
    ll ans=0;
    for(int i=lsize-1,j=0;i>=0;i--){
        while(j<rsize&&l[i]+r[j]<=m){
            j++;
        }
        ans+=j;
    }
    return ans;
}
int main(){
    cin>>n>>m;
  for(int i=0;i<n;i++) cin>>an[i];
  sort(an,an+n);
  cout<<compute();
}