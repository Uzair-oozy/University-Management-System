#ifndef QUEUE_H
#define QUEUE_H

#include <string>
using namespace std;

class QueueNode {
public:
    string rollNumber;
    string courseCode;
    QueueNode* next;

    QueueNode(string roll, string code) {
        rollNumber = roll;
        courseCode = code;
        next = nullptr;
    }
};

class Queue {
private:
    QueueNode* front;
    QueueNode* rear;
    int count;

public:
    Queue();
    void enqueue(string roll, string code);
    void dequeue();
    bool isEmpty();
    void display();
    QueueNode* getFront();
    int size();
    ~Queue();
};

#endif