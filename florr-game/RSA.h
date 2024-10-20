#ifndef RSA_H
#define RSA_H
#include <bits/stdc++.h>  
#include <windows.h>  
using namespace std;  

// 拓展欧几里得算法  
int exgcd(int a, int b, int *x, int *y);

// 素数判断  
bool isprime(int a);

// 生成素数表  
vector<int> primegenerator(int start, int count);

// 加密函数  
string encrypt(const string &plaintext, int p, int q, int e, int n);

// 解密函数  
string decrypt(const vector<int> &ciphertext, int d, int n);
extern int 钱包长度;
extern int 明文;
extern int 钱包[20];
extern int 私钥d,私钥n;
extern string 结果;
// 主函数封装调用  
void run(bool flag);

#endif
