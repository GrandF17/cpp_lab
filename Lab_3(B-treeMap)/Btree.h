/*map.h*/

#ifndef BTREE_H
#define BTREE_H

#include <fstream>
#include <iostream>

using namespace std;

const int t = 3;

struct BNode {
	int keys[2 * t];
	BNode *children[2*t+1];	
	BNode *parent;
	int count;	//	num of keys
	int countSons;	//	num of children
	bool leaf;
	bool is_leaf() {
		if (this->children[0]==NULL) return true;
		else return false;
	}
};

class Tree {
private:
	BNode *root;

	void insert_to_node(int key, BNode *node){
		node->keys[node->count]=key;
		node->count=node->count+1;
		sort(node);
	}


	void sort(BNode *node) { 
		int m;
		for (int i=0; i<(2*t-1); i++) {
			for (int j=i+1; j<=(2*t-1); j++) {
				if ((node->keys[i]!=0) && (node->keys[j]!=0)) {
					if ((node->keys[i]) > (node->keys[j])) {
						m=node->keys[i];
						node->keys[i]=node->keys[j];
						node->keys[j]=m;
					}
				} else {
					break;
				}
			}
		}
	}

	void restruct(BNode *node){
		if (node->count < 2 * t - 1) {
			return;
		}
		
		//	first son
		BNode *child1 = new BNode;
		for (int j = 0; j <= t - 2; j++){
			child1->keys[j] = node->keys[j];
		}
		for (int j = t - 1; j <= 2 * t - 1; j++){
			child1->keys[j] = 0;
		}
		child1->count = t - 1;	//	num of keys in node
		if(node->countSons != 0) {
			for (int i = 0; i <= t - 1; i++) {
				child1->children[i] = node->children[i];	
				child1->children[i]->parent = child1;
			} 
			for (int i = t; i <= 2 * t; i++) {
				child1->children[i] = NULL;
			} 
			child1->leaf = false;
			child1->countSons = t - 1;	//	num of children
		} else {
			child1->leaf = true;
			child1->countSons = 0;
			for (int i = 0; i <= 2 * t; i++) {
				child1->children[i] = NULL;
			} 
		}
		
		//	second son
		BNode *child2 = new BNode;
		for (int j = 0; j <= t - 1; j++) { 
			child2->keys[j] = node->keys[j + t];
		}
		for (int j = t; j <= 2 * t - 1; j++) {
			child2->keys[j] = 0;
		}
		child2->count = t;	//	num of keys in node
		if(node->countSons != 0) {
			for (int i = 0; i <= t; i++){
				child2->children[i] = node->children[i + t];
				child2->children[i]->parent = child2;
			}
			for (int i = t + 1; i <= 2 * t; i++){
				child2->children[i] = NULL;
			} 
			child2->leaf = false;
			child2->countSons = t;	//	num of children
		} else {
			child2->leaf = true;
			child2->countSons = 0;
			for (int i = 0; i <= 2 * t; i++){
				child2->children[i] = NULL;
			} 
		}
		
		//	parent
		//	no parent --> root
		if (node->parent == NULL) { 
			node->keys[0] = node->keys[t - 1];
			for(int j = 1; j <= 2 * t - 1; j++) {
				node->keys[j]=0;
			}
			node->children[0]=child1;
			node->children[1]=child2;
			for(int i = 2; i <= 2 * t; i++){
				node->children[i]=NULL;
			}
			node->parent = NULL;
			node->leaf = false;
			node->count = 1;
			node->countSons = 2;
			child1->parent = node;
			child2->parent = node;		
		} else {
			insert_to_node(node->keys[t - 1], node->parent);
			for (int i = 0; i <= 2 * t; i++) {
				if (node->parent->children[i] == node) {
					node->parent->children[i] = NULL;
				}
			}	
			for (int i = 0; i <= 2 * t; i++) {
				if (node->parent->children[i] == NULL) {	
					for (int j= 2 * t; j > i + 1; j--) {
						node->parent->children[j]=node->parent->children[j-1];
					}
					node->parent->children[i+1] = child2;
					node->parent->children[i] = child1;
					break;
				}
			}
			child1->parent = node->parent;
			child2->parent = node->parent;
			node->parent->leaf = false;
			delete node;	
		}
	}

