#include<bits/stdc++.h>
using namespace std;
struct node{
    int val;
    node* left;
    node *right;
    int height;
    node(int v):val(v),left(NULL),right(NULL),height(1){};
};
int getheight(node *x){
    if (x==NULL) return 0;
    return x->height;
}
int getbalance(node* x){
    if(x==NULL) return 0;
    return getheight(x->left)-getheight(x->right);
}
node *leftrotate(node *root){//RR
    node* newroot=root->right;
    node *temp=newroot->left;
    newroot->left=root;
    root->right=temp;
    root->height=1+max(getheight(root->left),getheight(root->right));
    newroot->height=1+max(getheight(newroot->left),getheight(newroot->right));
    return newroot;
}
node *rightrotate(node *root){//ll
    node* newroot=root->left;
    node *temp=newroot->right;
    newroot->right=root;
    root->left=temp;
    root->height=1+max(getheight(root->left),getheight(root->right));
    newroot->height=1+max(getheight(newroot->left),getheight(newroot->right));
    return newroot;
}
node *insert(node *root,int val){
    if(root==NULL) return new node(val);

    if(val<root->val){
        root->left=insert(root->left,val);
    }else if(val>root->val){
        root->right=insert(root->right,val);
    }else return root;
    root->height=1+max(getheight(root->left),getheight(root->right));
    int balance=getbalance(root);
    if(balance>1&&val<root->left->val){//LL
        return rightrotate(root);
    }else if(balance<-1&&val>root->right->val){//RR
        return leftrotate(root);
    }else if(balance>1&&val>root->left->val){//LR
        root->left=leftrotate(root->left);
        return rightrotate(root);
    }else if(balance<-1&&val<root->right->val){//RL
        root->right=rightrotate(root->right);
        return leftrotate(root);
    }
    return root;
}
int main(){
    int n;
    cin>>n;
    node*root=NULL;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        root=insert(root,x);
    }
    cout<<root->val;
}