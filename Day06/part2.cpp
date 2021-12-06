#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        uint64_t fish[9] = {};
        std::string line;
        std::getline(file, line);
        std::stringstream ss(line);
        std::string field;
        while (std::getline(ss, field, ','))
            fish[std::stoi(field)]++;    
        file.close();
        for (int k = 0; k < 256; k++) {
            uint64_t temp = fish[0];
            for (int i = 0; i < 8; i++)
                fish[i] = fish[i + 1];
            fish[6] += temp;
            fish[8] = temp;
        }
        uint64_t sum = 0;
        for (int i = 0; i < 9; i++)
            sum += fish[i];
        std::cout << sum << std::endl;
    }
    return 0;
}