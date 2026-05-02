#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "Student.h"
#include "Course.h"
#include "Enrollment.h"
#include "Graph.h"
#include "Heap.h"
#include "Stack.h"
#include "Queue.h"
#include "FileHandler.h"

// Include implementation files
#include "StudentManager.cpp"
#include "CourseManager.cpp"
#include "EnrollmentManager.cpp"
#include "Graph.cpp"
#include "FileHandler.cpp"

using namespace std;

// ==================== HEAP IMPLEMENTATION ====================
int MaxHeap::parent(int index) { return (index - 1) / 2; }
int MaxHeap::leftChild(int index) { return 2 * index + 1; }
int MaxHeap::rightChild(int index) { return 2 * index + 2; }

void MaxHeap::heapifyUp(int index) {
    while (index > 0 && heap[parent(index)].gpa < heap[index].gpa) {
        swap(heap[parent(index)], heap[index]);
        index = parent(index);
    }
}

void MaxHeap::heapifyDown(int index) {
    int maxIndex = index;
    int left = leftChild(index);
    int right = rightChild(index);

    if (left < heap.size() && heap[left].gpa > heap[maxIndex].gpa) {
        maxIndex = left;
    }
    if (right < heap.size() && heap[right].gpa > heap[maxIndex].gpa) {
        maxIndex = right;
    }
    if (index != maxIndex) {
        swap(heap[index], heap[maxIndex]);
        heapifyDown(maxIndex);
    }
}

void MaxHeap::insert(HeapNode node) {
    heap.push_back(node);
    heapifyUp(heap.size() - 1);
}

HeapNode MaxHeap::extractMax() {
    if (heap.empty()) {
        return HeapNode();
    }

    HeapNode maxNode = heap[0];      // root element
    heap[0] = heap.back();           // move last to root
    heap.pop_back();                 // remove last

    if (!heap.empty()) {
        heapifyDown(0);
    }

    return maxNode;
}

void MaxHeap::displayTop(int n) {
    vector<HeapNode> temp;
    int count = 0;

    cout << "\n" << string(70, '=') << "\n";
    cout << "TOP " << n << " STUDENTS BY GPA\n";
    cout << string(70, '=') << "\n";
    cout << left << setw(10) << "Rank" 
         << setw(20) << "Roll Number" 
         << setw(30) << "Name" 
         << setw(10) << "GPA" << "\n";
    cout << string(70, '=') << "\n";

    while (!heap.empty() && count < n) {
        HeapNode node = extractMax();
        temp.push_back(node);
        count++;
        cout << left << setw(10) << count
             << setw(20) << node.rollNumber
             << setw(30) << node.name
             << setw(10) << fixed << setprecision(2) << node.gpa << "\n";
    }
    cout << string(70, '=') << "\n";

    // Restore heap
    for (int i = 0; i < temp.size(); i++) {
        insert(temp[i]);
    }
}

bool MaxHeap::isEmpty() { return heap.empty(); }
int MaxHeap::size() { return heap.size(); }

// ==================== STACK IMPLEMENTATION ====================
Stack::Stack() {
    top = nullptr;
    count = 0;
}

void Stack::push(string data) {
    StackNode* newNode = new StackNode(data);
    newNode->next = top;
    top = newNode;
    count++;
}

string Stack::pop() {
    if (isEmpty()) {
        return "";
    }
    StackNode* temp = top;
    string data = temp->data;
    top = top->next;
    delete temp;
    count--;
    return data;
}

string Stack::peek() {
    if (isEmpty()) {
        return "";
    }
    return top->data;
}

bool Stack::isEmpty() {
    return top == nullptr;
}

void Stack::display() {
    if (isEmpty()) {
        cout << "\n✗ Stack is empty!\n";
        return;
    }

    cout << "\n" << string(50, '=') << "\n";
    cout << "RECENT ACTIVITIES (Stack)\n";
    cout << string(50, '=') << "\n";

    StackNode* temp = top;
    int count = 1;
    while (temp != nullptr) {
        cout << count++ << ". " << temp->data << "\n";
        temp = temp->next;
    }
    cout << string(50, '=') << "\n";
}

