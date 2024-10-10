#include <iostream>

using namespace std;

long long int binary_exp1(long long int num, long long int n) {
    if(n == 0)
        return 1;
    if((n % 2) == 1)
        return num * binary_exp1(num, n - 1);
    long long int b = binary_exp1(num, n / 2);
    return b * b;
}

long long int binary_exp2(long long int num, long long int n) {
    long long int result = 1;
    while(n != 0) {
        // if digit is even
        if(n & 1) result *= num;
        // divide by 2
        n >>= 1;
        num *= num;
    }
    return result;
}

int main() {
    cout << binary_exp1(2, 60) << endl;
    cout << binary_exp2(2, 62) << endl;
}