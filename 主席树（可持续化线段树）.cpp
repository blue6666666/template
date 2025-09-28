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
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=(1e6+1);
int top,root[maxn],a[maxn],n,m,rt,x,y,mode;
struct kkk{
	int l,r,val;
}tree[maxn*30];
int clone(int node){
	top++;
	tree[top]=tree[node];//全部信息都传到新节点
	return top;
}
int maketree(int node,int begin,int end){
	node=++top;
	if(begin==end){
		tree[node].val=a[begin];
		return top;
	}
	int mid=(begin+end)>>1;
	tree[node].l=maketree(tree[node].l,begin,mid);
	tree[node].r=maketree(tree[node].r,mid+1,end);
	return node;
}
int update(int node,int begin,int end,int x,int val){
	node=clone(node);	//更新就要新建节点 
	if(begin==end){
		tree[node].val=val;
	}else{
		int mid=(begin+end)>>1;
		if(x<=mid)
			tree[node].l=update(tree[node].l,begin,mid,x,val);	//访问左子树 
		else
			tree[node].r=update(tree[node].r,mid+1,end,x,val);	//访问右子树 
	}
	return node;
}
int query(int node,int begin,int end,int x){
	if(begin==end){
		return tree[node].val;
	}else{
		int mid=(begin+end)>>1;
		if(x<=mid)
			return query(tree[node].l,begin,mid,x);	//访问左子树 
		else
			return query(tree[node].r,mid+1,end,x);	//访问右子树 
	}
}
    signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);  
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	root[0]=maketree(0,1,n);	//root[i]为i版本的根编号，刚开始编号为0 
	for(int i=1;i<=m;i++){
		scanf("%lld%lld%lld",&rt,&mode,&x);
		if(mode==1){
			scanf("%lld",&y);
			root[i]=update(root[rt],1,n,x,y);	//保存版本 
		}
		else{
			printf("%lld\n",query(root[rt],1,n,x));	//输出
			root[i]=root[rt];					
		}
	}
}
