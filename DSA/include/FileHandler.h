#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
using namespace std;

class FileHandler {
public:
    static void logActivity(string activity);
    static void displayLogs();
    static void clearLogs();
};

#endif