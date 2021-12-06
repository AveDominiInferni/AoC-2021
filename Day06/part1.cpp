#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::vector<int> fish;
        std::string line;
        std::getline(file, line);
        std::stringstream ss(line);
        std::string field;
        while (std::getline(ss, field, ','))
            fish.push_back(std::stoi(field));
        for (int k = 0; k < 80; k++) {
            int s = fish.size();
            for (int i = 0; i < s; i++) {
                if (fish.at(i) == 0) {
                    fish.at(i) = 6;
                    fish.push_back(8);
                }
                else
                    fish.at(i)--;
            }
        }
        std::cout << fish.size() << std::endl;
    }
    file.close();
    return 0;
}