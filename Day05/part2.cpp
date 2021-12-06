#include <iostream>
#include <fstream>
#include <map>

int signum(int x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

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
            int x_step = signum(x2 - x1);
            int y_step = signum(y2 - y1);
            do {
                auto it = vents.find({x1, y1});
                if (it != vents.end())
                    vents[it->first] = it->second + 1;
                else
                    vents[{x1, y1}] = 1;
                x1 += x_step;
                y1 += y_step;
            } while(x1 - x_step != x2 || y1 - y_step != y2);
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