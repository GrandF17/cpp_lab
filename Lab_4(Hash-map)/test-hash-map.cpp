#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "hash-map.h"

using namespace std;

int main() {
    cout << "\n\n-_-_-_-_-_-_ First one -_-_-_-_-_-_\n\n";
    hash_map<int, int> q;

    cout << "Koefficient of congestion is " << q.getCKM() << ";" << endl;
    clock_t prev = clock()/1000.0;
    for(int i = 0; i < 10000000; i++) {
        q.insert(rand(), rand());
    }
    cout << "Operation of filling the array runtime is " << (clock()/1000.0 - prev) << endl;

    //q.print();
    prev = clock()/1000.0;  //test how fast is operation push
    try{ cout << "Element you search for: " << q.get(6729) << endl; }                            
    catch (exception) { cout << "Not found" << '\n'; }
    cout << "Operation get value runtime is " << (clock()/1000.0 - prev) << endl;
    q.size();

    prev = clock()/1000.0;  //test how fast is operation push
    q.insert(rand(), rand());
    cout << "Insertion runtime is " << (clock()/1000.0 - prev) << endl;
    q.size();

    q.clear();
    q.size();

    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

    cout << "\n\n-_-_-_-_-_-_ Second one -_-_-_-_-_-_\n\n";
    hash_map<int, int> new_q;
    new_q.setCKM(0.75);

    cout << "Koefficient of congestion is " << new_q.getCKM() << ";" << endl;
    prev = clock()/1000.0;
    for(int i = 0; i < 10000000; i++) {
        new_q.insert(rand(), rand());
    }
    cout << "Operation of filling the array runtime is " << (clock()/1000.0 - prev) << endl;

    //new_q.print();
    prev = clock()/1000.0;  //test how fast is operation push
    try{ cout << "Element you search for: " << new_q.get(6729) << endl; }                            
    catch (exception) { cout << "Not found" << '\n'; }
    cout << "Operation get value runtime is " << (clock()/1000.0 - prev) << endl;
    new_q.size();

    prev = clock()/1000.0;  //test how fast is operation push
    new_q.insert(rand(), rand());
    cout << "Insertion runtime is " << (clock()/1000.0 - prev) << endl;
    new_q.size();

    new_q.clear();
    new_q.size();
}