#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
    cin>>n;
    vector<int>a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    vector<int>L(n+1,0),R(n+1,0);
    vector<int> stk;
for (int i = 1; i <= n; ++i) {
	int flag = 0;
	while (!stk.empty()) {
		if (a[stk.back()] > a[i]) {  // 小根堆
			flag = stk.back(); stk.pop_back();
		} else {
			break;
		}
	}
	if (flag) { L[i] = flag; }
	if (!stk.empty()) { R[stk.back()] = i; }
	stk.push_back(i);
}
int ans1=0,ans2=0;
for(int i=1;i<=n;i++){
    ans1^=i*(L[i]+1);
    ans2^=i*(R[i]+1);
}
cout<<ans1<<' '<<ans2<<endl;
}