#include<bits/stdc++.h>
using namespace std;
//建树
struct treenode{
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
}