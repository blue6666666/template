/*#include<bits/stdc++.h>
using namespace std;
//建树
struct treenode{
//二叉树
    int val;
    treenode* left;
    treenode* right;
    treenode(int x): val(x),left(NULL),right(NULL){}
};
treenode* buildtree(const vector<int>&vals){
    if(vals.empty()||vals[0]==-1) return NULL;
    treenode* root= new treenode(vals[0]);
    queue<treenode*>q;
    q.push(root);
    int i=1;
    while(!q.empty()&&i<vals.size()){
        treenode* curr=q.front();
        q.pop();
        if(i<vals.size()&&vals[i]!=-1){
            curr->left=new treenode(vals[i]);
            q.push(curr->left);
        }
        i++;
        if(i<vals.size()&&vals[i]!=-1){
            curr->right=new treenode(vals[i]);
            q.push(curr->right);
        }
        i++;
    }
    return root;
}
//具体操作一般时dfs+动态规划

int main(){
vector<int> vals;
int x;
while(scanf("%d",&x)!=EOF){
    vals.push_back(x);
}
treenode* root=buildtree(vals);
cout<<root->val;
}*/
//树形dp套路
//1.分析父树得到答案需要子树的那些信息
//2.把子树信息的全集定义为递归返回值
//3.通过递归让子树返回全集信息
//4。整合子树全集信息得到父树全集信息返回
#include<bits/stdc++.h>
using namespace std;
const int maxn=10000;
int cnt=1,n,head[maxn],yes[maxn],no[maxn],num[maxn],b[maxn];
struct graph{
    int next,to;
}g[maxn];
void add(int u,int v){
    g[cnt].next=head[u];
    g[cnt].to=v;
    head[u]=cnt++;
}
void dfs(int i){
    no[i]=0;
    yes[i]=num[i];
    for(int ei=head[i],v;ei;ei=g[ei].next){
        v=g[ei].to;
        dfs(v);
        no[i]+=max(yes[v],no[v]);
        yes[i]+=no[v];
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>num[i];
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        b[u]=1;
        add(v,u);
        
    }
    for(int i=1;i<=n;i++){
        if(!b[i]){
            dfs(i);
            cout<<max(yes[i],no[i])<<endl;
            break;
        }
    }
}