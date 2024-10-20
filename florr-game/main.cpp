#include<bits/stdc++.h>
#include "RSA.h"
#include "chient.h"
#include "game.h"
int main() {
	cout<<"[info]输入你的ID"<<endl;
	cin>>ID;
	int curID = 0,curST = 0;
	int stcur = -1;
	run_chient(0);
	for(int i = 0;i < (int)server_string.length()&&server_string[i] != '#';i++,curST = i,curID = 0){
		bool flag = true;
		while(curID < ID.length() && curST < server_string.length()){
			if(server_string[curST] != ID[curID]){
				flag = false;
				break;
			}
			curID++,curST++;
		}
		if(flag == true){
			stcur = i+curID;
			break;
		}
	}
	if(stcur == -1){
		cout<<"[ERR]找不到用户或用户已被封禁，请联系管理员"<<endl;
		return 0;
	}
	cout<<"[info]解析数据中..."<<endl;
	int edcur = stcur;
	钱包长度 = 0;
	while(server_string[edcur] != '!') edcur++;
	for(int i = stcur+1;i < edcur;i++){
		string tempstring;
		while(server_string[i] != ' '){
			tempstring.push_back(server_string[i]);
			i++;
		}
		钱包[钱包长度++] = atoi(tempstring.c_str());
	}
	if(钱包长度 == 0){
		cout<<"[ERR]解析数据失败";
		return 0;
	}
	
	
	/*
	for(int i = 0;i < 钱包长度;i++){
		cout<<钱包[i]<<" ";
	}
	cout<<endl;
	*/
	cout<<"[info]解析数据成功"<<endl;
	run(1);
	has = atoi(结果.c_str());
	if(has == 0){
		cout<<"目前账户为空，请检查你的私钥或请求转账"<<endl;
		Sleep(100000);
		return 0;
	}
	
	server_string.erase(stcur+1,edcur-stcur-1);
	server_string.insert(stcur+1,"0");
	send_string = server_string;
	run_chient(1);
	cout<<"[info]数据覆写完成"<<endl;
	
	
	game();
	
	
	
	system("cls");
	明文 = has;
	run(0);
	curID = curST = 0;
	stcur = -1;
	server_string.clear();
	run_chient(0);
	for(int i = 0;i < (int)server_string.length()&&server_string[i] != '#';i++,curST = i,curID = 0){
		bool flag = true;
		while(curID < ID.length() && curST < server_string.length()){
			if(server_string[curST] != ID[curID]){
				flag = false;
				break;
			}
			curID++,curST++;
		}
		if(flag == true){
			stcur = i+curID;
			break;
		}
	}
	if(stcur == -1){
		cout<<"[ERR]数据错误：用户数据丢失"<<endl;
		return 0;
	}
	cout<<"[info]解析数据中..."<<endl;
	edcur = stcur;
	while(server_string[edcur] != '!') edcur++;
	server_string.erase(stcur+1,1);
	结果.pop_back();
	server_string.insert(stcur+1,结果);
	send_string = server_string;
	run_chient(1);
	cout<<"[info]数据已更新，请及时保存你的新的私钥"<<endl;
	Sleep(100000);
	return 0;
}
