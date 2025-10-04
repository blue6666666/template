// 这类题目一般是可以看出来使用线段树，但是不能满足一般的懒更新的条件
//简单的一般需要进行势能分析，再减枝就可以解决
//例如 洛谷 P4145，此题是开根号，换为取模同理
/*#include<bits/stdc++.h>
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
}*/
//这类属于比较简单的，没有懒标记
//P2184 更加简单的类型,感觉有点前缀和的意思
/*#include<bits/stdc++.h>
using namespace std;
const int maxn =100001;
long long bombf[maxn<<2],bombe[maxn<<2];
void up(int i){
    bombf[i]=bombf[i<<1]+bombf[i<<1|1];
    bombe[i]=bombe[i<<1]+bombe[i<<1|1];
}
void build(int l,int r ,int i){//对于这道题build其实没有用
    if(l<r){
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
    }
    up(i);
}
void add(int ji,int jt,int l,int r,int i){//单点修改
    if(l==r){
        if(jt) {
            bombf[i]++;
        }else bombe[i]++;
        return;
    }
    int mid=(l+r)>>1;
    if(ji<=mid) add(ji,jt,l,mid,i<<1);
    else add(ji,jt,mid+1,r,i<<1|1);
    up(i);
}
long long query(int jl,int jr,int jv,int l,int r,int i){
    if(jl<=l&&jr>=r){
        if(jv) return bombf[i];
        else return bombe[i];
       
    }
    int mid=(l+r)>>1;
    long long ans=0;
    if(jl<=mid) ans+=query(jl,jr,jv,l,mid,i<<1);
    if(jr>mid) ans+=query(jl,jr,jv,mid+1,r,i<<1|1); 
    return ans;
}
int main(){
    int n,m;
    cin>>n>>m;
    //build(1,n,1);
    while(m--){
        int q,l,r;
        cin>>q>>l>>r;
        if(q==1){
            add(l,1,1,n,1);
            add(r,0,1,n,1);
        }else{
            int ans1=query(1,r,1,1,n,1);
            int ans2=l==1?0:query(1,l-1,0,1,n,1);
            cout<<ans1-ans2<<endl;
        }
    }
}*/
// 此外，线段树上也可以差分，线段树上差分本质上就是线段树上的范围修改操作
//P1471 求方差
#include<bits/stdc++.h>
using namespace std;

const int maxn=100001;
double a[maxn],sum[maxn<<2],pf[maxn<<2],lazy[maxn<<2];
void up(int i){
    sum[i]=sum[i<<1]+sum[i<<1|1];
    pf[i]=pf[i<<1]+pf[i<<1|1];
}

void Lazy(int i,double v,int n){
    lazy[i]+=v;
    pf[i]+=2*v*sum[i]+v*v*n;
    sum[i]+=v*n;
}
void down(int i,int ln,int rn){
    if(lazy[i]!=0){
        Lazy(i<<1,lazy[i],ln);
        Lazy(i<<1|1,lazy[i],rn);
        lazy[i]=0;
    }
}
void add(int jl,int jr,double v,int l,int r,int i){
    if(jl<=l&&jr>=r){
        Lazy(i,v,r-l+1);
        return;
    }
    int mid=(l+r)>>1;
    down(i,mid-l+1,r-mid);
    if(jl<=mid){
        add(jl,jr,v,l,mid,i<<1);
    }
    if(jr>mid) add(jl,jr,v,mid+1,r,i<<1|1);
    up(i);
}
double query(int jl,int jr,int jt,int l,int r,int i){
    if(jl<=l&&jr>=r){
        if(jt){
            return pf[i];
        }else return sum[i];
    }
    int mid=(l+r)>>1;
    down(i,mid-l+1,r-mid);
    double ans=0;
    if(jl<=mid) ans+=query(jl,jr,jt,l,mid,i<<1);
    if(jr>mid) ans+=query(jl,jr,jt,mid+1,r,i<<1|1);
    return ans;
}
void build(int l,int r,int i){
    if(l==r){
        sum[i]=a[l];
        pf[i]=a[l]*a[l];
        
    }
    else {
    int mid=(l+r)>>1;
    build(l,mid,i<<1);
    build(mid+1,r,i<<1|1);
    up(i);
    }
    lazy[i]=0;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1,n,1);
    while(m--){
        int opt;
        cin>>opt;
        if(opt==1){
            int l,r;
            double v;
            cin>>l>>r>>v;
            add(l,r,v,1,n,1);
        }else if(opt==2){
            int l,r;
            cin>>l>>r;
            printf("%.4lf\n",query(l,r,0,1,n,1)/(r-l+1));
        }else {
            int l,r;
            cin>>l>>r;
            printf("%.4lf\n",query(l,r,1,1,n,1)/(r-l+1)-query(l,r,0,1,n,1)/(r-l+1)*query(l,r,0,1,n,1)/(r-l+1));
        }
    }
}

