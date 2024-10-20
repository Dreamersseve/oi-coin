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
void run() {  
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
	
	int choice;  
	cout << "请选择加密/解密" << endl;  
	cout << "输入0代表加密 输入1代表解密" << endl;  
	cin >> choice;  
	
	if (choice == 0) {  
		string plaintext;  
		cout << "请输入明文" << endl;  
		cin >> plaintext;  
		
		string ciphertext = encrypt(plaintext, p, q, e, n);  
		cout << "密文为: " << ciphertext << endl;  
		cout << "解密私钥为: " << d << ' ' << n << endl;  
	} else if (choice == 1) {  
		int k;  
		cout << "请输入密文长度" << endl;  
		cin >> k;  
		
		vector<int> ciphertext(k);  
		cout << "请输入密文" << endl;  
		for (int i = 0; i < k; i++) {  
			cin >> ciphertext[i];  
		}  
		
		cout << "请输入私钥（d，n） （分别输入d，n用空格隔开）" << endl;  
		int d1, n1;  
		cin >> d1 >> n1;  
		
		string plaintext = decrypt(ciphertext, d1, n1);  
		cout << "明文为: " << plaintext << endl;  
	} else {  
		cout << "无效选择" << endl;  
	}  
}  

