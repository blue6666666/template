// //没有修改操作，只靠遍历子树就可以得到结果
// #include<bits/stdc++.h>
// using namespace std;
// const int maxn=1e5+10;
// int n,m,color[maxn],a[maxn],ans[maxn];
// int head[maxn<<1],nex[maxn<<1],to[maxn<<1];
// int fa[maxn],dfn[maxn],siz[maxn],son[maxn];
// int dfncnt,tot,diff;

// void add(int u,int v){
//     nex[++tot]=head[u];
//     to[tot]=v;
//     head[u]=tot;
// }
// void dfs1(int u,int f){
//     fa[u]=f;
//     siz[u]=1;
//     for(int ei=head[u];ei;ei=nex[ei]){
//         int v=to[ei];
//         if(v==f) continue;
//         dfs1(v, u);
//         siz[u]+=siz[v];
//         if(son[u]==0||siz[son[u]]<siz[v]){
//             son[u]=v;
//         }
//     }
// }

// void effect(int u){
//     if(++color[a[u]]==1) diff++;
//     for(int ei=head[u];ei;ei=nex[ei]){
//         int v=to[ei];
//         if(v==fa[u]) continue;
//         effect(v);
//     }
// }
// void cancle(int u){
//     if(--color[a[u]]==0) diff--;
//     for(int ei=head[u];ei;ei=nex[ei]){
//         int v=to[ei];
//         if(v==fa[u]) continue;
//         cancle(v);
//     }
// }
// void dfs2(int u,int keep){
//     for(int ei=head[u];ei;ei=nex[ei]){
//         int v=to[ei];
//         if(v==fa[u]||v==son[u]) continue;
//         dfs2(v,0);
//     }
//     if(son[u]!=0) dfs2(son[u],1);
//     if(++color[a[u]]==1) diff++;
//     for(int ei=head[u];ei;ei=nex[ei]){
//         int v=to[ei];
//         if(v==fa[u]||v==son[u]) continue;
//         effect(v);
//     }
//     ans[u]=diff;
//     if(keep==0) cancle(u);
// }

// int main(){
//     cin>>n;
//     for(int i=1;i<n;i++){
//         int u,v;
//         cin>>u>>v;
//         add(u,v);
//         add(v,u);
//     }
//     for(int i=1;i<=n;i++) cin>>a[i];
//     dfs1(1,0);
//     dfs2(1,0);
//     cin>>m;
//     for(int i=1,u;i<=m;i++){
//         cin>>u;
//         cout<<ans[u]<<endl;
//     }
// }

//9233
// #include<bits/stdc++.h>
// using namespace std;
// const int maxn=2e5+10;
// int n,m,color[maxn],a[maxn],ans,num[maxn];
// int head[maxn<<1],nex[maxn<<1],to[maxn<<1];
// int fa[maxn],dfn[maxn],siz[maxn],son[maxn];
// int dfncnt,tot,diff;

// void add(int u,int v){
//     nex[++tot]=head[u];
//     to[tot]=v;
//     head[u]=tot;
// }
// void dfs1(int u,int f){
//     fa[u]=f;
//     siz[u]=1;
//     for(int ei=head[u];ei;ei=nex[ei]){
//         int v=to[ei];
//         if(v==f) continue;
//         dfs1(v, u);
//         siz[u]+=siz[v];
//         if(son[u]==0||siz[son[u]]<siz[v]){
//             son[u]=v;
//         }
//     }
// }

// void effect(int u){
//     color[a[u]]++;
//     num[color[a[u]]]++;
//     num[color[a[u]]-1]--;
//     for(int ei=head[u];ei;ei=nex[ei]){
//         int v=to[ei];
//         if(v==fa[u]) continue;
//         effect(v);
//     }
// }
// void cancle(int u){
//     color[a[u]]--;
//     num[color[a[u]]]++;
//     num[color[a[u]]+1]--;
   
//     for(int ei=head[u];ei;ei=nex[ei]){
//         int v=to[ei];
//         if(v==fa[u]) continue;
//         cancle(v);
//     }
// }
// void dfs2(int u,int keep){
//     for(int ei=head[u];ei;ei=nex[ei]){
//         int v=to[ei];
//         if(v==fa[u]||v==son[u]) continue;
//         dfs2(v,0);
//     }
//     if(son[u]!=0) dfs2(son[u],1);
//     color[a[u]]++;
//     num[color[a[u]]]++;
//     num[color[a[u]]-1]--;
//     for(int ei=head[u];ei;ei=nex[ei]){
//         int v=to[ei];
//         if(v==fa[u]||v==son[u]) continue;
//         effect(v);
//     }
//     if(num[color[a[u]]]*color[a[u]]==siz[u]) ans++;
//     if(keep==0) cancle(u);
// }

// int main(){
//     cin>>n;
//     for(int i=1;i<=n;i++){
//         int f;
//         cin>>a[i]>>f;
//         add(f,i);
//     }
//     dfs1(1,0);
//     dfs2(1,0);
//     cout<<ans<<endl;
// }

// #include<bits/stdc++.h>
// using namespace std;
// const int maxn=2e5+10;
// int n,m,ca[maxn],cb[maxn],a[maxn],b[maxn],ans[maxn];
// int head[maxn<<1],nex[maxn<<1],to[maxn<<1];
// int fa[maxn],dfn[maxn],siz[maxn],son[maxn];
// int dfncnt,tot,diff;
// int n;
// void clear(){
//     tot=0;
//     for(int i=1;i<=2*n;i++){
//         head[i]=nex[i]=to[i]=0;
//     }
//     for(int i=1;i<=n;i++){
//         fa[i]=siz[i]=son[i]=ans[i]=0;
//     }
//     dfncnt=0;
// }
// void add(int u,int v){
//     nex[++tot]=head[u];
//     to[tot]=v;
//     head[u]=tot;
// }
// void dfs1(int u,int f){
//     fa[u]=f;
//     siz[u]=1;
//     for(int ei=head[u];ei;ei=nex[ei]){
//         int v=to[ei];
//         if(v==f) continue;
//         dfs1(v, u);
//         siz[u]+=siz[v];
//         if(son[u]==0||siz[son[u]]<siz[v]){
//             son[u]=v;
//         }
//     }
// }

