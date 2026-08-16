const int MAXN = 1e7 + 10;
vector<int> primes;
vector<int> omega(MAXN, 0);
vector<bool> is_comp(MAXN, false);

void sieve_omega(int n) {
    omega[1] = 0;
    for (int i = 2; i <= n; ++i) {
        if (!is_comp[i]) {
            primes.push_back(i);
            omega[i] = 1;               // 质数：1个质因子
        }
        for (int p : primes) {
            long long nxt = 1LL * i * p;
            if (nxt > n) break;
            is_comp[nxt] = true;
            omega[nxt] = omega[i] + 1;  // 积性：多一个质因子
            if (i % p == 0) break;
        }
    }
}