int Stack::size() {
    return count;
}

Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

// ==================== QUEUE IMPLEMENTATION ====================
Queue::Queue() {
    front = nullptr;
    rear = nullptr;
    count = 0;
}

void Queue::enqueue(string roll, string code) {
    QueueNode* newNode = new QueueNode(roll, code);
    if (rear == nullptr) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    count++;
    cout << "\n✓ Enrollment request added to queue!\n";
}

void Queue::dequeue() {
    if (isEmpty()) {
        cout << "\n✗ Queue is empty!\n";
        return;
    }
    QueueNode* temp = front;
    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }
    delete temp;
    count--;
}

bool Queue::isEmpty() {
    return front == nullptr;
}

void Queue::display() {
    if (isEmpty()) {
        cout << "\n✗ No pending enrollment requests!\n";
        return;
    }

    cout << "\n" << string(50, '=') << "\n";
    cout << "PENDING ENROLLMENT REQUESTS (Queue)\n";
    cout << string(50, '=') << "\n";
    cout << left << setw(20) << "Roll Number" << setw(20) << "Course Code" << "\n";
    cout << string(50, '=') << "\n";

    QueueNode* temp = front;
    while (temp != nullptr) {
        cout << left << setw(20) << temp->rollNumber 
             << setw(20) << temp->courseCode << "\n";
        temp = temp->next;
    }
    cout << string(50, '=') << "\n";
}

QueueNode* Queue::getFront() {
    return front;
}

int Queue::size() {
    return count;
}

Queue::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

// ==================== MAIN MENU FUNCTIONS ====================
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void displayHeader() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════════╗\n";
    cout << "║     UNIVERSITY COURSE ENROLLMENT & RESULT MANAGEMENT SYSTEM    ║\n";
    cout << "╚════════════════════════════════════════════════════════════════╝\n";
}

void studentMenu(StudentManager& studentMgr, Stack& activityStack) {
    int choice;
    do {
        clearScreen();
        displayHeader();
        cout << "\n╔════════════════════════════════════╗\n";
        cout << "║      STUDENT MANAGEMENT MENU       ║\n";
        cout << "╠════════════════════════════════════╣\n";
        cout << "║ 1. Add Student                     ║\n";
        cout << "║ 2. Search Student                  ║\n";
        cout << "║ 3. Delete Student                  ║\n";
        cout << "║ 4. Display All Students            ║\n";
        cout << "║ 5. Update Student GPA              ║\n";
        cout << "║ 0. Back to Main Menu               ║\n";
        cout << "╚════════════════════════════════════╝\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string roll, name, dept;
                int sem;
                cout << "\nEnter Roll Number: ";
                cin >> roll;
                cin.ignore();
                cout << "Enter Name: ";
                getline(cin, name);
                cout << "Enter Department: ";
                getline(cin, dept);
                cout << "Enter Semester: ";
                cin >> sem;
                
                studentMgr.addStudent(roll, name, dept, sem);
                activityStack.push("Added student: " + roll);
                FileHandler::logActivity("Added student: " + roll);
                pause();
                break;
            }
            case 2: {
                string roll;
                cout << "\nEnter Roll Number: ";
                cin >> roll;
                
                Student* student = studentMgr.searchStudent(roll);
                if (student != nullptr) {
                    cout << "\n✓ Student Found!\n";
                    cout << string(90, '=') << "\n";
                    cout << left << setw(15) << "Roll Number" 
                         << setw(25) << "Name" 
                         << setw(20) << "Department" 
                         << setw(10) << "Semester"
                         << setw(10) << "GPA" << "\n";
                    cout << string(90, '=') << "\n";
                    student->display();
                    cout << string(90, '=') << "\n";
                } else {
                    cout << "\n✗ Student not found!\n";
                }
                pause();
                break;
            }
            case 3: {
                string roll;
                cout << "\nEnter Roll Number to delete: ";
                cin >> roll;
                
                studentMgr.deleteStudent(roll);
                activityStack.push("Deleted student: " + roll);
                FileHandler::logActivity("Deleted student: " + roll);
                pause();
                break;
            }
            case 4:
                studentMgr.displayAll();
                pause();
                break;
            case 5: {
                string roll;
                float gpa;
                cout << "\nEnter Roll Number: ";
                cin >> roll;
                cout << "Enter New GPA: ";
                cin >> gpa;
                
                studentMgr.updateGPA(roll, gpa);
                activityStack.push("Updated GPA for: " + roll);
                FileHandler::logActivity("Updated GPA for: " + roll);
                pause();
                break;
            }
            case 0:
                break;
            default:
                cout << "\n✗ Invalid choice!\n";
                pause();
        }
    } while (choice != 0);
}

