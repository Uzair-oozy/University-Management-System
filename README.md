# University-Management-System
A UMS that exercises almost all of the key DSAs

## University Course Enrollment & Result Management System

A C++ console application that simulates a university management system with student, course, enrollment, and GPA management features. It uses data structures like heaps, stacks, queues, and graph-based prerequisites to provide a complete academic workflow.

### Key Features

- **Student Management**
  - Add, search, delete, display, and update students
  - Track roll number, name, department, semester, and GPA

- **Course Management**
  - Add and display courses
  - Manage course prerequisites using a directed graph
  - Display prerequisite relationships

- **Enrollment Management**
  - Queue-based enrollment request handling
  - Process enrollment requests with prerequisite validation
  - Display pending requests and student-specific enrollments

- **Result & GPA Management**
  - Update student GPA
  - Generate merit list using a max heap
  - Display top students by GPA

- **Analytics & Reporting**
  - Display system statistics
  - Maintain recent activity log with a stack
  - Log file storage and report display

### Technical Details

- **Language**: C++
- **Data Structures**
  - `MaxHeap` for merit list ranking
  - `Stack` for recent activity history
  - `Queue` for pending enrollment requests
  - `Graph` for course prerequisites
- **Modular Design**
  - Uses manager classes for students, courses, enrollments, and file handling
  - Separate class headers and implementations for clarity
- **Persistence**
  - Loads and saves data from text files under `data/`
  - Supports persistent storage for students, courses, enrollments, and prerequisites

### How to Use

1. Compile main.cpp with a C++ compiler
2. Run the executable
3. Choose from the main menu:
   - Student Management
   - Course Management
   - Enrollment Management
   - Result & GPA Management
   - Analytics & Reports
4. Follow prompts to perform actions
5. Select `Exit & Save` to persist all data

### Notes

- Designed as an academic project for learning data structures, file I/O, and OOP
- Includes console UI with formatted menus and input validation
- Uses `system("cls")` on Windows to clear the screen for better menu flow
