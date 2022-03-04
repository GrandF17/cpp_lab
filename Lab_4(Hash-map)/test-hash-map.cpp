#include <iostream>
#include <string>
#include <vector>
#include "hash-map.h"

using namespace std;

int main() {
    cout << "\n\n-_-_-_-_-_-_ First one -_-_-_-_-_-_\n\n";
    hash_map<int, int> q;
    
    for(int i = 0; i < 1000000; i++) {
        q.insert(rand(), rand());
    }

    cout << "\n\n-_-_-_-_-_-_ Second one -_-_-_-_-_-_\n\n";
    hash_map<int, int> new_q;
    new_q.setCKM(0.75);

    for(int i = 0; i < 10; i++) {
        new_q.insert(rand(), rand());
    }

    new_q.insert(2125, 2);              //insert pair [2125, 2]
    cout << new_q.get(2125) << endl;    //check the insertion (value = 2)
    //new_q.get(2125) = 3;              //change value (3 instead 2)
    cout << new_q.get(2125) << endl;    //chech if the value of pair had been changed
    cout << "\n\n";

    new_q.print();            //do not use if the size of array is too big
    cout << "Size: " << q.congestion_koeff() << endl;
    
    try{ cout << "Element you search for: " << q.get(18467) << endl; }                            
    catch (exception) { cout << "Not found" << '\n'; }

    new_q.extract(18467);

    try{ cout << "Element you search for: " << q.get(18467) << endl; }                            
    catch (exception) { cout << "Not found" << '\n'; }

    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

    q.clear();
    q.print();
    q.size();
}