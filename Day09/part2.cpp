#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <set>

using namespace std::chrono;
auto start = high_resolution_clock::now();

const std::vector<std::pair<int, int>> neighbours {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int get_basin_size(const std::vector<std::string> &v, std::set<std::pair<int, int>> &visited, int x, int y) {
    auto it = visited.find({x, y});
    if (it != visited.end())
        return 0;
    visited.insert({x, y});
    int basin_size = 1;
    for (int i = 0; i < 4; i++) {
        int temp_x = x + neighbours.at(i).first;
        int temp_y = y + neighbours.at(i).second;
        if (!(temp_x > 0 && temp_x < v.at(0).size() - 1 && temp_y > 0 && temp_y < v.size() - 1))
            continue;
        int temp = v.at(temp_y).at(temp_x);
        if (temp < '9' && temp > v.at(y).at(x))
            basin_size += get_basin_size(v, visited, temp_x, temp_y);
    }
    return basin_size;
}

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::vector<std::string> v;
        std::string line;
        while (std::getline(file, line)) {
            if (v.size() == 0)
                v.push_back(std::string(line.length() + 2, ':'));
            v.push_back(':' + line + ':');
        }
        v.push_back(std::string(line.length() + 2, ':'));
        std::multiset<int> basins;
        std::set<std::pair<int, int>> visited;
        for (int j = 1; j < v.size() - 1; j++)
            for (int i = 1; i < v.at(j).size() - 1; i++)
                if (v.at(j).at(i) < v.at(j + 1).at(i) && v.at(j).at(i) < v.at(j - 1).at(i) 
                    && v.at(j).at(i) < v.at(j).at(i + 1) && v.at(j).at(i) < v.at(j).at(i -1))
                    basins.insert(get_basin_size(v, visited, i, j));
        auto it = basins.rbegin();
    	std::cout << (*it++) * (*it++) * (*it) << std::endl;
    }
    file.close();
    auto stop = high_resolution_clock::now();
    std::cout << "Execution time: " << duration_cast<microseconds>(stop - start).count() << " microseconds" << std::endl;
    return 0;
}