/*#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
//简单版
const int N=500010;
int n;char str[1000010];
int ch[N][26],cnt[N],idx;
int ne[N];

void insert(char *s){//建树
  int p=0;
  for(int i=0;s[i];i++){
    int j=s[i]-'a';
    if(!ch[p][j])ch[p][j]=++idx;
    p=ch[p][j];
  }
  cnt[p]++;
}
void build(){//建AC自动机
  queue<int> q;
  for(int i=0;i<26;i++)
    if(ch[0][i])q.push(ch[0][i]);
  while(q.size()){
    int u=q.front();q.pop();
    for(int i=0;i<26;i++){
      int v=ch[u][i];
      if(v)ne[v]=ch[ne[u]][i],q.push(v);
      else ch[u][i]=ch[ne[u]][i];
    }
  }
}
int query(char *s){
  int ans=0;
  for(int k=0,i=0;s[k];k++){
    i=ch[i][s[k]-'a'];
    for(int j=i;j&&~cnt[j];j=ne[j])
      ans+=cnt[j], cnt[j]=-1;
  }
  return ans;
}
int main(){
  cin>>n;
  for(int i=0;i<n; i++)
    cin>>str, insert(str);
  build();
  cin>>str;
  cout<<query(str)<<endl;
  return 0;
}*/
/*#include<bits/stdc++.h>
    using namespace std;
    string mob[300010];
    int num[300010];
    int ch[300010][26];
    int fail[300010];
    int ans[300010];
    int temp;
    int n,siz;
    void insert(string s,int v){
        int now=0;
        for(int i=0;i<s.size();i++){
            int o=s[i]-'a';
            if(!ch[now][o])ch[now][o]=++siz;
            now=ch[now][o];
        }
        num[now]=v;
    }
    void getfail(){
        int now=0;
        queue<int>que;
        for(int i=0;i<26;i++)if(ch[0][i])que.push(ch[0][i]),fail[ch[0][i]]=0;
        while(!que.empty()){
            int u=que.front();que.pop();
            for(int i=0;i<26;i++){
                int v=ch[u][i];
                if(v)fail[v]=ch[fail[u]][i],que.push(v);
                else ch[u][i]=ch[fail[u]][i];
            }
        }
    }
    void query(string s){
        int now=0;
        for(int i=0;i<s.size();i++){
            now=ch[now][s[i]-'a'];
            for(int j=now;j;j=fail[j])ans[num[j]]++;
        }
    }
    int main(){
        while(cin>>n&&n){
            memset(num,0,sizeof(num));
            memset(ans,0,sizeof(ans));
            memset(ch,0,sizeof(ch));
            memset(fail,0,sizeof(fail));
            siz=0;
            for(int i=1;i<=n;i++){
                cin>>mob[i];
                insert(mob[i],i);
            }
            getfail();
            string k;
            cin>>k;
            query(k);
            temp=0;
            for(int i=1;i<=n;i++)if(ans[i]>temp)temp=ans[i];
            cout<<temp<<"\n";
            for(int i=1;i<=n;i++)if(ans[i]==temp)cout<<mob[i]<<"\n";
        }
    }*/
