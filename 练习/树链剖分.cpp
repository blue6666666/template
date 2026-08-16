// #include<bits/stdc++.h>
// using namespace std;
// const int maxn=2e5+10;
// int n,m,r,mod;
// int head[maxn<<1],ne[maxn<<1],to[maxn<<1],cntg=0;
// int fa[maxn],dep[maxn],siz[maxn],son[maxn],top[maxn],dfn[maxn],seg[maxn],cntd=0;
// long long arr[maxn<<1],lazy[maxn<<1];
// int a[maxn];
// void add(int u,int v){
//     ne[++cntg]=head[u];
//     to[cntg]=v;
//     head[u]=cntg;
// }
// void up(int rt){
//     arr[rt]=(arr[rt<<1]+arr[rt<<1|1])%mod;
// }
// void Lazy(int rt,long long v,int l){
//     arr[rt]=(arr[rt]+v*l)%mod;
//     lazy[rt]=(lazy[rt]+v)%mod;
// }
// void down(int rt,int ln,int rn){
//     if(lazy[rt]){
//         Lazy(rt<<1,lazy[rt],ln);
//         Lazy(rt<<1|1,lazy[rt],rn);
//         lazy[rt]=0;
//     }
// }
// void build(int l,int r,int rt){
//     if(l==r){
//         arr[rt]=a[seg[l]]%mod;
//         return;
//     }
//     int mid=(l+r)>>1;
//     build(l,mid,rt<<1);
//     build(mid+1,r,rt<<1|1);
//     up(rt);
// }
// void addv(int jl,int jr,long long v,int l,int r,int rt){
//     if(jl<=l&&r<=jr){
//         Lazy(rt,v,r-l+1);
//         return;
//     }
//     int mid=(l+r)>>1;
//     down(rt, mid - l + 1, r - mid);
//     if(jl<=mid) addv(jl,jr,v,l,mid,rt<<1);
//     if(mid<jr) addv(jl,jr,v,mid+1,r,rt<<1|1);
//     up(rt);
// }
// long long query(int jl,int jr,int l,int r,int rt){
//     if(jl<=l&&r<=jr){
//         return arr[rt];
//     }
//     long long ans=0;
//     int mid=(l+r)>>1;
//     down(rt,mid-l+1,r-mid);
//     if(jl<=mid) ans=(ans+query(jl,jr,l,mid,rt<<1))%mod;
//     if(mid<jr) ans=(ans+query(jl,jr,mid+1,r,rt<<1|1))%mod;
//     up(rt);
//     return ans;
// }
// void pathadd(int x,int y,long long v){
//     while(top[x]!=top[y]){
//         if(dep[top[x]]<=dep[top[y]]) swap(x,y);
//         addv(dfn[top[x]],dfn[x],v,1,n,1);
//         x=fa[top[x]];
//     }
//     addv(min(dfn[x],dfn[y]),max(dfn[x],dfn[y]),v,1,n,1);
// }
// long long pathsum(int x,int y){
//     long long ans=0;
//     while(top[x]!=top[y]){
//         if(dep[top[x]]<=dep[top[y]]) swap(x,y);
//         ans=(ans+query(dfn[top[x]],dfn[x],1,n,1))%mod;
//         x=fa[top[x]];
//     }
//     ans=(ans+query(min(dfn[x],dfn[y]),max(dfn[x],dfn[y]),1,n,1))%mod;
//     return ans;
// }
// void subtreeadd(int x,long long v){
//     addv(dfn[x],dfn[x]+siz[x]-1,v,1,n,1);
// }
// long long subtreesum(int x){
//     return query(dfn[x],dfn[x]+siz[x]-1,1,n,1);
// }
// void dfs1(int u,int f){
//     dep[u]=dep[f]+1;
//     fa[u]=f;
//     siz[u]=1;
//     int maxson=-1;
//     for(int ei=head[u];ei;ei=ne[ei]){
//         int v=to[ei];
//         if(v==f) continue;
//         dfs1(v,u);
//         siz[u]+=siz[v];
//         if(siz[v]>maxson) son[u]=v,maxson=siz[v];
//     }
// }
// void dfs2(int u,int topf){
//     dfn[u]=++cntd;
//     top[u]=topf;
//     seg[cntd]=u;
//     if(son[u]==0) return;
//     dfs2(son[u],topf);
//     for(int ei=head[u];ei;ei=ne[ei]){
//         int v=to[ei];
//         if(v==fa[u]||v==son[u]) continue;
//         dfs2(v,v);
//     }
// }
// int main(){
//     cin>>n>>m>>r>>mod;
//     for(int i=1;i<=n;i++){
//         cin>>a[i];
//     }
//     for(int i=1,u,v;i<n;i++){
//         cin>>u>>v;
//         add(u,v);
//         add(v,u);
//     }
//     dfs1(r,0);
//     dfs2(r,r);
//     build(1,n,1);
//     for(int i=1,op;i<=m;i++){
//         cin>>op;
//         int x,y;
//         long long z;
//         if(op==1){
//             cin>>x>>y>>z;
//             pathadd(x,y,z);
//         }else if(op==2){
//             cin>>x>>y;
//             cout<<pathsum(x,y)<<endl;
//         }else if(op==3){
//             cin>>x>>z;
//             subtreeadd(x,z);

