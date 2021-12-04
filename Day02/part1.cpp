#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::vector <int> entries;
        std::string line;
        int x = 0, y = 0;
        while (std::getline(file, line)) {
            int pos = line.find(" ");
            if (line.substr(0, pos) == "forward")
                x += std::stoi(line.substr(pos + 1));
            else if (line.substr(0, pos) == "down")
                y += std::stoi(line.substr(pos + 1));
            else
                y -= std::stoi(line.substr(pos + 1));
        }
        std::cout << x * y << std::endl;
    }
    file.close();
    return 0;
}