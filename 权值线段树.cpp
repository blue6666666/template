/*#include<bits/stdc++.h>
using namespace std;
#define lson pos<<1
#define rson pos<<1|1
void build(int pos,int l,int r)
{
	int mid=(l+r)>>1;
	if(l==r)
	{
		tree[pos]=a[l];//a[l]表示数l有多少个
		return;
	}
	build(lson,l,mid);
	build(rson,mid+1,r);
	tree[pos]=tree[lson]+tree[rson];
}
void update(int pos,int l,int r,int k,int cnt)//表示数k的个数多cnt个
{
	int mid=(l+r)>>1;
	if(l==r)
	{
		tree[pos]+=cnt;
		return;
	}
	if(k<=mid)
		update(lson,l,mid,k,cnt);
	else	
		update(rson,mid+1,r,k,cnt);
	tree[pos]=tree[lson]+tree[rson];
}
int query(int pos,int l,int r,int k)//查询数k有多少个
{
	int mid=(l+r)>>1;
	if(l==r)
		return tree[pos];
	if(k<=mid)
		return query(lson,l,mid,k);
	else
		return query(rson,mid+1,r,k);
}
int kth(int pos,int l,int r,int k)//查询第k大值是多少
{
	int mid=(l+r)>>1;
	if(l==r)
		return l;
	if(k<mid)
		return kth(rson,mid+1,r,k);
	else
		return kth(lson,l,mid,k-mid);
}*/