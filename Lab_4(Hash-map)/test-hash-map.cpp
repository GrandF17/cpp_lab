#include <iostream>
#include <string>
#include <vector>
#include "hash-map.h"

using namespace std;

//319171894
int main() {
    hash_map<int, int> q;
    /*string s;
    string gen = {"abcdefghijklmnopqrstuvwxyz"};
    int str_num = 5;
    for(int i = 0; i < str_num; i++) {
        for(int j = 0; j < rand() % 13; j++) {
            if(j == 0) {
                s = gen[(int) (rand() % 26)];
            } else {
                s += gen[(int) (rand() % 26)];
            }
        }
        cout << "String: " << s << "\nString hash: " << q.string_hash(s) << endl;
    }*/

    //cout << "String: " << 103746 << "\nString hash: " << q.string_hash(103746) << endl;
    
    for(int i = 0; i < 100000; i++) {
        q.insert(rand(), rand());
    }
/*
    q.insert(2125, 2);
    q.insert(21543, 3);
    q.insert(3039, 4);
    q.print();
    cout << "\n\n";

    cout << q.get(2125);
    q.get(2125) = 3;
    cout << q.get(2125);
    cout << "\n\n";

    q.print();
*/
/*
    q.extract(1);
    q.print();
    cout << "\n\n";
    q.extract(1);
    q.print();
    cout << "\n\n";
    q.extract(1);
    q.print();
    cout << "\n\n";
    q.extract(1);
    q.print();
    cout << "\n\n";
*/
    cout << "Size: " << q.congestion_koeff() << endl;
    cout << "Size: " << q.size() << endl;
    //q.clear();
}