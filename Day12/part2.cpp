#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>
#include <map>

bool is_upper(const std::string &s) {
    for (auto x : s)
        if (!(isalpha(x) && x >= 65 && x <= 90))
            return false;
    return true;
}

int count(const std::map<std::string, std::vector<std::string>> &paths, std::set<std::string> cache, const std::string &cur = "start", std::string extra = "") {
    int k = 0;
    if (cur == "end")
        return 1;
    if (cur == "start") {
        auto it = cache.find("start");
        if (it != cache.end()) {
            return 0;
        }
    }
    if (!is_upper(cur)) {
        auto it = cache.find(cur);
        if (it != cache.end()) {
            if (extra == "")
                extra = cur;
            else
                return 0;
        }
    }
    cache.insert(cur);
    for (auto x : paths.at(cur))
        k += count(paths, cache, x, extra);
    return k;
}

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::map<std::string, std::vector<std::string>> paths;
        std::string line;
        while (std::getline(file, line)) {
            auto hyphen = line.find('-');
            std::string s1 = line.substr(0, hyphen);
            std::string s2 = line.substr(hyphen + 1);
            paths[s1].push_back(s2);
            paths[s2].push_back(s1);
        }
        std::set<std::string> cache;
        std::cout << count(paths, cache) << std::endl;
        
    }
    file.close();
    return 0;
}