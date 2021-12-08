#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

int count_common_segments(const std::string &s1, const std::string &s2) {
    int count = 0;
    for (auto x : s1)
        for (auto y : s2)
            if (x == y)
                count++;
    return count;
}

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string line;
        int sum = 0;
        while (std::getline(file, line)) {
            std::vector<std::string> input;
            std::vector<std::string> output;
            std::map<char, std::string> answer;
            std::stringstream ss1(line.substr(0, 58));
            std::stringstream ss2(line.substr(61));
            std::string field;
            while (std::getline(ss1, field, ' '))
                input.push_back(field);
            while (std::getline(ss2, field, ' '))
                output.push_back(field);
            // unique patterns first
            for (auto x : input) {
                if (x.length() == 2)
                    answer['1'] = x;
                else if (x.length() == 4)
                    answer['4'] = x;
                else if (x.length() == 3)
                    answer['7'] = x;
                else if (x.length() == 7)
                    answer['8'] = x;
            }   
            //find 0 6 9 using 1 and 4
            for (auto x : input) {
                if (x.length() == 6) {
                    if (count_common_segments(answer['1'], x) == 1)
                        answer['6'] = x;
                    else if (count_common_segments(answer['4'], x) == 4)
                        answer['9'] = x;
                    else
                        answer['0'] = x;
                }
            }
            //find 2 3 and 5 using 6 and 9
            for (auto x : input) {
                if (x.length() == 5) {
                    if (count_common_segments(answer['9'], x) == 4)
                        answer['2'] = x;
                    else if (count_common_segments(answer['6'], x) == 4)
                        answer['3'] = x;
                    else
                        answer['5'] = x;
                }
            }
            std::string n = "";
            for (auto x : output) {
                for (auto y : answer) {
                    if (x.length() == y.second.length() && count_common_segments(x, y.second) == x.length()) {
                        n += y.first;
                        break;
                    }
                }
            }
            sum += std::stoi(n);
        }
        file.close();
        std::cout << sum << std::endl;
    }
    return 0;
}