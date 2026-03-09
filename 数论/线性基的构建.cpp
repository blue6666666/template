//普通消元法
void insert(long long x)
{
    for(int i=63;~i;i--) if((x>>i)&1ll)
    {
        if(!place[i]) {place[i]=x;return;}
        else x^=place[i];
    }
}
void insert(int *num)
{
    for(int j=63;~j;j--)
    {
        int p=0;
        for(int i=1;(!p)&&i<=n;i++)
            if((!v[i])&&((num[i]>>j)&1ll)) p=i;
        if(!p) {place[j]=0;continue;}
        v[p]=true,place[j]=num[p];
        for(int i=1;i<=n;i++) if(i!=p&&((num[i]>>j)&1ll))
            num[i]^=num[p];
    }
}
bool check(long long x)
{
    for(int i=63;~i;i--)
        if((x>>i)&1ll) x^=place[i];
    return x==0;
}
struct Base
{
    long long place[N];
    void insert(long long x)
    {
        for(int i=63;~i;i--) if((x>>i)&1ll)
        {
            if(!place[i]) {place[i]=x;return;}
            else x^=place[i];
        }
    }
};
void merge(Base A,Base &B)
{
    for(int i=63;~i;i--) if(A.place[i])
        B.insert(A.place[i]);
}
long long mx()
{
    long long ans=0;
    for(int i=63;~i;i--)
        if((ans^place[i])>ans)
            ans^=place[i];
    return ans;
}
long long mn()
{
    for(int i=0;i<=63;i++)
        if(place[i]) return place[i];
    return -1;
}
/*
K大异或和

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
ll b[55];
int flg;
void insert(ll x) {
    int i;
    for(i=50;i>=0;i--) {
        if(x&(1ll<<i)) {
            if(b[i]) x^=b[i];
            else {b[i]=x; return ;}
        }
    }
    if(!x) flg=1;
}
void Guass() {
    int i,j;
    for(i=50;i>=0;i--) {
        if(b[i]) {
            for(j=50;j>=0;j--) {
                if(i!=j&&(b[j]&(1ll<<i))) {
                    b[j]^=b[i];
                }
            }
        }
    }
}
int main() {
    int n,m;
    scanf("%d",&n);
    int i;
    ll x;
    for(i=1;i<=n;i++) scanf("%lld",&x),insert(x);
    Guass();
    int cnt=0;
    for(i=0;i<=50;i++) {
        if(b[i]) b[cnt++]=b[i];
    }
    scanf("%d",&m);
    while(m--) {
        scanf("%lld",&x);
        if(x>(1ll<<cnt)) {
            puts("-1"); continue;
        }
        x-=flg;
        ll ans=0;
        for(i=cnt;i>=0;i--) {
            if(x&(1ll<<i)) ans^=b[i];
        }
        printf("%lld\n",ans);
    }
}*/