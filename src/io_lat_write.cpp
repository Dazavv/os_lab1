#include "../include/io_lat_write.h"

void io_lat_write(int iterations, const string& fileName) {
    const int block_size = 1024; // размер блока 1К
    vector<char> data(block_size, 'A');
    ofstream file(fileName, ios::binary);

    if (!file.is_open()) {
        cerr << "Error opening file for writing" << endl;
        return;
    }

    // Генератор случайных чисел для выбора случайных смещений в файле
    random_device rd;
    mt19937 gen(rd());
    // Распределение для выбора смещения от 0 до 1023
    uniform_int_distribution<> dis(0, 1023);

    auto start_time = chrono::high_resolution_clock::now();

    // Цикл записи данных в файл заданное количество раз
    for (int i = 0; i < iterations; ++i) {
        int offset = dis(gen); // Генерируем случайное смещение
        file.seekp(offset); // Устанавливаем указатель записи в файл на сгенерированное смещение
        file.write(data.data(), block_size);
    }
    auto end_time = chrono::high_resolution_clock::now();
    auto elapsed_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
    cout << "average write time per iteration: " << elapsed_time / iterations << " [ns]" << endl;
    file.close();
}
#ifndef TESTING
int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: io-lat-write <outputFile> <number of iterations>" << endl;
        return 1;
    }
    int iterations = stoi(argv[2]);
    io_lat_write(iterations, argv[1]);
    return 0;
}
#endif