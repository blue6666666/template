/*#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k;
queue<int>ans1,ans2;
deque<int>mx,mn;
int a[1000010];
signed main(){
cin>>n>>k;
for(int i=1;i<=n;i++){
    cin>>a[i];
    while(!mx.empty()&&mx.front()<max(1ll,i-k+1)) mx.pop_front();
    while(!mn.empty()&&mn.front()<max(1ll,i-k+1)) mn.pop_front();
    while(!mx.empty()&&a[mx.back()]<a[i]) mx.pop_back();
    while(!mn.empty()&&a[mn.back()]>a[i]) mn.pop_back();
    mn.push_back(i);
    mx.push_back(i);
    if(i-k+1>=1){
        ans1.push(a[mn.front()]);
        ans2.push(a[mx.front()]);
    }
}
    while(!ans1.empty()){
    cout<<ans1.front()<<' ';
    ans1.pop();
    }

cout<<endl;
while(!ans2.empty()){
    cout<<ans2.front()<<' ';
    ans2.pop();
    }
}*/
#include <iostream>
#include <vector>
#include <cmath>
#include <deque>
using namespace std;
using LL = long long;
struct node{
    LL val;
    int pos;
};
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	int n,m,d;
    cin>>n>>m>>d;
    vector<LL> arr[2]; 
    arr[0].resize(n,0);arr[1].resize(n);
    int cur=0,next;
    deque<node> deq;
    LL a,b,t=0,pret=0;
    for(int j=0;j<m;j++){
        next=cur^1;
        pret=t;
        cin>>a>>b>>t;
        deq.clear();
        LL l,r;
        l=0;r=min(d*(t-pret),(LL)n-1);
        for(int i=(int)l;i<r;i++){
            while(!deq.empty()&&deq.back().val<=arr[cur][i]){
                deq.pop_back();
            }
            deq.push_back({arr[cur][i],i});
        }
        for(int i=0;i<n;i++){
            //弹出队头
            l=max((LL)0,i-d*(t-pret));
            if(!deq.empty()&&deq.front().pos<l) deq.pop_front();
            //压入队尾
            r=min(i+d*(t-pret),(LL)n-1);
            while(!deq.empty()&&deq.back().val<=arr[cur][r]){
                deq.pop_back();
            }
            deq.push_back({arr[cur][r],(int)r});
            //更新答案
            arr[next][i]=deq.front().val+b*abs(i+1-a);
        }
        cur=next;
    } 
    LL ans=-1e6;
    for(int i=0;i<n;i++){
        ans=max(ans,arr[cur][i]);
    }
    cout<<ans;
    return 0;
}
/*#include <iostream>
#include <queue>
#include <vector>
#include <string>

struct Student {
    std::string name;
    int score;
    int age;
    
    // 重载 < 运算符，用于大根堆（按score从大到小）
    bool operator<(const Student& other) const {
        // 注意：priority_queue默认用 < 比较，但实际表现是最大堆
        // 所以这里返回 true 表示优先级更低
        return score < other.score;  // 大根堆
    }
    
    // 或者明确指定比较规则
    friend std::ostream& operator<<(std::ostream& os, const Student& s) {
        os << s.name << " (分数:" << s.score << ", 年龄:" << s.age << ")";
        return os;
    }
};

int main() {
    // 使用自定义结构体的大根堆（按分数）
    std::priority_queue<Student> studentHeap;
    
    studentHeap.push({"Alice", 85, 20});
    studentHeap.push({"Bob", 92, 21});
    studentHeap.push({"Charlie", 78, 19});
    studentHeap.push({"David", 95, 22});
    
    std::cout << "学生按分数排序（从高到低）:" << std::endl;
    while (!studentHeap.empty()) {
        std::cout << studentHeap.top() << std::endl;
        studentHeap.pop();
    }
    
    return 0;
}*/