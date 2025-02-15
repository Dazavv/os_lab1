#include "../../include/shell.h"
#include <iostream>
#include <sstream>
#include <gtest/gtest.h>

// Функция для имитации работы shell
std::string simulateShellInput(const std::string& input) {
    std::istringstream inputStream(input);
    std::ostringstream outputStream;
    std::streambuf* cinBackup = std::cin.rdbuf();
    std::streambuf* coutBackup = std::cout.rdbuf();

    std::cin.rdbuf(inputStream.rdbuf());
    std::cout.rdbuf(outputStream.rdbuf());

    ExecuteShell();

    std::cin.rdbuf(cinBackup);
    std::cout.rdbuf(coutBackup);

    return outputStream.str();
}

// Тест команды exit
TEST(ShellTest, ExitCommand) {
    std::string output = simulateShellInput("exit\n");
    EXPECT_NE(output.find("Exiting shell..."), std::string::npos);
}

// Тест команды info
TEST(ShellTest, InfoCommand) {
    std::string output = simulateShellInput("info\nexit\n");
    EXPECT_NE(output.find("dedup <inputFile> <outputFile>"), std::string::npos);
    EXPECT_NE(output.find("io-lat-write <outputFile> <number of iterations>"), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
