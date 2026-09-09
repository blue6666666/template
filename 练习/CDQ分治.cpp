//3810

// #include<bits/stdc++.h>
// using namespace std;
// const int maxn=1e5+10;
// const int maxk=2e5+10;
// struct node{
//     int idx,a,b,c;
//     bool operator==(const node& other) const {
//         return a == other.a &&b == other.b &&c == other.c;
//     }
// }t[maxn];
// int f[maxn],n,ans[maxk],k;
// struct BIT{
//     int n;
//     vector<int>t;
//     BIT(int n):n(n),t(n+1){};
//     int lowbit(int x) {return x&-x;}
//     void modify(int x,int d){
//         for(;x<=n;x+=lowbit(x)) t[x]+=d;
//     }
//     int query(int x){
//         int res=0;
//         for(;x;x-=lowbit(x)) res+=t[x];
//         return res;
//     }
// };
// BIT T(maxk);
// void prepare(){
//     sort(t+1,t+n+1,[](node a,node b){
//         if(a.a!=b.a) return a.a<b.a;
//         if(a.b!=b.b) return a.b<b.b;
//         return a.c<b.c;
//     });
//     for(int l=1,r=1;l<=n;l=++r){
//         while(r+1<=n&&t[l]==t[r+1]) r++;
//         for(int i=l;i<=r;i++){
//             f[t[i].idx]=r-i;
//         }
//     }
// }
// void merge(int l,int mid,int r){
//     int p,q;
//     for(p=l-1,q=mid+1;q<=r;q++){
//         while(p+1<=mid&&t[p+1].b<=t[q].b){
//             p++;
//             T.modify(t[p].c,1);
//         }
//         f[t[q].idx]+=T.query(t[q].c);
//     }
//     for(int i=l;i<=p;i++){
//         T.modify(t[i].c,-1);
//     }
//     sort(t+l,t+r+1,[](node a,node b){
//         return a.b<b.b;
//     });
// }
// void cdq(int l,int r){
//     if(l==r) return;
//     int mid=(l+r)>>1;
//     cdq(l,mid);
//     cdq(mid+1,r);
//     merge(l,mid,r);
// }

// int main(){
//     cin>>n>>k;
//     for(int i=1;i<=n;i++){
// //         cin>>t[i].a>>t[i].b>>t[i].c;
// //         t[i].idx=i;
// //     }
// //     prepare();
// //     cdq(1,n);
// //     for(int i=1;i<=n;i++){
// //         ans[f[i]]++;
// //     }
// //     for(int i=0;i<n;i++) cout<<ans[i]<<endl;
// // }
// #include<bits/stdc++.h>
// using namespace std;
// const int maxn=1e5+10;
// const int maxm=5e5+10;
// int n,m;
// long long ans[maxm],num[maxn],lo[maxn],del[maxm];
// struct node{
//     int x,l,d,q;
// }a[maxn+maxm];;
// int cnt=0;
// struct BIT{
//     int n;
//     vector<int>t;
//     BIT(int n):n(n),t(n+1){};
//     int lowbit(int x) {return x&-x;}
//     void modify(int x,int d){
//         for(;x<=n;x+=lowbit(x)) t[x]+=d;
//     }
//     int query(int x){
//         int res=0;
//         for(;x;x-=lowbit(x)) res+=t[x];
//         return res;
//     }
// }T(maxn);
// void prepare(){
//     for(int i=1;i<=n;i++){
//         a[++cnt].x=num[i];
//         a[cnt].l=i;
//         a[cnt].d=1;
//         a[cnt].q=0;
//     }
//     for(int i=1;i<=m;i++){
//         a[++cnt].x=del[i];
//         a[cnt].l=lo[del[i]];
//         a[cnt].d=-1;
//         a[cnt].q=i;
//     }
// }
// void merge(int l, int mid, int r) {
//     // 处理左区间位置 < 右区间位置，且左值 > 右值
//     int p = l;
//     for (int q = mid + 1; q <= r; ++q) {
//         while (p <= mid && a[p].l < a[q].l) {
//             T.modify(a[p].x, a[p].d);
//             ++p;
//         }
//         ans[a[q].q] += a[q].d * (T.query(n) - T.query(a[q].x));
//     }
//     for (int i = l; i < p; ++i) {
//         T.modify(a[i].x, -a[i].d);
//     }

