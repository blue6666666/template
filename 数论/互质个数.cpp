#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int t;
vector<ll> getPrimes(ll M) {
    vector<ll> p;
    for (ll i = 2; i * i <= M; ++i) {
        if (M % i == 0) {
            p.push_back(i);
            while (M % i == 0) M /= i;
        }
    }
    if (M > 1) p.push_back(M);
    return p;
}
ll countCoprime(ll N, const vector<ll>& primes) {
    if (N <= 0) return 0;
    ll res = 0;
    int k = primes.size();
    for (int m=0;m<(1<<k);++m) {
        ll p = 1;
        int bits = 0;
        bool flag = false;
        for (int i = 0; i < k; ++i) {
            if (m & (1 << i)) {
                if (p > N / primes[i]) { 
                    flag = true; 
                    break; 
                }
                p *= primes[i];
                bits++;
            }
        }
        if (flag) continue; 
        if (bits&1) res-=N/p; 
        else res+=N/p;          
    }
    return res;
}
void solve(){
    ll l,r,n;
    cin>>l>>r>>n;
    vector<ll> p=getPrimes(n);
    int k=countCoprime(r,p)-countCoprime(l-1,p);
    cout<<(r-l+1)*2-k<<endl;
}
int main() {
    cin>>t;
    while(t--){
        solve();
    }
}