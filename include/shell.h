#ifndef OS_LAB1_SHELL_H
#define OS_LAB1_SHELL_H

#include <string>
#include <vector>
#include <windows.h>
#include <chrono>
#include <iostream>

void ExecuteShell();
std::vector<std::string_view> splitCommand(const std::string& input);
bool launchProcess(const std::string& command, const std::vector<std::string_view>& args);

#endif //OS_LAB1_SHELL_H
