#include <iostream>

using namespace std;

long long binary_pow(long long num, long long n, long long mod) {
    long long result = 1;
    while(n != 0) {
        if(n & 1) {//if digit is even
            result *= num;
            result %= mod;
        }
        n >>= 1;//devide by 2
        num *= num;
        num %= mod;
    }
    return result;
}

int main() {
    long long mod = 1000000007;
    cout << 2 * binary_pow(5, mod - 2, mod) % mod;
}