	void print(BNode *node) {
		if (node == NULL) return;
		for(int i = 0; i <= 2 * t - 1; i++) {
			if (i==0) { cout << "\""; }
			if (node->keys[i] != 0) {
				cout << node->keys[i];
				if (i < 2 * t - 1 && node->keys[i + 1] != 0) {
					cout << ":";
				}
			} else {
				cout << "\";";
				break;
			}
		}

		cout << endl;
		int j = 0;

		while (node->children[j] != NULL) {
			for(int i = 0; i <= 2 * t - 1; i++) {
				if (i == 0) { cout << "\""; }
				if (node->keys[i] != 0) {
					cout << node->keys[i];
					if (i < 2 * t - 1)
					if (node->keys[i+1]!=0) { 
						cout << ":";
					}
				} else {
					cout << "\" -> ";
					break;
				}
			}
			print(node->children[j]);
			j++;
		}
	}

	void copy(Tree &oldTree, BNode *node) {
		if (node == NULL) {
			return;
		}

		for(int i = 0; i <= 2 * t - 1; i++) {
			if (node->keys[i] != 0) {
				oldTree.insert(node->keys[i]);
			}
		}

		int j = 0;
		while (node->children[j] != NULL) {
			copy(oldTree, node->children[j]);
			j++;
		}
    }

	BNode* deletenode(BNode *node){
		if (node != NULL){
			for (int i = 0; i <= 2 * t - 1; i++){
				if (node->children[i] != NULL){
					return deletenode(node->children[i]);	
				} else {
					delete(node);
					break;
				}
			}
		}
		return NULL; 
	}

public:
	Tree() {
		root = NULL;
	}

	~Tree() {
		if(root != NULL) {
			deletenode(root);
		}
	}

	Tree(const Tree& other) {
		copy(*this, other.root);
	}

    Tree& operator = (Tree &other) {
        if (this == &other) {
			return *this;
		}
		clear();
        copy(*this, other.root);
        return *this;
    }

	void clear() { 
		root = deletenode(root); 
	}

	void insert(int key){
		if (root == NULL) {
			BNode *newRoot = new BNode;
			newRoot->keys[0] = key;
			for(int j = 1; j <= 2 * t - 1; j++) {
				newRoot->keys[j] = 0;
			}
			for (int i = 0; i <= 2 * t; i++) {
				newRoot->children[i] = NULL;
			}
			newRoot->count = 1;
			newRoot->countSons = 0;
			newRoot->leaf = true;
			newRoot->parent = NULL;
			root = newRoot;
		} else {
			BNode *ptr = root;
			while (ptr->leaf == false) {
				for (int i = 0; i <= 2 * t - 1; i++){
					if (ptr->keys[i] != 0) {
						if (key<ptr->keys[i]) { 
							ptr = ptr->children[i];
							break;
						} 					
						if (ptr->keys[i + 1] == 0 && key > ptr->keys[i]) {
							ptr = ptr->children[i + 1];
							break;
						} 
						
					} else {
						break;
					}
				}
			}
			insert_to_node(key, ptr);

			while (ptr->count == 2 * t){
				if (ptr == root) {
					restruct(ptr);
					break;
				} else {
					restruct(ptr);
					ptr = ptr->parent;
				}
			}
		}
	}

	bool search(int key) {
		try {
			searchKey(key, this->root);
		} catch (exception) {
			return false;
		}
		return true;
	}

	bool isEmpty() {
		return root == NULL;
	}

	int& searchKey(int key, BNode *node) {
        if (node != NULL) {
			if (!node->leaf) {
				int i;
				for (i = 0; i <= 2 * t - 1; i++) {
					if (node->keys[i]!=0) {		
						if(key==node->keys[i]) {
							return node->keys[i];
						}
						if ((key<node->keys[i])) {
							return searchKey(key, node->children[i]);
							break;
						}
					} else {
						break;
					}
				}
				return searchKey(key, node->children[i]);
			} else {
				for(int j = 0; j <= 2 * t - 1; j++) {
					if (key == node->keys[j]) {
						return node->keys[j];
					}
				}
				throw exception();
			}
		} else {
			throw exception();
		}
    }

	void print() {
		if(this->root != NULL) {
			cout << "\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n\n" <<
			"Tree:" << endl;
			print(this->root);
			cout << "\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n" << endl;
		}
	}
};

#endif