//         }else{
//             cin>>x;

//             cout<<subtreesum(x)<<endl;
//         }
//     }

// }
// #include<bits/stdc++.h>
// using namespace std;
// const int maxn=2e5+10;
// int n,m;
// long long mod=1e10+10;
// int head[maxn<<2],ne[maxn<<2],to[maxn<<2],cntg=0;
// int fa[maxn],dep[maxn],siz[maxn],son[maxn],top[maxn],dfn[maxn],seg[maxn],cntd=0;
// long long arr[maxn<<2],lazy[maxn<<2],lcolor[maxn<<2],rcolor[maxn<<2];
// int a[maxn];
// void add(int u,int v){
//     ne[++cntg]=head[u];
//     to[cntg]=v;
//     head[u]=cntg;
// }
// void up(int rt){
//     arr[rt]=(arr[rt<<1]+arr[rt<<1|1]-(rcolor[rt<<1]==lcolor[rt<<1|1]));
//     lcolor[rt]=lcolor[rt<<1],rcolor[rt]=rcolor[rt<<1|1];
// }
// void Lazy(int rt,long long v){
//     arr[rt]=1;
//     lcolor[rt]=rcolor[rt]=lazy[rt]=v;
// }
// void down(int rt){
//     if(lazy[rt]){
//         Lazy(rt<<1,lazy[rt]);
//         Lazy(rt<<1|1,lazy[rt]);
//         lazy[rt]=0;
//     }
// }
// void build(int l,int r,int rt){
//     if(l==r){
//         lcolor[rt]=rcolor[rt]=a[seg[l]];
//         arr[rt]=1;
//         return;
//     }
//     int mid=(l+r)>>1;
//     build(l,mid,rt<<1);
//     build(mid+1,r,rt<<1|1);
//     up(rt);
// }
// void update(int jl,int jr,int jv,int l,int r,int rt){
//     if(jl<=l&&r<=jr){
//         Lazy(rt,jv);
//     }
//     else {
//         down(rt);
//         int mid=(l+r)>>1;
//     if(jl<=mid) update(jl,jr,jv,l,mid,rt<<1);
//     if(mid<jr) update(jl,jr,jv,mid+1,r,rt<<1|1);
//     up(rt);
//     }
// }
// long long query(int jl,int jr,int l,int r,int rt){
//     if(jl<=l&&r<=jr){
//         return arr[rt];
//     }
//     long long ans=0;
//     int mid=(l+r)>>1;
//     down(rt);
//     if(jr<=mid) ans=(ans+query(jl,jr,l,mid,rt<<1));
//     else if(mid<jl) ans=(ans+query(jl,jr,mid+1,r,rt<<1|1));
//     else{
//         ans=query(jl,jr,l,mid,rt<<1)+query(jl,jr,mid+1,r,rt<<1|1)-(rcolor[rt<<1]==lcolor[rt<<1|1]);
//     }
//     return ans;
// }
// int pointquery(int ji,int l,int r,int rt){
//     if(l==r){
//         return lcolor[rt];
//     }
//     down(rt);
//     int mid=(l+r)>>1;
//     if(ji<=mid) return pointquery(ji,l,mid,rt<<1);
//     else return pointquery(ji,mid+1,r,rt<<1|1);
// }
// void pathupdate(int u,int v,int c){
//     while(top[u]!=top[v]){
//         if(dep[top[u]]<=dep[top[v]]) swap(u,v);
//         update(dfn[top[u]],dfn[u],c,1,n,1);
//         u=fa[top[u]];
//     }
//      update(min(dfn[u],dfn[v]),max(dfn[v],dfn[u]),c,1,n,1);
// }
// long long pathsum(int x,int y){
//     long long ans=0;
//     while(top[x]!=top[y]){
//         if(dep[top[x]]<=dep[top[y]]) swap(x,y);
//         ans=(ans+query(dfn[top[x]],dfn[x],1,n,1));
//         int fc=pointquery(dfn[fa[top[x]]],1,n,1);
//         int sonc=pointquery(dfn[top[x]],1,n,1);
//         x=fa[top[x]];
//         if(fc==sonc) ans--;
//     }
//     ans=(ans+query(min(dfn[x],dfn[y]),max(dfn[x],dfn[y]),1,n,1))%mod;
//     return ans;
// }

