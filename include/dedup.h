#ifndef OS_LAB1_DEDUP_H
#define OS_LAB1_DEDUP_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <windows.h>
#include <filesystem>



std::vector<int> readDataFromFile(const std::string& filename);
void writeDataToFile(const std::string& filename, const std::vector<int>& data);
void dedup(const std::string& inputFile, const std::string& outputFile);

#endif //OS_LAB1_DEDUP_H
