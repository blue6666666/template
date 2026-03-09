#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll fpm(ll x, ll power, ll mod) {
    x %= mod;
    ll ans = 1;
    for (; power; power >>= 1, (x *= x) %= mod)
    	if(power & 1) (ans *= x) %= mod;
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,p;
    cin>>n>>p;
    for(int a=1;a<=n;a++){
	cout<< fpm(a, p - 2, p)<<endl;
    }//x为a在mod p意义下的逆元
}
/*
#include <cstdio>

const int maxn = 3000005;

int n, p;
int inv[maxn], factinv[maxn];

int main() {
  scanf("%d%d", &n, &p);
  factinv[1] = inv[1] = 1;
  printf("%d\n", 1);
  for (int i = 2; i <= n; ++i) {
    inv[i] = 1ll * (p - p / i) * inv[p % i] % p;
    printf("%d\n", inv[i]);
    factinv[i] = 1ll * factinv[i - 1] * inv[i] % p;//阶乘逆元
    
  }
  return 0;
}
*/
/*
long long modPow(long long base, long long exp, long long modulus) {
    base %= modulus;
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) 
            result = (result * base) % modulus;
        base = (base * base) % modulus;
        exp >>= 1;
    }
    return result;
}
*/