//     // 处理左区间位置 > 右区间位置，且左值 < 右值
//     p = mid;
//     for (int q = r; q > mid; --q) {
//         while (p >= l && a[p].l > a[q].l) {
//             T.modify(a[p].x, a[p].d);
//             --p;
//         }
//         ans[a[q].q] += a[q].d * T.query(a[q].x - 1);
//     }
//     for (int i = p + 1; i <= mid; ++i) {
//         T.modify(a[i].x, -a[i].d);
//     }

//     // 按位置 l 归并排序
//     sort(a + l, a + r + 1, [](const node& u, const node& v) {
//         return u.l < v.l;
//     });
// }
// void cdq(int l,int r){
//     if(l==r) return;
//     int mid=(l+r)>>1;
//     cdq(l,mid),cdq(mid+1,r);
//     merge(l,mid,r);
// } 
// int main(){
//     cin>>n>>m;
//     for(int i=1;i<=n;i++){
//         cin>>num[i];
//         lo[num[i]]=i;
//     }
//     for(int i=1;i<=m;i++){
//         cin>>del[i];
//     }
//     prepare();
//     cdq(1,cnt);
//     for(int i=1;i<m;i++){
//         ans[i]+=ans[i-1];
//     }
//     for(int i=0;i<m;i++){
//         cout<<ans[i]<<endl;
//     }
// }
// #include<bits/stdc++.h>
// using namespace std;
// const int maxn=2e5+10;
// int cnt;
// struct node{
//     int op,x,y,v,q;
// }a[maxn*5],tmp[maxn*5];
// int ans[maxn];

// void add(int x,int y,int v,int q){

