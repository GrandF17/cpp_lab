/*map.h*/

#ifndef MAP_H
#define MAP_H

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

template<typename KEY,  typename VALUE, typename COMPARATOR = std::less<KEY>>
class Map {
   
    struct Node {
        pair<KEY, VALUE> element;
        Node *left;
        Node *right;
        Node *parent;
        int height;
    };

    Node* root;
    COMPARATOR C;
    long long count;    //to count all the tree nodes in our AVL-tree

    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

    int height(Node *root) {
        if (root == NULL) return 0;
        return root->height;
    }
    
    int max(int height_left, int height_right) {
        return (height_left > height_right)? height_left : height_right;
    }
    
    Node* newNode(KEY key, VALUE value) {
        Node* node = new Node();
        node->element.first = key;
        node->element.second = value;
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
        node->height = 1;
        return(node);
    }
    
    Node* rightRotate(Node *y) {
        Node *x = y->left;
        Node *T2 = x->right;
    
        x->right = y;
        y->left = T2;
    
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
    
        return x;
    }

    Node* leftRotate(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;
    
        y->left = x;
        x->right = T2;
    
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
    
        return y;
    }
    
    int getBalance(Node *node) {
        if (node == NULL) return 0;
        return height(node->left) - height(node->right);
    }
    
    Node* insert(Node *node, KEY key, VALUE value) {
        Node *root = newNode(key, value);
        if (node == NULL) return root;  //insertion

        if (root->element.first == node->element.first)
            return node;
        else if (C(root->element.first, node->element.first)/*equals a < b == true*/)
            node->left = insert(node->left, key, value);
        else
            node->right = insert(node->right, key, value);
/*    
        if (compareLess(root, node))//key < node->element.first
            node->left = insert(node->left, key, value);
        else if (compareGreater(root, node))//key > node->element.first
            node->right = insert(node->right, key, value);
        else return node;   //if we find the same key we do nothing
*/
        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->element.first) return rightRotate(node);   //if left branch is longer
    
        if (balance < -1 && key > node->right->element.first) return leftRotate(node);  //if right branch is longer
    
        if (balance > 1 && key > node->left->element.first) {   //if left branch is longer
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    
        if (balance < -1 && key < node->right->element.first) { //if right branch is longer
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* find(Node* node, KEY key) {
        if(node) {
            if (key < node->element.first) return find(node->left, key);
            else if (key > node->element.first) return find(node->right, key);
            else return node;   //if we find the same key we return it back
        }

        return NULL;
    }

    void inOrder(Node *root) {
        if(root != NULL) {
            inOrder(root->left);
            cout << "[" << root->element.first << ", " << root->element.second << "]; ";
            inOrder(root->right);
        }
    }

    void counter_of_nodes(Node *root) {
        if(root != NULL) {
            count++;
            counter_of_nodes(root->left);
            counter_of_nodes(root->right);
        }
    }

    Node* destroyTree(Node *root) {
        if(root != NULL) {
            root->left = destroyTree(root->left);
            root->right = destroyTree(root->right);
            delete root;
        }
        return NULL;
    }

    void copy(Map &oldTree, Node *root) {
        if(root != NULL) {
            oldTree.insert(root->element.first, root->element.second);
            copy(oldTree, root->left);
            copy(oldTree, root->right);
        }
    }

public :
    void inOrder() {
        inOrder(root);
        cout << endl;
    }

    long long size() {
        count = 0;
        counter_of_nodes(root); 
        return count;
    }

    void insert(KEY key, VALUE value) { root = insert(root, key, value); }

    void copy(Map &oldTree) { copy(oldTree, root); }

    void clear() { root = destroyTree(root); }

    bool exists(KEY key) { return find(root, key); }

    VALUE& find(KEY key) { 
        Node* temp =  find(root, key);
        if (temp != NULL) return temp->element.second;
        else throw exception();
    }

    bool isEmpty() { return root == NULL ? true : false; }
    
    Map()
        : root(nullptr)
    {}

    ~Map() {
        clear();
        /*
        cout << "All created objects were destroyed" << endl;
        cout << (isEmpty() ? "Map is empty" : "Map is filled") << endl;
        */
    }

    Map(const Map& other) {
		copy(*this, other.root);
	}

    Map& operator = (Map &other) {
        if (this == &other) return *this;
        clear();
        copy(*this, other.root);
        return *this;
    }
};

#endif
