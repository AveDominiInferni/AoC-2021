#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
#include <chrono>

using namespace std::chrono;
auto start = high_resolution_clock::now();

std::vector<std::pair<int, int>> neighbours {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

int dijkstra(const std::vector<std::vector<int>> &g) {
    std::vector<std::vector<int>> min_dist(g.size(), std::vector<int> (g.size(), INT32_MAX));
    std::priority_queue<std::pair<int, std::pair<int, int>>> q;
    min_dist.at(0).at(0) = 0;
    q.push({0, {0, 0}});

    while (!q.empty()) {
        auto el = q.top();
        q.pop();
        for (auto n : neighbours) {
            int nx = el.second.first + n.first;
            int ny = el.second.second + n.second;
            if (ny < 0 || ny >= g.size() || nx < 0 || nx >= g.size())
                continue;
            int n_dist = g.at(nx).at(ny) - el.first;
            if (n_dist < min_dist.at(nx).at(ny)) {
                min_dist.at(nx).at(ny) = n_dist;
                q.push({-n_dist, {nx, ny}});
            }
        }
    }
    return min_dist.back().back();
}

int main() {
    std::vector<std::vector<int>> g(100, std::vector<int>(100));
    std::ifstream file("input.txt");
    std::string line;
    for (int i = 0; std::getline(file, line); i++)
        for (int j = 0; j < line.length(); j++) {
            g.at(i).at(j) = line.at(j) - '0';
    std::cout << dijkstra(g) << std::endl;
    auto stop = high_resolution_clock::now();
    std::cout << "Execution time: " << duration_cast<microseconds>(stop - start).count() << " microseconds" << std::endl;
    // std::queue instead of std::priority_queue: Execution time: 894053 microseconds
    // Execution time: 13003 microseconds
    return 0;
}