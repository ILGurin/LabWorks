#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main(){
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    unordered_map<string, string> visitors;

    visitors["Иванов Иван Иванович"] = "2022-04-10";
    visitors["Петров Петр Петрович"] = "2022-04-09";
    visitors["Сидоров Сидор Сидорович"] = "2022-04-11";
    visitors["Иванов Иван Иванович"] = "2022-04-11";

    for (auto& visitor : visitors) {
        cout << visitor.first << ": " << visitor.second << endl;
    }
    return 0;
}