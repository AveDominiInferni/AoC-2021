#include <iostream>
#include <fstream>
#include <vector>

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

void reduce(std::string &s) {
    while (true) {
        bool reduced = true;
        auto d = depth(s);
        if (d != -1) {
            explode(s, d);
            reduced = false;
        }
        else {
            for (int i = 0; i < s.length() - 1; i++)
                if (isdigit(s.at(i)) && isdigit(s.at(i + 1))) {
                    split(s, i);
                    reduced = false;
                    break;
                }
        }
        if (reduced)
            break;
    }
}

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        int max_magninute = 0;
        std::vector<std::string> v;
        std::string line;
        while (std::getline(file, line))
            v.push_back(line);
        for (int i = 0; i < v.size() - 1; i++) {
            for (int j = i + 1; j < v.size(); j++) {
                std::string s1 = "[" + v.at(i) + "," + v.at(j) + "]";
                std::string s2 = "[" + v.at(j) + "," + v.at(i) + "]";
                reduce(s1);
                reduce(s2);
                int temp = magnitude(s1);
                if (temp > max_magninute)
                    max_magninute = temp;
                temp = magnitude(s2);
                if (temp > max_magninute)
                    max_magninute = temp;
            } 
        }
        std::cout << max_magninute << std::endl;
    }

    file.close();
    return 0;
}