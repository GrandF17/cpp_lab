#include <iostream>
#include <vector>

using namespace std;

int queens(int row, vector<int>& col, vector<int>& diag1, vector<int>& diag2) {  // O(n!)
    const int n = col.size();
    if (row == n) {
        return 1;
    }
    int count = 0;
    for (int column = 0; column < n; column++) {
        if (col[column] == 0 && diag1[column + row] == 0 && diag2[row - column + (n - 1)] == 0) {
            col[column] = diag1[column + row] = diag2[row - column + (n - 1)] = 1;
            count += queens(row + 1, col, diag1, diag2);
            col[column] = diag1[column + row] = diag2[row - column + (n - 1)] = 0;
        }
    }
    return count;
}

int main() {
    for (int n = 1; n <= 40; n++) {
        vector<int> col(n);
        vector<int> diag1(2 * n - 1);
        vector<int> diag2(2 * n - 1);
        std::cout << queens(0, col, diag1, diag2) << endl;
    }
}