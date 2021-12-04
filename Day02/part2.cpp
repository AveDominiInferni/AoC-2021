#include <iostream>
#include <fstream>

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string line;
        int x = 0, y = 0, aim = 0;
        while (std::getline(file, line)) {
            int pos = line.find(" ");
            if (line.substr(0, pos) == "forward") {
                x += std::stoi(line.substr(pos + 1));
                y += aim * std::stoi(line.substr(pos + 1));
            }  
            else if (line.substr(0, pos) == "down")
                aim += std::stoi(line.substr(pos + 1));
            else
                aim -= std::stoi(line.substr(pos + 1));
        }
        file.close();
        std::cout << x * y << std::endl;
    }
    return 0;
}