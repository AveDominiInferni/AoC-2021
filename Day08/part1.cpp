#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        int count = 0;
        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> output;
            std::stringstream ss(line.substr(61));
            std::string field;
            while (std::getline(ss, field, ' '))
                if (field.length() == 3 || field.length() == 4 || field.length() == 2 || field.length() == 7)
                    count++;
        }
        file.close();
        std::cout << count << std::endl;
    }
    return 0;
}