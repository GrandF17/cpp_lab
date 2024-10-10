#include <iostream>

using namespace std;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

int main() {
    cout << gcd(13, 26) << endl;
    cout << gcd(13, 17) << endl;

    cout << lcm(13, 26) << endl;
    cout << lcm(13, 17) << endl;
}