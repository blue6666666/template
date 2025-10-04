//区间最值操作经典题 hdu 5306
/*
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
}*/
//如果在上一题的基础上补充范围增加，则代码如下
/*#include<bits/stdc++.h>
using namespace std;
const int maxn=1000001;
const int minest=-1000001;
long long arr[maxn<<2],sum[maxn<<2],mx[maxn<<2],sem[maxn<<2],cnt[maxn<<2],maxadd[maxn<<2],otheradd[maxn<<2];
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
void Lazy(int i,int n,long long maxaddv,long long otheraddv){
    sum[i]+=maxaddv*cnt[i]+otheraddv*(n-cnt[i]);
    mx[i]+=maxaddv;
    sem[i]+=sem[i]==minest?0:otheraddv;
    maxadd[i]+=maxaddv;
    otheradd[i]+=otheraddv;
}
void down(int i,int ln,int rn){
    int l=i<<1;
    int r=i<<1|1;
    int temp=max(mx[l],mx[r]);
    if(mx[l]==temp){
        Lazy(l,ln,maxadd[i],otheradd[i]);
    }else Lazy(l,ln,otheradd[i],otheradd[i]);
    if(mx[r]==temp) Lazy(r,rn,maxadd[i],otheradd[i]);
    else Lazy(r,rn,otheradd[i],otheradd[i]);
    maxadd[i]=0;
    otheradd[i]=0;
}
void setmin(int jl,int jr,int v,int l,int r,int i){
    if(v>mx[i]) return;
    if(jl<=l&&r<=jr&&v>sem[i]){
        Lazy(i,r-l+1,v-mx[i],0);
        return;
    }else {
        
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        if(jl<=mid) setmin(jl,jr,v,l,mid,i<<1);
        if(jr>mid) setmin(jl,jr,v,mid+1,r,i<<1|1);
    }
    up(i);
}
void add(int jl,int jr,int v,int l,int r,int i){
    if(jl<=l&&r<=jr){
        Lazy(i,r-l+1,v,v);
    }else {
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        if(jl<=mid) add(jl,jr,v,l,mid,i<<1);
        if(jr>mid) add(jl,jr,v,mid+1,r,i<<1|1);
        up(i);
    }
}
long long querymax(int jl,int jr,int l,int r,int i){
    if(jl<=l&&r<=jr){
        return mx[i];
    }
    
    int mid=(l+r)>>1;
    down(i,mid-l+1,r-mid);
    long long lm=minest,rm=minest;
    if(jl<=mid) lm=querymax(jl,jr,l,mid,i<<1);
    if(jr>mid)  rm=querymax(jl,jr,mid+1,r,i<<1|1);
    return max(lm,rm);
}
long long querysum(int jl,int jr,int l,int r,int i){
    if(jl<=l&&r<=jr){
        return sum[i];
    }
 
    int mid=(l+r)>>1;
    down(i,mid-l+1,r-mid);
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
*/
//于此基础上如果还要增加一个查询历史最大值的操作
#include<bits/stdc++.h>
using namespace std;
const int maxn=500010;
const long long minest=-1e18;
long long arr[maxn<<2],sum[maxn<<2],mx[maxn<<2],sem[maxn<<2],cnt[maxn<<2],maxadd[maxn<<2],otheradd[maxn<<2];
long long maxhistory[maxn<<2],maxaddtop[maxn<<2],otheraddtop[maxn<<2];
void up(int i){
    int l=i<<1;
    int r=i<<1|1;
    sum[i]=sum[l]+sum[r];
    maxhistory[i]=max(maxhistory[l],maxhistory[r]);
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
//maxaddvtop:最大值到过的最大提升幅度
//otheraddvtop：其他值到过的最大提升幅度
void Lazy(int i,int n,long long maxaddv,long long otheraddv,long long maxaddvtop,long long otheraddvtop){
    maxhistory[i]=max(maxhistory[i],mx[i]+maxaddvtop);
    maxaddtop[i]=max(maxaddtop[i],maxadd[i]+maxaddvtop);
    otheraddtop[i]=max(otheraddtop[i],otheradd[i]+otheraddvtop);
    sum[i]+=maxaddv*cnt[i]+otheraddv*(n-cnt[i]);
    mx[i]+=maxaddv;
    sem[i]+=sem[i]==minest?0:otheraddv;
    maxadd[i]+=maxaddv;
    otheradd[i]+=otheraddv;
    
}
void down(int i,int ln,int rn){
    int l=i<<1;
    int r=i<<1|1;
    int temp=max(mx[l],mx[r]);
    if(mx[l]==temp){
        Lazy(l,ln,maxadd[i],otheradd[i],maxaddtop[i],otheraddtop[i]);
    }else Lazy(l,ln,otheradd[i],otheradd[i],otheraddtop[i],otheraddtop[i]);
    if(mx[r]==temp) Lazy(r,rn,maxadd[i],otheradd[i],maxaddtop[i],otheraddtop[i]);
    else Lazy(r,rn,otheradd[i],otheradd[i],otheraddtop[i],otheraddtop[i]);
    maxadd[i]=0;
    otheradd[i]=0;
    maxaddtop[i]=0;
    otheraddtop[i]=0;
}
void setmin(int jl,int jr,long long v,int l,int r,int i){
    if(v>mx[i]) return;
    if(jl<=l&&r<=jr&&v>sem[i]){
        Lazy(i,r-l+1,v-mx[i],0,v-mx[i],0);
        return;
    }else {
        
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        if(jl<=mid) setmin(jl,jr,v,l,mid,i<<1);
        if(jr>mid) setmin(jl,jr,v,mid+1,r,i<<1|1);
    }
    up(i);
}
void add(int jl,int jr,long long v,int l,int r,int i){
    if(jl<=l&&r<=jr){
        Lazy(i,r-l+1,v,v,v,v);
    }else {
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        if(jl<=mid) add(jl,jr,v,l,mid,i<<1);
        if(jr>mid) add(jl,jr,v,mid+1,r,i<<1|1);
        up(i);
    }
}
long long querymax(int jl,int jr,int l,int r,int i){
    if(jl<=l&&r<=jr){
        return mx[i];
    }
    
    int mid=(l+r)>>1;
    down(i,mid-l+1,r-mid);
    long long lm=minest,rm=minest;
    if(jl<=mid) lm=querymax(jl,jr,l,mid,i<<1);
    if(jr>mid)  rm=querymax(jl,jr,mid+1,r,i<<1|1);
    return max(lm,rm);
}
long long queryhistorymax(int jl,int jr,int l,int r,int i){
    if(jl<=l&&r<=jr){
        return maxhistory[i];
    }
    
    int mid=(l+r)>>1;
    down(i,mid-l+1,r-mid);
    long long lm=minest,rm=minest;
    if(jl<=mid) lm=queryhistorymax(jl,jr,l,mid,i<<1);
    if(jr>mid)  rm=queryhistorymax(jl,jr,mid+1,r,i<<1|1);
    return max(lm,rm);
}
long long querysum(int jl,int jr,int l,int r,int i){
    if(jl<=l&&r<=jr){
        return sum[i];
    }
 
    int mid=(l+r)>>1;
    down(i,mid-l+1,r-mid);
    long long ans=0;
    if(jl<=mid) ans+=querysum(jl,jr,l,mid,i<<1);
    if(jr>mid)  ans+=querysum(jl,jr,mid+1,r,i<<1|1);
    return ans;
}
void build(int l,int r,int i){
    maxadd[i]=0;
    otheradd[i]=0;
    maxaddtop[i]=0;
    otheraddtop[i]=0;
    if(l==r){
        sum[i]=arr[l];
        mx[i]=arr[l];
        sem[i]=minest;
        cnt[i]=1;
        maxhistory[i]=arr[l];
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
    //cin>>t;
    //while(t--){
        int n,m;
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            cin>>arr[i];
        }
        build(1,n,1);
        while(m--){
            int opt;
            cin>>opt;
            if(opt==1){
                int l,r;
                long long v;
                cin>>l>>r>>v;
                add(l,r,v,1,n,1);
            }else if(opt==2){
                long long l,r,v;
                cin>>l>>r>>v;
                setmin(l,r,v,1,n,1);
            }else if (opt==3){
                int l,r;
                cin>>l>>r;
                cout<<querysum(l,r,1,n,1)<<endl;
            }else if(opt==4){
                int l,r;
                cin>>l>>r;
                cout<<querymax(l,r,1,n,1)<<endl;
            }else {
                int l,r;
                cin>>l>>r;
                cout<<queryhistorymax(l,r,1,n,1)<<endl;
            }
        }
    //}
}