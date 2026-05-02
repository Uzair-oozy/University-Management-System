#ifndef STACK_H
#define STACK_H

#include <string>
using namespace std;

class StackNode {
public:
    string data;
    StackNode* next;

    StackNode(string d) {
        data = d;
        next = nullptr;
    }
};

class Stack {
private:
    StackNode* top;
    int count;

public:
    Stack();
    void push(string data);
    string pop();
    string peek();
    bool isEmpty();
    void display();
    int size();
    ~Stack();
};

#endif