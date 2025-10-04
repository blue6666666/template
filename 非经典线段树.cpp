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
/*#include<bits/stdc++.h>
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
}*/

//线段树上的序列操作，稍难一点
//求连续1的最长子列，有点难度，容易打错
/*
#include<bits/stdc++.h>
using namespace std;
const int maxn=100001;
int arr[maxn],sum[maxn<<2],pre0[maxn<<2],len0[maxn<<2],suf0[maxn<<2],pre1[maxn<<2],len1[maxn<<2],suf1[maxn<<2];
int lazy[maxn<<2];
bool update[maxn<<2];
bool rever[maxn<<2];
void up(int i,int ln,int rn){
    int l=i<<1;
    int r=i<<1|1;
    sum[i]=sum[l]+sum[r];
    len0[i]=max(max(len0[l],len0[r]),suf0[l]+pre0[r]);
    pre0[i]=len0[l]<ln?pre0[l]:pre0[l]+pre0[r];
    suf0[i]=len0[r]<rn?suf0[r]:suf0[l]+suf0[r];
    len1[i]=max(max(len1[l],len1[r]),suf1[l]+pre1[r]);
    pre1[i]=len1[l]<ln?pre1[l]:pre1[l]+pre1[r];
    suf1[i]=len1[r]<rn?suf1[r]:suf1[l]+suf1[r];
}
void updateLazy(int i,int v,int n){
    sum[i]=v*n;
    pre0[i]=suf0[i]=len0[i]=v==0?n:0;
    pre1[i]=suf1[i]=len1[i]=v==1?n:0;
    lazy[i]=v;
    update[i]=true;
    rever[i]=false;
}
void reverseLazy(int i,int n){
    sum[i]=n-sum[i];
    swap(pre0[i],pre1[i]);
    swap(len0[i],len1[i]);
    swap(suf0[i],suf1[i]);
    rever[i]=!rever[i];
}
void down(int i,int ln,int rn){
    if(update[i]){
        updateLazy(i<<1,lazy[i],ln);
        updateLazy(i<<1|1,lazy[i],rn);
        update[i]=false;
    }
    if(rever[i]){
        reverseLazy(i<<1,ln);
        reverseLazy(i<<1|1,rn);
        rever[i]=false;
    }
}
void build(int l,int r,int i){
    if(l==r){
        sum[i]=arr[l];
        pre0[i]=arr[l]?0:1;
        suf0[i]=arr[l]?0:1;
        len0[i]=arr[l]?0:1;
        pre1[i]=arr[l]?1:0;
        suf1[i]=arr[l]?1:0;
        len1[i]=arr[l]?1:0;
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,i<<1),build(mid+1,r,i<<1|1);
    up(i,mid-l+1,r-mid);
    rever[i]=0;
    update[i]=0;
}
void Update(int jl,int jr,int v,int l,int r,int i){
    if(jl<=l&&r<=jr){
        updateLazy(i,v,r-l+1);
    }else {
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        if(jl<=mid) Update(jl,jr,v,l,mid,i<<1);
        if(jr>mid) Update(jl,jr,v,mid+1,r,i<<1|1);
        up(i,mid-l+1,r-mid);
    }
}
void Reverse(int jl,int jr,int l,int r,int i){
    if(jl<=l&&r<=jr){
        reverseLazy(i,r-l+1);
    }else {
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        if(jl<=mid) Reverse(jl,jr,l,mid,i<<1);
        if(jr>mid) Reverse(jl,jr,mid+1,r,i<<1|1);
        up(i,mid-l+1,r-mid);
    }
}
tuple<int,int,int> querylength(int jl,int jr,int l,int r,int i){
    if(jl<=l&&r<=jr){
        return make_tuple(len1[i],pre1[i],suf1[i]);
    }
    int mid=(l+r)>>1;
    down(i,mid-l+1,r-mid);
    if(jr<=mid) return querylength(jl,jr,l,mid,i<<1);
    if(jl>mid) return querylength(jl,jr,mid+1,r,i<<1|1);
    tuple<int,int,int> l1=querylength(jl,jr,l,mid,i<<1);
    tuple<int,int,int> r1=querylength(jl,jr,mid+1,r,i<<1|1);
    int llen=get<0>(l1),lpre=get<1>(l1),lsuf=get<2>(l1);
    int rlen=get<0>(r1),rpre=get<1>(r1),rsuf=get<2>(r1);
    int len=max(max(llen,rlen),lsuf+rpre);
    int pre=lpre<mid-max(l,jl)+1?lpre:lpre+rpre;
    int suf=rsuf<min(r,jr)-mid?rsuf:rsuf+lsuf;
    return make_tuple(len,pre,suf);
}
int query(int jl,int jr,int l,int r,int i){
    if(jl<=l&&r<=jr){
        return sum[i];
    }
    int mid=(l+r)>>1;
    down(i,mid-l+1,r-mid);
    int ans=0;
    if(jl<=mid) ans+=query(jl,jr,l,mid,i<<1); 
    if(jr>mid)  ans+=query(jl,jr,mid+1,r,i<<1|1);
    return ans;
}
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>arr[i];
    build(1,n,1);
    while(m--){
        int opt,l,r;
        cin>>opt>>l>>r;
        l+=1;
        r+=1;
        if(opt==0){
            Update(l,r,0,1,n,1);
        }else if(opt==1){
            Update(l,r,1,1,n,1);
        }else if(opt==2){
            Reverse(l,r,1,n,1);
        }else if(opt==3){
            cout<<query(l,r,1,n,1)<<endl;
        }else {
            tuple<int,int,int>a=querylength(l,r,1,n,1);
            cout<<get<0>(a)<<endl;
        }
    }
}
*/