void courseMenu(CourseManager& courseMgr, Graph& prereqGraph, Stack& activityStack) {
    int choice;
    do {
        clearScreen();
        displayHeader();
        cout << "\n╔════════════════════════════════════╗\n";
        cout << "║      COURSE MANAGEMENT MENU        ║\n";
        cout << "╠════════════════════════════════════╣\n";
        cout << "║ 1. Add Course                      ║\n";
        cout << "║ 2. Display All Courses             ║\n";
        cout << "║ 3. Add Prerequisite                ║\n";
        cout << "║ 4. Display Prerequisite Graph      ║\n";
        cout << "║ 0. Back to Main Menu               ║\n";
        cout << "╚════════════════════════════════════╝\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string code, name;
                int credits;
                cout << "\nEnter Course Code: ";
                cin >> code;
                cin.ignore();
                cout << "Enter Course Name: ";
                getline(cin, name);
                cout << "Enter Credit Hours: ";
                cin >> credits;
                
                courseMgr.addCourse(code, name, credits);
                activityStack.push("Added course: " + code);
                FileHandler::logActivity("Added course: " + code);
                pause();
                break;
            }
            case 2:
                courseMgr.displayAll();
                pause();
                break;
            case 3: {
                string course, prereq;
                cout << "\nEnter Course Code: ";
                cin >> course;
                cout << "Enter Prerequisite Course Code: ";
                cin >> prereq;
                
                prereqGraph.addEdge(course, prereq);
                activityStack.push("Added prerequisite: " + prereq + " -> " + course);
                FileHandler::logActivity("Added prerequisite: " + prereq + " -> " + course);
                pause();
                break;
            }
            case 4:
                prereqGraph.displayGraph();
                pause();
                break;
            case 0:
                break;
            default:
                cout << "\n✗ Invalid choice!\n";
                pause();
        }
    } while (choice != 0);
}

