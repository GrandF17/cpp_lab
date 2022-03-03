/*hash-map.h*/

#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

template <typename K, typename V>
class hash_map {
private:
    int count = 0;
    struct Node {
        int hash;
        pair<K, V> element;
        Node *next;
    };

    vector<Node*> hashes;
    const int p = 301;
    int m = 1e3 /*10^3*/+ 7;

public:
    int size() {
        int counter = 0; 
        for(int i = 0; i < m; i++) { counter += count_lists(hashes.at(i)); }
        return counter;
    }

    float congestion_koeff() { return (float) size() / (float) m; }
 
private:
    Node *newNode(K key, V value, int hash) {
        Node* node = new Node();
        node->hash = hash;
        node->element.first = key;
        node->element.second = value;
        node->next = NULL;
        return(node);
    }

    string toString(K key) {
        ostringstream oss;
        oss << key;
        return oss.str();
    }

    long long string_hash(const K& key) {//O(n)
        string s = toString(key);
        long long hash = 0;
        long long prime_pow = 1;
        for(char ch : s) {
            hash  = (hash + (ch - 'a' + 1) * prime_pow) % m;
            prime_pow = (prime_pow * p) % m;
        }
        return hash < 0 ? hash + m : hash;
    }

    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

    Node *extract(Node *root, K key) {
        if(root == NULL) { return NULL; }
        if(root->element.first == key) {
            delete root;
            if(root->next == NULL) {
                return NULL;
            } else {
                root = root->next;
                return root;
            }
        } else {
            return extract(root->next, key);
        }
    }

    Node* find(K key) {
        int hash = string_hash(key);
        while(hashes.at(hash) != NULL) {
            if(hashes.at(hash)->element.first == key) return hashes.at(hash); 
            hashes.at(hash) = hashes.at(hash)->next;
        }
        return NULL;
    }

    Node* destroy_HM(Node *root) {
        if(root != NULL) {
            delete root;
            while(root->next != NULL) {
                delete root;
                return root = root->next;
            }
        }
        return NULL;
    }

    int count_lists(Node *root) {
        int counter = 0;
        if(root != NULL) {
            while(root->next != NULL) {
                root = root->next;
                counter++;
            }
            counter++;
        }
        return counter;
    }

    void insert_lists(Node *root, Node *node) {
        if(root->element.first != node->element.first) {
            if(root->next != NULL) {
                insert_lists(root->next, node);
            } else {
                root->next = node;
            }
        }
    }

    void print_lists(Node *root) {
        if(root != NULL) {
            cout << "[" << root->element.first << ", " << root->element.second << "]; ";
            print_lists(root->next);
        } else {
            cout << endl;
        }
    }

    void overload_array() {
        vector<Node*> temp = hashes;
        m = 2 * m + 1;
        hashes.clear();
        hashes.resize(m);

        for(int i = 0; i < temp.size(); i++) {
            if(temp.at(i) != NULL) {
                insert(temp.at(i)->element.first, temp.at(i)->element.second);
                while(temp.at(i)->next != NULL) {
                    temp.at(i) = temp.at(i)->next;
                    insert(temp.at(i)->element.first, temp.at(i)->element.second);
                }
            }
        }
        temp.clear();
    }

public:
    //constructor
    hash_map() { hashes.resize(m); }

    //destructor
    ~hash_map() { clear(); }

    void insert(K key, V value) {
        int hash = string_hash(key);
        if(hashes.at(hash) == NULL) {
            hashes.at(hash) = newNode(key, value, hash);
        } else {
            insert_lists(hashes.at(hash), newNode(key, value, hash));
        }
        float k = congestion_koeff();
        if(k > 0.75) {
            cout << k << " - was; and size = " << m << "; resized; ";
            overload_array();
            cout << congestion_koeff() << " - now; and size = " << m << endl;
        }
    }

    void print() { 
        for(int i = 0; i < m; i++) { 
            if(hashes.at(i) != NULL) {
                cout << i << ") ";
                print_lists(hashes.at(i)); 
            }
        } 
    }

    void extract(K key) {
        int hash = string_hash(key);
        hashes.at(hash) = extract(hashes.at(hash), key);
    }

    V& get(K key) { 
        Node* temp =  find(key);
        if (temp != NULL) {
            return temp->element.second;
        } else {
            delete temp;
            throw exception();
        }
    }

    void clear() {
        for(int i = 0; i < m; i++) { 
            if(hashes.at(i) != NULL) {
                hashes.at(i) = destroy_HM(hashes.at(i));
            }
        }
    }
};
 
#endif