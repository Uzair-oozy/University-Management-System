#ifndef COURSE_H
#define COURSE_H

#include <string>
using namespace std;

class Course {
public:
    string courseCode;
    string courseName;
    int creditHours;

    Course(string code = "", string name = "", int credits = 0);
    void display();
};

#endif