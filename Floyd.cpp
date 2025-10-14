//求图中两点最短路
//适用于有向图和无向图
//图中不可以有负环（权值为负数的环），保证最短路存在
//时间复杂度O（n^3）,空间复杂度O（n^2）,
#include<bits/stdc++.h>
using namespace std;
const int maxn=1001;
const int inf =1e8;
int n,m,dis[maxn][maxn],ans;//

void floyd(){
    //枚举每个跳板
    //注意跳板一定要先枚举
    for(int bridge=1;bridge<=n;bridge++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(dis[i][bridge]!=inf&&dis[bridge][j]!=inf&&dis[i][j]>dis[i][bridge]+dis[bridge][j]){
                    dis[i][j]=dis[i][bridge]+dis[bridge][j];
                }
            }
        }
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            dis[i][j]=inf;
        }
    }
    vector<int>a;
    for(int i=1;i<=m;i++){
        int x;
        cin>>x;
        a.push_back(x);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>dis[i][j];
        }
    }
    floyd();
    for(int i=1;i<a.size();i++){
        ans+=dis[a[i-1]][a[i]];
    }
    cout<<ans<<endl;
}