// void dfs1(int u,int f){
//     dep[u]=dep[f]+1;
//     fa[u]=f;
//     siz[u]=1;
//     int maxson=-1;
//     for(int ei=head[u];ei;ei=ne[ei]){
//         int v=to[ei];
//         if(v==f) continue;
//         dfs1(v,u);
//         siz[u]+=siz[v];
//         if(siz[v]>maxson) son[u]=v,maxson=siz[v];
//     }
// }
// void dfs2(int u,int topf){
//     dfn[u]=++cntd;
//     top[u]=topf;
//     seg[cntd]=u;
//     if(son[u]==0) return;
//     dfs2(son[u],topf);
//     for(int ei=head[u];ei;ei=ne[ei]){
//         int v=to[ei];
//         if(v==fa[u]||v==son[u]) continue;
//         dfs2(v,v);
//     }
// }
// int main(){
//     cin>>n>>m;
//     for(int i=1;i<=n;i++){
//         cin>>a[i];
//     }
//     for(int i=1,u,v;i<n;i++){
//         cin>>u>>v;
//         add(u,v);
//         add(v,u);
//     }
//     dfs1(1,0);
//     dfs2(1,1);
//     build(1,n,1);
//     for(int i=1;i<=m;i++){
//         char op;
//         cin>>op;
//         int x,y,z;
//         if(op=='C'){
//             cin>>x>>y>>z;
//             pathupdate(x,y,z);
//         }else {
//             cin>>x>>y;
//             cout<<pathsum(x,y)<<endl;
//         }
        
//     }

