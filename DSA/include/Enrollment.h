#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include <string>
using namespace std;

class Enrollment {
public:
    string rollNumber;
    string courseCode;
    string semester;

    Enrollment(string roll = "", string code = "", string sem = "");
    void display();
};

#endif