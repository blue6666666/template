#include<bits/stdc++.h>
using namespace std;
void get_nxt(string s, int nxt[]){
    int j = 0;
    nxt[0] = 0;
    for (int i = 1; i < s.length(); i++)
    {
        while(j>0&&s[i]!=s[j]) j=nxt[j-1];
        if(s[i]==s[j])j++;
        nxt[i]=j;
    }
}
void solve(){
    int cnt=0;
    string s, t;
    cin >> s >> t;
    int* nxt = new int[t.length()];
    get_nxt(t, nxt);
    int j=0;
    for (int i = 0; i < s.length(); i++) //这里的s代表主串
    {
        while(j > 0 && s[i] != t[j]) j = nxt[j-1];
        if(s[i]==t[j]) j++;
        if(j==t.length()){
            cout<<i-t.length()+2<<endl;
        }
    }
    for (int i = 0; i < t.length(); i++){
        cout<<nxt[i]<<' ';
    }
}
int main(){
    solve();
}