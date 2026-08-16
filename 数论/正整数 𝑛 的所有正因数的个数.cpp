//线性筛
for(int i = 2; i <= n; i++){
 if(minp[i]==0){
    minp[i]=i;
    d[i]=2;
    num[i]=1;
 }
 for(auto p : prime){
 if(p * i > n) break;
 minp[p * i] = p;
 if(minp[i] == p){
 //求解
 num[p * i] = num[i] + 1;
 d[p * i] = d[i] / (num[i] + 1) * (num[p * i] + 1);
 break;
 }
 //求解
 num[p * i] = 1;
 d[p * i] = d[p] * d[i];
 }
}