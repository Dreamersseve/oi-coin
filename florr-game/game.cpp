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
void phb(){
	
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
			server_string.insert(tempi,to_string(has));
			p[playeri].score = has;
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
void drawmp(bool flag = false){
	system("cls");
	for(int i = 0;i <= n;i++){
		cout<<"    ";
		int start = n/2-i/2,ed = n/2+i/2;
		if(i%2) start--;
		for(int j = 0;j <= n;j++){
			if(j >= start && j <= ed){
				if(i%2) cout<<" "<<mp[i][j];
				else cout<<mp[i][j]<<" ";
			}
			else cout<<"  ";
		}
		cout<<endl;
	}
	/*
	cout<<"res:";
	for(int i = 0;i <= n;i++){
	res[i] += mp[n][i];
	cout<<res[i]<<" ";
	}
	cout<<endl;
	*/
	
	cout<<"倍率";
	for(int i = 0;i <= n;i++){
		cout<<sol[i]<<" ";
		has += mp[n][i] * ms[i];
	}
	cout<<"     D:500 L:70 | 输入-1退出";
	cout<<endl;
	cout<<"目前持有florrcoin："<<has<<endl;
	cout<<"排行榜(实时更新):"<<endl<<endl;
	if(flag) phb();
	drawphb();
}
mt19937 rd(time(0));
#define rand rannnd
int rand(){
	return rd()%2;
}

void game(){
	cout<<"请决定下落速度 300-1000"<<endl;
	int T;
	cin>>T;
	drawmp(1);
	while(1){
		start:
		drawmp(1);
		int num = 0;
		cin>>num;
		if (std::cin.fail()) {  
			std::cin.clear();  
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
			std::cout << "ERR:      输入无效" << std::endl;  
			goto start;
		} 
		if(has < num){
			system("cls");
			cout<<"ERR:You don't have that much leverage"<<endl;
			Sleep(1000);
			system("cls");
			drawmp(0);
			goto start;
		}
		if(num < 0) break;
		has -= num;
		mp[0][n/2] = num;
		for(int i = 0;i <= n;i++){
			
			for(int j = 0;j <= n;j++){
				while(mp[i][j] > 0){
					if(i%2 == 0){
						if(rand()){
							mp[i+1][j-1]++;
							mp[i][j]--;
						}
						else{
							mp[i+1][j]++;
							mp[i][j]--;
						}
					}
					else{
						if(rand()){
							mp[i+1][j+1]++;
							mp[i][j]--;
						}
						else{
							mp[i+1][j]++;
							mp[i][j]--;
						}
					}
				}
			}
			drawmp(0);
			Sleep(T-40*i>0?T-40*i:10);
			
		}
		
	}
}
