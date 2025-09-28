/*#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
int b[500010];
int lowbit(int x){
 return x&(-x);
}
int count(int p){//求前p个元素的和
int sum=0;
while(p){
    sum+=b[p];
    p-=lowbit(p);
 }
return sum;
}
void add(int p,int x,int n){//对某一个元素进行修改
    while(p<=n){
    b[p]+=x;
    p+=lowbit(p);
 }
}
void solve() {
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    int tmp;
    cin>>tmp;
    add(i,tmp,n);
 }
 while(m--){
    int choice;
    cin>>choice;
    if(choice==1){
    int x,k;
    cin>>x>>k;
    add(x,k,n);
 }
 else{
    int x,y;
    cin>>x>>y;
    cout<<count(y)-count(x-1)<<endl;
 }
 }
}
signed main() { 
  ios::sync_with_stdio(0); 
  cin.tie(0), cout.tie(0); 
 // int T; 
 // std:: cin >> T; 
 // while(T -- ) 
 solve(); 
 return 0;
}*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
int b[500010];
int lowbit(int x){
    return x&(-x);
}
int count(int p){
   int sum=0;
   while(p){
   sum+=b[p];
   p-=lowbit(p);
   }
   return sum;
}
void add(int p,int x,int n){
   while(p<=n){
   b[p]+=x;
   p+=lowbit(p);
   }
}
void solve() {
   int n,m,prev=0;
   cin>>n>>m;
   for(int i=1;i<=n;i++){
    int tmp;
   cin>>tmp;
   add(i,tmp-prev,n); // 差分建树
   prev=tmp;
    }
   while(m--){
    int choice;
  cin>>choice;
    if(choice==1){
   int x,y,k;
   cin>>x>>y>>k;
   add(x,k,n);
   add(y+1,-k,n); // 差分
 }
   else{
   int x;
   cin>>x;
   cout<<count(x)<<endl;
   }
 }
}
signed main() { 
 ios::sync_with_stdio(0); 
 cin.tie(0), cout.tie(0); 
 // int T; 
 // std:: cin >> T; 
 // while(T -- ) 
 solve(); 
 return 0;
}