/*
dfs优化   
void build() {
    queue<int> q;
    for (int i = 0; i < 26; i++)
        if (tr[0].son[i]) {
            q.push(tr[0].son[i]);
            g[0].push_back(tr[0].son[i]);
        }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            if (tr[u].son[i]) {
                tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];  
                g[tr[tr[u].fail].son[i]].push_back(tr[u].son[i]);
                q.push(tr[u].son[i]);
            } else
                tr[u].son[i] = tr[tr[u].fail].son[i];
        }
    }
}
void query(char t[]) {
    int u = 0;
    for (int i = 1; t[i]; i++) {
        u = tr[u].son[t[i] - 'a'];
        tr[u].ans++;
    }
}
void dfs(int u) {
    for (int v : g[u]) {
        dfs(v);
        tr[u].ans += tr[v].ans;
    }
    ans[tr[u].idx] = tr[u].ans;
}

*/
/*
拓扑排序版

#include<bits/stdc++.h>
#define maxn 2000001
using namespace std;
char s[maxn],T[maxn];
int n,cnt,vis[200051],ans,in[maxn],Map[maxn];
struct kkk{
    int son[26],fail,flag,ans;
    void clear(){memset(son,0,sizeof(son)),fail=flag=ans=0;}
}trie[maxn];
queue<int>q;
void insert(char* s,int num){
    int u=1,len=strlen(s);
    for(int i=0;i<len;i++){
        int v=s[i]-'a';
        if(!trie[u].son[v])trie[u].son[v]=++cnt;
        u=trie[u].son[v];
    }
    if(!trie[u].flag)trie[u].flag=num;
    Map[num]=trie[u].flag;
}
void getFail(){
    for(int i=0;i<26;i++)trie[0].son[i]=1;
    q.push(1);
    while(!q.empty()){
        int u=q.front();q.pop();
        int Fail=trie[u].fail;
        for(int i=0;i<26;i++){
            int v=trie[u].son[i];
            if(!v){trie[u].son[i]=trie[Fail].son[i];continue;}
            trie[v].fail=trie[Fail].son[i]; in[trie[v].fail]++;
            q.push(v);
        }
    }
}
void topu(){
    for(int i=1;i<=cnt;i++)
    if(in[i]==0)q.push(i);
    while(!q.empty()){
        int u=q.front();q.pop();vis[trie[u].flag]=trie[u].ans;
        int v=trie[u].fail;in[v]--;
        trie[v].ans+=trie[u].ans;
        if(in[v]==0)q.push(v);
    }
}
void query(char* s){
    int u=1,len=strlen(s);
    for(int i=0;i<len;i++)
    u=trie[u].son[s[i]-'a'],trie[u].ans++;
}
int main(){
    scanf("%d",&n); cnt=1;
    for(int i=1;i<=n;i++){
        scanf("%s",s);
        insert(s,i);
    }getFail();scanf("%s",T);
    query(T);topu();
    for(int i=1;i<=n;i++)printf("%d\n",vis[Map[i]]);
}
*/
//dfs版
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

constexpr int N = 2e5 + 6;
constexpr int LEN = 2e6 + 6;
constexpr int SIZE = 2e5 + 6;

int n;


struct Node {
  int son[26];
  int ans;
  int fail;
  int idx;

  void init() {
    memset(son, 0, sizeof(son));
    ans = idx = 0;
  }
} tr[SIZE];

int tot;
int ans[N], pidx;

vector<int> g[SIZE];  // fail 树

void init() {
  tot = pidx = 0;
  tr[0].init();
}

void insert(char s[], int &idx) {
  int u = 0;
  for (int i = 1; s[i]; i++) {
    int &son = tr[u].son[s[i] - 'a'];
    if (!son) son = ++tot, tr[son].init();
    u = son;
  }
  // 由于有可能出现相同的模式串，需要将相同的映射到同一个编号
  if (!tr[u].idx) tr[u].idx = ++pidx;  // 第一次出现，新增编号
  idx = tr[u].idx;  // 这个模式串的编号对应这个结点的编号
}

void build() {
  queue<int> q;
  for (int i = 0; i < 26; i++)
    if (tr[0].son[i]) {
      q.push(tr[0].son[i]);
      g[0].push_back(tr[0].son[i]);  // 不要忘记这里的 fail
    }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < 26; i++) {
      if (tr[u].son[i]) {
        tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];
        g[tr[tr[u].fail].son[i]].push_back(tr[u].son[i]);  // 记录 fail 树
        q.push(tr[u].son[i]);
      } else
        tr[u].son[i] = tr[tr[u].fail].son[i];
    }
  }
}

void query(char t[]) {
  int u = 0;
  for (int i = 1; t[i]; i++) {
    u = tr[u].son[t[i] - 'a'];
    tr[u].ans++;
  }
}

void dfs(int u) {
  for (int v : g[u]) {
    dfs(v);
    tr[u].ans += tr[v].ans;
  }
  ans[tr[u].idx] = tr[u].ans;
}


char s[LEN];
int idx[N];

int main() {
  init();
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%s", s + 1);
    insert(s, idx[i]);
    ans[i] = 0;
  }
  build();
  scanf("%s", s + 1);
  query(s);
  dfs(0);
  for (int i = 1; i <= n; i++) {
    printf("%d\n", ans[idx[i]]);
  }
  return 0;
}