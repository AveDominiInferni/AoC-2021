#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>

using namespace std::chrono;
auto start = high_resolution_clock::now();

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::vector<std::vector<int>> v;
        std::string line;
        while (std::getline(file, line)) {
            std::vector<int> temp {10};
            for (auto x : line)
                temp.push_back(int(x - 48));
            temp.push_back(10);
            if (v.size() == 0) {
                std::vector<int> border(temp.size(), 10);
                v.push_back(border);
            }
            v.push_back(temp);
        }
        std::vector<int> border(v.at(0).size(), 10);
        v.push_back(border);
        uint64_t sum = 0;
        for (int i = 1; i < v.size() - 1; i++) {
            for (int j = 1; j < v.at(i).size() - 1; j++) {
                if (v.at(i).at(j) < v.at(i + 1).at(j) && v.at(i).at(j) < v.at(i - 1).at(j) 
                    && v.at(i).at(j) < v.at(i).at(j + 1) && v.at(i).at(j) < v.at(i).at(j -1))
                    sum += v.at(i).at(j) + 1;
            }   
        }
        std::cout << sum << std::endl;
    }
    file.close();
    auto stop = high_resolution_clock::now();
    std::cout << "Execution time: " << duration_cast<microseconds>(stop - start).count() << " microseconds" << std::endl;
    return 0;
}