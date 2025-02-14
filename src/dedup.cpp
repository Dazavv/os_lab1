#include <sstream>
#include "../include/dedup.h"


// Функция для чтения данных
std::vector<int> readDataFromFile(const std::string& filename) {
    std::vector<int> data;
    HANDLE file = CreateFileA(filename.c_str(),
                             GENERIC_READ,
                             FILE_SHARE_READ,
                             NULL,
                             OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL,
                             NULL);
    if (file == INVALID_HANDLE_VALUE) {
        std::cerr << "error opening file: " << filename << std::endl;
        return data;
    }

    char buffer[1024];
    DWORD bytesRead;
    std::string content;
    while (ReadFile(file,
                    buffer,
                    sizeof (buffer),
                    &bytesRead,
                    NULL)
           && bytesRead > 0) {
        content.append(buffer, bytesRead);
    }
    CloseHandle(file);

    std::size_t pos = 0;
    while (pos < content.size()) {
        try {
            std::size_t newPos;
            int value = stoi(content.substr(pos), &newPos);
            data.push_back(value);
            pos += newPos;
        } catch (const std::exception&) {
            break;
        }
    }

    return data;
}

// Функция для записи данных в файл
void writeDataToFile(const std::string& filename, const std::vector<int>& data) {
    HANDLE file = CreateFileA(filename.c_str(),
                             GENERIC_WRITE,
                             0,
                             NULL,
                             CREATE_ALWAYS,
                             FILE_ATTRIBUTE_NORMAL,
                             NULL);
    if (file == INVALID_HANDLE_VALUE) {
        std::cerr << "error opening file: " << filename << std::endl;
        return;
    }

    std::string buffer;
    for (const int& value : data) buffer += std::to_string(value) + " ";

    DWORD bytesWritten;
    WriteFile(file,
              buffer.c_str(),
              buffer.size(),
              &bytesWritten,
              NULL);
    CloseHandle(file);
}

// Функция для удаления дубликатов из данных в файле
void dedup(const std::string& inputFile, const std::string& outputFile) {
    std::vector<int> arr = readDataFromFile(inputFile);
    if (arr.empty()) {
        std::cerr << "no data to deduplicate" << std::endl;
        return;
    }
    // Используем множество для удаления дубликатов
    std::unordered_set<int> unique_elements(arr.begin(), arr.end());
    std::vector<int> result(unique_elements.begin(), unique_elements.end());
    writeDataToFile(outputFile, result);
    std::cout << "deduplication complete. new file is: " << outputFile << std::endl;
}

#ifndef TESTING
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: dedup <inputFile> <outputFile>" << std::endl;
        return 1;
    }
    dedup(argv[1], argv[2]);
//    dedup("D:\\dasha\\UNI\\OS\\in.txt", "D:\\dasha\\UNI\\OS\\out.txt");
    return 0;
}
#endif

