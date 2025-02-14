#include "../include/io_lat_write.h"

void IOLatWrite(int iterations, const std::filesystem::path& filePath) {
    const int block_size = 1024; // размер блока 1К
    std::vector<char> data(block_size, 'A');
    std::ofstream file(filePath, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening file for writing" << std::endl;
        return;
    }

    // Генератор случайных чисел для выбора случайных смещений в файле
    std::random_device rd;
    std::mt19937 gen(rd());
    // Распределение для выбора смещения от 0 до 1023
    std::uniform_int_distribution<> dis(0, 1023);

    auto start_time = std::chrono::high_resolution_clock::now();

    // Цикл записи данных в файл заданное количество раз
    for (int i = 0; i < iterations; ++i) {
        int offset = dis(gen); // Генерируем случайное смещение
        file.seekp(offset); // Устанавливаем указатель записи в файл на сгенерированное смещение
        file.write(data.data(), block_size);
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
    std::cout << "average write time per iteration: " << elapsed_time / iterations << " [ns]" << std::endl;
}
#ifndef TESTING
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: io-lat-write <outputFile> <number of iterations>" << std::endl;
        return 1;
    }
    int iterations = std::stoi(argv[2]);
    IOLatWrite(iterations, argv[1]);
    return 0;
}
#endif