#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::vector<int> entries;
        std::string line;
        while (std::getline(file, line)) {
            entries.push_back(std::stoi(line));
        }
        file.close();
        for (int i = 0; i < entries.size(); i++) {
            for (int j = i + 1; j < entries.size(); j++) {
                for (int k = j + 1; k < entries.size(); k++) {
                    if (entries.at(i) + entries.at(j) + entries.at(k) == 2020) {
                        std::cout << entries.at(i) * entries.at(j) * entries.at(k);
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}