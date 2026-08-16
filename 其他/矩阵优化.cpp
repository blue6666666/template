//1939
// #include <iostream>
// #include <cstdio>
// #include <cstring>

// using namespace std;

// typedef long long LL;
// const int Mod = 1e9+7;
// int T, n;
// struct mat{
// 	LL m[5][5];
// }Ans, base;
// inline void init() {
// 	memset(Ans.m, 0, sizeof(Ans.m));
// 	for(int i=1; i<=3; i++) Ans.m[i][i] = 1;
// 	memset(base.m, 0, sizeof(base.m));
// 	base.m[1][1] = base.m[1][3] = base.m[2][1] = base.m[3][2] = 1;
// }
// inline mat mul(mat a, mat b) {
// 	mat res;
// 	memset(res.m, 0, sizeof(res.m));
// 	for(int i=1; i<=3; i++) {
// 		for(int j=1; j<=3; j++) {
// 			for(int k=1; k<=3; k++) {
// 				res.m[i][j] += (a.m[i][k] % Mod) * (b.m[k][j] % Mod);
// 				res.m[i][j] %= Mod;
// 			}
// 		}
// 	}
// 	return res;
// }
// inline void Qmat_pow(int p) {
// 	while (p) {
// 		if(p & 1) Ans = mul(Ans, base);
// 		base = mul(base, base);
// 		p >>= 1;
// 	}
// }

// int main() {
// 	scanf("%d", &T);
// 	while (T--) {
// 		scanf("%d", &n);
// 		if(n <= 3) {
// 			printf("1\n");
// 			continue;
// 		}
// 		init();
// 		Qmat_pow(n);
// 		printf("%lld\n", Ans.m[2][1]);
// 	}
// }
/*
f[i-1]       f[i]
f[i-2] ----> f[i-1]
f[i-3]       f[i-2]
f[i] = f[i-1] * 1 + f[i-2] * 0 + f[i-3] * 1
f[i-1] = f[i-1] * 1 + f[i-2] * 0 + f[i-3] * 0
f[i-2] = f[i-1] * 0 + f[i-2] * 1 + f[i-3] * 0
so
1 0 1
1 0 0
0 1 0
*/
//P6569
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct matrix{//用结构体存矩阵敲好使哒~
	long long qwq[105][105];
    int x,y;//x,y就是矩阵的行数和列数
	matrix(){x=0,y=0;memset(qwq,0,sizeof(qwq));};//构造函数，刚听说这玩意，用着玩玩
}; 
matrix operator * (const matrix &a,const matrix &b){//重载“异或版矩阵乘法”的运算符
	matrix c;
	c.x=a.x,c.y=b.y;
	for(int i=1;i<=a.x;i++){  
		for(int j=1;j<=b.y;j++){
			for(int k=1;k<=a.y;k++)
			c.qwq[i][j]^=a.qwq[i][k]*b.qwq[k][j];//和矩阵乘法别无二致，只不过就是改成异或
		}
	}
	return c;                   
}
matrix wyx[40];//存储e矩阵的2^i次方，取这个变量名是因为想借助神仙的力量AC本题
long long f[105];//每个城市的初始魔法值（提醒：十年OI一场空……）
int main(){
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++)
	scanf("%lld",&f[i]);
	wyx[0].x=n,wyx[0].y=n;//初始化一开始的邻接矩阵（也就是2的0次方）的大小
	for(int i=1;i<=m;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		wyx[0].qwq[a][b]=wyx[0].qwq[b][a]=1;//给邻接矩阵连上边
	}
	for(int i=1;i<32;i++)wyx[i]=wyx[i-1]*wyx[i-1];//利用快速幂的思想，处理出邻接矩阵2的i次方
	while(q--){
		long long x;
		scanf("%lld",&x);
        matrix ans;
		for(int i=1;i<=n;i++)ans.qwq[1][i]=f[i];//一开始就是初始f值
		ans.x=1,ans.y=n;
		for(int i=0;i<32;i++){//开始进行二进制拆分
			if((x>>i)&1)//如果这一位是1
			ans=ans*wyx[i];//就乘上对应的2的i次方
		}
		printf("%lld\n",ans.qwq[1][1]);
	}
	return 0;
}
