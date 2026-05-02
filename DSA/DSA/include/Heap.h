#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <string>
using namespace std;

class HeapNode {
public:
    string rollNumber;
    string name;
    float gpa;

    HeapNode(string roll = "", string n = "", float g = 0.0) {
        rollNumber = roll;
        name = n;
        gpa = g;
    }
};

class MaxHeap {
private:
    vector<HeapNode> heap;

    void heapifyUp(int index);
    void heapifyDown(int index);
    int parent(int index);
    int leftChild(int index);
    int rightChild(int index);

public:
    void insert(HeapNode node);
    HeapNode extractMax();
    void displayTop(int n);
    bool isEmpty();
    int size();
};

#endif