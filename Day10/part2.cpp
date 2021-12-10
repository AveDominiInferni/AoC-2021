#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

std::map<char, char> pairs {{'(',')'}, {'[',']'}, {'{','}'}, {'<','>'}};
std::map<char, int> points {{')', 1}, {']', 2}, {'}', 3}, {'>', 4}};

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::vector<std::string> chunks;
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
            bool corrupted = false;
            for (int i = 0; i < line.size(); i++) {
                auto it = points.find(line.at(i));
                if (it != points.end()) {
                    corrupted = true;
                    break;
                }
            }
            if (!corrupted)
                chunks.push_back(line);
        }
        std::set<uint64_t> scores;
        for (auto x : chunks) {
            uint64_t temp = 0;
            for (int i = x.size() - 1 ; i >= 0; i--) {
                temp *= 5;
                temp += points[pairs[x.at(i)]];
            }
            scores.insert(temp);
        }
        auto it = scores.begin();
        std::advance(it, scores.size() / 2);
        std::cout << *it << std::endl;
    }
    file.close();
    return 0;
}