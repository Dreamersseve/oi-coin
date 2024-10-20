#include <bits/stdc++.h>  
#include <windows.h>  
using namespace std;  

constexpr int maxn = 25;  

// 拓展欧几里得算法  
int exgcd(int a, int b, int *x, int *y) {  
	if (b == 0) {  
		*x = 1;  
		*y = 0;  
		return a;  
	}  
	int gcd = exgcd(b, a % b, x, y);  
	int temp = *x;  
	*x = *y;  
	*y = temp - a / b * (*y);  
	return gcd;  
}  

// 素数判断  
bool isprime(int a) {  
	for (int i = 2; i * i <= a; i++) {  
		if (a % i == 0) return false;  
	}  
	return true;  
}  

// 生成素数表  
vector<int> primegenerator(int start, int count) {  
	vector<int> primes;  
	for (int i = start; primes.size() < count; i++) {  
		if (isprime(i)) {  
			primes.push_back(i);  
		}  
	}  
	return primes;  
}  

// 加密函数  
string encrypt(const string &plaintext, int p, int q, int e, int n) {  
	string ciphertext = "";  
	for (char ch : plaintext) {  
		int mi = ch;  
		int cipher = 1;  
		for (int j = 1; j <= e; j++) {  
			cipher = (cipher * mi) % n;  
		}  
		ciphertext += to_string(cipher) + ' ';  
	}  
	return ciphertext;  
}  

// 解密函数  
string decrypt(const vector<int> &ciphertext, int d, int n) {  
	string plaintext = "";  
	for (int cipher : ciphertext) {  
		int ming = cipher;  
		int plain = 1;  
		for (int j = 0; j < d; j++) {  
			plain = (plain * ming) % n;  
		}  
		plaintext += char(plain);  
	}  
	// 去除多余的空格  
	while (plaintext.back() == ' ') {  
		plaintext.pop_back();  
	}  
	return plaintext;  
}  

// 主函数封装调用  
int 钱包长度;
int 钱包[20];
int 私钥d,私钥n;
string 结果;

int 明文;
void run(bool flag = 0) {  
	srand((unsigned int)time(0));  
	vector<int> primes = primegenerator(91, 10);  
	
	int p = rand() % 10;  
	int q;  
	do {  
		q = rand() % 10;  
	} while (q == p);  
	
	int n = primes[p] * primes[q];  
	int fi_n = (primes[p] - 1) * (primes[q] - 1);  
	
	int e, d, w1, w2;  
	for (e = fi_n / 2; e >= 1; e--) {  
		if (exgcd(e, fi_n, &w1, &w2) == 1) {  
			break;  
		}  
	}  
	int nu;  
	exgcd(e, fi_n, &d, &nu);  
	d = (d % fi_n + fi_n) % fi_n; // 确保d是非负的  
	
	
	if (flag == 0) {  
		string plaintext;  
	//	cout << "请输入明文" << endl;  
		plaintext = to_string(明文);
		
		string ciphertext = encrypt(plaintext, p, q, e, n);  
		结果 = ciphertext;
		cout << "私钥更新为: " << d << ' ' << n << endl;  
	} else if (flag == 1) {  
		int k;  
		k = 钱包长度; 
		
		vector<int> ciphertext(k);  
		
		for (int i = 0; i < k; i++) {
			ciphertext[i] = 钱包[i];
		}  
		
		cout << "请输入你的当前私钥（d，n） （分别输入d，n用空格隔开）" << endl;  
		int d1, n1;  
		cin >> d1 >> n1;  
		
		string plaintext = decrypt(ciphertext, d1, n1);  
		结果 = plaintext;
	//	cout << "明文为: " << plaintext << endl;  
	} else {  
		cout << "无效选择" << endl;  
	}  
}  

