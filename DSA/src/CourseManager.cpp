#include "Course.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// Course Constructor
Course::Course(string code, string name, int credits) {
    courseCode = code;
    courseName = name;
    creditHours = credits;
}

void Course::display() {
    cout << left << setw(15) << courseCode
         << setw(40) << courseName
         << setw(15) << creditHours << endl;
}

// ==================== COURSE MANAGER CLASS ====================
class CourseManager {
private:
    vector<Course> courses;

public:
    // Add new course
    void addCourse(string code, string name, int credits) {
        Course newCourse(code, name, credits);
        courses.push_back(newCourse);
        cout << "\n✓ Course added successfully!\n";
    }

    // Search course
    Course* findCourse(string code) {
        for (int i = 0; i < courses.size(); i++) {
            if (courses[i].courseCode == code) {
                return &courses[i];
            }
        }
        return nullptr;
    }

    // Display all courses
    void displayAll() {
        if (courses.empty()) {
            cout << "\n✗ No courses found!\n";
            return;
        }

        cout << "\n" << string(70, '=') << "\n";
        cout << left << setw(15) << "Course Code" 
             << setw(40) << "Course Name" 
             << setw(15) << "Credit Hours" << "\n";
        cout << string(70, '=') << "\n";

        for (int i = 0; i < courses.size(); i++) {
            courses[i].display();
        }
        cout << string(70, '=') << "\n";
    }

    // Get course count
    int getCount() {
        return courses.size();
    }

    // Save to file
    void saveToFile(string filename) {
        ofstream file(filename);
        for (int i = 0; i < courses.size(); i++) {
            file << courses[i].courseCode << "," 
                 << courses[i].courseName << "," 
                 << courses[i].creditHours << "\n";
        }
        file.close();
        cout << "✓ Courses saved to file.\n";
    }

    // Load from file
    void loadFromFile(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "No previous course data found.\n";
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string code, name, credStr;
            
            getline(ss, code, ',');
            getline(ss, name, ',');
            getline(ss, credStr, ',');

            int credits = stoi(credStr);
            courses.push_back(Course(code, name, credits));
        }
        file.close();
        cout << "✓ Courses loaded from file.\n";
    }
};