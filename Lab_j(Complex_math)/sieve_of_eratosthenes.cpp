#include <iostream>
#include <vector>

using namespace std;

vector<int> sieve(int n) {
    vector<bool> mark(n, true);
    vector<int> primes;
    primes.push_back(2);
    for(int i = 3; i * i <= n /*i < sqrt(n)*/; i += 2)
        if(mark[i])
            for(int j = i * i; j < n; j += i)
                mark[j] = false;
    
    for(int i = 3; i <= n; i += 2)
        if(mark[i]) 
            primes.push_back(i);

    return primes;
}

int main() {
    vector<int> primes = sieve(113);
    for(auto prime : primes) {
        cout << prime << " ";
    }
}