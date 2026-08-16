#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll arr[15010],n,height[15010];

struct node{
    ll l,r,h;
}a[15010];

struct compare{
    bool operator()(pair<ll,ll> a,pair<ll,ll> b){
        if(a.first!=b.first) return a.first<b.first;
        return a.second>b.second;
        //大根堆
    }
};
bool cmp(node x,node y){
    return x.l<y.l;
}
int main(){
    ll l,r,h,m=0;
    while(scanf("%lld %lld %lld",&l,&h,&r)!=EOF){
        a[++m].l=l;
        a[m].r=r-1;
        a[m].h=h;
        arr[++n]=l;
        arr[++n]=r;
        arr[++n]=r-1;
    }
    sort(arr+1,arr+n+1);
    ll len=unique(arr+1,arr+n+1)-arr-1;
    for(int j=1;j<=m;j++){
        a[j].l=lower_bound(arr+1,arr+len+1,a[j].l)-arr;
        a[j].r=lower_bound(arr+1,arr+len+1,a[j].r)-arr;
    }
    sort(a+1,a+m+1,cmp);
   priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, compare> heap;
   for(int i=1,j=0;i<=len;i++){
    for(;j<=m&&a[j].l<=i;j++){
        heap.push(make_pair(a[j].h,a[j].r));
    }
    while(!heap.empty()&&heap.top().second<i)
    {
        heap.pop();
    }
   
   if(!heap.empty()){
    height[i]=heap.top().first;
   }
}
    ll ansn=0;
    pair<ll,ll>ans[15010];
    for(ll i=1,pre=0;i<=len;i++){
        if(pre!=height[i]){
            ans[++ansn]=make_pair(arr[i],height[i]);
        }
        pre=height[i];
    }
    for(int i=1;i<=ansn;i++){
        cout<<ans[i].first<<' '<<ans[i].second<<' ';
    }
}