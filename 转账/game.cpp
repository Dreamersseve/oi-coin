#include<bits/stdc++.h>
#include<windows.h>
#include "game.h"
#include "RSA.h"
#include "chient.h"
using namespace std;
constexpr int maxn1 = 25;
string ID;
int mp[maxn1][maxn1];
int res[maxn1];
char sol[maxn1] = {'D','L','5','3','2','0','1','1','1','1','1','0','2','3','5','L','D'};
int ms[maxn1] = {500,70,5,3,2,0,1,1,1,1,1,0,2,3,5,70,500};
int getcur(int x){
	if(x%2) return x;
	else return x+1;
}
constexpr int n = 16;
int has;
struct player{
	string name;
	int score;
	bool operator <(player x){
		return score > x.score;
	}
}p[1000];
int playeri;
void phb(int val = has){
	run_chient();
	int curst = 0;
	while(server_string[curst] != '#') curst++;
	playeri = 0;
	for(int i = curst+1;i < (int)server_string.length();i++){
		string nametemp,scoretemp;
		while(server_string[i] != '|'){
			nametemp.push_back(server_string[i]);
			i++;
		}
		i++;
		p[playeri].name = nametemp;
		
		int tempi = -1;
		if(nametemp == ID){
			tempi = i;
		}
		
		while(server_string[i] != ']'){
			scoretemp.push_back(server_string[i]);
			i++;
		}
		
		if(tempi != -1){
			server_string.erase(tempi,i-tempi);
			server_string.insert(tempi,to_string(val));
			p[playeri].score = val;
			send_string = server_string;
			run_chient(1);
		}
		else p[playeri].score = atoi(scoretemp.c_str());
		
		
		playeri++;
	}
	sort(p,p+playeri);
}
void drawphb(){
	cout<<"用户ID | FlorrCoin余额"<<endl;
	for(int i = 0;i < playeri;i++){
		cout<<p[i].name<<" | "<<p[i].score<<endl;
	}
	return;
}
mt19937 rd(time(0));
#define rand rannnd
int rand2(){
	return rd()%2;
}
int game(){
	cout<<"[info]请输入转入用户ID"<<endl;
	
	重新输入:
	string inID;
	cin>>inID;
	
	phb();
	int IDcur = -1;
	for(int i = 0;i < playeri;i++){
		if(p[i].name == inID){
			IDcur = i;
			break;
		}
	}
	if(IDcur == -1){
		cout<<"[WAR]找不到ID，请重新输入"<<endl;
		Sleep(1000);
		goto 重新输入;
	}
	cout<<"[info]请输入转入数额"<<endl;
	int need;
	cin>>need;
	if(need > has || need <= 0){
		cout<<"[ERR]数额非法";
		Sleep(1000);
		return 0;
	}
	has -= need;
	p[IDcur].score += need;
	cout<<"目前剩余:"<<has<<"FlorrCoin"<<endl;
	明文 = p[IDcur].score;
	run(0);
	
	string tempID = ID;
	ID = inID;
	phb(p[IDcur].score);
	ID = tempID;
	
	int curID = 0,curST = 0;
	int stcur = -1;
	run_chient(0);
	for(int i = 0;i < (int)server_string.length()&&server_string[i] != '#';i++,curST = i,curID = 0){
		bool flag = true;
		while(curID < inID.length() && curST < server_string.length()){
			if(server_string[curST] != inID[curID]){
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
	while(server_string[edcur] != '!') edcur++;
	server_string.erase(stcur+1,1);
	结果.pop_back();
	server_string.insert(stcur+1,结果);
	send_string = server_string;
	run_chient(1);
	system("pause");
	return 0;
}
