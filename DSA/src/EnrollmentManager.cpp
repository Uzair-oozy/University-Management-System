#include "Enrollment.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// Enrollment Constructor
Enrollment::Enrollment(string roll, string code, string sem) {
    rollNumber = roll;
    courseCode = code;
    semester = sem;
}

void Enrollment::display() {
    cout << left << setw(15) << rollNumber
         << setw(15) << courseCode
         << setw(15) << semester << endl;
}

// ==================== ENROLLMENT MANAGER CLASS ====================
class EnrollmentManager {
private:
    vector<Enrollment> enrollments;

public:
    // Add enrollment
    void addEnrollment(string roll, string code, string sem) {
        Enrollment newEnrollment(roll, code, sem);
        enrollments.push_back(newEnrollment);
        cout << "\n✓ Student enrolled successfully!\n";
    }

    // Check if already enrolled
    bool isEnrolled(string roll, string code) {
        for (int i = 0; i < enrollments.size(); i++) {
            if (enrollments[i].rollNumber == roll && enrollments[i].courseCode == code) {
                return true;
            }
        }
        return false;
    }

    // Get completed courses for a student
    vector<string> getCompletedCourses(string roll) {
        vector<string> completed;
        for (int i = 0; i < enrollments.size(); i++) {
            if (enrollments[i].rollNumber == roll) {
                completed.push_back(enrollments[i].courseCode);
            }
        }
        return completed;
    }

    // Display all enrollments
    void displayAll() {
        if (enrollments.empty()) {
            cout << "\n✗ No enrollments found!\n";
            return;
        }

        cout << "\n" << string(50, '=') << "\n";
        cout << left << setw(15) << "Roll Number" 
             << setw(15) << "Course Code" 
             << setw(15) << "Semester" << "\n";
        cout << string(50, '=') << "\n";

        for (int i = 0; i < enrollments.size(); i++) {
            enrollments[i].display();
        }
        cout << string(50, '=') << "\n";
    }

    // Display enrollments for specific student
    void displayByStudent(string roll) {
        bool found = false;
        cout << "\n" << string(50, '=') << "\n";
        cout << "Enrollments for: " << roll << "\n";
        cout << string(50, '=') << "\n";
        cout << left << setw(15) << "Course Code" << setw(15) << "Semester" << "\n";
        cout << string(50, '=') << "\n";

        for (int i = 0; i < enrollments.size(); i++) {
            if (enrollments[i].rollNumber == roll) {
                cout << left << setw(15) << enrollments[i].courseCode
                     << setw(15) << enrollments[i].semester << "\n";
                found = true;
            }
        }

        if (!found) {
            cout << "No enrollments found.\n";
        }
        cout << string(50, '=') << "\n";
    }

    // Get enrollment count
    int getCount() {
        return enrollments.size();
    }

    // Save to file
    void saveToFile(string filename) {
        ofstream file(filename);
        for (int i = 0; i < enrollments.size(); i++) {
            file << enrollments[i].rollNumber << "," 
                 << enrollments[i].courseCode << "," 
                 << enrollments[i].semester << "\n";
        }
        file.close();
        cout << "✓ Enrollments saved to file.\n";
    }

    // Load from file
    void loadFromFile(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "No previous enrollment data found.\n";
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string roll, code, sem;
            
            getline(ss, roll, ',');
            getline(ss, code, ',');
            getline(ss, sem, ',');

            enrollments.push_back(Enrollment(roll, code, sem));
        }
        file.close();
        cout << "✓ Enrollments loaded from file.\n";
    }
};