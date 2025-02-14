#include <gtest/gtest.h>
#include <fstream>
#include "../../include/dedup.h"

using namespace std;

// Вспомогательная функция для чтения данных из файла
vector<int> readFileData(const string& filename) {
    ifstream file(filename);
    vector<int> data;
    int value;
    while (file >> value) {
        data.push_back(value);
    }
    return data;
}

// Тест команды dedup
TEST(DedupTest, RemovesDuplicates) {
    string inputFile = "test_input.txt";
    string outputFile = "test_output.txt";

    // Заполняем файл с дублирующимися данными
    ofstream inFile(inputFile);
    inFile << "1 2 2 3 4 4 5 5 6 6 6 7 8 8 9 9 10 10";
    inFile.close();

    // Запускаем dedup
    dedup(inputFile, outputFile);

    // Получаем данные из файла после выполнения команды
    vector<int> result = readFileData(outputFile);
    vector<int> expected = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    // Сравниваем полученный результат с ожидаемым
    EXPECT_EQ(result, expected);
}