//     a[++cnt].x=x;
//     a[cnt].y=y;
//     a[cnt].v=v;
//     a[cnt].q=q;
//     a[cnt].op=2;
// }
// void merge(int l,int m,int r){
//     int p1,p2,tree=0;
//     for(p1=l-1,p2=m+1;p2<=r;p2++){
//         while(p1+1<=m&&a[p1+1].y<=a[p2].y){
//             p1++;
//             if(a[p1].op==1) tree++;
//         }
//         if(a[p2].op==2){
//             ans[a[p2].q]+=tree*a[p2].v;
//         }
//     }
//     p1=l,p2=m+1;
//     int i=l;
//     while(p1<=m&&p2<=r){
//         tmp[i++]=a[p1].y<=a[p2].y?a[p1++]:a[p2++];
//     }
//     while(p1<=m){
//          tmp[i++]=a[p1++];
//     }
//     while(p2<=r){
//         tmp[i++]=a[p2++];
//     }
//     for(i=l;i<=r;i++){
//         a[i]=tmp[i];
//     }
// }
// void cdq(int l,int r){
//     if(l==r) return;
//     int mid=(l+r)/2;
//     cdq(l,mid);
//     cdq(mid+1,r);
//     merge(l,mid,r);
// }
// int main(){
//     int n,m;
//     cin>>n>>m;
//     for(int i=1,x,y;i<=n;i++){
//         cin>>x>>y;
//         cnt++;
//         a[cnt].op=1;
//         a[cnt].x=x;
//         a[cnt].y=y;
//     }
//     for(int i=1,x,y,x2,y2;i<=m;i++){
//         cin>>x>>y>>x2>>y2;
//         add(x-1,y-1,1,i);
//         add(x2,y2,1,i);
//         add(x-1,y2,-1,i);
//         add(x2,y-1,-1,i);
//     }
// sort(a+1,a+cnt+1,[](const node &x, const node &y){
//     if (x.x != y.x) return x.x < y.x;
//     if (x.y != y.y) return x.y < y.y;
//     return x.op < y.op;   
// });
//     cdq(1,cnt);
//     for(int i=1;i<=m;i++){
//         cout<<ans[i]<<endl;
//     }
// }
// #include<bits/stdc++.h>
// using namespace std;
// const int maxn=1e5+10;
// struct BIT {
// 	int n;
//     vector<int> t;
//     BIT(int n): n(n), t(n+1) { }  // 注意值域树状数组中 n=tot
//     int lowbit(int x) { return x&-x; }
//     void more(int x, int d) {
//         for (; x <= n; x += lowbit(x)) { t[x] = max(d,t[x]); }
//     }
//     int query(int x) {
//         int res = 0;
//         for (; x; x -= lowbit(x)) { res = max(t[x],res); }
//         return res;
//     }
//     void clear(int x){
//         for(;x<=n;x+=lowbit(x)){t[x]=0;}
//     }
// };
// BIT T(maxn);
// int n,m,v[maxn],lv[maxn],rv[maxn],dp[maxn];
// struct node{
//     int i,v,lv,rv;
// }a[maxn];
// void merge(int l,int m,int r){
//     for(int i=l;i<=r;i++){
//         a[i]={i,v[i],lv[i],rv[i]};
//     }
//     sort(a+l,a+m+1,[](node x,node y){
//         if(x.v!=y.v) return x.v<y.v;
//         return x.rv<y.rv;
//     });
//     sort(a+m+1,a+r+1,[](node x,node y){
//         if(x.lv!=y.lv) return x.lv<y.lv;
//         return x.v<y.v;
//     });
//     int p1,p2;
//     for(p1=l-1,p2=m+1;p2<=r;p2++){
//         while(p1+1<=m&&a[p1+1].v<=a[p2].lv){
//             p1++;
//             T.more(a[p1].rv,dp[a[p1].i]);
//         }
//         dp[a[p2].i]=max(T.query(a[p2].v)+1,dp[a[p2].i]);
//     }
//     for(int i=l;i<=p1;i++){
//         T.clear(a[i].rv);
//     }
// }
// void cdq(int l,int r){
//     if(l==r){
//         return;
//     }
//     int mid=(l+r)>>1;
//     cdq(l,mid);
//     merge(l,mid,r);
//     cdq(mid+1,r);
// }
// int main(){
//     cin>>n>>m;
//     for(int i=1;i<=n;i++){
//         cin>>v[i];
//         lv[i]=v[i];
//         rv[i]=v[i];
//     }
//     for(int i=1;i<=m;i++){
//         int l,vv;
//         cin>>l>>vv;
//         lv[l]=min(vv,lv[l]);
//         rv[l]=max(vv,rv[l]);
//     }
//     for(int i=1;i<=n;i++){
//         dp[i]=1;
//     }
//     cdq(1,n);
//     int ans=0;
//     for(int i=1;i<=n;i++){
//         ans=max(ans,dp[i]);
//     }
//     cout<<ans<<endl;
// }
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e4+10;
struct BIT {
	int n;
    vector<int> t;
    vector<int> cnt;
    BIT(int n): n(n), t(n+1,0),cnt(n+1,0) { }  // 注意值域树状数组中 n=tot
    int lowbit(int x) { return x&-x; }
    void more(int x, int d) {
        for (; x <= n; x += lowbit(x)) { t[x] = max(d,t[x]); }
    }
    int query(int x) {
        int res = 0;
        for (; x; x -= lowbit(x)) { res = max(t[x],res); }
        return res;
    }
    void clear(int x){
        for(;x<=n;x+=lowbit(x)){t[x]=0;cnt[x]=0;}
    }
};
BIT T(maxn);
int h[maxn],v[maxn];
int pl[maxn],sl[maxn],pc[maxn],sc[maxn];
void merge(int l,int m,int r){
    
}
void cdq(int l,int r){
    if(l==r) return;
    int mid=(l+r)>>1;
    cdq(l,mid);
    merge(l,mid,r);
    cdq(mid+1,r);
}