// }
// #include<bits/stdc++.h>
// using namespace std;
// const int maxn=5e4+10;
// const int inf=1e9+10;
// struct q{
//     int mx,mn,lp,rp;
// };
// int n,m;
// int head[maxn<<2],ne[maxn<<2],to[maxn<<2],cntg=0;
// int fa[maxn],dep[maxn],siz[maxn],son[maxn],top[maxn],dfn[maxn],seg[maxn],cntd=0;
// long long lazy[maxn<<2],lp[maxn<<2],rp[maxn<<2],mx[maxn<<2],mn[maxn<<2];
// int a[maxn];
// void add(int u,int v){
//     ne[++cntg]=head[u];
//     to[cntg]=v;
//     head[u]=cntg;
// }
// void up(int rt){
//     mx[rt]=max(mx[rt<<1],mx[rt<<1|1]);
//     mn[rt]=min(mn[rt<<1],mn[rt<<1|1]);
//     lp[rt]=max({lp[rt<<1],lp[rt<<1|1],mx[rt<<1|1]-mn[rt<<1]});
//     rp[rt]=max({rp[rt<<1],rp[rt<<1|1],mx[rt<<1]-mn[rt<<1|1]});
// }
// void Lazy(int rt,long long v){
//     lazy[rt]+=v;
//     mx[rt]+=v;
//     mn[rt]+=v;
// }
// void down(int rt){
//     if(lazy[rt]){
//         Lazy(rt<<1,lazy[rt]);
//         Lazy(rt<<1|1,lazy[rt]);
//         lazy[rt]=0;
//     }
// }
// void build(int l,int r,int rt){
//     if(l==r){
//         mx[rt]=mn[rt]=a[seg[l]];
//         lp[rt]=rp[rt]=0;
//         return;
//     }
//     int mid=(l+r)>>1;
//     build(l,mid,rt<<1);
//     build(mid+1,r,rt<<1|1);
//     up(rt);
// }
// void update(int jl,int jr,int jv,int l,int r,int rt){
//     if(jl<=l&&r<=jr){
//         Lazy(rt,jv);
//     }
//     else {
//     down(rt);
//     int mid=(l+r)>>1;
//     if(jl<=mid) update(jl,jr,jv,l,mid,rt<<1);
//     if(mid<jr) update(jl,jr,jv,mid+1,r,rt<<1|1);
//     up(rt);
//     }
// }
// void merge(q&ans,int mx,int mn,int lp,int rp){
//     ans.lp=max({ans.lp,lp,mx-ans.mn});
//     ans.rp=max({ans.rp,rp,ans.mx-mn});
//     ans.mx=max(mx,ans.mx);
//     ans.mn=min(mn,ans.mn);
// }
// void query(q&ans,int jl,int jr,int l,int r,int rt){
//     if(jl<=l&&r<=jr){
//        merge(ans,mx[rt],mn[rt],lp[rt],rp[rt]);
//        return;
//     }
//     down(rt);
//     int mid=(l+r)>>1;
//     if(jl<=mid) query(ans,jl,jr,l,mid,rt<<1);
//     if(mid<jr) query(ans,jl,jr,mid+1,r,rt<<1|1);
// }
// void query(q&ans,int x,int y){
//     ans={-inf,inf,0,0};
//     query(ans,x,y,1,n,1);
// }

// int compute(int x,int y,int v){
//     int tx=x,ty=y;
//     q xp={-inf,inf,0,0};
//     q yp={-inf,inf,0,0};
//     q cur;
//     while(top[x]!=top[y]){
//         if(dep[top[x]]>dep[top[y]]){
//         query(cur,dfn[top[x]],dfn[x]);
//         merge(cur,xp.mx,xp.mn,xp.lp,xp.rp);
//         xp=cur;
//         x=fa[top[x]];
//         }else {
//         query(cur,dfn[top[y]],dfn[y]);
//         merge(cur,yp.mx,yp.mn,yp.lp,yp.rp);
//         yp=cur;
//         y=fa[top[y]];
//         }
//     }
//     if(dep[x]<=dep[y]) {
//     query(cur,dfn[x],dfn[y]);
//     merge(cur,yp.mx,yp.mn,yp.lp,yp.rp);
//     yp=cur;
//     }else {
//     query(cur,dfn[y],dfn[x]);
//     merge(cur,xp.mx,xp.mn,xp.lp,xp.rp);
//     xp=cur;
//     }
//     int ans=max(max(xp.rp,yp.lp),yp.mx-xp.mn);
//     x=tx,y=ty;
//     while(top[x]!=top[y]){
//         if(dep[top[x]]<=dep[top[y]]) swap(x,y);
//         update(dfn[top[x]],dfn[x],v,1,n,1);
//         x=fa[top[x]];
//     }
//     update(min(dfn[x],dfn[y]),max(dfn[x],dfn[y]),v,1,n,1);
//     return ans;
// }

