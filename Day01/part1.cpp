#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::vector <int> entries;
        std::string line;
        while (std::getline(file, line))
            entries.push_back(std::stoi(line));
        file.close();
        int count = 0;
        for (int i = 3; i < entries.size(); i++)
            if (entries.at(i) + entries.at(i - 1) + entries.at(i - 2) > entries.at(i - 1) + entries.at(i - 2) + entries.at(i - 3))
                count++;
        std::cout << count << std::endl;
    }
    return 0;
}