#ifndef OS_LAB1_SHELL_H
#define OS_LAB1_SHELL_H

#include <string>
#include <vector>
#include <windows.h>
#include <chrono>
#include <iostream>

using namespace std;

void ExecuteShell();
vector<string> splitCommand(const string& input);
bool launchProcess(const string& command, vector<string>& args);

#endif //OS_LAB1_SHELL_H
