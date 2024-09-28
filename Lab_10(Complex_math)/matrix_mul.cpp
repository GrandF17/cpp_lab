#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> matrix_mul(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size()/*num of columns in A*/, m = A[0].size()/*num of strings in A = num of columns in B*/, t = B[0].size()/*num of strings in B*/;
    vector<vector<int>> C(n, vector<int>(t));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < t; j++) {
            for(int k = 0; k < m; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

int main() {
    vector<vector<int>> A = {
        {1, 2, 3},
        {3, 1, 2}
    };
    vector<vector<int>> B = {
        {1, 2},
        {3, 2},
        {1, 2}
    };
    vector<vector<int>> C = {
        {10, 12},
        {8, 12}
    };
    cout << (matrix_mul(A, B) == C);
}