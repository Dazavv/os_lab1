#include <gtest/gtest.h>
#include <fstream>
#include "../../include/io_lat_write.h"

// Вспомогательная функция для проверки существования файла и его размера
bool isFileValid(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) return false;
    return file.tellg() > 0;
}

// Тест команды io-lat-write
TEST(IOLatWriteTest, CheckFile) {
    std::string outputFile = "test_io.txt";
    int iterations = 1000;

    // Запускаем io-lat-write
    IOLatWrite(iterations, outputFile);

    // Проверяем, что файл был создан и содержит данные
    EXPECT_TRUE(isFileValid(outputFile));
}
