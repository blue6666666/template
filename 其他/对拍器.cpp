#include<bits/stdc++.h>
using namespace std;
int main(){
    int t=0;
    while(true){
    cout<<"test: "<<t++<<endl;
    system("data.exe>data.in");//data.exe 随机数生成器
    system("std.exe<data.in>data.out");//std.exe 标准程序
    system("solve.exe<data.in>solve.out");//solve.exe 暴力求解算法
    if(system("fc std.out solve.out>diff.log")){
        cout<<"WA"<<endl;
        break;
    }
    
}
cout<<"AC\n";
}