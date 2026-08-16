//与MAnacher类似
#include<bits/stdc++.h>
using namespace std;
string s;
vector<int> zArray(string s){
    vector<int>z(s.length(),0);
    z[0]=s.length();;
    int c=0,r=0;
    for(int i=1;i<s.length();i++){
        if(r>i) z[i]=min(z[i-c],r-i);
        while(i+z[i]<s.length()&&s[i+z[i]]==s[z[i]]) ++z[i];
        if(i+z[i]>r){
            r=i+z[i];
            c=i;
        }
    }
    return z;
}
vector<int> eArray(string a,string b,vector<int>z){
    vector<int>e(a.length(),0);
    int c=0,r=0;
    for(int i=0;i<a.length();i++){
        e[i]=r>i?min(r-i,z[i-c]):0;
        while(i+e[i]<a.length()&&e[i]<b.length()&&a[i+e[i]]==b[e[i]]) ++e[i];
        if(i+e[i]>r){
            r=i+e[i];
            c=i;
        }
    }
    return e;
}
signed main(){
    long long ans1=0,ans2=0;
    string a,b;
    cin>>a>>b;
    vector<int>z=zArray(b),e=eArray(a,b,z);
    for(int i=0;i<b.length();i++){
        ans1^=1LL*(i+1)*(z[i]+1);
    }
    for(int i=0;i<a.length();i++){
        
        ans2^=1LL*(i+1)*(e[i]+1);
    }
    cout<<ans1<<endl;
    cout<<ans2<<endl;
}