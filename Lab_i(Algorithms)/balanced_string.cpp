#include <iostream>
#include <stack>

using namespace std;

bool isBalansed(string str) {
    stack<char> st;
    for (int i = 0; i < str.length(); i++) {
        if (st.empty()) {
            st.push(str[i]);
        } else {
            if (str[i] == ')' && st.top() == '(') {
                st.pop();
            } else if (str[i] == '}' && st.top() == '{') {
                st.pop();
            } else if (str[i] == ']' && st.top() == '[') {
                st.pop();
            } else {
                st.push(str[i]);
            }
        }
    }
    return st.empty();
}

int main() {
    string s1 = "()({[]}())";  // true
    string s2 = "{}";          // true
    string s3 = "}{";          // false
    string s4 = "";            // true
    string s5 = "(()";         // false
    string s6 = "())";         // false
    string s7 = "[(])";        // false

    cout << isBalansed(s1) << endl;
    cout << isBalansed(s2) << endl;
    cout << isBalansed(s3) << endl;
    cout << isBalansed(s4) << endl;
    cout << isBalansed(s5) << endl;
    cout << isBalansed(s6) << endl;
    cout << isBalansed(s7) << endl;
}