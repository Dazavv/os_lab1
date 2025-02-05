#include "../../include/shell.h"
#include <iostream>
#include <sstream>
#include <gtest/gtest.h>

using namespace std;

// Функция для имитации работы shell
string simulateShellInput(const string& input) {
    istringstream inputStream(input);
    ostringstream outputStream;
    streambuf* cinBackup = cin.rdbuf();
    streambuf* coutBackup = cout.rdbuf();

    cin.rdbuf(inputStream.rdbuf());
    cout.rdbuf(outputStream.rdbuf());

    ExecuteShell();

    cin.rdbuf(cinBackup);
    cout.rdbuf(coutBackup);

    return outputStream.str();
}

// Тест команды exit
TEST(ShellTest, ExitCommand) {
    string output = simulateShellInput("exit\n");
    EXPECT_NE(output.find("Exiting shell..."), string::npos);
}

// Тест команды info
TEST(ShellTest, InfoCommand) {
    string output = simulateShellInput("info\nexit\n");
    EXPECT_NE(output.find("dedup <inputFile> <outputFile>"), string::npos);
    EXPECT_NE(output.find("io-lat-write <outputFile> <number of iterations>"), string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
