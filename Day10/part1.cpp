#include <iostream>
#include <fstream>
#include <map>

std::map<char, char> pairs {{'(',')'}, {'[',']'}, {'{','}'}, {'<','>'}};
std::map<char, int> points {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string line;
        uint64_t score = 0;
        while (std::getline(file, line)) {
            for (int i = 0; i < line.size() - 1; i++) {
                for (auto x : pairs) {
                    if (line.at(i) == x.first && line.at(i + 1) == x.second) {
                        line.erase(i, 2);
                        i = - 1;
                        break;
                    }
                }
            }
            for (int i = 0; i < line.size(); i++) {
                auto it = points.find(line.at(i));
                if (it != points.end()) {
                    score += it->second;
                    break;
                }
            }
        }
        std::cout << score << std::endl;
    }
    file.close();
    return 0;
}