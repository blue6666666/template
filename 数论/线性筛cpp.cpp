int n = 100;
vector<int> minp(n + 1, 0), prime;
//minp存的是该数的最小质因数
for(int i = 2; i <= n; i++){
 if(minp[i] == 0){
 minp[i] = i;
 prime.push_back(i);
 }
 for(auto p : prime){
    if(i * p > n) break;
    minp[i * p] = p;
    if(minp[i] == p) break;
 }
}