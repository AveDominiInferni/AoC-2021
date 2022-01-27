#include <iostream>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>
#include <map>

using namespace std::chrono;
auto start = high_resolution_clock::now();
using path = std::map<std::string, std::vector<std::string>>;

bool is_upper(const std::string &s) {
    for (auto x : s)
        if (!(isalpha(x) && x >= 65 && x <= 90))
            return false;
    return true;
}

int count(const path &p, std::set<std::string> visited, const std::string &cur) {
    int k = 0;
    if (cur == "end")
        return 1;
    if (!is_upper(cur)) {
        auto it = visited.find(cur);
        if (it != visited.end())
            return 0;
    }
    visited.insert(cur);
    for (auto x : p.at(cur))
        k += count(p, visited, x);
    return k;
}

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        path p;
        std::string line;
        while (std::getline(file, line)) {
            auto hyphen = line.find('-');
            std::string s1 = line.substr(0, hyphen);
            std::string s2 = line.substr(hyphen + 1);
            p[s1].push_back(s2);
            p[s2].push_back(s1);
        }
        std::set<std::string> visited;
        std::cout << count(p, visited, "start") << std::endl;
        
    }
    auto stop = high_resolution_clock::now();
    std::cout << "Execution time: " << duration_cast<microseconds>(stop - start).count() / 1000 << " miliseconds" << std::endl;
    // 0.501 seconds
    file.close();
    return 0;
}