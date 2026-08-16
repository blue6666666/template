//将复杂样本变成数字
//long base = 599
// 1313,131,21,131313等值容易被出题人针对

//easy case:P3370
// #include<bits/stdc++.h>
// using namespace std;
// int n;
// const long long base=599;
// long long a[100010];
// int v(char c){
//     if(c>='0'&&c<='9') return c-'0'+1;
//     if(c>='A'&&c<='Z') return c-'A'+11;
//     if(c>='a'&&c<='z') return c-'a'+37;
// } 
// long long value(string s){
//     long long ans=v(s[0]);
//     for(int i=1;i<(int)s.length();i++) ans=ans*base+v((char)s[i]);
//     return ans;
// }
// int main(){
//     cin>>n;
//     for(int i=1;i<=n;i++){
//         string s;
//         cin>>s;
//         a[i]=value(s);
//     }
//     sort(a+1,a+n+1);
//     int ans=1;
//     for(int i=2;i<=n;i++){
//         if(a[i]!=a[i-1]) ans++;
//     }
//     cout<<ans;
// }

// 如何快速从字符串中得到任意字串的hash
// #inlcude<bis/stdc++.h>
// using namespace std;
// typedef long long ll;
// const ll maxn=1e5+10;
// ll base=499;
// ll pow[maxn],hash[maxn];
// void build(string s,int n){
//     pow[0]=1;
//     for(int i=1;i<n;i++){
//         pow[i]=pow[i-1]*base;
//     }
//     ll l=s.length();
//     for(int i=1;i<=l;i++){
//         hash[i]=hash[i-1]*power+s[i]-'a'+1;
//     }
// }
// ll gethash(ll l,ll r){
//     ans=hash[r];
//     if(l>0){
//         ans-=hash[l-1]*power[r-l+1];
//     }
//     return ans;
// }



//字符串哈希与树上倍增的结合
//https://ac.nowcoder.com/acm/contest/78807/G
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
typedef long long ll;
struct tree{
    int t,n;
}tr[maxn*2];
int getlog2(int x){
    int ans=0;
    while((1<<(ans+1))<=x) ans++;
    return ans;
}
int power;
int head[maxn*2],tot=1,st[maxn][32],deep[maxn],n;
ll base =599;
ll Hash[maxn],a[maxn],stup[maxn][32],stdown[maxn][32];
void add(int u,int v){
    tr[++tot].t=v;
    tr[tot].n=head[u];
    head[u]=tot;
}
void dfs(int u,int f){
    deep[u]=deep[f]+1;
    st[u][0]=f;
    stup[u][0]=a[f];
    stdown[u][0]=a[f];
    for(int p=1;(1<<p)<=deep[u];p++){
        st[u][p]=st[st[u][p-1]][p-1];
        stup[u][p]=stup[u][p-1]*Hash[(1<<(p-1))]+stup[st[u][p-1]][p-1];
        stdown[u][p]=stdown[u][p-1]+stdown[st[u][p-1]][p-1]*Hash[1<<(p-1)];
    }
    for(int ei=head[u];ei;ei=tr[ei].n){
        int v=tr[ei].t;
        if(v!=f){
            dfs(v,u);
        }
    }
}
int findlca(int u,int v){
    if(deep[u]<deep[v])swap(u,v);
    for(int p=power;p>=0;p--){
        if(deep[st[u][p]]>=deep[v]) {
            u=st[u][p];
        }
    }
    if(u==v) return u;
    for(int p=power;p>=0;p--){
        if(st[u][p]!=st[v][p]){
            u=st[u][p];
            v=st[v][p];
        }
    }
    return st[u][0];
}
ll findhash(int u,int lca,int v){
    ll up =a[u];
    for(int p=power;p>=0;p--){
        if(deep[st[u][p]]>=deep[lca]){
        up=up*Hash[1<<p]+stup[u][p];
        u=st[u][p];
        }
    }
    if(v==lca)return up;
    ll down=a[v];
    int height=1;
    for(int p=power;p>=0;p--){
        if(deep[st[v][p]]>deep[lca]){
            down=down+stdown[v][p]*Hash[height];
            height+=1<<p;
            v=st[v][p];
        }
    }
    return up*Hash[height]+down;
}
int main(){
    cin>>n;
    vector<char>c(n);
    for(int i=0;i<n;i++){
        cin>>c[i];
        a[i+1]=c[i]-'a'+1;
    }
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        add(i,x);
        add(x,i);
    }
    power=getlog2(n);
    Hash[0]=1;
    for(int i=1;i<=n;i++){
        Hash[i]=Hash[i-1]*base;
    }
    dfs(1,0);
    int m;
    cin>>m;
    for(int i=1;i<=m;i++){
        int a,b;
        cin>>a>>b;
        int lca=findlca(a,b);
        ll hash1=findhash(a,lca,b);
        ll hash2=findhash(b,lca,a);
        // cout<<hash1<<' '<<hash2<<endl;
        if(hash1==hash2) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
}