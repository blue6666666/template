//适用于范围很大，但是操作较少
//用于减小空间复杂度
//如果操作过多，则与没有优化相同，因此可能被卡
//在线段树的合并与分裂中不可替代，树链剖分
//P2781 这题其实完全可以不用线段树
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=100001;
ll le[maxn],ri[maxn],sum[maxn],add[maxn],cnt;
void up(ll i, ll l, ll r){
    sum[i]=sum[l]+sum[r];
}
void lazy(ll i,ll v, ll n){
    sum[i]+=v*n;
    add[i]+=v;
}
void down(ll i, ll ln, ll rn){
    if(add[i]!=0){
     if(le[i]==0){
        le[i]=++cnt;
     }
    if(ri[i]==0){
        ri[i]=++cnt;
    }
    lazy(le[i],add[i],ln);
    lazy(ri[i],add[i],rn);
    add[i]=0;
    }
}
void Add(ll jl,ll jr,ll v,ll l,ll r,ll i){
     if(jl<=l&&r<=jr){
        lazy(i,v,r-l+1);
       return;
     }
     
    ll mid=(l+r)>>1;
     down(i,mid-l+1,r-mid);
     if(jl<=mid){
        if(le[i]==0){
            le[i]=++cnt;
        }
        Add(jl,jr,v,l,mid,le[i]);
     }
     if(jr>mid){
        if(ri[i]==0){
            ri[i]=++cnt;
        }
        Add(jl,jr,v,mid+1,r,ri[i]);
     }
    
    up(i,le[i],ri[i]);
}
ll query(ll jl,ll jr,ll l, ll r,ll i){
    if(jl<=l&&r<=jr){
        return sum[i];
    }
    ll mid=(l+r)>>1;
    down(i,mid-l+1,r-mid);
    ll ans=0;
    if(jl<=mid){
        if(le[i]!=0){
            ans+=query(jl,jr,l,mid,le[i]);
        }
    }
    if(jr>mid){
        if(ri[i]!=0){
            ans+=query(jl,jr,mid+1,r,ri[i]);
        }
    }
    return ans;
}
int main(){
    int n,m;
    cin>>n>>m;
    cnt=1;
    while(m--){
        int opt;
        cin>>opt;
        if(opt==1){
            int l,r,v;
            cin>>l>>r>>v;
            Add(l,r,v,1,n,1);
        }
    else {
        int l,r;
        cin>>l>>r;
        cout<<query(l,r,1,n,1)<<endl;
    }
}
}