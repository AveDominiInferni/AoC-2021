#include <iostream>
#include <fstream>
#include <map>

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::map<std::pair<int, int>, int> vents;
        std::string line;
        while (std::getline(file, line)) {
            int hyphen = line.find('-');
            int x1, y1, x2, y2;
            int coma1 = line.find(',');
            int coma2 = line.find(',', hyphen);
            x1 = std::stoi(line.substr(0, coma1));
            y1 = std::stoi(line.substr(coma1 + 1, hyphen - coma1 - 1));
            x2 = std::stoi(line.substr(hyphen + 3, coma2 - hyphen - 3));
            y2 = std::stoi(line.substr(coma2 + 1));
            if (x1 > x2 || y1 > y2) {
                std::swap(x1, x2);
                std::swap(y1, y2);
            }
            if (x1 == x2) {
                for (int i = y1; i <= y2; i++) {
                    auto it = vents.find({x1, i});
                    if (it != vents.end())
                        vents[it->first] = it->second + 1;
                    else
                        vents[{x1, i}] = 1;
                }
            }
            else if (y1 == y2) {
                for (int i = x1; i <= x2; i++) {
                    auto it = vents.find({i, y1});
                    if (it != vents.end())
                        vents[it->first] = it->second + 1;
                    else
                        vents[{i, y1}] = 1;
                }
            }
        }
        int count = 0;
        for (auto x : vents)
            if (x.second > 1)
                count++;
        std::cout << count << std::endl;
    }
    file.close();
    return 0;
}