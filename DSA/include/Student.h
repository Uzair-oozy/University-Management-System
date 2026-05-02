#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

class Student {
public:
    string rollNumber;
    string name;
    string department;
    int semester;
    float gpa;
    Student* next;  // For linked list

    Student(string roll, string n, string dept, int sem, float g = 0.0);
    void display();
};

#endif