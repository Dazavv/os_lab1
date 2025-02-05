#ifndef OS_LAB1_DEDUP_H
#define OS_LAB1_DEDUP_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <set>

using namespace std;

vector<int> readDataFromFile(const string& filename);
void writeDataToFile(const string& filename, const vector<int>& data);
void dedup(const string& inputFile, const string& outputFile);

#endif //OS_LAB1_DEDUP_H
