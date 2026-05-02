#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;

// Log activity with timestamp
void FileHandler::logActivity(string activity) {
    ofstream file("data/logs.txt", ios::app);
    
    time_t now = time(0);
    char* dt = ctime(&now);
    string timestamp(dt);
    timestamp.pop_back();  // Remove newline
    
    file << "[" << timestamp << "] " << activity << "\n";
    file.close();
}

// Display all logs
void FileHandler::displayLogs() {
    ifstream file("data/logs.txt");
    if (!file.is_open()) {
        cout << "\n✗ No logs found!\n";
        return;
    }

    cout << "\n" << string(80, '=') << "\n";
    cout << "ACTIVITY LOGS\n";
    cout << string(80, '=') << "\n";

    string line;
    while (getline(file, line)) {
        cout << line << "\n";
    }
    cout << string(80, '=') << "\n";
    file.close();
}

// Clear all logs
void FileHandler::clearLogs() {
    ofstream file("data/logs.txt", ios::trunc);
    file.close();
    cout << "\n✓ Logs cleared successfully!\n";
}