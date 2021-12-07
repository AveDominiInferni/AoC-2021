#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::vector<int> pos;
        std::string line;
        std::getline(file, line);
        std::stringstream ss(line);
        std::string field;
        while (std::getline(ss, field, ','))
            pos.push_back(std::stoi(field));
        int max_el = *std::max_element(pos.begin(), pos.end());
        uint64_t min_sum = UINT64_MAX;
        for (int i = 0; i <= max_el; i++) {
            uint64_t sum = 0;
            for (int j = 0; j < pos.size(); j++)
                sum += abs(pos.at(j) - i) * (abs(pos.at(j) - i) + 1) / 2;
            min_sum = std::min(min_sum, sum);
        }
        std::cout << min_sum << std::endl;
    }
    file.close();
    return 0;
}