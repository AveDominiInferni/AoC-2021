#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

using grid = std::map<std::pair<int, int>, int>;
std::vector<std::pair<int, int>> adjacent {{1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}};
int flashes = 0;

void increase_energy(grid &g, int i, int j, std::set<std::pair<int, int>> &cache) {
    auto it = g.find({i, j});
    if (it != g.end()) {
        auto c = cache.find({i, j});
        if (c != cache.end())
            return;
        it->second++;
        if (it->second > 9) {
            cache.insert({i, j});
            it->second = 0;
            flashes++;
            for (auto x : adjacent)
                increase_energy(g, i + x.first, j + x.second, cache);
        }
    }
}

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        grid g;
        std::string line;
        int i = 0;
        while (std::getline(file, line)) {
            int j = 0;
            for (auto x : line) {
                g[{i, j}] = int(x) - 48;
                j++;
            }
            i++;
        }
        for (int k = 0; ; k++) {
            std::set<std::pair<int, int>> cache;
            for (auto x : g)
                increase_energy(g, x.first.first, x.first.second, cache);
            if (cache.size() == 100) {
                std::cout << k + 1;
                break;
            } 
        }
    }
    file.close();
    return 0;
}