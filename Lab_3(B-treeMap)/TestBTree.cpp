#include <fstream>
#include <iostream>
#include <ctime>
#include "BTree.h"

using namespace std;

int simple_test() {
	Tree tree, new_tree;

	for(int i = 0; i < 120; i++) {
		tree.insert(i); 
	}
	
	cout << "\nSearch for: ";
	int value = rand() % 1000;
	cout << value << endl;
	try {
		tree.search(value);
		if (tree.search(value) == 1) { 
			cout << "Exists" << endl;
		} else {
			cout << "Not Exists" << endl;
		}
	} catch (exception) {
		cout << "Fail" << endl;
		return 0;
	}

	cout << "\nPrint tree: " << endl;
	try {
		tree.print();
	} catch (exception) {
		cout << "Fail" << endl;
		return 0;
	}

	cout << "\nCopy tree to new_tree: " << endl;
	try {
		new_tree = tree;
	} catch (exception) {
		cout << "Fail" << endl;
		return 0;
	}

	cout << "\nPrint new_tree: " << endl;
	new_tree.print();

	tree.clear();
	if (tree.isEmpty()) { 
		cout << "Tree is empty" << endl;
	} else {
		cout << "Tree is not empty" << endl;
		cout << "Fail" << endl;
		return 0;
	}

	if (new_tree.isEmpty()) { 
		cout << "New_tree is empty" << endl;
		cout << "Fail" << endl;
		return 0;
	} else {
		cout << "New_tree is not empty" << endl;
	}
	return 1;
}

int hard_test() {
	Tree tree, new_tree;

	clock_t prev = clock()/1000.0;  //test how fast is operation insert on 10^7 elements
	for(int i = 0; i < 1e7 /* 10 ^ 7 */; i++) {
		tree.insert(i); 
	}
	cout << "Insertion runtime is " << (clock()/1000.0 - prev) << endl;
	return 1;
}

int main() {
	
	cout << "Simple test:" <<
		"\n1) create tree of 120 elements" <<
		"\n2) print it and search random element" <<
		"\n3) copy tree to new_tree and print new_tree" <<
		"\n4) clear tree and check if it is empty, then check if new_tree is empty" <<
	endl;
	if(simple_test()) {
		cout << "Simple test passed" << endl;
	}
	if(hard_test()) {
		cout << "Hard test passed" << endl;
	}

	return 0;
}