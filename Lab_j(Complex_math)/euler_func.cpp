#include <iostream>

using namespace std;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int euler(int n) {//O(n*log(n))
    int count = 1;
    for(int i = 2; i < n; i++) {
        if(gcd(i, n) == 1) {
            count++;
        }
    }
    return count;
}

int euler_fast(int n) {//O(sqrt(n))
    int result = n;
    int prime = 2;
    while(n >= prime * prime) {
        if(n % prime == 0) {
            result = result / prime * (prime - 1);// (1 - 1/p) = (p - 1)/p
            while(n % prime == 0) {// if we'll meet 4 after 2 we could not repeat the same action cause 4 = 2^2 etc.
                n /= prime;
            }
        }
        prime++;
    }
    if(n != 1) {
        result = result / n * (n - 1);
    }
    return result;
}

int main() {
    cout << (euler(9) == 6);
    cout << (euler_fast(9) == 6);

    cout << (euler(36) == 12);
    cout << (euler_fast(36) == 12);

    cout << (euler(84) == 24);
    cout << (euler_fast(84) == 24);
}