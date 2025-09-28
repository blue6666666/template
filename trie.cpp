#include<bits/stdc++.h>
using namespace std;
int tree[3000005][70],pass[3000005],endp[3000005],cnt=1;
int getidx(char ch){
// 映射函数
if(ch>='a'&&ch<='z') return ch-'a';
if(ch>='A'&&ch<='Z') return ch-'A'+26;
return ch-'0'+52;    
}
void insert(string s){//插入操作
 int cur=1;
 pass[cur]++;
    for(int i=0;i<s.length();i++){
        int idx=getidx(s[i]);
        if(tree[cur][idx]==0) {
            tree[cur][idx]=++cnt;
        }
        cur=tree[cur][idx];
        pass[cur]++;
    }
    endp[cur]++;
}
int search_whole_s(string s){
    //查询整个字符串出现次数
    int cur=1;
    for(int i=0;i<s.length();i++){
        int idx=getidx(s[i]);
        if(tree[cur][idx]==0) return 0;
        cur=tree[cur][idx];
    }
    return endp[cur];
}
int search_prefix_s(string s){
    //查询s作为前缀字符串出现次数
    int cur=1;
    for(int i=0;i<s.length();i++){
        int idx=getidx(s[i]);
        if(tree[cur][idx]==0) return 0;
        cur=tree[cur][idx];
    }
    return pass[cur];
}
void delete1(string s)
{
    if(search_whole_s(s)>0)
    {
    int cur=1;
    for(int i=0;i<s.length();i++)
    {
    int idx=getidx(s[i]);
    if(--pass[tree[cur][idx]]==0)
    {
    tree[cur][idx]==0;
    return;
    }
    cur=tree[cur][idx];
    }
    endp[cur]--;
}
}
void clear()
{
    for(int i=1;i<=cnt;i++)
    {
    for(int j=0;j<=69;j++) tree[i][j]=0;
    pass[i]=0;
    endp[i]=0;
    }
    cnt=1;
}