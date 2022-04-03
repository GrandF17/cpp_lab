/*hash-map.h*/

#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <list>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

template <typename K, typename V, typename Hash = std::hash<K>>
class hash_map {
private:
    int amount_of_hashes = 0;           //amount of elements in our hash table
    vector<list<pair<K, V>>> hashes;    //vector of lists of pairs :)
    const int p = 301;                  //simple digit for hash func
    int m = 16;                         //array size (modulus) - variable
    float congestion_koeff_max = 2.0;   //CKM
    Hash h;

public:
    float congestion_koeff() { return (float) amount_of_hashes / (float) m; }

    void size() { cout << "Size of array of hashes: " << hashes.size() << " Elements at all: " << amount_of_hashes << endl; }

    void setCKM(float new_koeff) { congestion_koeff_max = new_koeff; }

    float getCKM() { return congestion_koeff_max; }

private:
    /*
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
    */

    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

    void clear(vector<list<pair<K, V>>>& arr) {
        for(int i = 0; i < arr.size(); i++) { arr.at(i).clear();}
        arr.erase(arr.begin(), arr.end());
    }

    void overload_array() {
        vector<list<pair<K, V>>> temp = hashes;
        m = 2 * m + 1;
        clear(hashes);
        hashes.resize(m);

        for(int i = 0; i < temp.size(); i++) {
            if(!temp.at(i).empty()) {
                for (auto currentPair : temp.at(i)) {
                    pair<K, V> currentpair = currentPair;
                    size_t hash = h(currentpair.first) % m;
                    hashes.at(hash).push_back(currentpair);
                }
            }
        }
        //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
        clear(temp);
        temp.resize(0);
    }

    void print_lists(list<pair<K, V>>& list) {
        for (auto currentPair : list) {
            pair<K, V> currentpair = currentPair;
            cout << "[" << currentpair.first << ", " << currentpair.second << "] ";
        }
        cout << "\n";
    }

    pair<K, V>& find_list(list<pair<K, V>> l, K key) {
        if(!l.empty()) {
            for(auto iter = l.begin(); iter != l.end(); iter++) {
                pair<K, V> currentpair = *iter;
                if(currentpair.first == key) {
                    return *iter;
                }
            }
        }
        throw exception();
    }
public:
    //constructor
    hash_map() { hashes.resize(m); }

    void insert(K key, V value) {
        pair<K, V> p = {key, value};
        size_t hash = h(key) % m;
        if(hashes.at(hash).empty()) {
            hashes.at(hash).push_back(p);
            amount_of_hashes++;
        } else {
            for (auto currentPair : hashes.at(hash)) {
                pair<K, V> currentpair = currentPair;
                if(currentPair.first == p.first) {
                    return;
                }
            }
            hashes.at(hash).push_back(p);
            amount_of_hashes++;
        }
        if(congestion_koeff() > congestion_koeff_max) {
            cout << congestion_koeff() << " - congestion_koeff()" << endl;
            //cout << "Array was: \n\n";
            //print();
            overload_array();
            //cout << "\n\nArray now: \n\n";
            //print();
        }
    }

    void print() { 
        if(!hashes.empty()) {
            for(int i = 0; i < m; i++) { 
                if(!hashes.at(i).empty()) {
                    cout << i << ") ";
                    print_lists(hashes.at(i)); 
                }
            }
        }
    }

    void extract(K key) {
        size_t hash = h(key) % m;
        for(auto iter = hashes.at(hash).begin(); iter != hashes.at(hash).end(); iter++) {
            pair<K, V> currentpair = *iter;
            if(currentpair.first == key) {
                hashes.at(hash).erase(iter);
                return;
            }
        }
    }

    void clear() {
        clear(hashes);
        m = 16;
        hashes.resize(m);
        amount_of_hashes = 0;
    }

    V& get(K key) {
        size_t hash = h(key) % m;
        if(!hashes.at(hash).empty()) {
            try {
                return find_list(hashes.at(hash), key).second;
            } catch (exception) { }
        }
        throw exception();
    }
};
 
#endif
