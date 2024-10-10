#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include "PriorityQueue.h"

using namespace std;

int main() {
    priority_queue<int> q;
    srand(time(0));
/*    
    q.push(2);  //uncomment to test simple queue
    q.push(5);
    q.push(3);
    q.push(10);
    q.push(6);
    q.push(9);
    q.push(40);
    q.push(5);
    q.push(12);

    cout << "Queue is empty: " << (q.empty() == 0 ? "true" : "false") << endl;

    cout << q.front() << endl;//40
    q.pop();
    cout << q.front() << endl;//12
    q.pop();
    cout << q.front() << endl;//10
    q.pop();
    cout << q.front() << endl;//9
    q.pop();
    cout << q.front() << endl;//6
    q.pop();
    cout << q.front() << endl;//5
    q.pop();
    cout << q.front() << endl;//5
    q.pop();
    cout << q.front() << endl;//3
    q.pop();
    cout << q.front() << endl;//2
    q.pop();//delete 2

    cout << "Size: " << q.size() << endl;
*/
    long long size_of_queue = 10000;
    while(size_of_queue <= 100000000) {
        cout << "New test is running...\nSize of queue is supposed to be: " << size_of_queue << "\n\n";

        cout << "Queue is empty: " << (q.empty() == 0 ? "true" : "false") << endl;
        cout << "Queue size: " << q.size() << endl;

        for(int i = 0; i < size_of_queue; i++) { q.push(rand()); }

        cout << "Queue is empty: " << (q.empty() == 0 ? "true" : "false") << endl;
        cout << "Queue size: " << q.size() << endl;
        cout << "Max element in the queue is " << q.front() << "\n\n";

        //test how fast is operation push:
        clock_t prev = clock()/1000.0;
        q.push(rand());
        cout << "Operation push runtime is " << (clock()/1000.0 - prev) << endl;

        //test how fast is operation pop:
        prev = clock()/1000.0;
        q.pop();
        cout << "Operation pop runtime is " << (clock()/1000.0 - prev) << "\n\n";

        for(int i = 0; i < size_of_queue; i++) { q.pop(); }

        cout << "Queue is empty: " << (q.empty() == 0 ? "true" : "false") << endl;//Make sure the queue is empty
        cout << "Queue size: " << q.size() << endl;
        cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_" << endl;

        size_of_queue *= 100;
    }
    return 0;
}