 //利用主席树求区间最小值
/* #include <iostream>
  #include <cstdio>
  #include <cstring>
  #include <algorithm>
  using namespace std;
  const int maxn=200001;
  struct Node{
      int ls,rs;
      int cnt;
 }tr[maxn*20];
 int cur,rt[maxn];
 void init(){
     cur=0;
 }
 inline void push_up(int o){
     tr[o].cnt=tr[tr[o].ls].cnt+tr[tr[o].rs].cnt;
 }
 int build(int l,int r){
     int k=cur++;
     if (l==r) {
         tr[k].cnt=0;
         return k;
     }
     int mid=(l+r)>>1;
     tr[k].ls=build(l,mid);
     tr[k].rs=build(mid+1,r);
     push_up(k);
     return k;
 }
 int update(int o,int l,int r,int pos,int val){
     int k=cur++;
     tr[k]=tr[o];
     if (l==pos&&r==pos){
        tr[k].cnt+=val;
         return k;
     }
     int mid=(l+r)>>1;
     if (pos<=mid) tr[k].ls=update(tr[o].ls,l,mid,pos,val);
     else tr[k].rs=update(tr[o].rs,mid+1,r,pos,val);
     push_up(k);
     return k;
 }
 int query(int l,int r,int o,int v,int kth){
     if (l==r) return l;
     int mid=(l+r)>>1;
    int res=tr[tr[v].ls].cnt-tr[tr[o].ls].cnt;
     if (kth<=res) return query(l,mid,tr[o].ls,tr[v].ls,kth);
     else return query(mid+1,r,tr[o].rs,tr[v].rs,kth-res);
 }
 int b[maxn];
 int sortb[maxn];
 int main()
 {
     int n,m;
    // int T;
     //scanf("%d",&T);
     //while (T--){
     while (~scanf("%d%d",&n,&m)){
         init();
         for (int i=1;i<=n;i++){
             scanf("%d",&b[i]);
             sortb[i]=b[i];
         }
         sort(sortb+1,sortb+1+n);
         int cnt=1;
         for (int i=2;i<=n;i++){
             if (sortb[i]!=sortb[cnt]){
                 sortb[++cnt]=sortb[i];
             }
         }
         rt[0]=build(1,cnt);
         for (int i=1;i<=n;i++){
             int p=lower_bound(sortb+1,sortb+cnt+1,b[i])-sortb;
             rt[i]=update(rt[i-1],1,cnt,p,1);
         }
         for (int i=0;i<m;i++){
             int a,b,k;
             scanf("%d%d%d",&a,&b,&k);
             int idx=query(1,cnt,rt[a-1],rt[b],k);
             printf("%d\n",sortb[idx]);
         }
     }
     return 0;
 }
*/
//p3919
/*

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=(1e6+1);
int top,root[maxn],arr[maxn],n,m,cnt=0;
struct kkk{
    int l,r,val;
} a[maxn*30];
int build(int l,int r){
    int rt=++cnt;
    if(l==r)a[rt].val=arr[l];
    else {
        int mid=(l+r)>>1;
        a[rt].l=build(l,mid);
        a[rt].r=build(mid+1,r);
    }
    return rt;
}
int update(int ji,int jv,int l,int r,int i)//单点修改
{
    int rt=++cnt;
    a[rt].l=a[i].l;
    a[rt].r=a[i].r;
    if(l==r) a[rt].val=jv;
    else {
        int mid=(l+r)>>1;
        if(ji<=mid)a[rt].l=update(ji,jv,l,mid,a[rt].l);
        else a[rt].r=update(ji,jv,mid+1,r,a[rt].r);
    }
    return rt;
}
int query(int ji,int l,int r,int i){
    if(l==r) return a[i].val;
    int mid=(l+r)>>1;
    if(ji<=mid) return query(ji,l,mid,a[i].l);
    else return query(ji,mid+1,r,a[i].r);
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    root[0]=build(1,n);
    for(int i=1,version,op,x,v;i<=m;i++){
        cin>>version>>op>>x;
        if(op==1){
            cin>>v;
            root[i]=update(x,v,1,n,root[version]);
        }else {
            root[i]=root[version];
            cout<<query(x,1,n,root[i])<<endl;
        }
    }
}
*/
//单点修改+范围查询，最重要的模板
//求范围内第k小的数
//空间复杂度O（4*n+nlog（n）+mlog（n））
//P3834
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=200100;
ll n,m,s,arr[maxn],sorted[maxn],cnt,root[maxn];//sorted 用于离散化,cnt 动态分布编号，详见开点线段树篇
struct tree{
    ll l,r,size;//size用于存储排名范围内收集了多少数
}a[maxn*32];
ll build(ll l,ll r){
    int rt=++cnt;
    a[rt].size=0;
    if(l<r){
        ll mid=(l+r)>>1;
        a[rt].l=build(l,mid);
        a[rt].r=build(mid+1,r);
    }
    return rt;
}
ll insert(ll x,ll l,ll r,ll i){
    int rt=++cnt;
    a[rt].l=a[i].l;
    a[rt].r=a[i].r;
    a[rt].size=a[i].size+1;
    if(l<r){
        int mid=(l+r)>>1;
        if(x<=mid) a[rt].l=insert(x,l,mid,a[rt].l);
        else a[rt].r=insert(x,mid+1,r,a[rt].r);
    }
    return rt;
}
void prepare(){
    cnt=0;
    for(int i=1;i<=n;i++) sorted[i]=arr[i];
    sort(sorted+1,sorted+n+1);
    s=unique(sorted+1,sorted+n+1)-sorted-1;
    root[0]=build(1,s);
    for(int i=1;i<=n;i++){
        ll x=lower_bound(sorted+1,sorted+s+1,arr[i])-sorted;
        root[i]=insert(x,1,s,root[i-1]);
    }
}
int query(int jk,int l,int r,int u,int v){
    if(l==r){
        return l;
    }
    int lsize=a[a[v].l].size-a[a[u].l].size;
    int mid=(l+r)>>1;
    if(lsize>=jk){
        return query(jk,l,mid,a[u].l,a[v].l);
    }else return query(jk-lsize,mid+1,r,a[u].r,a[v].r);
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>arr[i];
    prepare();//离散化,并初始化
    for(int i=1;i<=m;i++){
        int l,r,k;
        cin>>l>>r>>k;
        cout<<sorted[query(k,1,s,root[l-1],root[r])]<<endl;
    }
}