#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#include <ctime> 

using namespace std;

void selection_sort(vector<int>& arr) {
    for(int i = arr.size() - 1; i >= 1 ; i--) {
        int max = 0;
        for(int j = 1; j <= i; j++) {
            if(arr[max] < arr[j])
                max = j;
        }
        swap(arr[max], arr[i]);
    }
}

//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

void bubble_sort(vector<int>& arr) {
    for(int i = 0; i < arr.size(); i++) {
        bool is_sorted = true;
        for(int j = 0; j < arr.size() - 1 - i; j++) {
            if(arr[j] > arr[j + 1]) {
                is_sorted = false;
                swap(arr[j], arr[j + 1]);
            }
        }
        if(is_sorted)
            return;
    }
}

//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

void insertion_sort(vector<int>& arr) {
    for(int i = 1; i < arr.size(); i++) {
        int cur = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > cur) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = cur;
    }
}

//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

void counting_sort(vector<int>& arr) {
    int min = arr[0];
    int max = arr[0];
    //searching for min and max elements
    for(int i = 1; i < arr.size(); i++) {
        if(arr[i] > max)
            max = arr[i];
        if(arr[i] < min)
            min = arr[i];
    }
    //filing our array with zeros
    vector<int> arrCount(max - min + 1);

    for(int i = 0; i < arr.size(); i++)
        arrCount[arr[i] - min]++;
    
    int j = 0;
    for(int i = 0; i < max - min + 1; i++) {
        while(arrCount[i] > 0) {
            arr[j] = i + min;
            arrCount[i]--;
            j++;
        }
    }
}

//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

vector<int> merge(vector<int>& left, vector<int>& right) {
    int left_idx = 0, right_idx = 0;
    vector<int> merged;

    while(left_idx < left.size() && right_idx < right.size()) {
        if(left[left_idx] <= right[right_idx]) {
            merged.push_back(left[left_idx++]);
        } else {
            merged.push_back(right[right_idx++]);
        }
    }
    while(left_idx < left.size())
        merged.push_back(left[left_idx++]);
    while(right_idx < right.size())
        merged.push_back(right[right_idx++]);
    return merged;
}

void merge_sort(vector<int>& arr) {
    if(arr.size() <= 1)
        return;

    vector<int> left, right; 
    int n = arr.size() / 2;

    for(int i = 0; i < n; i++)
        left.push_back(arr[i]);
    for(int i = n; i < arr.size(); i++)
        right.push_back(arr[i]);
    
    merge_sort(left);
    merge_sort(right);

    arr = merge(left, right);
}

//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

int partition(vector<int>& arr, int begin_idx, int end_idx) {
    //int s2 = begin_idx;//section of bigger or equal digits
    int s1 = begin_idx;//size - 1 of section of digits which are less than pivot
    
    int pivot = (begin_idx + end_idx) / 2;
    swap(arr[begin_idx], arr[pivot]);
    pivot = begin_idx;

    for(int i = begin_idx + 1; i <= end_idx; i++) {
        if(arr[i] < arr[begin_idx]){
            s1++;
            swap(arr[i], arr[s1]);
        }
    }
    swap(arr[begin_idx], arr[s1]);
    return s1;
}

void quick_sort(vector<int>& arr, int begin_idx, int end_idx) {
    if(begin_idx == end_idx + 1)
        return;

    int pivot = partition(arr, begin_idx, end_idx);//[begin_idx, pivot - 1] < arr[pivot] <= [pivot + 1, end_idx]
    quick_sort(arr, begin_idx, pivot - 1);
    quick_sort(arr, pivot + 1, end_idx);
}

void quick_sort(vector<int>& arr) {
    if(arr.size() == 0) {
        return;
    } else {
        quick_sort(arr, 0, arr.size() - 1);
    }
}

//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

int max_digit_pow(vector<int>& arr) {
    int max = arr[0];
    for(int i = 1; i < arr.size(); i++)
        if(arr[i] > max) max = arr[i];

    int counter = 0;
    while(max > 0) {
        max /= 10;
        counter++;
    }
    return counter;
}

int getNthDigit(int number, int n) {
    return  ((number / (int)pow(10, n - 1)) % 10);
}

void radix_sort(vector<int>& arr) {
    vector<vector<int>> buckets(10);
    int power_of_ten = 1;
    for(int pow = 1; pow <= max_digit_pow(arr); pow++) {
        for(auto elem : arr) {
            buckets[getNthDigit(elem, pow)].push_back(elem);
        }
        arr.clear();
        for(int i = 0; i < buckets.size(); i++) {
            for(int  j = 0; j < buckets[i].size(); j++) {
                arr.push_back(buckets[i][j]);
            }
            buckets[i].clear();
        }
    }
}

int main() {
    cout << "Compariosn of 7 types of sorts:";

    vector<int> arr, arr_copy, final_arr;
    int num = 10000;

    while(num <= 10000000) {
        cout << "Array cositsts of ";
        cout << num;
        cout << " digits..."<< endl;

        const int n = num;
        for (int i = 0; i < n; ++i) {
            arr.push_back(rand());
            arr_copy.push_back(arr[i]);
            final_arr.push_back(arr[i]);
        }

        if(final_arr == arr) cout << "Arr copy equals Arr" << endl;
        sort(final_arr.begin(), final_arr.end());//sort our final array

        //time ~ O(n^2):
        cout << "Selection sort is running..." << endl;
        arr = arr_copy;
        clock_t prev = clock()/1000.0;
        selection_sort(arr);
        cout << "runtime = " << (clock()/1000.0 - prev) << endl;
        if(final_arr == arr) cout << "Correct" << endl;

        cout << "Bubble sort is running..." << endl;
        arr = arr_copy;
        prev = clock()/1000.0;
        bubble_sort(arr);
        cout << "runtime = " << (clock()/1000.0 - prev) << endl;
        if(final_arr == arr) cout << "Correct" << endl;
        
        cout << "Isertion sort is running..." << endl;
        arr = arr_copy;
        prev = clock()/1000.0;
        insertion_sort(arr);
        cout << "runtime = " << (clock()/1000.0 - prev) << endl;
        if(final_arr == arr) cout << "Correct" << endl;

        //time ~ O(n*log(n)):
        cout << "Merge sort is running..." << endl;
        arr = arr_copy; 
        prev = clock()/1000.0;    
        merge_sort(arr);
        cout << "runtime = " << (clock()/1000.0 - prev) << endl;
        if(final_arr == arr) cout << "Correct" << endl;
        
        cout << "Quick sort is running..." << endl;
        arr = arr_copy;
        prev = clock()/1000.0;
        quick_sort(arr);
        cout << "runtime = " << (clock()/1000.0 - prev) << endl;
        if(final_arr == arr) cout << "Correct" << endl;

        //time ~ O(n + m):
        cout << "Counting sort is running..." << endl;
        arr = arr_copy;
        prev = clock()/1000.0;
        counting_sort(arr);
        cout << "runtime = " << (clock()/1000.0 - prev) << endl;
        if(final_arr == arr) cout << "Correct" << endl;

        //time ~ O(n*d):
        cout << "LSD (radix) sort is running..." << endl;
        arr = arr_copy;
        prev = clock()/1000.0;
        radix_sort(arr);//LSD sort (also exists MSD)
        cout << "runtime = " << (clock()/1000.0 - prev) << endl;
        if(final_arr == arr) cout << "Correct" << endl;

        num *= 10;
    }
}