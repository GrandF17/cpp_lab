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
        cout << "New test is running...\nSize of AVL-tree is supposed to be: " << size << "\n\n";
        cout << (q.isEmpty() ? "Map is empty" : "Map is filled") << endl;

        for(int i = 0; i < size; i++) { q.insert(rand() * rand(), rand() * rand()); }
    
        cout << (q.isEmpty() ? "Map is empty" : "Map is filled") << endl;       
        cout << "Real size of AVL-tree is: " << q.size() << "\n\n";
        //_-_-_-_-_-_-_-_-_-_-_-_-_-_-for find_-_-_-_-_-_-_-_-_-_-_-_-_-_-
        int N1 = rand() * rand(), N2 = N1;
        clock_t prev = clock()/1000.0;  //test how fast is operation push
        q.insert(N1, rand() * rand());
        cout << "Operation push runtime is " << (clock()/1000.0 - prev) << endl;
        N1++;
        //_-_-_-_-_-_-_-_-_-_-_-_-_-_-for find_-_-_-_-_-_-_-_-_-_-_-_-_-_-

        //q.inOrder();

        cout << "Element you search for (N1): " << (q.exists(N1) ? "Exist" : "Doesn't exist") << endl;
        try{ cout << "Element you search for is (N1): " << q.find(N1) << endl; }                            
        catch (exception) {
            std::cout << "Not found" << '\n';
        }
        if(q.exists(N2)) { cout << "Element you search for is (N2): " << q.find(N2) << endl; }

        q.clear();

        cout << (q.isEmpty() ? "Map is empty" : "Map is filled") << endl;
        cout << "Real size of AVL-tree is: " << q.size() << "\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n";

        size *= 100;
    }
    return 0;
    
}