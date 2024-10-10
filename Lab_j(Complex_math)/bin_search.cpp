#include <iostream>
#include <vector>

using namespace std;

bool bin_search(vector<int>& arr, int start_idx, int end_idx, int num) {
    if(start_idx > end_idx)
        return false;

    int middle = (start_idx + end_idx) / 2;
    if(num > arr[middle])
        return bin_search(arr, middle + 1, end_idx, num);

    if(num < arr[middle])
        return bin_search(arr, start_idx, middle - 1, num);

    return (arr[middle] == num);
}

bool bin_search(vector<int>& arr, int num) {
    return bin_search(arr, 0, arr.size() - 1, num);
}

int main() {
    vector<int> arr;

    const int n = 100;
    for (int i = 0; i < n; ++i) {
        arr.push_back(i);
        cout << arr[i];
        cout << " ";
    }

    cout << endl;
    
    cout << bin_search(arr, 37) << endl;
}