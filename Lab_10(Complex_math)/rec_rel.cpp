#include <iostream>
#include <vector>

using namespace std;

vector<vector<long long>> matrix_mul(const vector<vector<long long>>& A, const vector<vector<long long>>& B, long long mod) {
    int n = A.size();//num of columns in A
    int m = A[0].size();//num of strings in A = num of columns in B
    int k = B[0].size();//num of strings in B
    vector<vector<long long>> C(n, vector<long long>(k));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < k; j++) {
            for(int k = 0; k < m; k++) {
                C[i][j] += (A[i][k] * B[k][j]) % mod;
            }
            C[i][j] %= mod;
        }
    }
    return C;
}

vector<vector<long long>> bin_pow(vector<vector<long long>> A, long long n, long long mod) {
    vector<vector<long long>> result(A.size(), vector<long long>(A.size()));
    for(int i = 0; i < result.size(); i++)
        result[i][i] = 1;
    
    while(n) {
        if(n & 1) {//if digit is even
            result = matrix_mul(result, A, mod);
        }
        n >>= 1;//devide by 2
        A = matrix_mul(A, A, mod);
    }
    return result;
}

int main() {//fibonacci digits
    vector<vector<long long>> fib_matrix{
        {1, 1},
        {1, 0}
    };

    vector<vector<long long>> fib_first{
        {1, 0}
    };

    long long f1 = 1, f0 = 0;
    const int mod = 10000;
    for(int i = 1; i <= 10; i++) {
        //cout << "F(" << i << ") = " << fib_first[0][0] << endl;
        fib_first = matrix_mul(fib_first, fib_matrix, mod);

        long long tmp = f1;
        f1 = (f1 + f0) % mod;
        f0 = tmp;
        //cout << "F(" << i << ") = " << f0 << endl;

        if(f1 != fib_first[0][0]) {
            cout << "ERROR" << f1 << " " << fib_first[0][0] << endl;
        }
        auto matrix_pow = bin_pow(fib_matrix, i, mod);
        auto fibs = matrix_mul({ {1, 0} }, matrix_pow, mod);
        if(f1 != fibs[0][0]) {
            cout << "ERROR" << f1 << " " << fibs[0][0]<< endl;
        }
    }
}