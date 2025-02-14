#include "../include/shell.h"

// Функция для разбиения введенной строки на команду и аргументы
std::vector<std::string_view> splitCommand(const std::string& input) {
    std::vector<std::string_view> parts;
    size_t pos = 0, found;
    while ((found = input.find_first_of(' ', pos)) != std::string::npos) {
        if (found > pos) {
            parts.push_back(std::string_view(input.data() + pos, found - pos));
        }
        pos = found + 1;
    }
    if (pos < input.length()) parts.push_back(std::string_view(input.data() + pos));
    return parts;
}
// Функция для запуска процесса с заданной командой и аргументами
bool launchProcess(const std::string& command, const std::vector<std::string_view>& args) {
    std::string fullCommand = "\"" + command + "\"";
    for (const auto& arg : args) {
        fullCommand += " \"" + std::string(arg) + "\"";
    }

    HANDLE hToken;
    // Открываем текущий процесс для получения его токена доступа
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_DUPLICATE | TOKEN_ASSIGN_PRIMARY | TOKEN_QUERY, &hToken)) {
        std::cerr << "Failed to open process token. Error code: " << GetLastError() << std::endl;
        return false;
    }

    HANDLE hNewToken;
    // Дублируем токен для нового процесса
    if (!DuplicateTokenEx(hToken, MAXIMUM_ALLOWED, nullptr, SecurityImpersonation, TokenPrimary, &hNewToken)) {
        std::cerr << "Failed to duplicate token. Error code: " << GetLastError() << std::endl;
        CloseHandle(hToken);
        return false;
    }
    CloseHandle(hToken);

    STARTUPINFO si = {sizeof(STARTUPINFO)};
    PROCESS_INFORMATION pi = {};
    auto startTime = std::chrono::high_resolution_clock::now();

    // Создаем новый процесс с использованием дублированного токена
    if (!CreateProcessAsUserA(hNewToken, nullptr, fullCommand.data(), nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)) {
        std::cerr << "Failed to start process. Error code: " << GetLastError() << std::endl;
        CloseHandle(hNewToken);
        return false;
    }

    // Завершения процесса
    WaitForSingleObject(pi.hProcess, INFINITE);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto executionTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout << "Execution time: " << executionTime << " ms" << std::endl;

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(hNewToken);

    return true;
}

// Основная функция оболочки
void ExecuteShell() {
    std::string input;
    std::cout << "Welcome to the new shell! Type 'exit' to exit the shell\n";
    while (true) {
        std::cout << "shell> ";
        getline(std::cin, input);

        auto parts = splitCommand(input);
        if (parts.empty()) continue;

        std::string command = std::string(parts[0]);
        std::vector<std::string_view> args(parts.begin() + 1, parts.end());

        if (command == "exit") {
            std::cout << "Exiting shell...\n";
            break;
        }
        if (command == "info") {
            std::cout << "dedup <inputFile> <outputFile>\nio-lat-write <outputFile> <number of iterations>\n" << std::endl;
            continue;
        } else {
            if (!launchProcess(command, args)) {
                std::cerr << "Error executing command: " << command << std::endl;
            }
        }
    }
}
