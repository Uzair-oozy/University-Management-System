#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Add prerequisite edge
void Graph::addEdge(string course, string prerequisite) {
    adjList[course].push_back(prerequisite);
    cout << "\n✓ Prerequisite added: " << prerequisite << " -> " << course << "\n";
}

// Get prerequisites for a course
vector<string> Graph::getPrerequisites(string course) {
    if (adjList.find(course) != adjList.end()) {
        return adjList[course];
    }
    return vector<string>();
}

// Check if student has completed prerequisites
bool Graph::checkPrerequisites(string course, vector<string> completedCourses) {
    vector<string> prerequisites = getPrerequisites(course);
    
    if (prerequisites.empty()) {
        return true;  // No prerequisites required
    }

    for (int i = 0; i < prerequisites.size(); i++) {
        bool found = false;
        for (int j = 0; j < completedCourses.size(); j++) {
            if (completedCourses[j] == prerequisites[i]) {
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "\n✗ Missing prerequisite: " << prerequisites[i] << "\n";
            return false;
        }
    }
    return true;
}

// Display prerequisite graph
void Graph::displayGraph() {
    if (adjList.empty()) {
        cout << "\n✗ No prerequisites defined!\n";
        return;
    }

    cout << "\n" << string(60, '=') << "\n";
    cout << "COURSE PREREQUISITE GRAPH\n";
    cout << string(60, '=') << "\n";

    for (auto& pair : adjList) {
        cout << pair.first << " requires: ";
        if (pair.second.empty()) {
            cout << "None";
        } else {
            for (int i = 0; i < pair.second.size(); i++) {
                cout << pair.second[i];
                if (i < pair.second.size() - 1) cout << ", ";
            }
        }
        cout << "\n";
    }
    cout << string(60, '=') << "\n";
}

// Save to file
void Graph::saveToFile(string filename) {
    ofstream file(filename);
    for (auto& pair : adjList) {
        for (int i = 0; i < pair.second.size(); i++) {
            file << pair.first << "," << pair.second[i] << "\n";
        }
    }
    file.close();
    cout << "✓ Prerequisites saved to file.\n";
}

// Load from file
void Graph::loadFromFile(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "No previous prerequisite data found.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string course, prereq;
        
        getline(ss, course, ',');
        getline(ss, prereq, ',');

        adjList[course].push_back(prereq);
    }
    file.close();
    cout << "✓ Prerequisites loaded from file.\n";
}