void enrollmentMenu(StudentManager& studentMgr, CourseManager& courseMgr, 
                    EnrollmentManager& enrollMgr, Graph& prereqGraph, 
                    Queue& enrollQueue, Stack& activityStack) {
    int choice;
    do {
        clearScreen();
        displayHeader();
        cout << "\n╔════════════════════════════════════╗\n";
        cout << "║    ENROLLMENT MANAGEMENT MENU      ║\n";
        cout << "╠════════════════════════════════════╣\n";
        cout << "║ 1. Add Enrollment Request (Queue)  ║\n";
        cout << "║ 2. Process Enrollment Request      ║\n";
        cout << "║ 3. Display Pending Requests        ║\n";
        cout << "║ 4. Display All Enrollments         ║\n";
        cout << "║ 5. Display Student Enrollments     ║\n";
        cout << "║ 0. Back to Main Menu               ║\n";
        cout << "╚════════════════════════════════════╝\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string roll, code;
                cout << "\nEnter Roll Number: ";
                cin >> roll;
                cout << "Enter Course Code: ";
                cin >> code;
                
                // Validate student and course exist
                if (studentMgr.searchStudent(roll) == nullptr) {
                    cout << "\n✗ Student not found!\n";
                } else if (courseMgr.findCourse(code) == nullptr) {
                    cout << "\n✗ Course not found!\n";
                } else {
                    enrollQueue.enqueue(roll, code);
                    activityStack.push("Enrollment request: " + roll + " for " + code);
                    FileHandler::logActivity("Enrollment request added: " + roll + " -> " + code);
                }
                pause();
                break;
            }
            case 2: {
                if (enrollQueue.isEmpty()) {
                    cout << "\n✗ No pending requests!\n";
                } else {
                    QueueNode* request = enrollQueue.getFront();
                    string roll = request->rollNumber;
                    string code = request->courseCode;
                    
                    // Check if already enrolled
                    if (enrollMgr.isEnrolled(roll, code)) {
                        cout << "\n✗ Student already enrolled in this course!\n";
                        enrollQueue.dequeue();
                    } else {
                        // Check prerequisites
                        vector<string> completed = enrollMgr.getCompletedCourses(roll);
                        if (prereqGraph.checkPrerequisites(code, completed)) {
                            enrollMgr.addEnrollment(roll, code, "Spring 2024");
                            activityStack.push("Enrolled: " + roll + " in " + code);
                            FileHandler::logActivity("Enrollment processed: " + roll + " -> " + code);
                            enrollQueue.dequeue();
                        } else {
                            cout << "\n✗ Prerequisites not met!\n";
                            enrollQueue.dequeue();
                        }
                    }
                }
                pause();
                break;
            }
            case 3:
                enrollQueue.display();
                pause();
                break;
            case 4:
                enrollMgr.displayAll();
                pause();
                break;
            case 5: {
                string roll;
                cout << "\nEnter Roll Number: ";
                cin >> roll;
                enrollMgr.displayByStudent(roll);
                pause();
                break;
            }
            case 0:
                break;
            default:
                cout << "\n✗ Invalid choice!\n";
                pause();
        }
    } while (choice != 0);
}

void resultMenu(StudentManager& studentMgr, MaxHeap& meritHeap, Stack& activityStack) {
    int choice;
    do {
        clearScreen();
        displayHeader();
        cout << "\n╔════════════════════════════════════╗\n";
        cout << "║     RESULT & GPA MANAGEMENT        ║\n";
        cout << "╠════════════════════════════════════╣\n";
        cout << "║ 1. Update Student GPA              ║\n";
        cout << "║ 2. Generate Merit List (Heap)      ║\n";
        cout << "║ 3. Display Top Students            ║\n";
        cout << "║ 0. Back to Main Menu               ║\n";
        cout << "╚════════════════════════════════════╝\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string roll;
                float gpa;
                cout << "\nEnter Roll Number: ";
                cin >> roll;
                cout << "Enter GPA: ";
                cin >> gpa;
                
                Student* student = studentMgr.searchStudent(roll);
                if (student != nullptr) {
                    studentMgr.updateGPA(roll, gpa);
                    activityStack.push("Updated GPA for: " + roll);
                    FileHandler::logActivity("GPA updated: " + roll + " -> " + to_string(gpa));
                } else {
                    cout << "\n✗ Student not found!\n";
                }
                pause();
                break;
            }
            case 2: {
                // Clear existing heap and rebuild
                while (!meritHeap.isEmpty()) {
                    meritHeap.extractMax();
                }
                
                Student* temp = studentMgr.getHead();
                while (temp != nullptr) {
                    if (temp->gpa > 0) {
                        meritHeap.insert(HeapNode(temp->rollNumber, temp->name, temp->gpa));
                    }
                    temp = temp->next;
                }
                cout << "\n✓ Merit list generated successfully!\n";
                FileHandler::logActivity("Merit list generated");
                pause();
                break;
            }
            case 3: {
                if (meritHeap.isEmpty()) {
                    cout << "\n✗ Merit list is empty! Generate it first.\n";
                } else {
                    int n;
                    cout << "\nEnter number of top students to display: ";
                    cin >> n;
                    meritHeap.displayTop(n);
                }
                pause();
                break;
            }
            case 0:
                break;
            default:
                cout << "\n✗ Invalid choice!\n";
                pause();
        }
    } while (choice != 0);
}

