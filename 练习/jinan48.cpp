// #include<bits/stdc++.h>
// using namespace std;
// int t;
// int n;
// int a[110],b[110];
// void solve(){
//     cin>>n;
//     for(int i=1;i<=n;i++){
//         cin>>a[i];
//         b[a[i]]=i;
//     }
//     vector<pair<int,int>>ans;
//     for(int i=1;i<=n;i++){
//         if(b[i]!=i){
//             int l;
//             for(int j=i+1;j<=n;j++){
//                 if(a[j]<a[i]){
//                     l=j;
//                 }
//             }
//             ans.push_back({i,l});
            
//             sort(a+i,a+l+1);
//             for(int j=i;j<=l;j++){
//                 b[a[j]]=j;
//             }
//         }
//     }
//     cout<<ans.size()<<endl;
//     for(auto [x,y]:ans){
//         cout<<x<<' '<<y<<endl;
//     }
// }
// int main(){
//     cin>>t;
//     while(t--){
//         solve();
//     }
// }
// #include<bits/stdc++.h>
// using namespace std;
// int t;
// int check(int x){
//     int res=0;
//     while(x){
//         res=max(res,x%10);
//         x/=10;
//     }
//     return res;
// }
// void solve(){
//     int l1,r1,l2,r2;
//     cin>>l1>>r1>>l2>>r2;
//     int ll=l1+l2,rr=r1+r2;
//     if(rr-ll+1>=9) cout<<9<<endl;
//     else {
//         int ans=0;
//         for(int i=ll;i<=rr;i++){
//             ans=max(ans,check(i));
//         }
//         cout<<ans<<endl;
//     }
// }
// int main(){
//     cin>>t;
//     while(t--){
//         solve();
//     }
// }
// #include <bits/stdc++.h>
// using namespace std;
// int getType(char c)
// {
//     return (c == '(' || c == ')') ? 0 : 1;
// }

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     int T;
//     cin >> T;
//     while (T--)
//     {
//         string s;
//         cin >> s;
//         vector<array<int,2>> cnt(s.size()+2);
//         vector<int> st;
//         bool ok = true;

//         for(char c:s)
//         {
//             int t=getType(c);

//             if(st.empty())
//             {
//                 st.push_back(t);
//             }
//             else if(st.back()==t)
//             {
//                 int dep=st.size()-1;

//                 cnt[dep][t]++;
//                 if(cnt[dep][t]>=2)
//                 {
//                     ok=false;
//                     break;
//                 }
//                 st.pop_back();
//             }
//             else
//             {
//                 st.push_back(t);
//             }
//         }
//         cout << (ok ? "Yes" : "No") << '\n';
//     }
//     return 0;
// }
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int mod = 1e9 + 7;
struct DSU{
    vector<int> fa, dis;
    DSU(int n){
        fa.resize(n+1);
        dis.assign(n+1,0);
        iota(fa.begin(),fa.end(),0);
    }
    pair<int,int> find(int x){
        if(fa[x]==x)
            return {x,0};
        auto [f,v]=find(fa[x]);
        dis[x]^=v;
        fa[x]=f;
        return {fa[x],dis[x]};
    }

    // x_u xor x_v = val
    bool merge(int u,int v,int val){
        auto a=find(u);
        auto b=find(v);
        if(a.first==b.first)
            return ((a.second^b.second)==val);
        fa[a.first]=b.first;

        // a.second xor dis[a] xor b.second = val
        dis[a.first]=a.second^b.second^val;

        return true;
    }
};


int qpow(int a,int b){
    int res=1;

    while(b){
        if(b&1)
            res=res*a%mod;

        a=a*a%mod;
        b>>=1;
    }

    return res;
}



void solve(){

    int r,c;
    cin>>r>>c;

    vector<string>a(r);

    for(auto &s:a)
        cin>>s;


    DSU dsu(r);


    bool ok=true;


    for(int j=0;j<c;j++){

        int k=c-1-j;


        vector<pair<int,int>> v;


        // 当前列
        for(int i=0;i<r;i++){
            if(a[i][j]=='1')
                v.push_back({i,0});
        }


        // 对称列
        if(k!=j){
            for(int i=0;i<r;i++){
                if(a[i][k]=='1')
                    v.push_back({i,1});
            }
        }


        // 中间列
        if(k==j){

            if(v.size()>1)
                ok=false;

            continue;
        }


        if(v.size()>2){
            ok=false;
            break;
        }


        if(v.size()==2){

            auto [x,p1]=v[0];
            auto [y,p2]=v[1];


            if(p1==p2){
                // 同一列
                // 必须一个翻一个不翻

                if(!dsu.merge(x+1,y+1,1))
                    ok=false;

            }
            else{
                // 对称列
                // 翻转状态相同

                if(!dsu.merge(x+1,y+1,0))
                    ok=false;
            }
        }
    }


    if(!ok){
        cout<<0<<"\n";
        return;
    }


    int cnt=0;

    vector<int>vis(r+1);


    for(int i=1;i<=r;i++){

        int f=dsu.find(i).first;

        if(!vis[f]){
            vis[f]=1;
            cnt++;
        }
    }


    cout<<qpow(2,cnt)%mod<<"\n";
}



signed main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int T;
    cin>>T;

    while(T--)
        solve();

    return 0;
}