// 这类题目一般是可以看出来使用线段树，但是不能满足一般的懒更新的条件
//简单的一般需要进行势能分析，再减枝就可以解决
//例如 洛谷 P4145，此题是开根号，换为取模同理
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100001;
ll arr[maxn],mx[maxn*4],sum[maxn*4];
void up(ll i){
    sum[i]=sum[i<<1]+sum[i<<1|1];
    mx[i]=max(mx[i<<1],mx[i<<1|1]);
}
void Sqrt(ll jl,ll jr,ll l,ll r,ll i){
    if(l==r){
        ll s=sqrt(mx[i]);
        mx[i]=s;
        sum[i]=s;
        return;
    }
    ll mid=(l+r)>>1;
    if(jl<=mid&&mx[i<<1]>1) Sqrt(jl,jr,l,mid,i<<1);
    if(jr>mid&&mx[i<<1|1]>1) Sqrt(jl,jr,mid+1,r,i<<1|1);
    up(i); 
}
void build(ll l,ll r,ll i){
    if(l==r){
        mx[i]=arr[l];
        sum[i]=arr[l];
        return;
    }
    ll mid=(l+r)>>1;
    build(l,mid,i<<1);
    build(mid+1,r,i<<1|1);
    up(i);
}
ll query(ll jl,ll jr,ll l,ll r, ll i){
    if(jl<=l&&jr>=r) {
        return sum[i];
    }
    ll mid=(l+r)>>1;
    ll ans=0;
    if(jl<=mid) ans+=query(jl,jr,l,mid,i<<1);
    if(jr>mid) ans+=query(jl,jr,mid+1,r,i<<1|1);
    return ans;
}
int main(){
    ll n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>arr[i];
    build(1,n,1);
    ll m;
    cin>>m;
    while(m--){
    ll opt, l,r;
    cin>>opt>>l>>r;
    if(l>r) swap(l,r);
    if(opt==0) Sqrt(l,r,1,n,1);
    else {
        cout<<query(l,r,1,n,1)<<endl;
    }
    }
}
//这类属于比较简单的，没有懒标记
