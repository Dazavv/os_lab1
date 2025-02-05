#include "../include/shell.h"

// Функция для разбиения введенной строки на команду и аргументы
vector<string> splitCommand(const string& input) {
    vector<string> parts;
    size_t pos = 0, found;
    while ((found = input.find_first_of(' ', pos)) != string::npos) {
        if (found > pos) {
            parts.push_back(input.substr(pos, found - pos));
        }
        pos = found + 1;
    }
    if (pos < input.length()) parts.push_back(input.substr(pos));
    return parts;
}
// Функция для запуска процесса с заданной командой и аргументами
bool launchProcess(const string& command, vector<string>& args) {
    string fullCommand = "\"" + command + "\"";
    for (const auto& arg : args) {
        fullCommand += " \"" + arg + "\"";
    }

    HANDLE hToken;
    // Открываем текущий процесс для получения его токена доступа
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_DUPLICATE | TOKEN_ASSIGN_PRIMARY | TOKEN_QUERY, &hToken)) {
        cerr << "Failed to open process token. Error code: " << GetLastError() << endl;
        return false;
    }

    HANDLE hNewToken;
    // Дублируем токен для нового процесса
    if (!DuplicateTokenEx(hToken, MAXIMUM_ALLOWED, nullptr, SecurityImpersonation, TokenPrimary, &hNewToken)) {
        cerr << "Failed to duplicate token. Error code: " << GetLastError() << endl;
        CloseHandle(hToken);
        return false;
    }
    CloseHandle(hToken);

    STARTUPINFO si = {sizeof(STARTUPINFO)}; // Для информации о запуске процесса
    PROCESS_INFORMATION pi = {}; // Для информации о процессе
    auto startTime = chrono::high_resolution_clock::now();

    // Создаем новый процесс с использованием дублированного токена
    if (!CreateProcessAsUserA(hNewToken, nullptr, fullCommand.data(), nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)) {
        cerr << "Failed to start process. Error code: " << GetLastError() << endl;
        CloseHandle(hNewToken);
        return false;
    }

    // Завершения процесса
    WaitForSingleObject(pi.hProcess, INFINITE);
    auto endTime = chrono::high_resolution_clock::now();
    auto executionTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
    cout << "Execution time: " << executionTime << " ms" << endl;

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(hNewToken);

    return true;
}

// Основная функция оболочки
void ExecuteShell() {
    string input;
    cout << "Welcome to the new shell! Type 'exit' to exit the shell\n";
    while (true) {
        cout << "shell> ";
        getline(cin, input);

        auto parts = splitCommand(input);
        if (parts.empty()) continue;

        string command = parts[0];
        vector<string> args(parts.begin() + 1, parts.end());

        if (command == "exit") {
            cout << "Exiting shell...\n";
            break;
        }
        if (command == "info") {
            cout << "dedup <inputFile> <outputFile>\nio-lat-write <outputFile> <number of iterations>\n" << endl;
            continue;
        } else {
            if (!launchProcess(command, args)) {
                cerr << "Error executing command: " << command << endl;
            }
        }
    }
}
