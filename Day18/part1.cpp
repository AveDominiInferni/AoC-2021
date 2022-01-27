#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <vector>
#include <sstream>

int depth(const std::string &s) {
    int depth = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s.at(i) == '[')
            depth++;
        else if (s.at(i) == ']')
            depth--;
        if (depth > 4)
            return i;
    }
    return -1;
}

void explode(std::string &s, int i) {
    int len1 = 1;
    while (isdigit(s.at(i + len1 + 1)))
        len1++;
    int n1 = std::stoi(s.substr(i + 1, len1));
    int len2 = 1;   
    while (isdigit(s.at(i + len1 + len2 + 2)))
        len2++;
    int n2 = std::stoi(s.substr(i + len1 + 2, len2));
    s.replace(i, len1 + len2 + 3, "0");
    
    for (int j = i - 1; j >= 0; j--) {
        if (isdigit(s.at(j))) {
            int len = 1;
            while (isdigit(s.at(j - len)))
                len++;
            s.replace(j - len + 1, len, std::to_string(std::stoi(s.substr(j - len + 1, len)) + n1));
            i += len;
            break;
        }
    }
    for (int j = i + 1; j < s.length(); j++) {
        if (isdigit(s.at(j))) {
            int len = 1;
            while (isdigit(s.at(j + len)))
                len++;
            s.replace(j, len, std::to_string(std::stoi(s.substr(j, len)) + n2));
            break;
        }
    }
}

void split(std::string &s, int i) {
    int n = std::stoi(s.substr(i, 2));
    int n1 = n / 2, n2 = n / 2;
    if (n % 2 == 1)
        n2++;
    s.replace(i, 2, "[" + std::to_string(n1) + "," + std::to_string(n2) + "]");
}

int magnitude(std::string s) {
    while (s.at(0) == '[') {
        for (int i = 0; i < s.length(); i++) {
            if (s.at(i) == ',' && isdigit(s.at(i - 1)) && isdigit(s.at(i + 1))) {
                int len1 = 1, len2 = 1;
                while (isdigit(s.at(i - len1 - 1)))
                    len1++;
                while (isdigit(s.at(i + len2 + 1)))
                    len2++;
                int n1 = std::stoi(s.substr(i - len1, len1));
                int n2 = std::stoi(s.substr(i + 1, len2));
                s.replace(i - len1 - 1, len1 + len2 + 3, std::to_string(3 * n1 + 2 * n2));
            }
        }
    }
    return std::stoi(s);
}

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string snails;
        std::string line;
        std::getline(file, snails);
        while (std::getline(file, line)) {
            snails.insert(snails.begin(), '[');
            snails.push_back(',');
            snails.append(line);
            while (true) {
                bool reduced = true;
                auto d = depth(snails);
                if (d != -1) {
                    explode(snails, d);
                    reduced = false;
                }
                else {
                    for (int i = 0; i < snails.length() - 1; i++)
                        if (isdigit(snails.at(i)) && isdigit(snails.at(i + 1))) {
                            split(snails, i);
                            reduced = false;
                            break;
                        }
                }
                
                if (reduced)
                    break;
            }
            snails.push_back(']');
        }
        std::cout << magnitude(snails) << std::endl;
    }

    file.close();
    return 0;
}