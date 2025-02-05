#include "../include/dedup.h"

// Функция для чтения данных
vector<int> readDataFromFile(const string& filename) {
    vector<int> data;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "error opening file: " << filename << endl;
        return data;
    }
    int value;
    while (file >> value) data.push_back(value);
    file.close();
    return data;
}

// Функция для записи данных в файл
void writeDataToFile(const string& filename, const vector<int>& data) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "error opening file: " << filename << endl;
        return;
    }
    for (const int& value : data) file << value << " ";
    file.close();
}

// Функция для удаления дубликатов из данных в файле
void dedup(const string& inputFile, const string& outputFile) {
    vector<int> arr = readDataFromFile(inputFile);
    if (arr.empty()) {
        cerr << "no data to deduplicate" << endl;
        return;
    }
    // Используем множество для удаления дубликатов
    set<int> unique_elements(arr.begin(), arr.end());
    vector<int> result(unique_elements.begin(), unique_elements.end());
    writeDataToFile(outputFile, result);
    cout << "deduplication complete. new file is: " << outputFile << endl;
}

#ifndef TESTING
int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: dedup <inputFile> <outputFile>" << endl;
        return 1;
    }
    dedup(argv[1], argv[2]);
    return 0;
}
#endif

