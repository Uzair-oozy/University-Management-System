#include "Student.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

// Student Constructor
Student::Student(string roll, string n, string dept, int sem, float g) {
    rollNumber = roll;
    name = n;
    department = dept;
    semester = sem;
    gpa = g;
    next = nullptr;
}

void Student::display() {
    cout << left << setw(15) << rollNumber
         << setw(25) << name
         << setw(20) << department
         << setw(10) << semester
         << setw(10) << fixed << setprecision(2) << gpa << endl;
}

// ==================== STUDENT MANAGER CLASS ====================
class StudentManager {
private:
    Student* head;

public:
    StudentManager() {
        head = nullptr;
    }

    // Add new student
    void addStudent(string roll, string name, string dept, int sem, float gpa = 0.0) {
        Student* newStudent = new Student(roll, name, dept, sem, gpa);
        
        if (head == nullptr) {
            head = newStudent;
        } else {
            Student* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newStudent;
        }
        cout << "\n✓ Student added successfully!\n";
    }

    // Search student by roll number
    Student* searchStudent(string roll) {
        Student* temp = head;
        while (temp != nullptr) {
            if (temp->rollNumber == roll) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    // Delete student
    void deleteStudent(string roll) {
        if (head == nullptr) {
            cout << "\n✗ No students found!\n";
            return;
        }

        // If head is to be deleted
        if (head->rollNumber == roll) {
            Student* temp = head;
            head = head->next;
            delete temp;
            cout << "\n✓ Student deleted successfully!\n";
            return;
        }

        // Search for student to delete
        Student* temp = head;
        while (temp->next != nullptr && temp->next->rollNumber != roll) {
            temp = temp->next;
        }

        if (temp->next == nullptr) {
            cout << "\n✗ Student not found!\n";
        } else {
            Student* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
            cout << "\n✓ Student deleted successfully!\n";
        }
    }

    // Display all students
    void displayAll() {
        if (head == nullptr) {
            cout << "\n✗ No students found!\n";
            return;
        }

        cout << "\n" << string(90, '=') << "\n";
        cout << left << setw(15) << "Roll Number" 
             << setw(25) << "Name" 
             << setw(20) << "Department" 
             << setw(10) << "Semester"
             << setw(10) << "GPA" << "\n";
        cout << string(90, '=') << "\n";

        Student* temp = head;
        while (temp != nullptr) {
            temp->display();
            temp = temp->next;
        }
        cout << string(90, '=') << "\n";
    }

    // Update student GPA
    void updateGPA(string roll, float newGPA) {
        Student* student = searchStudent(roll);
        if (student != nullptr) {
            student->gpa = newGPA;
            cout << "\n✓ GPA updated successfully!\n";
        } else {
            cout << "\n✗ Student not found!\n";
        }
    }

    // Get total count
    int getCount() {
        int count = 0;
        Student* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    // Get head pointer
    Student* getHead() {
        return head;
    }

    // Save to file
    void saveToFile(string filename) {
        ofstream file(filename);
        Student* temp = head;
        while (temp != nullptr) {
            file << temp->rollNumber << "," 
                 << temp->name << "," 
                 << temp->department << "," 
                 << temp->semester << ","
                 << temp->gpa << "\n";
            temp = temp->next;
        }
        file.close();
        cout << "✓ Students saved to file.\n";
    }

    // Load from file
    void loadFromFile(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "No previous student data found.\n";
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string roll, name, dept, semStr, gpaStr;
            
            getline(ss, roll, ',');
            getline(ss, name, ',');
            getline(ss, dept, ',');
            getline(ss, semStr, ',');
            getline(ss, gpaStr, ',');

            int sem = stoi(semStr);
            float gpa = stof(gpaStr);

            Student* newStudent = new Student(roll, name, dept, sem, gpa);
            if (head == nullptr) {
                head = newStudent;
            } else {
                Student* temp = head;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newStudent;
            }
        }
        file.close();
        cout << "✓ Students loaded from file.\n";
    }

    // Destructor
    ~StudentManager() {
        Student* temp = head;
        while (temp != nullptr) {
            Student* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
    }
};