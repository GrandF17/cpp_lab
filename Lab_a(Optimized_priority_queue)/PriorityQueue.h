/*priority_queue.h*/

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class priority_queue {
private:
    vector<T> heap;
public:
    int size() { return heap.size() - 1; }

    bool empty() { return heap.size() > 1 ? true : false; }
 
private:       
  // some addition methods (no one)
 
public:
    //constructor
    priority_queue() { heap.resize(1); }
    
    //delete:
    void pop() { //O(log(n))
        swap(heap[1], heap[heap.size() - 1]);
        heap.pop_back();
        int ind = 1;
        while((ind << 1) < heap.size() && heap[ind] <= heap[ind << 1] || (ind << 1 | 1) < heap.size() && heap[ind] <= heap[ind << 1 | + 1]) {
            if((ind << 1 | 1) >= heap.size() || heap[ind << 1] >= heap[ind << 1 | 1]) {
                swap(heap[ind], heap[ind << 1]);
                ind <<= 1;
            } else  {
                swap(heap[ind], heap[ind << 1 | 1]);
                ind <<= 1;
                ind++;
            }
        }
     }
 
   //add:
    void push(const T &node) { //O(log(n))
        heap.push_back(node);
        int ind = heap.size() - 1;
        while(ind != 1 && heap[ind] > heap[ind >> 1]) {
            swap(heap[ind], heap[ind >> 1]);
            ind >>= 1;
        }
    }
   
   //max element
    T& front() { return heap[1]; } //O(1)
};
 
#endif