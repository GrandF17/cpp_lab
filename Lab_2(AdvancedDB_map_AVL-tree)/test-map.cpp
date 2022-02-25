#include "map.h"
#include <iostream>

using namespace std;

int main() {
    Map<int/*key*/, int/*value*/> /*trie*/q;
/*
    //check if map is empty:
    cout << (trie.isEmpty() ? "Map is empty" : "Map is filled") << endl;

    //filling our map:
    trie.insert(10, 50);
    trie.insert(20, 40);
    trie.insert(30, 25);
    trie.insert(40, 20);
    trie.insert(50, 10);
    trie.insert(25, 30);

    //check if map is not empty:
    cout << (trie.isEmpty() ? "Map is empty" : "Map is filled") << endl;
     

//            30
//            / \
//           20 40
//           / \ \
//          10 25 50

    
    //Show tree in order
    trie.inOrder();
    cout << "Element you search for is: " << trie.find(30) << endl;
    trie.find(30) = 40;
    cout << "Element you search for is: " << trie.find(30) << endl;
    
    cout << "Element you search for: " << (trie.exists(30) ? "exists" : "doesn't exist") << endl;

    Map<int, int> newTrie = trie;
    //newTrie = trie;

    int a = 1;
    int b = a;

    trie.clear();
    trie.inOrder();
    newTrie.inOrder();
    
    return 0;
*/

    long long size = 1000;
    while(size <= 10000000) {
        cout << "New test is running...\nSize of queue is supposed to be: " << size << "\n\n";

        cout << (q.isEmpty() ? "Map is empty" : "Map is filled") << endl;

        for(int i = 0; i < size; i++) { q.insert(rand(), rand()); }
    
        cout << (q.isEmpty() ? "Map is empty" : "Map is filled") << endl;       
        
        //for find
        int N1 = rand(), N2 = N1;
        clock_t prev = clock()/1000.0;  //test how fast is operation push
        q.insert(N1, rand());
        cout << "Operation push runtime is " << (clock()/1000.0 - prev) << endl;
        N1++;
        //for find

        //q.inOrder();

        cout << "Element you search for (N1): " << (q.exists(N1) ? "exist" : "doesn't exist") << endl;
        if(q.exists(N2)) { cout << "Element you search for is (N2): " << q.find(N2) << endl; }

        try{ q.find(N1); }                            
        catch (const std::exception& e) {
            std::cout << e.what() << '\n';
            throw;
        }

        q.clear();

        cout << (q.isEmpty() ? "Map is empty" : "Map is filled") << "\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n";

        size *= 100;
    }
    return 0;
    
}