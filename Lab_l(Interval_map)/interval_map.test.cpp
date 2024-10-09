#include <cassert>
#include <iostream>
#include <string>

#include "./interval_map.cpp"

using namespace std;

auto it=[](const string& testName, auto testFunc)->bool{
    try {
        cout << "Running " << testName << "..." << endl;
        testFunc();
        return true;
    } catch (const exception& e) {
        return false;
    }
};

void IntervalMapTest() {
    // Тест 1: Проверка инициализации
    char defaultVal = 'A';
    interval_map<int, char> imap(defaultVal);

    auto checkInterval = [&imap](int begin, int end, char const& val) {
        for (int i = begin; i < end; ++i)
            if (imap[i] != val) return false; 
        return true; 
    };
    
    it("1 test",  [&]() {
        imap.assign(1, 6, 'B');
        assert(checkInterval(1, 6, 'B'));
        assert(imap[0] == defaultVal);
    });

    it("2 test", [&]() {
        imap.assign(6, 10, 'C');
        assert(checkInterval(6, 10, 'C'));
    });

    it("3 test", [&]() {
        imap.assign(10, 15, 'D');
        assert(checkInterval(10, 15, 'D'));
    });

    it("4 test", [&]() {
        imap.assign(12, 13, 'H');
        assert(checkInterval(12, 13, 'H'));
    });

    it("5 test", [&]() {
        imap.assign(-10, -1, 'K');
        assert(checkInterval(-10, -1, 'K'));
    });

    it("6 test", [&]() {
        imap.assign(17, 18, 'K');
        assert(checkInterval(17, 18, 'K'));
    });

    it("7 test", [&]() {
        imap.assign(17, 18, 'K');
        assert(checkInterval(17, 18, 'K'));
    });

    it("8 test", [&]() {
        imap.assign(4, 11, 'P');
        assert(checkInterval(4, 11, 'P'));
    });

    it("9 test", [&]() {
        imap.assign(-2, 18, 'K');
        assert(checkInterval(-10, 18, 'K'));
        assert(imap[-11] == 'A');
        assert(imap[18] == 'A');
        assert(imap[30] == 'A');
    });

    cout << "All tests passed!" << endl;
}

int main(int argc, char ** argv) {
    IntervalMapTest();
    return 0;
}