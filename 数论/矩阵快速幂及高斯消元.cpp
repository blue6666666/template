
//# 1.矩阵快速幂
#include <bits/stdc++.h>
using namespace std; 
#define int long long
using ll = long long;
const int MOD = 1e9 + 7;
// 矩a阵结构体
struct Matrix {
    int n, m; // n: 行数, m: 列数
    vector<vector<ll>> a;
    Matrix(int _n, int _m) : n(_n), m(_m), a(_n + 1, vector<ll>(_m + 1, 0)) {}

    static Matrix identity(int n) {
        Matrix I(n, n);
        for (int i = 1; i <= n; ++i) {
            I.a[i][i] = 1;
        }
        return I;
    }
};
// 矩阵乘法: C = A * B
// 时间复杂度: O(n^3) 或 O(A.n * A.m * B.m)
Matrix operator*(const Matrix& A, const Matrix& B) {
    Matrix C(A.n, B.m);
    for (int i = 1; i <= A.n; ++i) {
        for (int j = 1; j <= B.m; ++j) {
            for (int k = 1; k <= A.m; ++k) {
                C.a[i][j] = (C.a[i][j] + A.a[i][k] * B.a[k][j]) % MOD;
            }
        }
    }
    return C;
}



// 矩阵快速幂: A^p, 时间复杂度: O(n^3 * log p) , A必须是方阵
Matrix power(Matrix A, ll p) {
    Matrix res = Matrix::identity(A.n);
    while (p) {
        if (p & 1) res= res * A;
        A = A * A;
        p >>= 1;
    }
    return res;
}
signed main(){
    ios::sync_with_stdio(false); 
    cin.tie(0), cout.tie(0); 
    int n, k; cin >> n >> k; 
    Matrix A(n, n);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n;j++){
            cin >> A.a[i][j]; 
        }
    }
    Matrix res = power(A, k); 
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cout << res.a[i][j] << " ";  
        }
        cout << endl; 
    }
}

/*## 2.高斯消元

int gauss_jordan(vector<vector<double>>& a, int vars) {
    int eqs = a.size();
    if (eqs == 0) return 0;
    int rk = 0;
    for (int col = 0; col < vars && rk < eqs; ++col) {
        int pivot_row = rk;
        for (int i = rk + 1; i < eqs; ++i) {
            if (abs(a[i][col]) > abs(a[pivot_row][col])) {
                pivot_row = i;
            }
        }
        swap(a[rk], a[pivot_row]);
        if (abs(a[rk][col]) < EPS) {
            continue; 
        }
        double pivot_val = a[rk][col];
        for (int j = col; j < a[0].size(); ++j) {
            a[rk][j] /= pivot_val;
        }
        for (int i = 0; i < eqs; ++i) {
            if (i != rk) {
                double factor = a[i][col];
                for (int j = col; j < a[0].size(); ++j) {
                    a[i][j] -= factor * a[rk][j];
                }
            }
        }
        rk++;
    }
    return rk;
}
*/
/*
// 快速幂二号

#include<bits/stdc++.h>
#define mul(x,y) Wuguidechengfa(x,y)
using namespace std;
typedef long long ll;
const int N=40;
inline ll read()
{
	char c;ll res=0;
	for(;!isdigit(c);c=getchar());
	for(;isdigit(c);c=getchar())res=(res<<3)+(res<<1)+(c^48);
	return res;
}
ll mod,a,c,x0,n,g;
ll Wuguidechengfa(ll x,ll y)
{
	ll ans=0;
	while(y)
	{
		if(y&1) (ans+=x)%=mod;
		(x+=x)%=mod;
		y>>=1;
	}
	return ans;
}
//龟速乘
struct Mat
{
	ll a[N][N];
	//矩阵
	int n,m;
	//行、列
	Mat(){n=m=0;memset(a,0,sizeof a);}
	//构造空矩阵
	Mat(int k){n=m=k;memset(a,0,sizeof a);for(int i=1;i<=k;i++)a[i][i]=1;}
	//构造k*k的单位矩阵
	Mat(int x,int y){n=x,m=y;memset(a,0,sizeof a);}
	//构造x*y的空矩阵
	Mat operator *(Mat b)
	{
		Mat c(n,b.m);
		for(int i=1;i<=c.n;i++)
		{
			for(int j=1;j<=c.m;j++)
			{
				for(int k=1;k<=m;k++)
				{
					c.a[i][j]=(c.a[i][j]+mul(a[i][k],b.a[k][j]))%mod;
					//注意这里用龟速乘而不是直接写乘号
				}
			}
		}
		return c;
	}
	Mat operator *=(Mat b)
	{
		return *this=*this*b;
	}
	//重载乘法
	Mat operator ^(ll k)
	{
		Mat ans(n),t=*this;
		while(k)
		{
			if(k&1) ans*=t;
			t*=t;
			k>>=1;
		}
		return ans;
	}
	Mat operator ^=(ll k)
	{
		return *this=*this^k;
	}
	//矩阵快速幂
};
int main()
{
	mod=read();a=read();c=read();x0=read();n=read();g=read();
	if(!n)return printf("%d\n",x0)&0;
	//特判n==0的情况
	Mat res(4,4);
	res.a[1][1]=a,res.a[1][2]=1,res.a[2][2]=1;
	//构造转移矩阵
	Mat p(2,1);
	p.a[1][1]=x0,p.a[2][1]=c;
	//构造初始矩阵
	res^=n;
	res*=p;
	//注意乘法顺序，矩阵乘法不满足交换律
	printf("%lld\n",res.a[1][1]%g);
	
    return 0;
}
*/


