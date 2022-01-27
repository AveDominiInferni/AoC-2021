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
    std::vector<std::vector<int>> g(500, std::vector<int>(500));
    std::ifstream file("input.txt");
    std::string line;
    for (int i = 0; std::getline(file, line); i++)
        for (int j = 0; j < line.length(); j++)
            for (int x = 0; x < 5; x++)
                for (int y = 0; y < 5; y++) {
                    int temp = (line.at(j) - '0') + x + y;
                    if (temp > 9)
                        temp -= 9;
                    g.at(i + line.length() * x).at(j + line.length() * y) = temp;
                }
    std::cout << dijkstra(g) << std::endl;
    auto stop = high_resolution_clock::now();
    std::cout << "Execution time: " << duration_cast<microseconds>(stop - start).count() / 1000 << " miliseconds" << std::endl;
    // Execution time: 398 miliseconds
    return 0;
}