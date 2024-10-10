#include <iostream>
#include <queue>
#include <vector>
#define N 8

using namespace std;

void ShowPermutation(vector<int> tmp) {
    for (int i = 0; i < N; i++) {
        printf("%d ", i + 1);
    }
    printf("\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", tmp[i]);
    }
    printf("\n");
}

bool check(vector<vector<int>> a, vector<int> b) {
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == b) {
            return false;
        }
    }
    return true;
}

int main() {
    int i, n;
    vector<int> a, b;
    vector<vector<int>> arrayOfPermutations;

    a.push_back(7);
    a.push_back(8);
    a.push_back(6);
    a.push_back(2);
    a.push_back(4);
    a.push_back(5);
    a.push_back(3);
    a.push_back(1);

    // a.push_back(4);
    // a.push_back(2);
    // a.push_back(3);
    // a.push_back(5);
    // a.push_back(1);
    // a.push_back(6);

    cout << "g1 = " << endl;
    ShowPermutation(a);
    arrayOfPermutations.push_back(a);


    // -_-_-_-_-_ second permutaion -_-_-_-_-_

    b.push_back(4);
    b.push_back(8);
    b.push_back(6);
    b.push_back(1);
    b.push_back(7);
    b.push_back(3);
    b.push_back(5);
    b.push_back(2);

    // b.push_back(6);
    // b.push_back(4);
    // b.push_back(5);
    // b.push_back(2);
    // b.push_back(3);
    // b.push_back(1);

    cout << "g2 = " << endl;
    ShowPermutation(b);
    arrayOfPermutations.push_back(b);

    // -_-_-_-_-_ permutaion multiplication -_-_-_-_-_

    queue<vector<int>> tmp;
    vector<int> c;

    // -_-_-_-_-_ | -_-_-_-_-_

    // printf("\n\nMultiplication g1 * g1: \n");
    for (i = 0; i < N; i++) {
        c.push_back(a[a[i] - 1]);
    }
    // ShowPermutation(c);
    if (check(arrayOfPermutations, c)) {
        arrayOfPermutations.push_back(c);
        tmp.push(c);
    }
    c.clear();

    // -_-_-_-_-_ | -_-_-_-_-_

    // printf("Multiplication g1 * g2: \n");
    for (i = 0; i < N; i++) {
        c.push_back(b[a[i] - 1]);
    }
    if (check(arrayOfPermutations, c)) {
        arrayOfPermutations.push_back(c);
        tmp.push(c);
    }
    // ShowPermutation(c);
    c.clear();

    while (!tmp.empty()) {
        // printf("\n\nMultiplication g1 * g_n: \n");
        vector<int> d = tmp.front();
        for (i = 0; i < N; i++) {
            c.push_back(d[a[i] - 1]);
        }
        // ShowPermutation(c);
        if (check(arrayOfPermutations, c)) {
            arrayOfPermutations.push_back(c);
            tmp.push(c);
        }
        c.clear();
        d.clear();
        tmp.pop();
    }

    for (int i = 0; i < arrayOfPermutations.size(); i++) {
        tmp.push(arrayOfPermutations[i]);
    }

    while (!tmp.empty()) {
        // printf("\n\nMultiplication g_n * g_1: \n");
        vector<int> d = tmp.front();
        for (i = 0; i < N; i++) {
            c.push_back(a[d[i] - 1]);
        }
        // ShowPermutation(c);
        if (check(arrayOfPermutations, c)) {
            arrayOfPermutations.push_back(c);
            tmp.push(c);
        }
        d.clear();
        c.clear();
        tmp.pop();
    }

    // -_-_-_-_-_ | -_-_-_-_-_

    // printf("\n\nMultiplication g2 * g2: \n");
    for (i = 0; i < N; i++) {
        c.push_back(b[b[i] - 1]);
    }
    // ShowPermutation(c);
    if (check(arrayOfPermutations, c)) {
        arrayOfPermutations.push_back(c);
        tmp.push(c);
    }
    c.clear();

    // -_-_-_-_-_ | -_-_-_-_-_

    // printf("\n\nMultiplication g2 * g1: \n");
    for (i = 0; i < N; i++) {
        c.push_back(a[b[i] - 1]);
    }
    // ShowPermutation(c);
    if (check(arrayOfPermutations, c)) {
        arrayOfPermutations.push_back(c);
        tmp.push(c);
    }
    c.clear();

    // -_-_-_-_-_ | -_-_-_-_-_

    for (int i = 0; i < arrayOfPermutations.size(); i++) {
        tmp.push(arrayOfPermutations[i]);
    }

    while (!tmp.empty()) {
        // printf("\n\nMultiplication g2 * g_n: \n");
        vector<int> d = tmp.front();
        for (i = 0; i < N; i++) {
            c.push_back(d[b[i] - 1]);
        }
        // ShowPermutation(c);
        if (check(arrayOfPermutations, c)) {
            arrayOfPermutations.push_back(c);
            tmp.push(c);
        }
        c.clear();
        d.clear();
        tmp.pop();
    }

    for (int i = 0; i < arrayOfPermutations.size(); i++) {
        tmp.push(arrayOfPermutations[i]);
    }

    while (!tmp.empty()) {
        // printf("\n\nMultiplication g_n * g_2: \n");
        vector<int> d = tmp.front();
        for (i = 0; i < N; i++) {
            c.push_back(b[d[i] - 1]);
        }
        // ShowPermutation(c);
        if (check(arrayOfPermutations, c)) {
            arrayOfPermutations.push_back(c);
            tmp.push(c);
        }
        d.clear();
        c.clear();
        tmp.pop();
    }

    cout << "All permutations: " << endl;
    for (int i = 0; i < arrayOfPermutations.size(); i++) {
        ShowPermutation(arrayOfPermutations[i]);
        cout << endl;
    }

    cout << "Permutations at all: " << arrayOfPermutations.size() << endl;

    return 0;
}