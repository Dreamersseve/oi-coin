#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
constexpr int maxn = 25;
int exgcd(int a, int b,int *x,int *y)                                     //拓展欧几里得算法
{
	if(b==0)
	{
		*x=1;
		*y=0;
		return a;
	}
	int gcd=exgcd(b,a%b,x,y);
	int temp=*x;
	*x=*y;
	*y=temp-a/b*(*y);
	return gcd;
}

int isprime(int a)                                                          //素数判断
{
	int i;
	for(i=2;i<1+(a/2);i++){
		if(a%i==0)return 1;
	}
	return 0;
}

void primegenerator(int prime[10])                             //生成素数表
{
	int i,j=0;
	for(i=91;i<=1000;i++){
		if(isprime(i)==0){
			prime[j]=i;
			j++;
		}
		if(j>9)break;
	}
}
int mp[maxn][maxn];
int res[maxn];
char sol[maxn] = {'D','L','5','3','2','0','1','1','1','1','1','0','2','3','5','L','D'};
int ms[maxn] = {500,20,5,3,2,0,1,1,1,1,1,0,2,3,5,20,500};
int getcur(int x){
	if(x%2) return x;
	else return x+1;
}
constexpr int n = 16;
int has;
void drawmp(){
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
	cout<<"     D:500 L:20 | 输入-1退出";
	cout<<endl;
	cout<<"目前持有："<<has<<endl;
}
mt19937 rd(time(0));
#define rand rannnd
int rand(){
	return rd()%2;
}

void game(){
	cout<<"请决定下落速度 300-1000";
	int T;
	cin>>T;
	drawmp();
	while(1){
		start:
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
			drawmp();
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
			system("cls");
			drawmp();
			Sleep(T-40*i>0?T-40*i:10);
			
		}
		
	}
}
const int cz = 1000;
int main(){
	int prime[10];
	primegenerator(prime);
	int seed,p,q;
	seed=time(0);
	srand((unsigned int)seed);                              //生成在范围内的随机素数p，q
	p=rand()%9;
	do{
		q=rand()%9;
	}while(q==p);
	int e,d,n,fi_n,r,nu,w1,w2;
	char minwen[1000];
	int i,j,mi;
	
	int shuma_jiemiwen[10000];
	
	cout<<"请输入钱包长度"<<endl;
	int k;
	cin>>k;
	if(k < 0){
		cout<<"ERR K < 0";
		return 0;
	}
	cout<<"请输入钱包"<<endl;                                                      //录入密文
	int t=0;
	for(i=0;i<k;i++){
		cin>>shuma_jiemiwen[i];
	}
	int sizel=k;
	
	cout<<"请输入私钥（d，n） （分别输入d，n用空格隔开）"<<endl;
	int d1,n1;
	cin>>d1>>n1;
	int ming;
	int shuma_jieminwen[sizel];                                                    //开始解密
	for(i=0;i<sizel;i++){
		ming=shuma_jiemiwen[i];
		shuma_jieminwen[i]=1;
		for(j=0;j<d1;j++){
			shuma_jieminwen[i]=shuma_jieminwen[i]*ming%n1;
		}
	}
	
	char jieminwen[sizel];
	for(i=0;i<sizel;i++){
		jieminwen[i]=shuma_jieminwen[i];
	}    //输出明文
	has = atoi(jieminwen);
	system("cls");
	game();
	cout<<"钱包已更新"<<endl;
	
	
	
	
	for(int i = 0;i < 10;i++) prime[i] = 0;
	primegenerator(prime);
	seed = 0,p = 0,q = 0;
	seed=time(0);
	srand((unsigned int)seed);                              //生成在范围内的随机素数p，q
	p=rand()%9;
	do{
		q=rand()%9;
	}while(q==p);
	e=d=n=fi_n=r=nu=w1=w2 = 0;
	i=j=mi = 0;
	cout<<p<<" "<<q<<endl;
	int a;
	for(int i = 0;i < 1000;i++) minwen[i] = '\0';
	
	n=prime[p]*prime[q];
	fi_n=(prime[p]-1)*(prime[q]-1);
	for(r=fi_n/2;n>=1;r--){                                                 //求得公钥
		if(exgcd(r,fi_n,&w1,&w2)==1){
			e=r;
			break;
		}
	}
	r=exgcd(e,fi_n,&d,&nu);
	string temp = to_string(has);
	
	
	for(int i = 0;i < temp.length();i++){
		minwen[i] = temp[i];
	}
	int shuma_minwen[strlen(minwen)];
	for(i=0;i<strlen(minwen);i++){
		shuma_minwen[i]=minwen[i];
	}
	int shuma_miwen[strlen(minwen)];                                         //录入结束，开始加密
	for(i=0;i<strlen(minwen);i++){
		mi=shuma_minwen[i];
		shuma_miwen[i]=1;
		for(j=1;j<=e;j++){
			shuma_miwen[i]=(shuma_miwen[i]*mi)%n;
		}
	}
	cout<<"钱包为"<<endl;
	for(i=0;i<strlen(minwen);i++){
		cout<<shuma_miwen[i]<<' ';                                       //加密结束，输出密文，私钥
	}
	cout<<endl<<"钱包长度为"<<i<<endl;
	cout<<endl<<"私钥为"<<endl;
	cout<<d<<' '<<n<<endl;
	
	Sleep(100000);
}