// void effect(int u){
//     if(a[u]){
//         if(ca[a[u]]>=cb[a[u]]){
//             diff++;
//         }
//         ca[a[u]]++;
//     }
//     if(b[u]){
//         if(cb[b[u]]>=ca[b[u]]){
//             diff++;
//         }
//         cb[b[u]]++;
//     }
//     for(int ei=head[u];ei;ei=nex[ei]){
//         int v=to[ei];
//         if(v==fa[u]) continue;
//         effect(v);
//     }
// }
// void cancle(int u){
//     diff=0;
//    ca[a[u]]=0;
//    cb[b[u]]=0;
//     for(int ei=head[u];ei;ei=nex[ei]){
//         int v=to[ei];
//         if(v==fa[u]) continue;
//         cancle(v);
//     }
// }
// void dfs2(int u,int keep){
//     for(int ei=head[u];ei;ei=nex[ei]){
//         int v=to[ei];
//         if(v==fa[u]||v==son[u]) continue;
//         dfs2(v,0);
//     }
//     if(son[u]!=0) dfs2(son[u],1);
//     if(a[u]){
//         if(ca[a[u]]>=cb[a[u]]){
//             diff++;
//         }
//         ca[a[u]]++;
//     }
//     if(b[u]){
//         if(cb[b[u]]>=ca[b[u]]){
//             diff++;
//         }
//         cb[b[u]]++;
//     }
//     for(int ei=head[u];ei;ei=nex[ei]){
//         int v=to[ei];
//         if(v==fa[u]||v==son[u]) continue;
//         effect(v);
//     }
//     if(diff<=siz[u]) ans[u]=1;
//     if(keep==0) cancle(u);
// }
// void solve(){
//     cin>>n;
//     clear();
//     for(int i=1;i<=n;i++){
//         cin>>a[i];
//     }
//     for(int i=1;i<=n;i++){
//         cin>>b[i];
//     }
//     for(int i=1,u,v;i<n;i++){
//         cin>>u>>v;
//         add(u,v);
//         add(v,u);
//     }
//     dfs1(1,0);
//     dfs2(1,0);
//     for(int i=1;i<=n;i++){
//         cout<<ans[i];
//     }
//     cout<<endl;
// }
// int main(){
//     int t;
//     cin>>t;
//     while(t--){
//         solve();
//     }
// }

//CF246E
#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

int h[maxn], t[maxn], nxt[maxn], tot1;
int hq[maxn], id[maxn], nq[maxn], kq[maxn], tot2;

int dep[maxn], fa[maxn], son[maxn], siz[maxn];
vector< set<string> > se;
int ans[maxn];
string s[maxn];
int nn, m;

void add1(int u, int v) {
    t[++tot1] = v;
    nxt[tot1] = h[u];
    h[u] = tot1;
}

void add2(int u, int v, int k) {
    id[++tot2] = v;
    nq[tot2] = hq[u];
    kq[tot2] = k;
    hq[u] = tot2;
}

void dfs1(int u, int f) {
    fa[u] = f;                    
    dep[u] = dep[f] + 1;
    siz[u] = 1;
    for (int ei = h[u]; ei; ei = nxt[ei]) {
        int v = t[ei];
        if (v == f) continue;
        dfs1(v, u);               
        siz[u] += siz[v];
        if (!son[u] || siz[son[u]] < siz[v])
            son[u] = v;
    }
}

void effect(int u) {
    se[dep[u]].insert(s[u]);
    for (int ei = h[u]; ei; ei = nxt[ei]) {
        int v = t[ei];
        if (v == fa[u]) continue;
        effect(v);
    }
}

void clear(int u) {
    se[dep[u]].erase(s[u]);
    for (int ei = h[u]; ei; ei = nxt[ei]) {
        int v = t[ei];
        if (v == fa[u]) continue;
        clear(v);
    }
}

void dfs2(int u, int keep) {
    for (int ei = h[u]; ei; ei = nxt[ei]) {
        int v = t[ei];
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, 0);
    }
    if (son[u]) dfs2(son[u], 1);
    se[dep[u]].insert(s[u]);
    for (int ei = h[u]; ei; ei = nxt[ei]) {
        int v = t[ei];
        if (v == fa[u] || v == son[u]) continue;
        effect(v);
    }
    for (int ei = hq[u]; ei; ei = nq[ei]) {
        if (dep[u] + kq[ei] > nn) continue;
        ans[id[ei]] = se[dep[u] + kq[ei]].size();
    }
    if (keep == 0) clear(u);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> nn;
    for (int i = 1; i <= nn; ++i) {
        cin >> s[i] >> fa[i];
        if (fa[i]) add1(fa[i], i);
    }

    for (int i = 1; i <= nn; ++i) {
        if (!fa[i]) dfs1(i, 0);
    }

    se.resize(nn + 1);
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        int v, k;
        cin >> v >> k;
        add2(v, i, k);
    }

    for (int i = 1; i <= nn; ++i) {
        if (!fa[i]) dfs2(i, 0);
    }

    for (int i = 1; i <= m; ++i)
        cout << ans[i] << '\n';
    return 0;
}