void analyticsMenu(StudentManager& studentMgr, CourseManager& courseMgr, 
                   EnrollmentManager& enrollMgr, Stack& activityStack) {
    int choice;
    do {
        clearScreen();
        displayHeader();
        cout << "\n╔════════════════════════════════════╗\n";
        cout << "║      ANALYTICS & REPORTS           ║\n";
        cout << "╠════════════════════════════════════╣\n";
        cout << "║ 1. System Statistics               ║\n";
        cout << "║ 2. Display Activity Log (Stack)    ║\n";
        cout << "║ 3. Display All Logs                ║\n";
        cout << "║ 4. Clear Logs                      ║\n";
        cout << "║ 0. Back to Main Menu               ║\n";
        cout << "╚════════════════════════════════════╝\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\n" << string(50, '=') << "\n";
                cout << "SYSTEM STATISTICS\n";
                cout << string(50, '=') << "\n";
                cout << "Total Students: " << studentMgr.getCount() << "\n";
                cout << "Total Courses: " << courseMgr.getCount() << "\n";
                cout << "Total Enrollments: " << enrollMgr.getCount() << "\n";
                cout << "Recent Activities: " << activityStack.size() << "\n";
                cout << string(50, '=') << "\n";
                pause();
                break;
            case 2:
                activityStack.display();
                pause();
                break;
            case 3:
                FileHandler::displayLogs();
                pause();
                break;
            case 4:
                FileHandler::clearLogs();
                pause();
                break;
            case 0:
                break;
            default:
                cout << "\n✗ Invalid choice!\n";
                pause();
        }
    } while (choice != 0);
}

// ==================== MAIN FUNCTION ====================
int main() {
    // Initialize all managers and data structures
    StudentManager studentMgr;
    CourseManager courseMgr;
    EnrollmentManager enrollMgr;
    Graph prereqGraph;
    MaxHeap meritHeap;
    Queue enrollQueue;
    Stack activityStack;

    // Load data from files
    cout << "Loading data from files...\n";
    studentMgr.loadFromFile("data/students.txt");
    courseMgr.loadFromFile("data/courses.txt");
    enrollMgr.loadFromFile("data/enrollments.txt");
    prereqGraph.loadFromFile("data/prerequisites.txt");
    cout << "\n";

    int choice;
    do {
        clearScreen();
        displayHeader();
        cout << "\n╔════════════════════════════════════╗\n";
        cout << "║          MAIN MENU                 ║\n";
        cout << "╠════════════════════════════════════╣\n";
        cout << "║ 1. Student Management              ║\n";
        cout << "║ 2. Course Management               ║\n";
        cout << "║ 3. Enrollment Management           ║\n";
        cout << "║ 4. Result & GPA Management         ║\n";
        cout << "║ 5. Analytics & Reports             ║\n";
        cout << "║ 0. Exit & Save                     ║\n";
        cout << "╚════════════════════════════════════╝\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                studentMenu(studentMgr, activityStack);
                break;
            case 2:
                courseMenu(courseMgr, prereqGraph, activityStack);
                break;
            case 3:
                enrollmentMenu(studentMgr, courseMgr, enrollMgr, prereqGraph, 
                              enrollQueue, activityStack);
                break;
            case 4:
                resultMenu(studentMgr, meritHeap, activityStack);
                break;
            case 5:
                analyticsMenu(studentMgr, courseMgr, enrollMgr, activityStack);
                break;
            case 0:
                cout << "\nSaving data...\n";
                studentMgr.saveToFile("data/students.txt");
                courseMgr.saveToFile("data/courses.txt");
                enrollMgr.saveToFile("data/enrollments.txt");
                prereqGraph.saveToFile("data/prerequisites.txt");
                cout << "\n✓ All data saved successfully!\n";
                cout << "Thank you for using the system!\n";
                break;
            default:
                cout << "\n✗ Invalid choice!\n";
                pause();
        }
    } while (choice != 0);

    return 0;
}