#include <iostream>
#include <fstream>
#include <map>
#include <chrono>

using namespace std::chrono;
auto start = high_resolution_clock::now();

void add_pair(std::map<std::pair<char, char>, uint64_t> &pairs, char x, char y, uint64_t q = 1) {
    std::pair<char, char> pair = {x, y};
    if (pairs.find(pair) != pairs.end())
        pairs[pair] += q;
    else
        pairs[pair] = q;
}

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::map<std::pair<char, char>, uint64_t> pairs;
        std::string line;
        std::getline(file, line);
        char last_char = line.at(line.length() - 1);
        for (int i = 0; i < line.length() - 1; i++)
            add_pair(pairs, line.at(i), line.at(i + 1));

        std::getline(file, line);
        std::map<std::pair<char, char>, char> templates;
        while (std::getline(file, line))
            templates[{line.at(0), line.at(1)}] = line.at(6);

        for (int k = 0; k < 40; k++) {
            std::map<std::pair<char, char>, uint64_t> temp = pairs;
            for (auto x : templates) {
                auto it = pairs.find(x.first);
                if (it != pairs.end()) {
                    add_pair(temp, it->first.first, x.second, it->second);
                    add_pair(temp, x.second, it->first.second, it->second);
                    temp[x.first] -= it->second;
                }
            }
            pairs = temp;
        }

        std::map<char, uint64_t> quantity;
        for (auto x : pairs) {
            if (quantity.find(x.first.first) != quantity.end())
                quantity[x.first.first] += x.second;
            else
                quantity[x.first.first] = x.second;
        }
        quantity[last_char]++;

        uint64_t most_q = 0, least_q = UINT64_MAX;
        for (auto x : quantity) {
            if (x.second > most_q)
                most_q = x.second;
            if (x.second < least_q)
                least_q = x.second;
        }
        std::cout << most_q - least_q<< std::endl;
    }
    auto stop = high_resolution_clock::now();
    std::cout << "Execution time: " << duration_cast<microseconds>(stop - start).count() / 1000 << " miliseconds" << std::endl;
    // Execution time: 11 miliseconds
    file.close();
    return 0;
}