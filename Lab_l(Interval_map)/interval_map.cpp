#include <map>
#include <iostream>

using namespace std;

// NOTE: K should be comparable "<=>"
template <typename K, typename V>
class interval_map {
    friend void IntervalMapTest();

    /**
     * m_valBegin = A
     *
     * map({3, B}, {7, C}, {20, A})
     * map([3...)[7...)[20...))
     * [A )[B   )[C   )[A     )
     *
     * assign(11, 13, "H") -->
     *
     * map(3, 7, 11, 13, 20)
     * map([3...)[7...)[11...)[13...)[20...))
     * [A )[B   )[C   )[H    )[C    )[A     )
     */

    V m_valBegin;
    map<K, V> m_map;

    V const& getValue(K const& key) const {
        auto it = m_map.upper_bound(key);
        if (it == m_map.begin()) {
            return m_valBegin;
        } else {
            return (--it)->second;
        }
    }

   public:
    // constructor associates whole range of K with val
    interval_map(V const& val)
        : m_valBegin(val) {}
    
    /**
     *  total time complexity: O(log(n))
     *  space complexity: O(n)
     */
    void assign(K const& keyBegin, K const& keyEnd, V const& val) {
        // request validation
        if (!(keyBegin < keyEnd) || val == m_valBegin) return;

        // pointers to left and right boders
        auto leftBorder = m_map.lower_bound(keyBegin);  // O(log(n))
        auto rightBorder = m_map.lower_bound(keyEnd);   // O(log(n))
        V tmp = getValue(keyEnd);                       // O(log(n))

        // iterate till the right border
        while (leftBorder != rightBorder) {             // O(K)
            auto nextIt = next(leftBorder);
            m_map.erase(leftBorder);
            leftBorder = nextIt;
        }

        if (getValue(keyBegin) != val) m_map[keyBegin] = val;
        m_map[keyEnd] = tmp;
    }

    // look-up of the value associated with key
    V const& operator[](K const& key) const {
        return getValue(key);
    }

    void print() {
        for(auto it = m_map.begin(); it != m_map.end(); ++it) {
            cout << "{" << it->first << ", " << it->second<< "}";
            if (next(it) != m_map.end()) cout << ",";
        }
        cout << endl;
    }
};