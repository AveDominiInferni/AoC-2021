#include <iostream>
#include <fstream>
#include <deque>
#include <cmath>
#include <memory>

int bin_to_dec(const std::string &s) {
    int result = 0;
    for (int i = s.length() - 1; i >= 0; i--)
        if (s.at(s.length() - i - 1) == '1')
            result += pow(2, i);
    return result;
}

void remove_entry(std::deque <std::shared_ptr<std::string>> &m, int j, char c) {
    for (int i = 0; i < m.size(); i++) {
        if (m.at(i)->at(j) == c) {
            m.erase(m.begin() + i);
            i--;
        }
    }
}

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string line;
        std::deque <std::shared_ptr<std::string>> d1, d2;
        while (std::getline(file, line)) {
            std::shared_ptr<std::string> s = std::make_shared<std::string>(std::string(line));
            d1.push_back(s);
            d2.push_back(s);
        }
        file.close();

        for (int j = 0 ; d1.size() > 1; j++) {
            int count = 0;
            for (int i = 0; i < d1.size(); i++)
                if (d1.at(i)->at(j) == '1')
                    count++;
            if (2 * count >= d1.size())
                remove_entry(d1, j, '0');
            else
                remove_entry(d1, j, '1');
        }

        for (int j = 0 ; d2.size() > 1; j++) {
            int count = 0;
            for (int i = 0; i < d2.size(); i++)
                if (d2.at(i)->at(j) == '1')
                    count++;
            if (2 * count < d2.size())
                remove_entry(d2, j, '0');
            else
                remove_entry(d2, j, '1');
        }
        
        std::cout << bin_to_dec(*d1.at(0)) * bin_to_dec(*d2.at(0)) << std::endl;
    }
    return 0;
}