// void dfs1(int u,int f){
//     dep[u]=dep[f]+1;
//     fa[u]=f;
//     siz[u]=1;
//     int maxson=-1;
//     for(int ei=head[u];ei;ei=ne[ei]){
//         int v=to[ei];
//         if(v==f) continue;
//         dfs1(v,u);
//         siz[u]+=siz[v];
//         if(siz[v]>maxson) son[u]=v,maxson=siz[v];
//     }
// }
// void dfs2(int u,int topf){
//     dfn[u]=++cntd;
//     top[u]=topf;
//     seg[cntd]=u;
//     if(son[u]==0) return;
//     dfs2(son[u],topf);
//     for(int ei=head[u];ei;ei=ne[ei]){
//         int v=to[ei];
//         if(v==fa[u]||v==son[u]) continue;
//         dfs2(v,v);
//     }
// }
// int main(){
//     cin>>n;
//     for(int i=1;i<=n;i++){
//         cin>>a[i];
//     }
//     for(int i=1,u,v;i<n;i++){
//         cin>>u>>v;
//         add(u,v);
//         add(v,u);
//     }
//     cin>>m;
//     dfs1(1,0);
//     dfs2(1,1);
//     build(1,n,1);
//     for(int i=1;i<=m;i++){
//         int x,y,v;
//         cin>>x>>y>>v;
//         cout<<compute(x,y,v)<<endl;
//     }

// }
//边权转点权技巧
//3038
#include<bits/stdc++.h>
using namespace std;
#define li i<<1
#define ri i<<1|1
const int maxn=1e5+10;
int head[maxn<<1],nex[maxn<<1],to[maxn<<1],tot=0;
int fa[maxn],dfn[maxn],seg[maxn],son[maxn],top[maxn],dep[maxn],siz[maxn],dfncnt=0;
int sum[maxn<<2],addtag[maxn<<2];
 int n,m;
void add(int u,int v){
    nex[++tot]=head[u];
    to[tot]=v;
    head[u]=tot;
}
void up(int i){
    sum[i]=sum[li]+sum[ri];
}
void Lazy(int i,int v,int n){
        sum[i]+=v*n;
        addtag[i]+=v;
}
void down(int i,int ln,int rn){
    if(addtag[i]){
        Lazy(li,addtag[i],ln);
        Lazy(ri,addtag[i],rn);
        addtag[i]=0;
    }
}
void update(int jl,int jr ,int v,int l,int r,int i){
    if(jl<=l&&r<=jr){
        Lazy(i,v,r-l+1);
    }else{
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        if(jl<=mid) update(jl,jr,v,l,mid,li);
        if(jr>mid) update(jl,jr,v,mid+1,r,ri);
        up(i);
    }
}
int querypoint(int ji ,int l,int r,int i){
    if(ji==l&&r==ji){
        return sum[i];     
    }else{
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        if(ji<=mid) return querypoint(ji,l,mid,li);
        else if(ji>mid) return querypoint(ji,mid+1,r,ri);
        
    }
}
void pathadd(int x,int y,int v){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        update(dfn[top[x]],dfn[x],v,1,n,1);
        x=fa[top[x]];
    }
    update(min(dfn[x],dfn[y])+1,max(dfn[x],dfn[y]),v,1,n,1);
}
int edgequery(int x,int y){
    return querypoint(max(dfn[x],dfn[y]),1,n,1);
}
void dfs1(int u,int f){
    dep[u]=dep[f]+1;
    fa[u]=f;
    siz[u]=1;
    int mx=-1;
    for(int ei=head[u];ei;ei=nex[ei]){
        int v=to[ei];
        if(v==f) continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(mx<siz[v]){
            mx=siz[v];
            son[u]=v;
        }
    }
}
void dfs2(int u,int topf){
    top[u]=topf;
    dfn[u]=++dfncnt;
    seg[dfncnt]=u;
    if(son[u]==0) return;
    dfs2(son[u],topf);
    for(int ei=head[u];ei;ei=nex[ei]){
        int v=to[ei];
        if(v==fa[u]||v==son[u]) continue;
        dfs2(v,v);
    }
}
int main(){
   
    cin>>n>>m;
    for(int i=1;i<n;i++){
        int u, v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs1(1,0);
    dfs2(1,1);
    char op;
    for(int i=1,x,y;i<=m;i++){
        cin>>op>>x>>y;
        if(op=='P') pathadd(x,y,1);
        else cout<<edgequery(x,y)<<endl;
    }
}