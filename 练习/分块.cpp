#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+10;
const int maxb=1e3+10;
int arr[maxn],sv[maxn],n,m;
int blen,bnum;
int bi[maxn],bl[maxb],br[maxb];
void build(){
    blen=sqrt(n);
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(i*blen,n);
    }
    for(int i=1;i<=n;i++) sv[i]=arr[i];
    for(int i=1;i<=bnum;i++){
        sort(sv+bl[i],sv+br[i]+1);
    }
}
int getcnt(int i,int v){
    int l=bl[i],r=br[i],m,res=0;
    while(l<=r){
        m=(l+r)>>1;
        if(sv[m]>=v){
            res+=r-m+1;
            r=m-1;
        }else l=m+1;
    }
    return res;

}
void update(int ii,int v){
    int l=bl[bi[ii]];
    int r=br[bi[ii]];
    arr[ii]=v;
    for(int i=l;i<=r;i++) sv[i]=arr[i];
    sort(sv+l,sv+r+1);
}
int query(int l,int r,int v){
    int res=0;
    if(bi[l]==bi[r]){
        for(int i=l;i<=r;i++){
            if(arr[i]>=v) res++;
        }
    }else{
        for(int i=l;i<=br[bi[l]];i++){
            if(arr[i]>=v) res++;
        }
        for(int i=bl[bi[r]];i<=r;i++){
            if(arr[i]>=v) res++;
        }
        for(int i=bi[l];i<bi[r];i++){
            res+=getcnt(i,v);
        }
    }
    return res;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    build();
    cin>>m;
    for(int i=1;i<=m;i++){
        int op,a,b,c;
        cin>>op>>a>>b;
        if(op==0){
            cin>>c;
            cout<<query(a,b,c)<<endl;
        }else update(a,b);
    }
}