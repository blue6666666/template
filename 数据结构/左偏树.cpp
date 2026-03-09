/*
//可并堆结构，两个堆的合并时间复杂度为log（n）
//查询操作需要并查集的优化
//P3377,模板
#include<bits/stdc++.h>
using namespace std;
const int maxn=100001;
int n,m;
int num[maxn],lef[maxn],righ[maxn],dis[maxn];
int father[maxn];
//father并不是代表该节点的父亲节点，而是代表并查集所对应的路径信息
//需要保证，并查集最上方代表节点=左偏树的头，也就是堆顶
void prepare(){
    dis[0]=-1;
    for(int i=1;i<=n;i++){
        lef[i]=0;
        righ[i]=0;
        dis[i]=0;
        father[i]=i;
    }
}
int find(int i){
    father[i]=father[i]==i?i:find(father[i]);
    return father[i];
}
int merge(int i,int j){
    if(i==0||j==0) return i+j;
    //维护小根堆，如果值一样，编号小的节点做头,大根堆同理
    if(num[i]>num[j]||(num[i]==num[j]&&i>j)){
        swap(i,j);
    }
    righ[i]=merge(righ[i],j);
    if(dis[lef[i]]<dis[righ[i]]){
        swap(lef[i],righ[i]);
    }
    dis[i]=dis[righ[i]]+1;
    father[lef[i]]=father[righ[i]]=i;
    return i;
}
//节点i一定是左偏树的头，在左偏树上删除节点i，返回新树的头结点编号
int pop(int i){
    father[lef[i]]=lef[i];
    father[righ[i]]=righ[i];
    father[i]=merge(lef[i],righ[i]);//保证删除节点后，能够正确再次查询
    lef[i]=righ[i]=dis[i]=0;
    return father[i];
}
int main(){
    cin>>n>>m;
    prepare();
    for(int i=1;i<=n;i++) cin>>num[i];
    for(int i=1;i<=m;i++){
        int op;
        cin>>op;
        if(op==1){
            int l,r;
            cin>>l>>r;
            if(num[l]!=-1&&num[r]!=-1){
                l=find(l),r=find(r);
                if(l!=r) merge(l,r);
            }
        }else {
            int x;
            cin>>x;
            if(num[x]==-1) cout<<-1<<endl;
            else {
            int ans=find(x);
            cout<<num[ans]<<endl;
            pop(ans);
            num[ans]=-1;
        }
    }
    }
}
*/

//进一步，删除任意一个节点
//P4971
#include<bits/stdc++.h>
using namespace std;
#define  int long long 
const int maxn=2000100;
int n,m;
int num[maxn],father[maxn],lef[maxn],righ[maxn],dis[maxn],up[maxn];
int t,w,k;
// up数组存储的就是节点真正的父节点
void prepare(){
    dis[0]=-1;
    for(int i=1;i<=n;i++){
        dis[i]=lef[i]=righ[i]=up[i]=0;
        father[i]=i;
    }
}
int find(int i){
    father[i]=father[i]==i?i:find(father[i]);
    return father[i];
}
int merge(int i,int j){
    if(i==0||j==0){
        return i+j;
    }
    //这段代码是维护的大根堆
    if(num[i]<num[j]||(num[i]==num[j]&&i>j)){
        swap(i,j);
    }
    righ[i]=merge(righ[i],j);
    up[righ[i]]=i;//多了一句
    if(dis[lef[i]]<dis[righ[i]]){
        swap(lef[i],righ[i]);
    }
    dis[i]=dis[righ[i]]+1;
    father[lef[i]]=father[righ[i]]=i;
    return i;
}
//删除任意节点，返回整棵树的头节点
//这是主要的改动
int remove(int i){
    int h=find(i);
    father[lef[i]]=lef[i];
    father[righ[i]]=righ[i];
    int s=merge(lef[i],righ[i]);
    int f=up[i];
    father[i]=s;
    up[s]=f;
    if(h!=i){
        father[s]=h;
        if(lef[f]==i) lef[f]=s;
        else righ[f]=s;
        for(int d=dis[s];dis[f]>d+1;f=up[f],d++){// log(n)
            if(dis[lef[f]]<dis[righ[f]]){
                swap(lef[f],righ[f]);
            }
            dis[f]=d+1;
        }
    }
    up[i]=lef[i]=righ[i]=dis[i]=0;
    return father[s];
}
void reduce(int i,int v){
    int h=remove(i);
    num[i]=max((int)0,num[i]-v);
    father[h]=father[i]=merge(h,i);
}
int compute(){
    int ans=0,mx=0;
    for(int i=1;i<=n;i++){
        if(father[i]==i) {
            ans+=num[i];
            mx=max(num[i],mx);
        }
    }
    if(w==2) ans-=mx;
    else if(w==3) ans+=mx;
    return ans;
}
void solve(){
    cin>>n>>m;
    prepare();
    for(int i=1;i<=n;i++){
        cin>>num[i];
    }
    for(int i=1;i<=m;i++){
        int op;
        cin>>op;
        if(op==2){
            int x;
            cin>>x;
            reduce(x,num[x]);
        }else if(op==3){
            int x,y;
            cin>>x>>y;
            reduce(find(x),y);
        }else {
            int x,y;
            cin>>x>>y;
            x=find(x),y=find(y);
            if(x!=y) merge(x,y);
        }
    }
    int ans=compute();
    if(ans==0) cout<<"Gensokyo"<<' ';
    else if(ans>k) cout<<"Hell"<<' ';
    else cout<<"Heaven"<<' ';
    cout<<ans<<endl;
}
signed main(){
ios::sync_with_stdio(0); 
cin.tie(0), cout.tie(0); 
    cin>>t>>w>>k;
    while(t--){
        solve();
    }
}