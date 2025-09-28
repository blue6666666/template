#include<bits/stdc++.h>
using namespace std;
int main(){
	//什么是map？map是干什么用的
	map<int,int>mp; //定义了一个名叫mp的map容器
	mp[10001]=82;mp[100002]=82;
	//输出10001信息
	cout<<mp[10001]<<endl;//可能会溢出
	//安全的方法
	if(mp.find(10005)!=mp.end()){
		cout<<mp[10005]<<endl;
	}
	
	else cout<<"没有此人信息"<<endl;
	//储存学生姓名对应成绩
	map<string,int>stu;
	stu["xiaoming"]=85;
	stu["xiaohong"]=77;
	cout<<stu["xiaohong"]<<endl;
	//map的遍历
	//1.
	for(auto it:stu){//将容器从头到尾遍历了一遍
		//map自动按照首位字典序从小到大排序
		cout<<it.first<<' '<<it.second<<endl;
	}
	//2.迭代器类型
	map<string,int>::iterator it;//定义map<string,int>类型的迭代器it
	for(it=stu.begin();it!=stu.end();it++){
		cout<<(*it).first<<' '<<(*it).second<<endl;
	}
}