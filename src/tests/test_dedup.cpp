#include <gtest/gtest.h>
#include <fstream>
#include "../../include/dedup.h"


// Вспомогательная функция для чтения данных из файла
std::vector<int> readFileData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        ADD_FAILURE() << "error opening file " << filename;
        return {};
    }
    std::vector<int> data;
    int value;
    while (file >> value) {
        data.push_back(value);
    }
    return data;
}

// Тест команды dedup
TEST(DedupTest, RemovesDuplicates) {
    std::string inputFile = "test_input.txt";
    std::string outputFile = "test_output.txt";

    // Заполняем файл с дублирующимися данными
    std::ofstream inFile(inputFile);
    if (!inFile) {
        FAIL() << "File creation error " << inputFile;
    }
    inFile << "1 2 2 3 4 4 5 5 6 6 6 7 8 8 9 9 10 10";
    inFile.close();

    std::ofstream outFile(outputFile);
    if (!outFile) {
        FAIL() << "File creation error " << outputFile;
    }
    outFile.close();

    // Запускаем dedup
    dedup(inputFile, outputFile);

    // Получаем данные из файла после выполнения команды
    std::vector<int> result = readFileData(outputFile);
    std::vector<int> expected = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    // Сравниваем полученный результат с ожидаемым
    EXPECT_EQ(result, expected);
}