//区间最值操作经典题 hdu 5306
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000001;
const int minest=-1000001;
long long arr[maxn<<2],sum[maxn<<2],mx[maxn<<2],sem[maxn<<2],cnt[maxn<<2];
void up(int i){
    int l=i<<1;
    int r=i<<1|1;
    sum[i]=sum[l]+sum[r];
    mx[i]=max(mx[l],mx[r]);
    if(mx[l]>mx[r]){
        cnt[i]=cnt[l];
        sem[i]=max(sem[l],mx[r]);
    }else if(mx[r]>mx[l]){
        cnt[i]=cnt[r];
        sem[i]=max(sem[r],mx[l]);
    }else {
        sem[i]=max(sem[l],sem[r]);
        cnt[i]=cnt[l]+cnt[r];
    }
}
void Lazy(int i,int v){
    if(v<mx[i]){
        sum[i]-=(mx[i]-v)*cnt[i];
        mx[i]=v;
    }
}
void down(int i){
    Lazy(i<<1,mx[i]);
    Lazy(i<<1|1,mx[i]);
}
void setmin(int jl,int jr,int v,int l,int r,int i){
    if(v>mx[i]) return;
    if(jl<=l&&r<=jr&&v>sem[i]){
        Lazy(i,v);
        return;
    }else {
        down(i);
        int mid=(l+r)>>1;
        if(jl<=mid) setmin(jl,jr,v,l,mid,i<<1);
        if(jr>mid) setmin(jl,jr,v,mid+1,r,i<<1|1);
    }
    up(i);
}
long long querymax(int jl,int jr,int l,int r,int i){
    if(jl<=l&&r<=jr){
        return mx[i];
    }
    down(i);
    int mid=(l+r)>>1;
    long long lm=minest,rm=minest;
    if(jl<=mid) lm=querymax(jl,jr,l,mid,i<<1);
    if(jr>mid)  rm=querymax(jl,jr,mid+1,r,i<<1|1);
    return max(lm,rm);
}
long long querysum(int jl,int jr,int l,int r,int i){
    if(jl<=l&&r<=jr){
        return sum[i];
    }
    down(i);
    int mid=(l+r)>>1;
    long long ans=0;
    if(jl<=mid) ans+=querysum(jl,jr,l,mid,i<<1);
    if(jr>mid)  ans+=querysum(jl,jr,mid+1,r,i<<1|1);
    return ans;
}
void build(int l,int r,int i){
    if(l==r){
        sum[i]=arr[l];
        mx[i]=arr[l];
        sem[i]=minest;
        cnt[i]=1;
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,i<<1),build(mid+1,r,i<<1|1);
    up(i);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            cin>>arr[i];
        }
        build(1,n,1);
        while(m--){
            int opt;
            cin>>opt;
            if(opt==0){
                int l,r;
                long long mi;
                cin>>l>>r>>mi;
                setmin(l,r,mi,1,n,1);
            }else if(opt==1){
                int l,r;
                cin>>l>>r;
                cout<<querymax(l,r,1,n,1)<<endl;
            }else {
                int l,r;
                cin>>l>>r;
                cout<<querysum(l,r,1,n,1)<<endl;
            }
        }
    }
}