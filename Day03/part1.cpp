#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

int bin_to_dec(const std::string &s) {
    int result = 0;
    for (int i = s.length() - 1; i >= 0; i--)
        if (s.at(s.length() - i - 1) == '1')
            result += pow(2, i);
    return result;
}

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::vector <std::string> entries;
        std::string line;
        while (std::getline(file, line))
            entries.push_back(line);
        file.close();
        std::string bin_num1, bin_num2;
        for (int j = 0 ; j < entries.at(0).length(); j++) {
            int count = 0;
            for (int i = 0; i < entries.size(); i++)
                if (entries.at(i).at(j) == '1')
                    count++;
            if (2 * count > entries.size()) {
                bin_num1.push_back('1');
                bin_num2.push_back('0');
            }
            else {
                bin_num1.push_back('0');
                bin_num2.push_back('1');
            }
        }
        std::cout << bin_to_dec(bin_num1) * bin_to_dec(bin_num2) << std::endl;
    }
    return 0;
}