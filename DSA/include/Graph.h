#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <map>
using namespace std;

class Graph {
private:
    map<string, vector<string>> adjList;

public:
    void addEdge(string course, string prerequisite);
    vector<string> getPrerequisites(string course);
    bool checkPrerequisites(string course, vector<string> completedCourses);
    void displayGraph();
    void saveToFile(string filename);
    void loadFromFile(string filename);
};

#endif